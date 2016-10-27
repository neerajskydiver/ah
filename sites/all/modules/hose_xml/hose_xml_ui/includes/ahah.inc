<?php

/**
 * @file
 * AHAH callbacks for the Hose XML UI module.
 * 
 * @ingroup hose_xml_ui_mod
 * @{
 */

/**
 * AHAH callback for settings selection list.
 */
function hose_xml_ui_settings_ahah() {
  module_load_include('inc', 'hose_xml_ui', 'includes/fields');
  $form_state = array('storage' => NULL, 'submitted' => FALSE, 'rebuild' => TRUE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);

  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;

  $form_state['hose_xml_skip_validation'] = TRUE;

  drupal_process_form($form_id, $form, $form_state);

  if (form_get_errors()) {
    form_execute_handlers('submit', $form, $form_state);
  }

  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  $settings = $form['settings'];
  unset($settings['#prefix'], $settings['#suffix']);
  $output = drupal_render($settings);

  drupal_json(array('status' => TRUE, 'data' => $output));
} // hose_xml_ui_settings_ahah

/**
 * AHAH callback for required selection list.
 */
function hose_xml_ui_relies_on_ahah() {
  module_load_include('inc', 'hose_xml_ui', 'includes/fields');
  $form_state = array('storage' => NULL, 'submitted' => FALSE, 'rebuild' => TRUE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);

  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;

  $form_state['hose_xml_skip_validation'] = TRUE;

  drupal_process_form($form_id, $form, $form_state);

  if (form_get_errors()) {
    form_execute_handlers('submit', $form, $form_state);
  }

  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  $relies_on = $form['relies_on_wrapper'];
  unset($relies_on['#prefix'], $relies_on['#suffix']);
  $output = drupal_render($relies_on);

  drupal_json(array('status' => TRUE, 'data' => $output));
} // hose_xml_ui_relies_on_ahah

/**
 * AHAH callback for attributes add more button.
 */
function hose_xml_ui_profile_attributes_ahah() {
  module_load_include('inc', 'hose_xml_ui', 'includes/fields');
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);

  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;

  $form_state['hose_xml_skip_validation'] = TRUE;

  drupal_process_form($form_id, $form, $form_state);

  if (form_get_errors()) {
    form_execute_handlers('submit', $form, $form_state);
  }

  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  $attribute_form = $form['attributes']['attribute'];
  unset($attribute_form['#prefix'], $attribute_form['#suffix']);
  $output = drupal_render($attribute_form);

  drupal_json(array('status' => TRUE, 'data' => $output));
} // hose_xml_ui_profile_attributes_ahah

/**
 * @} End of "ingroup hose_xml_ui_mod".
 */