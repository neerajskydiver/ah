<?php

/**
 * @file
 * Export XML profile as CSV
 * 
 * @ingroup hose_xml_ui_mod
 * @{
 */

/**
 * Export XML profile.
 * 
 * @see hose_xml_ui_profile_manage_export_submit()
 */
function hose_xml_ui_profile_manage_export(&$form_state, $profile) {
  drupal_add_css(drupal_get_path('module', 'hose_xml') .'/misc/shared.css');
  
/*  $form['#attributes'] = array('enctype' => 'multipart/form-data');
   $form['upload'] = array(
    '#type' => 'file',
    '#title' => t('Export directory'),
    '#description' => t('Click "Browse" to choose a directory on your computer for the exported csv file.'),
  );
 */
  //$form['bar']['#theme'] = 'hose_xml_ui_view_bar';
  $form['pid'] = array('#type' => 'hidden', '#value' => $profile->pid);
  $form['profile_name'] = array('#type' => 'hidden', '#value' => $profile->name);
  
  return confirm_form($form, t("Export profile '@profile'", array('@profile' => $profile->name)), "hose_xml/profiles/$profile->pid/view", 
      ' ', t('Export'), t('Cancel'));
} // hose_xml_ui_profile_manage_export

/**
 * Submit callback for hose_xml_ui_profile_manage_export form.
 * 
 * @param $form
 *   Drupal form array.
 * @param $form_state
 *   Drupal form_state array.
 * 
 * @see hose_xml_ui_profile_manage_export()
 */
function hose_xml_ui_profile_manage_export_submit($form, &$form_state) {
  $pid = $form_state['values']['pid'];
  $filename = hose_xml_filename_safe($form_state['values']['profile_name']);
  if (!hose_xml_ui_dbtable_to_csv('hose_xml_ui_profile_data', array('pid'), array('column' => 'pid', 'value' => $pid), $filename)) {
    drupal_set_message(t("Profile export failed, please contact your systems administrator."), "error");
  }
  else {
    drupal_set_message(t("Profile exported correctly."), "status");
    exit();
  }
}
/**
 * Exports a csv from the table in $table
 * 
 * @param $table
 *   No idea...
 * @param $exclude
 *   Columns can be excluded by passing an array of column names into $exclude
 * @param $filter
 *   Results can be filtered by supplying a filter as an array e.g.('column' => 'id',  'value' => '1' ), ... ) as the filter parameter
 * @param $filename
 *   Filename of generated file
 * 
 * @TODO: allow multiple filters :)
 */
function hose_xml_ui_dbtable_to_csv($table, $exclude = NULL, $filter = NULL, $filename = 'myfile') {
  global $base_url;
  $header = drupal_schema_fields_sql($table);
  if ($header) {
    // remove the excluded columns
    if (is_array($exclude)) $header = array_diff($header, $exclude);
    $header_string = implode(',', $header);
    $output .= $header_string ."\r\n";
    
    // add the filter if it's there
    $where = "";
    if (is_array($filter)) {
      $where = " WHERE ". $filter['column'] ." = ". $filter['value'];
    }
    $result = db_query("SELECT %s FROM {hose_xml_profile_data}" . $where, $header_string, $filter['column'], $filter['value']);
    
    while ($row = db_fetch_array($result)) {
      $data[] = $row;
    }
    pimport_export_csv($data, $filename, 'push', 'admin/settings/hose_xml/profiles');
    drupal_set_header('Content-Type: text/csv');
    drupal_set_header('Content-Disposition: attachment; filename='. $filename);
    drupal_set_header("Refresh: 2; url=$base_url/admin/settings/hose_xml/profiles");
    
    print $output;
    return TRUE;
  }
  return FALSE;
}

/**
 * Theme the submission buttons along the bottom of the profile export form.
 */
function theme_hose_xml_ui_view_bar($form) {
  $output = '<div class="container-inline">';
  $output .= drupal_render($form['submit']);
  
  $output .= '</div>';
  // Render any remaining form elements
  $output .= drupal_render($form);
  $output .= l(t('Return to profile overview screen'), 'hose_xml/profiles/'. $form['pid'] .'/view');
  return $output;
} // theme_hose_xml_import_view_bar

/**
 * @} End of "ingroup hose_xml_ui_mod".
 */