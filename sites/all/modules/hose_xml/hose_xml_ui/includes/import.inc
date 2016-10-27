<?php

/**
 * @file
 * Import XML profile from CSV file for the Hose XML UI module.
 * 
 * @ingroup hose_xml_ui_mod
 * @{
 */

/**
 * Import into XML profile callback.
 */
function hose_xml_ui_profile_manage_import(&$form_state, $profile) {
  drupal_add_css(drupal_get_path('module', 'hose_xml') .'/misc/shared.css');
  $form['#attributes'] = array('enctype' => 'multipart/form-data');

  $form['upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload'),
    '#description' => t('Click "Browse" to choose a csv file on your computer for import into this profile.'),
  );
  $form['file_placeholder'] = array('#type' => 'hidden', '#value' => '');
  $form['pid'] = array(
  	'#type' => 'hidden', 
  	'#value' => $profile->pid
  );
  $form['profile_name'] = array(
  	'#type' => 'hidden', 
  	'#value' => $profile->name
  );
  $form['clear'] = array(
    '#type' => 'checkbox',
    '#title' => t('Clear existing profile before importing tags.'),
    '#default_value' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
} // hose_xml_ui_profile_manage_import

function hose_xml_ui_profile_manage_import_validate(&$form, &$form_state) {
  $validators = array(
    'hose_xml_is_spreadsheet' => array(),
  );
  if (!($file = file_save_upload('upload', $validators))) {
  // return an error on failure
    form_set_error('upload', t('File upload failed, please contact your system administrator.'));
  }
  else {
  // fill in placeholder variable so we get to pass our file variables into the submit function
    form_set_value(array('#parents' => array('file_placeholder')), $file, $form_state);
  }
} // hose_xml_ui_profile_manage_import_validate

/**
 * Import an XML profile
 * TODO: This function is broken because it relies on child tags being below parent tags in the database. It needs to 
 * be rewritten.  Suggested approach:
 * As each row is created in the table create an array that maps the old did (parent id) to the new id
 * After all the rows are created do an update correcting all the dids
 * Also a setting should be added to replace or append to existing rows in the profile
 * @param $form
 * @param $form_state
 */
function hose_xml_ui_profile_manage_import_submit(&$form, &$form_state) {
  $form_values = $form_state['values'];
  $pid = $form_values['pid'];
  $file = $form_values['file_placeholder'];
  $handle = fopen($file->filepath, "r");
  $flag = FALSE;
  if ($form_values['clear']) {
    db_query("DELETE FROM {hose_xml_profile_data} WHERE pid = %d", $pid);
    $weight_offset = 0; 
  }
  else {
    $weight_offset = db_result(db_query('SELECT MAX(weight) FROM {hose_xml_profile_data} WHERE pid = %d', $pid)) + 1;
  }
  while (($fetch = fgetcsv($handle)) !== FALSE) {
    db_query("INSERT INTO {hose_xml_profile_data} 
    	(pid, did, title, description, cck_match, tag, type, defaults, required, relies_on, attributes, settings, weight, cdata) 
    	VALUES (%d, %d, '%s', '%s', '%s', '%s', '%s', '%s', %d, '%s', '%s', '%s', %d, %d)",
      $pid,
      0,  // stick a default value in
      $fetch[2],
      $fetch[3],
      $fetch[4],
      $fetch[5],
      $fetch[6],
      $fetch[7],
      $fetch[8],
      $fetch[9],
      $fetch[10],
      $fetch[11],
      $fetch[12] + $weight_offset,
      $fetch[13]
    );
    $id = db_last_insert_id('hose_xml_ui_profile_data', 'id');
    $ids_map[$fetch[0]] = $id;
    $old_dids[$id] = $fetch[1];
  }
  // set the dids correctly
  foreach ($ids_map as $old_id => $new_id) {
    db_query('UPDATE {hose_xml_profile_data} SET did = %d WHERE id = %d', $ids_map[$old_dids[$new_id]], $new_id);
  }
  fclose($handle);

  // housekeeping
  file_delete($file->filepath);

/*  if ($flag) {
    drupal_set_message(t("Error importing into profile '@profile'. Please contact your <a href=\"mailto:!sysadmin\">System Administrator</a>", array('@profile' => $form_values['profile_name'],'!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  else {*/
  // Success!
    drupal_set_message(t("Importing into profile '@profile' has been successful.", array('@profile' => $form_values['profile_name'])));
//  }

  $form_state['redirect'] = "hose_xml/profiles/$pid/view";
} // hose_xml_ui_profile_manage_import_submit

/**
 * @} End of "ingroup hose_xml_ui_mod".
 */