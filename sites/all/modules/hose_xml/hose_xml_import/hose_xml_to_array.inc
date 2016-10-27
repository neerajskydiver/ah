<?php

/**
 * Taken from http://www.php.net/manual/en/function.xml-parse.php#90733
 *
 * Given a XML string returns a formatted array that represents the input XML.
 */
function xml2array($contents) {
  $xml_values = array();
  $parser = xml_parser_create('');
  if (!$parser) {
    return FALSE;
  }

  xml_parser_set_option($parser, XML_OPTION_TARGET_ENCODING, 'UTF-8');
  xml_parser_set_option($parser, XML_OPTION_CASE_FOLDING, 0);
  xml_parser_set_option($parser, XML_OPTION_SKIP_WHITE, 1);
  xml_parse_into_struct($parser, trim($contents), $xml_values);
  xml_parser_free($parser);
  if (!$xml_values) {
    return array();
  }

  $xml_array = array();
  $last_tag_ar = & $xml_array;
  $parents = array();
  $last_counter_in_tag = array(1 => 0);
  $tag_path = '';
  foreach ($xml_values as $data) {
    switch ($data['type']) {
      case 'open':
        $last_counter_in_tag[$data['level'] + 1] = 0;
        $tag_path = trim($tag_path . '/' . $data['tag'], '/');
        $new_tag = array(
          '#name' => $data['tag'],
          '#tag_path' => $tag_path,
        );
        if (isset($data['attributes'])) {
          $new_tag['#attributes'] = $data['attributes'];
        }
        if (isset($data['value']) && trim($data['value'])) {
          $new_tag['#value'] = trim($data['value']);
        }
        $last_tag_ar[$last_counter_in_tag[$data['level']]] = $new_tag;
        $parents[$data['level']] = & $last_tag_ar;
        $last_tag_ar = & $last_tag_ar[$last_counter_in_tag[$data['level']]++];
        break;
      case 'complete':
        $new_tag = array(
          '#name' => $data['tag'],
          '#tag_path' => $tag_path . '/' . $data['tag'],
        );
        if (isset($data['attributes'])) {
          $new_tag['#attributes'] = $data['attributes'];
        }
        if (isset($data['value']) && trim($data['value'])) {
          $new_tag['#value'] = trim($data['value']);
        }
        $last_count = count($last_tag_ar) - 1;
        $last_tag_ar[$last_counter_in_tag[$data['level']]++] = $new_tag;
        break;
      case 'close':
        $tag_paths = explode('/', $tag_path);
        array_pop($tag_paths);
        $tag_path = implode('/', $tag_paths);
        $last_tag_ar = & $parents[$data['level']];
        break;
      default:
        break;
    };
  }
  return $xml_array;
}

//
// use this to get node of tree by path with '/' terminator
// get_value_by_path($arr, 'tag/sub_tag/sub_sub_tag')
//
function get_value_by_path($__xml_tree, $__tag_path) {
  $tmp_arr = & $__xml_tree;
  $tag_path = explode('/', trim($__tag_path, '/'));
  foreach ($tag_path as $tag_name) {
    $res = FALSE;
    foreach ($tmp_arr as $key => $node) {
      if (is_int($key) && $node['#name'] == $tag_name) {
        $tmp_arr = $node;
        $res = true;
        break;
      }
    }
    if (!$res) {
      return FALSE;
    }
  }
  return $tmp_arr;
}
