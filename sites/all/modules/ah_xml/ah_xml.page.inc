<?php
// $id

/**
  * Implement of hook_form()
	* ah_dir_import_form()
	*/
function ah_dir_import_form()
{
	unset($_SESSION['toc_parsed']);
	$_SESSION['toc_parsed'][] = "Element Zero";
	$count = 1954;
			$options['None'] =  t('None');
		do{
			$options[$count] =  t($count);
			$count++;
		}
	while($count <=2010);
		$form['import']['path'] = array (
		'#title' => 'Path to directory',
		'#type' => 'textfield',
		'#description' => 'Select directory import from server',
		'#default_value' => 'sites/default/files/ah_xml_magazine',
		);
	
	$form['import']['folder'] = array (
		'#title' => 'Name of the directory',
		'#type' => 'select',
		'#default_value' => array('None'=>t('None')),
		'#options' => $options,
		);
	
		$form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
		
		$form['resubmit'] = array('#type' => 'submit', 
		'#value' => t('Resubmit'),
		'#submit' => array('import_form_resubmit'),
		);
		
		$form['#redirect']='admin/content/node';
		return $form;
	}

function ah_dir_import() {
	return drupal_get_form('ah_dir_import_form');
}

/**
  * @file
	* this file conatains directory handling code
	*
	*/
function ah_dir_import_form_submit($form, &$form_state)
{
	if($form_state['values']['folder'] != 'None') {
	
		$path = $form_state['values']['path']."/" .$form_state['values']['folder'];
	
	}
	else {
	
		$path = $form_state['values']['path'];
	}
	$output = _ah_recur_dir($path);

	return false;
}

/**
  * @file
	* this file conatains directory handling code
	*
	*/
function import_form_resubmit($form, &$form_state) {

		$path = $form_state['values']['path'];

	return false;
}

/**
  * recursive files parsing code
	*
	*/
	 $toc_files;

function _ah_recur_dir($dir) {

	$dirlist = opendir($dir);

	// Parse the _toc file at first

	//$dirlist_toc = $dirlist;
	$tempnewfile = _parse_toc($dir);
	$currfilename =  end(explode('/', $tempnewfile));

	//if (!in_array($tempnewfile, $_SESSION['toc_parsed'])) {
	 if (!db_result(db_query("SELECT COUNT(*) FROM {ah_xml} WHERE filename = '%s';", $currfilename))) {
	
	 $_SESSION['toc_parsed'][] = $tempnewfile;
	//dsm($_SESSION['toc_parsed']);		
	}
	 else {
			drupal_set_message(t('1 File(Issue) @filename is already parsed .', array('@filename' => $currfilename)), 'error');

	}
	while ($file = readdir ($dirlist))
	{
	if (in_array($file, $_SESSION['toc_parsed'])) {
		 exit; 
 	}
		if ($file != '.' && $file != '..' && strlen(strstr($file,'toc')) <=0 )
		{
			$newpath = $dir.'/'.$file;
			
			$level = explode('/',$newpath);
			if (is_dir($newpath))
			{
				$mod_array[] = array(
						'level'=>count($level)-1,
						'path'=>$newpath,
						'name'=>end($level),
						'kind'=>'dir',
						'mod_time'=>filemtime($newpath),
						'content'=>_ah_recur_dir($newpath));
			}else{
				$mod_array[] = array(
						'level'=>count($level)-1,
						'path'=>$newpath,
						'name'=>end($level),
						'kind'=>'file',
						'mod_time'=>filemtime($newpath),
						'size'=>filesize($newpath));
						$name = end($level);

					if(is_xml_file($name)){
						ah_xml_import($newpath, 'article', $name);
					}

		   }
		}
	}//while
	closedir($dirlist); 
	return $mod_array;
}

/**
	*   For validating file extention
	*		
	*/
function is_xml_file($filename) {
		$path_info = pathinfo($filename);
    if($path_info['extension'] == 'xml'){
//		echo $path_info['extension'].'<br/ >';
			return true;
		}
		else {
			return false;
		}

}

/**
	*   For parsing code to import _toc (Table of Content at very First)
	*		_parse_toc()
	*/
	
function _parse_toc(&$dir){
	$dirlist = opendir($dir);
/**
	*Parse the _toc file at first
	*/
	$dirlist_toc = $dirlist;
	while ($file = readdir ($dirlist))
	{
		if ($file != '.' && $file != '..')
		{
			$newpath = $dir.'/'.$file;
			
			$level = explode('/',$newpath);
			if (is_dir($newpath))
			{
				$mod_array[] = array(
						'level'=>count($level)-1,
						'path'=>$newpath,
						'name'=>end($level),
						'kind'=>'dir',
						'mod_time'=>filemtime($newpath),
						'content'=>_ah_recur_dir($newpath));
			}else{
					if  (strlen(strstr($file,'toc'))>0) {

					$mod_array[] = array(
							'level'=>count($level)-1,
							'path'=>$newpath,
							'name'=>end($level),
							'kind'=>'file',
							'mod_time'=>filemtime($newpath),
							'size'=>filesize($newpath));
						$name = end($level);

if (!in_array($newpath, $_SESSION['toc_parsed'])) {
							if(is_xml_file($name)){
		
								ah_xml_import($newpath, 'issue', $name);
							}
						}
						return $newpath;

					} // toc condition

		   }
		}
	}//while
}

/**
  *
	*  hook_node_save() for saving articles and Issues
	*/
	
function ah_xml_node_save(&$node) {
  // Let modules modify the node before it is saved to the database.
  node_invoke_nodeapi($node, 'presave');
  global $user;

  // Insert a new node.
  $node->is_new = empty($node->nid);

  if ($node->is_new || !empty($node->revision)) {
    // When inserting a node, $node->log must be set because
    // {node_revisions}.log does not (and cannot) have a default
    // value.  If the user does not have permission to create
    // revisions, however, the form will not contain an element for
    // log so $node->log will be unset at this point.
    if (!isset($node->log)) {
      $node->log = '';
    }
  }
  elseif (empty($node->log)) {
    // When updating a node, however, avoid clobbering an existing
    // log entry with an empty one.
    unset($node->log);
  }

  // For the same reasons, make sure we have $node->teaser and
  // $node->body set.
  if (!isset($node->teaser)) {
    $node->teaser = '';
  }
  if (!isset($node->body)) {
    $node->body = '';
  }

  // Save the old revision if needed.
  if (!$node->is_new && !empty($node->revision) && $node->vid) {
    $node->old_vid = $node->vid;
  }

  $time = time();
  if (empty($node->created)) {
    $node->created = $time;
  }
  // The changed timestamp is always updated for bookkeeping purposes (revisions, searching, ...)
  $node->changed = $time;

  $node->timestamp = $time;
  $node->format = isset($node->format) ? $node->format : FILTER_FORMAT_DEFAULT;

  // Generate the node table query and the node_revisions table query.
  if ($node->is_new) {
    _node_save_revision($node, $user->uid);
    drupal_write_record('node', $node);
    db_query('UPDATE {node_revisions} SET nid = %d WHERE vid = %d', $node->nid, $node->vid);
    $op = 'insert';
  }
  else {
    drupal_write_record('node', $node, 'nid');
    if (!empty($node->revision)) {
      _node_save_revision($node, $user->uid);
      db_query('UPDATE {node} SET vid = %d WHERE nid = %d', $node->vid, $node->nid);
    }
    else {
      _node_save_revision($node, $user->uid, 'vid');
    }
    $op = 'update';
  }

  // Call the node specific callback (if any).
  node_invoke($node, $op);
  node_invoke_nodeapi($node, $op);

  // Update the node access table for this node.
  node_access_acquire_grants($node);

  // Clear the page and block caches.
  cache_clear_all();
	return (integer)$node->nid;
}


/**
  *
	*
	*/
function in_arrayi($needle, $haystack)
{
    for($h = 0 ; $h < count($haystack) ; $h++)
    {
        $haystack[$h] = strtolower($haystack[$h]);
    }
		if($haystack){
	    return in_array(strtolower($needle),$haystack);
		} else { return false; }
}//function for case insensetive search

/**
   *  Image text on center
	 *
	 */

 function CenterImageString($image, $image_width, $string, $font_size, $y, $color)
{
	 $text_width = imagefontwidth($font_size)*strlen($string);
	 $center = ceil($image_width / 2);
	 $x = $center - (ceil($text_width/2));
	 ImageString($image, $font_size, $x, $y, $string, $color);
} 

/**
	* Parse Article tag for its attributes
	*/
function parse_article($values, $key) {

					if(!empty($values[$key]['attributes'])) {
								foreach($values[$key]['attributes'] as $attr => $val) {
										$attributes[strtolower($attr)] = $val;
								}
					}
return $attributes;
}

function parse_type_complete($values, $key){
$def_key = $key;
//echo "<pre>";
//print_r($values);

	$output = '';
	if($values[$key]['type'] == 'open' || $values[$key]['type'] == 'complete'){
	$parsed_keys = array();

					do {
						global $pq;

						switch($values[$key]['tag']) {
								case "BODY":
										$tag = 'span';
										$class = 'body';
								break;
								case "DECK":
										$tag = 'span';
										$class = 'deck';
								break;
								case "AUTHORNOTE":
										$authornoteobj = parse_authornote($values, $key);
										$authornote = $authornoteobj->html;
										$key = $authornoteobj->lastkey;
										$tag = 'span';
										$class = 'authornote';
								break;
								case "HEADLINE":
										$tag = 'span';
										$class = 'headline';
								break;
								case "TYPESTYLE":
										$tag = 'span';
										$class = 'typestyle';
								break;
								case "CAPTION":
										$tag = 'span';		
										$class = 'caption';
								break;
								case "SIDEBAR_REF":
										$tag = 'span';
										$class = 'sidebar-ref';
								break;
								case "PULLQUOTE":
										$tag = 'span';		
										$class = 'pullquote '.$pq;
										if($values[$key]['type'] == 'open'){
											if($pq == 'odd'){
												$pq = 'even';
												//echo $class.'<br>';
											}
											else{
												if($pq == 'even'){
													$pq = 'odd';
												}
											}
										}
								break;
								case "CREDIT":
										$tag = 'span';		
										$class = 'credit';
								break;
								case "INSERTABLE":
										$tag = 'div';
										$class = 'insertable';
								break;
								case "ARTIST_CONTACT":
										$tag = 'span';	
										$class = 'artist_contact';
								break;
								case "ARTIST_NAME":
										$tag = 'span';
										$class = 'artist_name';
								break;
								case "RIGHTS":
										$tag = 'span';
										$class = 'rights';
								break;
								case "START":
										$tag = 'span';
										$class = 'start';
								break;
								case "END":
										$tag = 'span';
										$class = 'end';
								break;
								case 'SPECIAL_INSTRUCTIONS':
										$tag = 'span';//strtolower($values[$key]['tag']);
										$class = 'special_instructions';
								break;
								case "AUTHORNOTE":
										$tag = 'span';
										$class = 'authornote';
								break;
								default:
										$tag = strtolower($values[$key]['tag']);
										$class='';
								break;
							}						

					if($values[$key]['tag'] == 'IMG') {
						$bodyobj = parse_image($values, $key);
						$body .= $bodyobj->html;
						$key = $bodyobj->lastkey;
						$output .= $bodyobj->html;//parse_image($values, $key);
					}
					else{

									switch($values[$key]['type']) {
											case "open":
												if(!empty($values[$key]['attributes'])) {
															foreach($values[$key]['attributes'] as $attr => $val) {
																	$attributes .= strtolower($attr).'="'.$val.'"';
															}
												}

												$output .= "<".$tag.' '.$attributes." class='".$class."'> ".$values[$key]['value']."";
												unset($tag);
												unset($attributes);
												unset($class);
											break;
											case "cdata":
												$output .= $values[$key]['value']." ";
											break;
											case "close":
												$output .= "</".$tag.">";
											break;
											case "complete":
												if(!empty($values[$key]['value'])) {
													$output .= "<".$tag.' '.$attributes." class='".$class."'> ".$values[$key]['value']."</".$tag."> ";
												}
											//	$output .= "<".$tag."> ".$values[$key]['value']."</".$tag."> ";
											break;
									}
							}

							//	 echo ''.$values[$key]['value'].'<br />'.$values[$key]['tag'].'<br />'.$values[$key]['type'].'<br />';
							$parsed_keys[] = $key;
							if( $values[$def_key]['type'] == 'complete')	break;
							$key ++;
					} while (!($values[$key]['type']=='close' && $values[$key]['tag']==$values[$def_key]['tag']));
		}
		$result->html = $output;
		$result->lastkey = $key;
		$result->authornote = $authornote;
		return $result;
}

/**
	*	Parse headline tag
	*/
function parse_headline($values, $key){
$def_key = $key;
	$output = '';
	if($values[$key]['type'] == 'open' || $values[$key]['type'] == 'complete'){
	$parsed_keys = array();
					do {
						switch($values[$key]['tag']) {
								default:
										$tag = strtolower($values[$key]['tag']);
										$class='';
								break;
							}						
									switch($values[$key]['type']) {
											case "open":
												$output .= $values[$key]['value'];
											break;
											case "cdata":
												$output .= $values[$key]['value'];
											break;
											case "close":
												$output .= '';
											break;
											case "complete":
												if(!empty($values[$key]['value'])) {
													$output .= $values[$key]['value'];
												}
											break;
									}
							$parsed_keys[] = $key;
							if( $values[$def_key]['type'] == 'complete')	 break;
							$key ++;
					} while (!($values[$key]['type']=='close' && $values[$key]['tag']==$values[$def_key]['tag']));
		}
		$result->html = $output;
		$result->lastkey = $key;
		return $result;
}

function parse_image($values, $key){
$def_key = $key;
//echo "<pre>";
//print_r($values);
	$caption= '';
	$output = '';
	if($values[$key]['type'] == 'open'){

	$img = new stdClass();
					do {

							//to remove whitespaces to ultimately remove <br /> tags from body		
							$values[$key]['value'] = str_replace(array("\n"), '', $values[$key]['value']);

						switch($values[$key]['tag']) {
						
								case 'IMG':
								if($values[$key]['type'] == 'open') {
									//$img->img= strtolower($values[$key]['value']);
									$img->img['attributes'] = $values[$key]['attributes'];
								}
								break;
								case 'CAPTION':
								$img->caption= strtolower($values[$key]['value']);//field_cover_caption
								if($values[$key]['type'] == 'open' && $caption !='') {
									$caption = $img->caption;
								}
								break;
								case 'CREDIT':
									$img->attr['credit']= strtolower($values[$key]['value']);
								break;
								case 'ARTIST_NAME':
									$img->attr['artist_name'] = strtolower($values[$key]['value']);
								break;
								case 'ARTIST_CONTACT':
									$img->attr['artist_contact']= strtolower($values[$key]['value']);
								break;
								case 'SUBJECT':
									$img->attr['subject'] = strtolower($values[$key]['value']);
								break;
								case 'KEYWORD':
									$img->attr['keyword'] = strtolower($values[$key]['value']);
								break;
								case 'MEDIUM':
									$img->attr['medium'] = strtolower($values[$key]['value']);
									$img->medium['attributes'] = $values[$key]['attributes'];
								break;
								case 'IMAGE_ID':
									$img->attr['image_id'] = strtolower($values[$key]['value']);
								break;
								case 'RIGHTS':
									if($values[$key]['type'] == 'open') {
										$img->attr['rights'] = strtolower($values[$key]['value']);
										$img->rights['attributes'] = $values[$key]['attributes'];
									}
								break;
								case 'START':
									$img->attr['rights_start'] = strtolower($values[$key]['value']);
								break;
								case 'END':
									$img->attr['rights_end'] = strtolower($values[$key]['value']);
								break;
								case 'SPECIAL_INSTRUCTIONS':
									$img->attr['special_instructions']= strtolower($values[$key]['value']);
								break;

								default:
								break;
							}


								if($values[$key]['tag'] == 'IMG' && $values[$key]['type'] == 'open' ) {										

									foreach($img->img['attributes'] as $attr => $val) {

																		if($attr == 'SRC') {
																		$attributes .= strtolower($attr).'= "sites/default/files/article/'.$val.'" ';
																			$src = $val;
																		}
																		else {
																		$attributes .= strtolower($attr).'= "'.$val.'" ';
																		}
																

										$image_html = '<img '.$attributes.' '.$classes.'/>';
										$caption_html = '<div class = "caption">'.$img->caption.'</div>';
								}
							}

						//		 echo ''.$values[$key]['value'].'<br />'.$values[$key]['tag'].'<br />'.$values[$key]['type'].'<br />';
							$key ++;
					} while (!($values[$key]['type']=='close' && $values[$key]['tag']==$values[$def_key]['tag']));
					
		}
										if(!empty($img->attr)){
											foreach($img->attr as $imgattr => $imgval)  {
													$image_attr .= '<span class = "'.$imgattr .'">'.$imgval.'</span>';
											}
										}
								if($img->rights['attributes']['WEB'] != 'no') {
									$output = $image_html;
									$output .= $caption_html;
									$output.= '<div class="image-attributes">'.$image_attr.'</div>';
								}
								else{
									$output = '';
								}

		$result->html = '<div class="img-block">'.$output.'</div>';

		$result->lastkey=$key;
		$result->src=$src;
		$result->caption=$img->caption;
		return $result;
}

/**
	*  to parse authornote tag
	*
	*/
function parse_authornote($values, $key){
/*echo $values[$key]['tag'];
*/	$def_key = $key;
	$output = '';
	if($values[$key]['type'] == 'open'){
	$parsed_keys = array();
					do {
						switch($values[$key]['tag']) {
								default:
										$tag = 'span';
										$class = strtolower($values[$key]['tag']);
								break;
							}
									switch($values[$key]['type']) {
											case "open":
												if(!empty($values[$key]['attributes'])) {
															foreach($values[$key]['attributes'] as $attr => $val) {
																	$attributes .= strtolower($attr).'="'.$val.'"';
															}
												}
												$output .= "<".$tag.' '.$attributes." class='".$class."'> ".$values[$key]['value']."";
												unset($tag);
												unset($attributes);
												unset($class);
											break;
											case "cdata":
												$output .= $values[$key]['value']." ";
											break;
											case "close":
												$output .= "</".$tag.">";
											break;
											case "complete":
												if(!empty($values[$key]['value'])) {
													$output .= "<".$tag.' '.$attributes." class='".$class."'> ".$values[$key]['value']."</".$tag."> ";
												}
											break;
									}
							$parsed_keys[] = $key;
							$key ++;
					} while (!($values[$key]['type']=='close' && $values[$key]['tag']==$values[$def_key]['tag']));
		}
		$result->html = $output;
		$result->lastkey=$key;
		return $result;
}