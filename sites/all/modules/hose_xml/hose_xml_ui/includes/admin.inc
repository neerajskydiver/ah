<?php

/**
 * @file
 * Admin settings include file for the Hose XML module.
 * 
 * @ingroup hose_xml_ui_mod
 * @{
 */

/**
 * Form wrapper around hose_xml_ui_profiles theme.
 */
function hose_xml_ui_settings_profiles() {
  $form['profiles'] = array(
    '#type' => 'markup',
    '#value' => theme('hose_xml_ui_profiles'),
  );

  return $form;
} // hose_xml_ui_settings_profiles

/**
 * Main form to view and manage export profile fields.
 * 
 * @see hose_xml_ui_profile_view_submit()
 */
function hose_xml_ui_profile_view(&$form_state, $profile) {
  $config = hose_xml_fetch_config($profile->pid);

  $form['name'] = array(
    '#type' => 'hidden',
    '#value' => check_plain($profile->name),
  );
  $form['description'] = array(
    '#type' => 'markup',
    '#value' => check_plain($profile->description),
  );
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $profile->pid,
  );
  $form['settings']['#tree'] = TRUE;

  foreach ($config as $setting) {
    $form['settings'][$setting->id]['title'] = array(
      '#type' => 'markup',
      '#value' => !empty($setting->description) ? sprintf('<a href="#" class="hose_xml-tooltip">%s<span>%s</span></a>', check_plain($setting->title), check_plain($setting->description)) : check_plain($setting->title),
      '#size' => 12,
    );
    $form['settings'][$setting->id]['cck_match'] = array(
      '#type' => 'markup',
      '#value' => preg_match("/^vocab_(\d+)$/", $setting->cck_match, $match) ? t("Vocab: @vocab", array('@vocab' => db_result(db_query("SELECT name FROM {vocabulary} WHERE vid = %d", $match[1])))) : $setting->cck_match,
      '#size' => 12,
    );
    $form['settings'][$setting->id]['tag'] = array(
      '#type' => 'markup',
      '#value' => $setting->tag,
      '#size' => 12,
    );
    $form['settings'][$setting->id]['type'] = array(
      '#type' => 'markup',
      '#value' => $setting->type,
      '#size' => 12,
    );
    $form['settings'][$setting->id]['weight'] = array(
      '#type' => 'weight',
      '#delta' => count($config),
      '#default_value' => $setting->weight,
    );
    $form['settings'][$setting->id]['did'] = array(
      '#type' => 'hidden',
      '#value' => $setting->did,
    );
    $form['settings'][$setting->id]['id'] = array(
      '#type' => 'textfield',
      '#default_value' => $setting->id,
    );
    $form['settings'][$setting->id]['required'] = array(
      '#type' => 'select',
      '#options' => _hose_xml_required_options(),
      '#default_value' => $setting->required,
    );
    if ($setting->required == HOSE_XML_RELIES_ON) {
      $form['settings'][$setting->id]['relies_on'] = array(
        '#type' => 'select',
        '#options' => hose_xml_cck_options($profile->pid, 'export'),
        '#default_value' => $setting->relies_on,
      );
    }
    $form['settings'][$setting->id]['cdata'] = array(
      '#type' => 'hidden',
      '#default_value' => $setting->cdata,
    );
  }
  $form['bar']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
} // hose_xml_ui_profile_view

/**
 * View fields submit callback.
 * 
 * @see hose_xml_ui_profile_view()
 */
function hose_xml_ui_profile_view_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  $order = array_flip(array_keys($form['#post']));
  $form = array_merge($order, $form);

  $flag = FALSE;
  foreach (element_children($form['settings']) as $index) {
    // id is the primary key and is incremental, so matching to pid isn't necessary here
    if (!db_query("UPDATE {hose_xml_profile_data} SET weight = %d, did = %d, required = %d, relies_on = '%s' WHERE id = %d",
        $form['#post']['settings'][$index]['weight'],
        $form['#post']['settings'][$index]['did'],
        $form['#post']['settings'][$index]['required'],
        $form['#post']['settings'][$index]['relies_on'],
        $form['#post']['settings'][$index]['id'])) {
      $flag = TRUE;
    }
  }
  if ($flag) {
    watchdog('hose_xml', "Error updating the order of profile '@profile'.", array('@profile' => $form_values['name']), WATCHDOG_ERROR, l(t('view'), "hose_xml/profiles/". $form_values['pid'] ."/view"));
    drupal_set_message(t("Error updating the order of profile '@profile'. Please contact your <a href=\"mailto:!sysadmin\">System Administrator</a>", array('@profile' => $form_values['name'], '!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  else {
    // Success!
// TODO - what use cases change the "changed"?? db_query("UPDATE {hose_xml_profiles} SET changed = %d WHERE pid = %d", time(), $form_values['pid']);
    drupal_set_message(t("Order of profile '@profile' has been saved.", array('@profile' => $form_values['name'])));
  }
} // hose_xml_ui_profile_view_submit

/**
 * @} End of "ingroup hose_xml_ui_mod".
 */