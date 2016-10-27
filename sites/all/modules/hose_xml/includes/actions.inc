<?php

/**
 * @file
 * Actions for Hose XML module.
 *
 * @ingroup hose_xml_core
 * @{
 */

/**
 * Implementation of hook_action_info().
 */
function hose_xml_action_info() {
  return array(
  /* moved to pimport
    'hose_xml_export_nodes_csv_action' => array(
      'type' => 'node',
      'description' => t('Export nodes as CSV'),
      'configurable' => TRUE,
      'aggregate' => TRUE,
      'hooks' => array('any' => TRUE),
    ),
  */
  /* deprecated
    'hose_xml_export_nodes_xls_action' => array(
      'type' => 'node',
      'description' => t('Export nodes as XLS'),
      'configurable' => TRUE,
      'aggregate' => TRUE,
      'hooks' => array('any' => TRUE),
    ),
  */
    'hose_xml_export_nodes_xml_action' => array(
      'type' => 'node',
      'description' => t('Export nodes as XML'),
      'configurable' => TRUE,
      'aggregate' => TRUE,
      'hooks' => array('any' => TRUE),
    ),
    'hose_xml_export_nodes_xml_bucket_action' => array(
      'type' => 'node',
      'description' => t('Export nodes as XML by Bucket'),
      'configurable' => TRUE,
      'aggregate' => TRUE,
      'hooks' => array('any' => TRUE),
    ),
  );
} // hose_xml_action_info

/**
 * Implementation of hook_(action)_form().
 *
 * @param $context
 *   Array containing View information and Object (which is an array of the selected node ids {node}.nid).
 *
 * @return
 *   Returns Drupal form array for rendering.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_csv_action_submit(), hose_xml_export_nodes_csv_action()
 */
/* moved to pimport
function hose_xml_export_nodes_csv_action_form($context) {
  global $user;
  $form['profile'] = array(
    '#type' => 'select',
    '#title' => t('Profile'),
    '#description' => t('Select which profile to use for this export.'),
    '#options' => hose_xml_import_fetch_profiles('names'),
    '#default_value' => !empty($user->hose_xml_import_default_profile) ? $user->hose_xml_import_default_profile : variable_get('hose_xml_import_default_profile', NULL),
  );
  $form['filename'] = array(
    '#type' => 'textfield',
    '#title' => t('Filename'),
    '#description' => t('Set a filename for this export, it will be appended with the current date.'),
    '#default_value' => module_exists('token') ? '[site-name]' : 'metadata',
  );
  if (module_exists('token')) {
    $form['tokens'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available tokens'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['tokens']['values'] = array(
      '#type' => 'markup',
      '#value' => theme('token_help', 'global'),
    );
  }
  return $form;
} // hose_xml_export_nodes_csv_action_form

*/

/**
 * Implementation of hook_(action)_form().
 *
 * @param $context
 *   Array containing View information and Object (which is an array of the selected node ids {node}.nid).
 *
 * @return
 *   Returns Drupal form array for rendering.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_xls_action_submit(), hose_xml_export_nodes_xls_action()
 */
/* deprecated
function hose_xml_export_nodes_xls_action_form($context) {
  global $user;
  $form['profile'] = array(
    '#type' => 'select',
    '#title' => t('Profile'),
    '#description' => t('Select which profile to use for this export.'),
    '#options' => hose_xml_import_fetch_profiles('names'),
    '#default_value' => !empty($user->hose_xml_import_default_profile) ? $user->hose_xml_import_default_profile : variable_get('hose_xml_import_default_profile', NULL),
  );
  $form['filename'] = array(
    '#type' => 'textfield',
    '#title' => t('Filename'),
    '#description' => t('Set a filename for this export, it will be appended with the current date.'),
    '#default_value' => module_exists('token') ? '[site-name]' : 'metadata',
  );
  if (module_exists('token')) {
    $form['tokens'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available tokens'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['tokens']['values'] = array(
      '#type' => 'markup',
      '#value' => theme('token_help', 'global'),
    );
  }
  return $form;
} // hose_xml_export_nodes_xls_action_form
*/

/**
 * Implementation of hook_(action)_form().
 *
 * @param $context
 *   Array containing View information and Object (which is an array of the selected node ids {node}.nid).
 *
 * @return
 *   Returns Drupal form array for rendering.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_xml_action_submit(), hose_xml_export_nodes_xml_action()
 */
function hose_xml_export_nodes_xml_action_form($context) {
  global $user;
  $form['profile'] = array(
    '#type' => 'select',
    '#title' => t('Profile'),
    '#description' => t('Select which profile to use for this export.'),
    '#options' => hose_xml_fetch_profiles('names'), //  hose_xml_export_fetch_profiles('names'),
    '#multiple' => TRUE,
    '#required' => TRUE,
    '#default_value' => !empty($user->hose_xml_export_default_profile) ? $user->hose_xml_export_default_profile : variable_get('hose_xml_export_default_profile', NULL),
  );
  if (variable_get('hose_xml_force_download', FALSE)) {
    $form['force'] = array(
      '#type' => 'checkbox',
      '#title' => t('Force output'),
      '#description' => t('Check this box if you want to force the output to be downloadable if validation fails. Usually in this case, the download link is not available to prevent use of invalid data.'),
    );
  }
  if (module_exists('hose_xml_delivery')) {
    hose_xml_delivery_export_nodes_xml_action_form($form);
  }
  return $form;
} // hose_xml_export_nodes_xml_action_form

/**
 * Implementation of hook_(action)_form().
 *
 * @param $context
 *   Array containing View information and Object (which is an array of the selected node ids {node}.nid).
 *
 * @return
 *   Returns Drupal form array for rendering.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_xml_bucket_action_submit(), hose_xml_export_nodes_xml_bucket_action()
 */
function hose_xml_export_nodes_xml_bucket_action_form($context) {
  $form['profile'] = array(
    '#type' => 'select',
    '#title' => t('Profile'),
    '#description' => t('Select which bucket to use for this export.'),
    '#options' => hose_xml_fetch_buckets(),
    '#multiple' => FALSE,
  );
  if (variable_get('hose_xml_force_download', FALSE)) {
    $form['force'] = array(
      '#type' => 'checkbox',
      '#title' => t('Force output'),
      '#description' => t('Check this box if you want to force the output to be downloadable if validation fails. Usually in this case, the download link is not available to prevent use of invalid data.'),
    );
  }
  if (module_exists('hose_xml_delivery')) {
    hose_xml_delivery_export_nodes_xml_action_form($form);
  }
  return $form;
} // hose_xml_export_nodes_xml_action_form

/**
 * Implementation of hook_(action)_submit().
 *
 * @param $form
 *   Drupal form array.
 * @param $form_state
 *   Drupal form_state array.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_csv_action_form(), hose_xml_export_nodes_csv_action()
 */
/* moved to pimport
function hose_xml_export_nodes_csv_action_submit($form, $form_state) {
	hose_xml_clean_export_dir();
  return array(
    'profile' => $form_state['values']['profile'],
    'filename' => $form_state['values']['filename'],
  );
} // hose_xml_export_nodes_csv_submit
*/

/**
 * Implementation of hook_(action)_submit().
 *
 * @param $form
 *   Drupal form array.
 * @param $form_state
 *   Drupal form_state array.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_xls_action_form(), hose_xml_export_nodes_xls_action()
 */
/* deprecated
function hose_xml_export_nodes_xls_action_submit($form, $form_state) {
	hose_xml_clean_export_dir();
  return array(
    'profile' => $form_state['values']['profile'],
    'filename' => $form_state['values']['filename'],
  );
} // hose_xml_export_nodes_xls_action_submit
*/

/**
 * Implementation of hook_(action)_submit().
 *
 * @param $form
 *   Drupal form array.
 * @param $form_state
 *   Drupal form_state array.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_xml_action_form(), hose_xml_export_nodes_xml_action()
 */
function hose_xml_export_nodes_xml_action_submit($form, $form_state) {
	hose_xml_clean_export_dir();
	$pids = is_array($form_state['values']['profile']) ? $form_state['values']['profile'] : array($form_state['values']['profile']);
	foreach ($pids as $key => $pid) {
	  $profiles[$pid] = hose_xml_profile_load($pid);
	}
  return array(
    'profile' => $profiles,
    'force' => $form_state['values']['force'],
    'delivery' => $form_state['values']['hose_xml_delivery_method'],
    'delivery_settings' => $form_state['values']['delivery_settings'],
  );
} // hose_xml_export_nodes_xml_action_submit

/**
 * Implementation of hook_(action)_submit().
 *
 * @param $form
 *   Drupal form array.
 * @param $form_state
 *   Drupal form_state array.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_xml_bucket_action_form(), hose_xml_export_nodes_xml_bucket_action()
 */
function hose_xml_export_nodes_xml_bucket_action_submit($form, $form_state) {
  hose_xml_clean_export_dir();
  $pids = is_array($form_state['values']['profile']) ? $form_state['values']['profile'] : array($form_state['values']['profile']);
  foreach ($pids as $key => $pid) {
    $profiles[$pid] = hose_xml_profile_load($pid);
  }
  return array(
    'profile' => $profiles,
    'force' => $form_state['values']['force'],
    'delivery' => $form_state['values']['hose_xml_delivery_method'],
    'delivery_settings' => $form_state['values']['delivery_settings'],
  );
} // hose_xml_export_nodes_xml_action_submit

/**
 * Action callback for hose_xml_export_nodes_csv_action().
 *
 * @param $object
 *   Contains an array of node ids {node}.nid.
 * @param $context
 *   Contains all the Actions related information, including the results of the forms the users filled out to fire this Action.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_csv_action_form(), hose_xml_export_nodes_csv_action_submit()
 */
/* moved to pimport
function hose_xml_export_nodes_csv_action(&$object, $context) {
	$filename = module_exists('token') ? token_replace($context['filename']) : $context['filename'];
	hose_xml_export_multiple_nodes($object, $context['profile'], $filename, 'CSV');
} // hose_xml_export_nodes_csv_action
*/

/**
 * Action callback for hose_xml_export_nodes_xls_action.
 *
 * @param $object
 *   Contains an array of node ids {node}.nid.
 * @param $context
 *   Contains all the Actions related information, including the results of the forms the users filled out to fire this Action.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_xls_action_form(), hose_xml_export_nodes_xls_action_submit()
 */
/* deprecated
function hose_xml_export_nodes_xls_action(&$object, $context) {
	$filename = module_exists('token') ? token_replace($context['filename']) : $context['filename'];
  hose_xml_export_multiple_nodes($object, $context['profile'], $filename, 'XLS');
} // hose_xml_export_nodes_xls_action
*/

/**
 * Action callback for hose_xml_export_nodes_xml_action().
 *
 * @param $object
 *   Contains an array of node ids {node}.nid.
 * @param $context
 *   Contains all the Actions related information, including the results of the forms the users filled out to fire this Action.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_xml_action_form(), hose_xml_export_nodes_xml_action_submit()
 */
function hose_xml_export_nodes_xml_action(&$object, $context) {
	foreach ($context['profile'] as $pid => $profile) {
	  $operations[] = array(
      'hose_xml_export_batch_process',
      array(
        $profile,
        $object,
        $context['force'],
        $context['delivery'],
        $context['delivery_settings'],
      ),
    );
	}
	$batch = array(
    'operations' => $operations,
    'finished' => 'hose_xml_export_batch_finished',
    'title' => t('Processing export...'),
    'init_message' => t('Batch processing is starting...'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Batch processing has encountered an error.'),
  );
  batch_set($batch);
} // hose_xml_export_nodes_xml_action

/**
 * Action callback for hose_xml_export_nodes_xml_bucket_action().
 *
 * @param $object
 *   Contains an array of node ids {node}.nid.
 * @param $context
 *   Contains all the Actions related information, including the results of the forms the users filled out to fire this Action.
 *
 * @see hose_xml_action_info(), hose_xml_export_nodes_xml_bucket_action_form(), hose_xml_export_nodes_xml_bucket_action_submit()
 */
function hose_xml_export_nodes_xml_bucket_action(&$object, $context) {
  $buckets = $context['profile'];
  foreach ($buckets as $bid => $bucket) {
  	foreach ($bucket->profiles as $pid => $profile) {
      $operations[] = array(
        'hose_xml_export_batch_process',
        array(
          $pid,
          $object,
          $context['force'],
          $context['delivery'],
          $context['delivery_settings'],
        ),
      );
    }
  }
  $batch = array(
    'operations' => $operations,
    'finished' => 'hose_xml_export_batch_finished',
    'title' => t('Processing bucket export...'),
    'init_message' => t('Bucket processing is starting...'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Bucket processing has encountered an error.'),
  );
  batch_set($batch);
} // hose_xml_export_nodes_xml_bucket_action

/**
 * @} End of "ingroup hose_xml_core".
 */
