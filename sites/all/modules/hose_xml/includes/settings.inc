<?php

/**
 * @file
 * System settings form for Hose XML module.
 *
 * @ingroup hose_xml_core
 * @{
 */

/**
 * Administration page.
 */
function hose_xml_settings() {
  $form['hose_xml_handbook'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create Handbooks'),
    '#description' => t('Check this to enable handbooks for each profile.'),
    '#default_value' => variable_get('hose_xml_handbook', FALSE),
  );
  $form['hose_xml_content_types'] = array(
    '#type' => 'select',
    '#title' => t('Enable for these Content Types'),
    '#description' => t('Select which content types hose_xml should interact with.'),
    '#default_value' => variable_get('hose_xml_content_types', array()),
    '#options' => array_map('check_plain', node_get_types('names')),
    '#multiple' => TRUE,
  );
  $form['hose_xml_use_permissions'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use permissions"),
    '#description' => t('To add to the confusion, checking this box will activate <a href="@url">permissions</a> PER PROFILE.<br />The downside to this is that if a user creates a profile they *must* also be able to grant permissions else they won\'t be able to view their own profile.', array('@url' => url('admin/user/permissions', array('fragment' => 'module-hose_xml')))),
    '#default_value' => variable_get('hose_xml_use_permissions', FALSE),
  );
  $form['hose_xml_force_download'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force downloads'),
    '#description' => t("Check this to provide an option to download generated XML files even if they fail validation."),
    '#default_value' => variable_get('hose_xml_force_download', FALSE),
  );
  // Only show if there are any vocabs to clean...
  if ($vocabs = _hose_xml_fetch_vocabs()) {
    $form['hose_xml_clean_vocabs'] = array(
      '#type' => 'select',
      '#title' => t('Select Vocabularies For Housekeeping'),
      '#description' => t('Select which vocabularies should have their terms deleted (on cron runs) when empty.'),
      '#options' => $vocabs,
      '#default_value' => variable_get('hose_xml_clean_vocabs', array(30)),
      '#multiple' => TRUE,
    );
  }
  $form['hose_xml_export_bars'] = array(
    '#type' => 'select',
    '#title' => t('Where to display the export bar on node views'),
    '#description' => t('Select either top, bottom or both.'),
    '#options' => array(
      'both' => t('Both top and bottom'),
      'top' => t('Top'),
      'bottom' => t('Bottom'),
    ),
    '#default_value' => variable_get('hose_xml_export_bars', 'bottom'),
  );
  $form += module_invoke_all('hose_xml_settings');
  $form['#pre_render'][] = 'vertical_tabs_form_pre_render';

  $form = system_settings_form($form);
  $form['buttons']['#weight'] = 100;
  return $form;
} // hose_xml_settings

/**
 * Provides a 'clean' list of Drupal vocabularies for use with selection lists.
 *
 * @param $reset
 *   Boolean flag representing whether to reset the static variable or not.
 *
 * @return
 *   Returns keyed array where key is Vocabulary ID and values are Vocabulary names.
 */
function _hose_xml_fetch_vocabs($reset = FALSE) {
  static $vocabs;
  if (!isset($vocabs) || $reset) {
    $all_vocabs = taxonomy_get_vocabularies();
    foreach ($all_vocabs as $vocab) {
      $vocabs[$vocab->vid] = $vocab->name;
    }
    if (!empty($vocabs)) {
      asort($vocabs);
    }
  }
  return $vocabs;
} // _hose_xml_fetch_vocabs

/**
 * @} End of "ingroup hose_xml_core".
 */