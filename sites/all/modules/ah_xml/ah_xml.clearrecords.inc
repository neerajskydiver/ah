<?php

/**
  * Delete all records in ah_xml Table
	*/

function ah_xml_clear() {

$count = db_affected_rows();

	if($_GET['delete'] == TRUE) {
		  db_query("DELETE FROM {ah_xml} ");
			if($count) drupal_set_message(t('All recordshave been deleted. Number of records deleted: !count.', array('!count' => $count)));
		}
		$url = url("admin/content/ah-xml/clear-records", array('query' => 'delete='. TRUE,'absolute' => TRUE));
		$link = '<a href = '.$url.'> Delete Records </a>';

		return $link;
}

/**
	*		Imported Data Listing
	*/
	
function ah_dir_import_list() {

	$search_form = drupal_get_form('search_data_by_file_form');

$filename = $_GET['filename'];
if($filename) {
	$where = " WHERE filename = '$filename' ";
}

$sql = "SELECT ah_xml_nid,	ah_xml_uid, node_type, filename FROM {ah_xml}".$where;

$query = db_query($sql);
 while ($results2 = db_fetch_object($query)) {
	 $results1[] = $results2->filename;
}
$total = t('Total records:') . count($results1);
	$headers = array(
		array('data' => t('Title'), 'sort' => 'asc'),
		array('data' => t('User')),
		array('data' => t('NID'), 'field' => 'ah_xml_nid'),
		array('data' => t('Created')),
		array('data' => t('Issue'), 'field' => 'node_type'),
		array('data' => t('File')),
		array('data' => t('Edit Link')),
	);

  $rows = array();

$count = 100;
$query = pager_query($sql, $count);

  while ($results = db_fetch_object($query)) {
		$node = node_load($results->ah_xml_nid);
    $rows[] = array(
								l($node->title, 'node/'. $results->ah_xml_nid .'/edit'),
								theme_username(user_load($results->ah_xml_uid)),
								$results->ah_xml_nid,
								format_date($node->created, 'small'),
								$results->node_type,
								$results->filename,
								l('Edit', 'node/'. $results->ah_xml_nid .'/edit'),
                );
   }
	 $output = theme('table', $headers, $rows);
	 return $search_form.$output . theme('pager', $count) . $total;
}


/**
	*		Imported Data Search by file
	*/
	
function search_data_by_file_form() {
 $form = array();
 
 		$form['filepath'] = array (
		'#title' => 'Path in Article',
		'#type' => 'textfield',
		'#description' => 'Enter Filepath to search an article',
		);
	
		$form['submit'] = array('#type' => 'submit', '#value' => t('Find'));
		return $form;
}

function search_data_by_file_form_submit($form, &$form_state) {
		$path = $form_state['values']['filepath'];
		$arr = explode('/', $path);
		$filename =  end($arr);
drupal_goto("admin/content/ah-xml/list", array('filename' => $filename));
}