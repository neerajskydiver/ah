<?php

// we connect to localhost at port 3307
$link = mysql_connect('10.181.80.130', 'root', 'm317sMKYEEOrlvcAax4p');



mysql_select_db('americanheritage', $link);

if (!$link) {
    die('Could not connect: ' . mysql_error());
}
else
{
  # code...
  echo '<p>Connected successfully</p>';
}
//, CONCAT(t.tid) AS terms 
#$selectQuery = 'SELECT n.title AS ArtifactTitle, n.nid, t.tid FROM node AS n LEFT JOIN term_node t ON n.nid = t.nid 
#where t.tid is NOT NULL
#limit 100, 1000';

$selectQuery = "SELECT n.title AS ArtifactTitle, n.nid as NID, n1.title AS SiteTitle, f.filepath AS path, nr.body AS Contentdescription, c.field_description_physical_value AS physicalDescription, c.field_creator_value AS Creator
FROM content_type_collection c
LEFT JOIN node n ON c.nid = n.nid
LEFT JOIN node n1 ON c.field_site_id_nid = n1.nid
LEFT JOIN files f ON c.field_image_fid = f.fid
LEFT JOIN node_revisions nr ON c.nid = nr.nid
WHERE f.filepath NOT LIKE  '%no_record.png'
and n.status != 0 and n1.title IS NOT NULL ORDER BY `n1`.`title` ASC";


/*"SELECT n.title AS ArtifactTitle,n.nid as NID, n1.title AS SiteTitle, f.filepath AS path, nr.body AS Contentdescription, c.field_description_physical_value AS physicalDescription
FROM content_type_collection c
LEFT JOIN node n ON c.nid = n.nid
LEFT JOIN node n1 ON c.field_site_id_nid = n1.nid
LEFT JOIN files f ON c.field_image_fid = f.fid
LEFT JOIN node_revisions nr ON c.nid = nr.nid
WHERE f.filepath NOT LIKE  '%no_record.png'
and n.status != 0";*/

$result = mysql_query($selectQuery) or die(mysql_error());
//$row = mysql_fetch_array($result);
#   echo '"' . addslashes ($row['ArtifactTitle']) . '";"' . $row['nid'] . '";"' . $row['tid'] . '";';

$rec_count = 1;
$records = array();

// First Comma Separated value (Titles)
$records[0] = array("ArtifactTitle" => '"ArtifactTitle"',"SiteTitle" => '"SiteTitle"', "path" => '"path"', "Contentdescription" => '"Contentdescription"', "physicalDescription" => 'physicalDescription', "creator" => '"creator"', "Creator" => '"terms"');

while($row = mysql_fetch_assoc($result))
{

    $records[$rec_count] = $row;
    foreach ($records[$rec_count] as $key => $value)
    {
      if (!empty($value))
      {
#        if ($key == 'path')

          $records[$rec_count][$key] = '"'. addslashes($value) .'"';
      }
      else
      {
        $records[$rec_count][$key] = NULL;
      }
    }
    $selectterms = 'SELECT td.name AS term FROM term_data td INNER JOIN term_node tn ON tn.tid = td.tid where tn.nid = ' .  $records[$rec_count]['NID'];
    
    $result2 = mysql_query($selectterms);
    $terms = array();
    $i = 0;
    while($row1 = mysql_fetch_array($result2))
      {
         $terms[$i] = $row1['term'];
         $i++;
      }
      if (!empty($terms))
      {
        # code...
        $records[$rec_count]['terms'] = '"' . addslashes(implode(',',$terms)) . '"';
      }
      else
      {
        # code...
        $records[$rec_count]['terms'] = NULL;
      }
    // Delete NID From array
    unset($records[$rec_count]['NID']);
    $rec_count++;
}
echo count($records) . "<br />";
$fp = fopen('orangeLogicImportData.csv', 'w');
foreach ($records as $fields) {
   fputcsv_custom($fp, $fields);
}
mysql_close($link);



    function fputcsv_custom(&$handle, $fields = array(), $delimiter = ';', $enclosure = '') {

        // Sanity Check
        if (!is_resource($handle)) {
            trigger_error('fputcsv() expects parameter 1 to be resource, ' .
                gettype($handle) . ' given', E_USER_WARNING);
            return false;
        }

        if ($delimiter!=NULL) {
            if( strlen($delimiter) < 1 ) {
                trigger_error('delimiter must be a character', E_USER_WARNING);
                return false;
            }elseif( strlen($delimiter) > 1 ) {
                trigger_error('delimiter must be a single character', E_USER_NOTICE);
            }

            /* use first character from string */
            $delimiter = $delimiter[0];
        }

        if( $enclosure!=NULL ) {
             if( strlen($enclosure) < 1 ) {
                trigger_error('enclosure must be a character', E_USER_WARNING);
                return false;
            }elseif( strlen($enclosure) > 1 ) {
                trigger_error('enclosure must be a single character', E_USER_NOTICE);
            }

            /* use first character from string */
            $enclosure = $enclosure[0];
       }

        $i = 0;
        $csvline = '';
        $escape_char = '\\';
        $field_cnt = count($fields);
        $enc_is_quote = in_array($enclosure, array('"',"'"));
        reset($fields);

        foreach( $fields AS $field ) {

            /* enclose a field that contains a delimiter, an enclosure character, or a newline */
            if( is_string($field) && ( 
                strpos($field, $delimiter)!==false ||
                strpos($field, $enclosure)!==false ||
                strpos($field, $escape_char)!==false ||
                strpos($field, "\n")!==false ||
                strpos($field, "\r")!==false ||
                strpos($field, "\t")!==false ||
                strpos($field, ' ')!==false ) ) {

                $field_len = strlen($field);
                $escaped = 0;

                //$csvline .= "";
                for( $ch = 0; $ch < $field_len; $ch++ )    {
                    if( $field[$ch] == $escape_char && $field[$ch+1] == $enclosure && $enc_is_quote ) {
                        continue;
                    }elseif( $field[$ch] == $escape_char ) {
                        $escaped = 1;
                    }elseif( !$escaped && $field[$ch] == $enclosure ) {
                        $csvline .= $enclosure;
                    }else{
                        $escaped = 0;
                    }
                    $csvline .= $field[$ch];
                }
                //$csvline .= "";
            } else {
                $csvline .= $field;
            }

            if( $i++ != $field_cnt ) {
                $csvline .= $delimiter;
            }
        }

        $csvline .= "\n";

        return fwrite($handle, $csvline);
    }

#  echo '<td style='text-align: center; border:1px solid #ccc'>';
#  echo $row['name'];
#  echo '</td>';
?>
