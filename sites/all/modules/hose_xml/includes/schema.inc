<?php 
/**
 * Create a struct with schema information from an XML profile - see http://php.net/manual/en/function.xml-parse-into-struct.php
 * @param $pid
 */
function hose_xml_profile_to_schema_struct($pid, $namespace = '') {
  //$result = db_query("SELECT * FROM {hose_xml_profile_data} WHERE pid = %d ORDER BY did, weight, id ASC", $pid);
  $configs = hose_xml_get_export_config_flat($pid);
  $last_config = NULL;
  $level = 0;
  $new_level = 1;
  foreach ($configs as $config) {
    if (strtolower($config->tag == "xml")) continue;
    while ($config->depth < $level){
      // each drop in level must have close tags for element, complexType and sequence
      $elements[] = array(
        'type' => 'close',
        'tag' => $namespace. "sequence",
        'level' => --$new_level,
      );
      $elements[] = array(
        'type' => 'close',
        'tag' => $namespace. "complexType",
        'level' => --$new_level,
      );
      $elements[] = array(
        'type' => 'close',
        'tag' => $namespace. "element",
        'level' => --$new_level,
      );  
      $level--;
    }
    
    if ($config->depth >= level) {
      //open a new element
      if ($config->children) {
        //it's a container      
        $elements[] = array(
          'type' => 'open',
          'tag' => $namespace. "element",
          'level' => $new_level++,
          'value' => '',  // value is allways empty for xsd?
          'attributes' => array('name' => $config->tag),
         ); 
         $elements[] = array(
          'type' => 'open',
          'tag' => $namespace. "complexType",
          'level' => $new_level++,
          'value' => '',  // value is allways empty for xsd?
         ); 
         $elements[] = array(
          'type' => 'open',
          'tag' => $namespace. "sequence",
          'level' => $new_level++,
          'value' => '',  // value is allways empty for xsd?
         );
       }
       else {
         // it's a simple element
         $elements[] = array(
           'type' => 'complete',
           'tag' => $namespace. "element",
           'level' => $new_level,
           'attributes' => array('name' => $config->tag, 'type' => $namespace.'string'),
         );
       }    
    }
    $level = $config->depth;
  }
  // last config so close unfinished open tags
  while ($new_level > 1) {
    // each drop in level must have close tags for element, complexType and sequence
    $elements[] = array(
    'type' => 'close',
    'tag' => $namespace. "sequence",
    'level' => --$new_level,
    );
    $elements[] = array(
      'type' => 'close',
      'tag' => $namespace. "complexType",
      'level' => --$new_level,
    );
    $elements[] = array(
      'type' => 'close',
      'tag' => $namespace. "element",
      'level' => --$new_level,
    );  
    
  }
  return $elements;
} // hose_xml_get_export_config_flat




//Translate the settings into an XSD type
function _hose_xml_schema_get_config_type($config) {
  return "xs:string";  
}


// Schema attributes are actually information about the tag
function _hose_xml_get_schema_attributes($config) {
  
}

/**
 * Create XML from a struct with the same format as those created by http://php.net/manual/en/function.xml-parse-into-struct.php
 * @param $xmlary
 * 
 */
function _hose_xml_from_struct($xmlary){
  $o='';
  if (!is_array($xmlary) || empty($xmlary)) {
  	return $o;
  }
  foreach($xmlary as $tag ){
    /*
    if($tag['tag'] == 'textarea' && !isset($tag['value'])){
      //fake a value so it won't self close
      $tag['value']='';
    }
    */
    //tab space:
    $t = '';
    for($i=1; $i < $tag['level'];$i++){
      $t.= "  ";
    }
    switch($tag['type']){
      case 'complete':
      case 'open':
        $o.=$t.'<'.$tag['tag'];
        if(isset($tag['attributes'])){
          foreach($tag['attributes'] as $attr=>$aval){
            $o.=' '.$attr.'="'.$aval.'"';
          }//foreach
        }//attributes
        if($tag['type'] == 'complete'){
          if(!isset($tag['value'])){
            $o .= ' />'."\n";
          } else {
            $o .= '>'."\n".$t.$tag['value']." ".$t.'</'.$tag['tag'].'>'."\n";
          }
        }else{
          $o .= '>'."\n";
        }
        break;
      case 'close':
        $o .= $t.'</'.$tag['tag'].'>'."\n";
        break;
      case 'cdata':
        $o .= $t.$tag['value']."\n";
        break;
    }//switch
  }//foreach
  return $o;
} 
/**
 * Get typedefs for a profile in XSD format
 * @param $profile_id
 */
function hose_xml_get_xsd_type_defs($profile_id, $namespace) {
  $xsd_struct = hose_xml_profile_to_schema_struct($profile_id, $namespace);
  $xsd_type_defs = _hose_xml_from_struct($xsd_struct);
  return $xsd_type_defs;
}

/**
 * Create a schema for a given XML profile in XSD format (normally for inclusing in a WSDL)
 * @param $profile_id
 */
function hose_xml_get_schema($profile_id, $method_name) {
  $xsd_type_defs = hose_xml_get_xsd_type_defs($profile_id, '');
  $schema_url = url("hose_xml/schema/", array('absolute' => true));
  $schema = "
  <schema targetNamespace='$schema_url'
  	xmlns='http://www.w3.org/2000/10/XMLSchema'>
  	<element name='". $method_name ."Type'>
      <complexType>
        <sequence>
          $xsd_type_defs
        </sequence>     
      </complexType>
    </element>
  </schema>";
  return $schema;
}  

/*
 * Output a XSD schema file for a given profile
 */
function hose_xml_schema_output($profile_id) {
  $schema = hose_xml_get_schema($profile_id);
  //return "<code>". htmlentities($schema) ."</code>";
  ob_end_clean();
  drupal_set_header('Connection: close');
  drupal_set_header('Content-Length: '. strlen($schema));
  drupal_set_header('Content-Type: application/xml; charset=utf-8');
  drupal_set_header('Date: '. date('r'));
  echo $schema;
  exit;
  
}
