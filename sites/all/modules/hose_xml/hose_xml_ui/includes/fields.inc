<?php

/**
 * @file
 * Profile administration include file for the Hose XML UI module.
 * 
 * @ingroup hose_xml_ui_mod
 * @{
 */

/**
 * Add field form.
 */
function hose_xml_ui_profile_manage_add(&$form_state, $profile) {
  // Add css here as confirm_form overwrites theme functionality
  drupal_add_css(drupal_get_path('module', 'hose_xml') .'/misc/shared.css');
  $form['#action'] = url("hose_xml/profiles/$profile->pid/add");

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t("The human readable title of this entry."),
    '#required' => TRUE,
  );
  $form['desc'] = array(
    '#type' => 'textarea',
    '#title' => t("Description"),
    '#description' => t("(optional) A full description from the handbook for this entry."),
  );
  $form['cck_match'] = array(
    '#type' => 'select',
    '#title' => t("CCK Match"),
    '#description' => t("The CCK field to match against this entry."),
    '#options' => array_merge(array(NULL => t('-- Ignore --')), hose_xml_cck_options($profile->pid, 'export')),
  );
  $form['tag'] = array(
    '#type' => 'textfield',
    '#title' => t("Tag"),
    '#description' => t("The XML tag for this entry."),
    '#required' => TRUE,
  );
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t("Type"),
    '#description' => t("Holds the tag type (text, numeric, etc) for validation."),
    '#options' => hose_xml_fetch_types(),
    '#required' => TRUE,
    '#default_value' => 'text',
    '#ahah' => array(
      'path' => 'hose_xml/profiles/settings/ahah',
      'wrapper' => 'hose_xml-settings',
      'effect' => 'fade',
    ),
  );
  $form['defaults'] = array(
    '#type' => 'textfield',
    '#title' => t("Default Value"),
    '#description' => t("If this field has a static default value enter it here."),
  );
  if (module_exists('token')) { 
    $form['tokens'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => 'Tokens'
    );
    $form['tokens']['list'] = array(
      '#type' => 'markup',
      '#value' => theme('token_help', 'node'),
    );
  }

  $type = isset($form_state['values']['type']) ? $form_state['values']['type'] : 'text';

  if (function_exists("hose_xml_{$type}_hose_xml_settings_information")) {
    $function = "hose_xml_{$type}_hose_xml_settings_information";
    $settings = $function();
  }
  else {
    $settings = array(
      'default' => array(
        'type' => 'markup',
        'value' => t("There are no applicable settings for this field 'type'."),
      ),
    );
  }
  drupal_alter("hose_xml_global_hose_xml_settings", $settings, $profile);
  drupal_alter("hose_xml_{$type}_hose_xml_settings", $settings, $profile);
  $form['settings'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#prefix' => '<div id="hose_xml-settings">',
    '#suffix' => '</div>',
  );
  foreach ($settings as $key => $setting) {
    // If there are settings...?
    switch ($setting['type']) {
      case 'checkbox':
      case 'textarea':
        $form['settings'][$key] = array(
          '#type' => $setting['type'],
          '#title' => $setting['title'],
          '#description' => $setting['description'],
//          '#default_value' => isset($form_state['values']['settings'][$key]) && !empty($form_state['values']['settings'][$key]) ? $form_state['values']['settings'][$key] : '',
        );
        break;
      case 'select':
        $form['settings'][$key] = array(
          '#type' => $setting['type'],
          '#title' => $setting['title'],
          '#options' => $setting['options'],
          '#description' => $setting['description'],
//          '#default_value' => isset($form_state['values']['settings'][$key]) && !empty($form_state['values']['settings'][$key]) ? $form_state['values']['settings'][$key] : '',
        );
        break;
      case 'markup':
        $form['settings'][$key] = array(
          '#type' => $setting['type'],
          '#value' => $setting['value'],
        );
        break;
      default:
        $form['settings'][$key] = array(
          '#type' => 'textfield',
          '#title' => $setting['title'],
          '#description' => $setting['description'],
//          '#default_value' => isset($form_state['values']['settings'][$key]) && !empty($form_state['values']['settings'][$key]) ? $form_state['values']['settings'][$key] : '',
        );
        break;
    }
  }

  if (isset($form_state['hose_xml_form'])) {
    $hose_xml_form = $form_state['hose_xml_form'] + (array)$hose_xml_form;
  }

  if (isset($form_state['attribute_count'])) {
    $attribute_count = $form_state['attribute_count'];
  }
  else {
    $attribute_count = max(2, empty($form_state['values']['attributes']) ? 2 : count($form_state['values']['attributes']));
  }

  // Add a wrapper for the attributes and add more button
  $form['attributes'] = array(
    '#tree' => FALSE,
    '#prefix' => '<div class="clear-block" id="attributes-wrapper">',
    '#suffix' => '</div>',
  );

  // Container for just the attributes
  $form['attributes']['attribute'] = array(
    '#prefix' => '<div id="attributes">',
    '#suffix' => '</div>',
    '#theme' => 'hose_xml_ui_ahah_form',
  );

  // Add the current attributes to the form.
  for ($delta = 0; $delta < $attribute_count; $delta++) {
    $attribute = isset($form_state['values']['attribute'][$delta]['attribute-attribute']) ? $form_state['values']['attribute'][$delta]['attribute-attribute'] : '';
    $value = isset($form_state['values']['attribute'][$delta]['attribute-value']) ? $form_state['values']['attribute'][$delta]['attribute-value'] : '';
    $required = isset($form_state['values']['attribute'][$delta]['attribute-required']) ? $form_state['values']['attribute'][$delta]['attribute-required'] : 0;
    
    $form['attributes']['attribute'][$delta] = _hose_xml_ui_attributes_form($delta, $attribute, $value, $required);
  }

  $form['attributes']['attribute_more'] = array(
    '#type' => 'submit',
    '#value' => t('Add more attributes'),
    '#description' => t("If the amount of boxes above isn't enough, click here to add more."),
    '#weight' => 1,
    '#submit' => array('hose_xml_ui_more_attributes_submit'),
    '#ahah' => array(
      'path' => 'hose_xml/profiles/attributes/ahah',
      'wrapper' => 'attributes',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['relies_on_wrapper'] = array(
    '#prefix' => '<div id="hose_xml-required">',
    '#suffix' => '</div>',
  );
  $form['relies_on_wrapper']['required'] = array(
    '#type' => 'select',
    '#title' => t("Required"),
    '#description' => t("This entry is a required tag. Note: This forces any tags that contain this tag to be displayed."),
    '#default_value' => isset($form_state['values']['required']) ? $form_state['values']['required'] : HOSE_XML_OPTIONAL,
    '#options' => _hose_xml_required_options(),
    '#ahah' => array(
      'path' => 'hose_xml/profiles/relies_on/ahah',
      'wrapper' => 'hose_xml-required',
      'effect' => 'fade',
    ),
  );
  if ($form_state['values']['required'] == HOSE_XML_RELIES_ON || $form['relies_on_wrapper']['required']['#default_value'] == HOSE_XML_RELIES_ON) {
    $form['relies_on_wrapper']['relies_on'] = array(
      '#type' => 'select',
      '#title' => t("Relies On"),
      '#description' => t("The CCK field this field relies on (i.e. won't display unless the selected field *has* content)."),
      '#options' => hose_xml_cck_options($profile->pid, 'export'),
      '#default_value' => $conf->relies_on,
    );
  }
  $form['cdata'] = array(
    '#type' => 'checkbox',
    '#title' => t("CDATA"),
    '#description' => t("The content of this tag is unparsed character data. A CDATA section starts with &quot;&lt;![CDATA[&quot; and ends with &quot;]]&gt;&quot; these tags will be inserted by the system during the export process."),
  );
  
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $profile->pid,
  );
  $form['name'] = array(
    '#type' => 'hidden',
    '#value' => $profile->name,
  );

  return confirm_form($form, t("Add element to profile '@profile':", array('@profile' => $profile->name)), "hose_xml/profiles/$profile->pid/view", ' ', t('Create'), t('Cancel'));
} // hose_xml_ui_profile_manage_add

/**
 * Add field validation callback.
 */
function hose_xml_ui_profile_manage_add_validate($form, &$form_state) {
  if ($form_state['hose_xml_skip_validation']) {
    return;
  }
  $form_values = $form_state['values'];
  $function = "hose_xml_{$form_values['type']}_hose_xml_settings_validate";
  foreach (element_children($form['settings']) as $key) {
    if (function_exists($function) && ($reason = $function($key, $form_values['settings'][$key]))) {
      form_set_error("settings][$key", $reason);
    }
  }
  if (!preg_match('/^[a-zA-Z][\S]*$/', $form_values['tag'])) {
    form_set_error('tag', t("Not a valid XML tag. Tags must start with a letter and contain no spaces."));
  }
  if (!empty($form_values['defaults'])) {
    $function = "hose_xml_{$form_values['type']}_hose_xml_validate";
    if (function_exists($function) && ($ret = $function($form_values['defaults'], $form_values['settings']))) {
      if (!empty($ret['reason'])) {
        form_set_error('defaults', $ret['reason']);
      }
    }
  }
} // hose_xml_ui_profile_manage_add_validate

/**
 * Add field submit callback.
 */
function hose_xml_ui_profile_manage_add_submit($form, &$form_state) {
  if ($form_state['hose_xml_skip_validation']) {
    return;
  }
  $form_values = $form_state['values'];
  $pid = $form_values['pid'];

  foreach ($form_values['attribute'] as $attribute) {
    if (!empty($attribute['attribute-attribute'])) {
      $attributes[] = $attribute;
    }
  }

  if (db_query(
      "INSERT INTO {hose_xml_profile_data} 
      (pid, title, description, cck_match, tag, type, defaults, attributes, settings, required, relies_on, cdata) 
      VALUES (%d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %d, '%s', %d)", 
      $form_values['pid'], 
      $form_values['title'], 
      $form_values['desc'], 
      $form_values['cck_match'], 
      $form_values['tag'], 
      $form_values['type'],
      $form_values['defaults'],
      serialize($attributes), 
      serialize($form_values['settings']), 
      $form_values['required'],
      $form_values['relies_on'],
      $form_values['cdata'])) {
    drupal_set_message(t("Configuration saved to profile '@profile'.", array('@profile' => $form_values['name'])));
  }
  else {
    drupal_set_message(t('Error saving element. Please contact your <a href="mailto:!sysadmin">System Administrator</a>', array('!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  module_invoke_all('hose_xml_ui_profile_altered', $pid);
  $form_state['redirect'] = "hose_xml/profiles/$pid/view";
} // hose_xml_ui_profile_manage_add_submit

/**
 * Edit field form.
 */
function hose_xml_ui_profile_manage_edit(&$form_state, $profile, $conf) {
  // Add css here as confirm_form overwrites theme functionality
  drupal_add_css(drupal_get_path('module', 'hose_xml') .'/misc/shared.css');
  $form['#action'] = url("hose_xml/profiles/$profile->pid/edit/$conf->id");
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t("The human readable title of this entry."),
    '#required' => TRUE,
    '#default_value' => $conf->title,
  );
  $form['desc'] = array(
    '#type' => 'textarea',
    '#title' => t("Description"),
    '#description' => t("(optional) A full description from the handbook for this entry."),
    '#default_value' => $conf->description,
  );
  $form['cck_match'] = array(
    '#type' => 'select',
    '#title' => t("CCK Match"),
    '#description' => t("The CCK field to match against this entry."),
    '#options' => array_merge(array(NULL => t('-- Ignore --')), hose_xml_cck_options($profile->pid, 'export')),
    '#default_value' => $conf->cck_match,
  );
  $form['tag'] = array(
    '#type' => 'textfield',
    '#title' => t("Tag"),
    '#description' => t("The XML tag for this entry."),
    '#required' => TRUE,
    '#default_value' => $conf->tag,
  );
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t("Type"),
    '#description' => t("Holds the tag type (text, numeric, etc) for validation."),
    '#options' => hose_xml_fetch_types(),
    '#required' => TRUE,
    '#default_value' => $conf->type,
    '#ahah' => array(
      'path' => 'hose_xml/profiles/settings/ahah',
      'wrapper' => 'hose_xml-settings',
      'effect' => 'fade',
    ),
  );
  $form['defaults'] = array(
    '#type' => 'textfield',
    '#title' => t("Default Value"),
    '#description' => t("If this field has a static default value enter it here or choose a token from the list below."),
    '#default_value' => $conf->defaults,
  );
  
  if (module_exists('token')) { 
    $form['tokens'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => 'Tokens'
    );
    $form['tokens']['list'] = array(
      '#type' => 'markup',
      '#value' => theme('token_help', 'node'),
    );
  }

  $type = isset($form_state['values']['type']) ? $form_state['values']['type'] : $conf->type;

  if (function_exists("hose_xml_{$type}_hose_xml_settings_information")) {
    $function = "hose_xml_{$type}_hose_xml_settings_information";
    $settings = $function();
  }
  else {
    $settings = array(
      'default' => array(
        'type' => 'markup',
        'value' => t("There are no applicable settings for this field 'type'."),
      ),
    );
  }
  $expand_settings = unserialize($conf->settings);
  drupal_alter("hose_xml_global_hose_xml_settings", $settings, $profile);
  drupal_alter("hose_xml_{$type}_hose_xml_settings", $settings, $profile);
  $form['settings'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#prefix' => '<div id="hose_xml-settings">',
    '#suffix' => '</div>',
  );
  foreach ($settings as $key => $setting) {
    // If there are settings...?
    switch ($setting['type']) {
      case 'checkbox':
      case 'textarea':
        $form['settings'][$key] = array(
          '#type' => $setting['type'],
          '#title' => $setting['title'],
          '#description' => $setting['description'],
          '#default_value' => !empty($expand_settings[$key]) ? $expand_settings[$key] : '',
        );
        break;
      case 'select':
        $form['settings'][$key] = array(
          '#type' => $setting['type'],
          '#title' => $setting['title'],
          '#options' => $setting['options'],
          '#description' => $setting['description'],
          '#default_value' => !empty($expand_settings[$key]) ? $expand_settings[$key] : '',
        );
        break;
      case 'markup':
        $form['settings'][$key] = array(
          '#type' => $setting['type'],
          '#value' => $setting['value'],
        );
        break;
      default:
        $form['settings'][$key] = array(
          '#type' => 'textfield',
          '#title' => $setting['title'],
          '#description' => $setting['description'],
          '#default_value' => !empty($expand_settings[$key]) ? $expand_settings[$key] : '',
        );
        break;
    }
  }

  if (isset($form_state['hose_xml_form'])) {
    $hose_xml_form = $form_state['hose_xml_form'] + (array)$hose_xml_form;
  }

  $attributes = unserialize($conf->attributes);

  if (isset($form_state['attribute_count'])) {
    $attribute_count = $form_state['attribute_count'];
  }
  elseif (isset($attributes)) {
    $attribute_count = max(2, empty($attributes) ? 2 : count($attributes));
  }
  else {
    $attribute_count = max(2, empty($form_state['values']['attributes']) ? 2 : count($form_state['values']['attributes']));
  }

  // Add a wrapper for the attributes and add more button
  $form['attributes'] = array(
    '#tree' => FALSE,
    '#prefix' => '<div class="clear-block" id="attributes-wrapper">',
    '#suffix' => '</div>',
    '#value' => t('To use attribute values from the field put the attribute name in square brackets in the value field. 
    	This will cause the attribute value to be retrieved from the field if the content of the field 
    	looks like [attribute-name:attribute-value]'),
  );

  // Container for just the attributes
  $form['attributes']['attribute'] = array(
    '#prefix' => '<div id="attributes">',
    '#suffix' => '</div>',
    '#theme' => 'hose_xml_ui_ahah_form',
  );

  // Add the current attributes to the form.
  for ($delta = 0; $delta < $attribute_count; $delta++) {
    $attribute = isset($form_state['values']['attribute'][$delta]['attribute-attribute']) ? $form_state['values']['attribute'][$delta]['attribute-attribute'] : $attributes[$delta]['attribute-attribute'];
    $value = isset($form_state['values']['attribute'][$delta]['attribute-value']) ? $form_state['values']['attribute'][$delta]['attribute-value'] : $attributes[$delta]['attribute-value'];
    $required = isset($form_state['values']['attribute'][$delta]['attribute-required']) ? $form_state['values']['attribute'][$delta]['attribute-required'] : $attributes[$delta]['attribute-required'];
    
    $form['attributes']['attribute'][$delta] = _hose_xml_ui_attributes_form($delta, $attribute, $value, $required);
  }

  $form['attributes']['attribute_more'] = array(
    '#type' => 'submit',
    '#value' => t('Add more attributes'),
    '#description' => t("If the amount of boxes above isn't enough, click here to add more."),
    '#weight' => 1,
    '#submit' => array('hose_xml_ui_more_attributes_submit'),
    '#ahah' => array(
      'path' => 'hose_xml/profiles/attributes/ahah',
      'wrapper' => 'attributes',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['relies_on_wrapper'] = array(
    '#prefix' => '<div id="hose_xml-required">',
    '#suffix' => '</div>',
  );
  $form['relies_on_wrapper']['required'] = array(
    '#type' => 'select',
    '#title' => t("Required"),
    '#description' => t("This entry is a required tag. Note: This forces any tags that contain this tag to be displayed."),
    '#default_value' => isset($form_state['values']['required']) ? $form_state['values']['required'] : $conf->required,
    '#options' => _hose_xml_required_options(),
    '#ahah' => array(
      'path' => 'hose_xml/profiles/relies_on/ahah',
      'wrapper' => 'hose_xml-required',
      'effect' => 'fade',
    ),
  );
  if ($form_state['values']['required'] == HOSE_XML_RELIES_ON || $form['relies_on_wrapper']['required']['#default_value'] == HOSE_XML_RELIES_ON) {
    $form['relies_on_wrapper']['relies_on'] = array(
      '#type' => 'select',
      '#title' => t("Relies On"),
      '#description' => t("The CCK field this field relies on (i.e. won't display unless the selected field *has* content)."),
      '#options' => hose_xml_cck_options($profile->pid, 'export'),
      '#default_value' => $conf->relies_on,
    );
  }
  $form['cdata'] = array(
    '#type' => 'checkbox',
    '#title' => t("CDATA"),
    '#default_value' => $conf->cdata,
    '#description' => t("The content of this tag is unparsed character data. A CDATA section starts with &quot;&lt;![CDATA[&quot; and ends with &quot;]]&gt;&quot; these tags will be inserted by the system during the export process."),
  );
  
  
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $profile->pid,
  );
  $form['id'] = array(
    '#type' => 'hidden',
    '#value' => $conf->id,
  );
  $form['name'] = array(
    '#type' => 'hidden',
    '#value' => $profile->name,
  );

  return confirm_form($form, t("Edit element from profile '@profile':", array('@profile' => $profile->name)), "hose_xml/profiles/$profile->pid/view", ' ', t('Save'), t('Cancel'));
} // hose_xml_ui_profile_manage_edit

/**
 * Edit field validation callback.
 */
function hose_xml_ui_profile_manage_edit_validate($form, &$form_state) {
  if ($form_state['hose_xml_skip_validation']) {
    return;
  }
  $form_values = $form_state['values'];
  $function = "hose_xml_{$form_values['type']}_hose_xml_settings_validate";
  foreach (element_children($form['settings']) as $key) {
    if (function_exists($function) && ($reason = $function($key, $form_values['settings'][$key]))) {
      form_set_error("settings][$key", $reason);
    }
  }
  if (!preg_match('/^[a-z][\S]*$/i', $form_values['tag']) && !preg_match('/^!DOCTYPE [a-z]+$/i', $form_values['tag'])) {
    form_set_error('tag', t("Not a valid XML tag. Tags must start with a letter and contain no spaces."));
  }
  if (!empty($form_values['defaults'])) {
    $function = "hose_xml_{$form_values['type']}_hose_xml_validate";
    if (function_exists($function) && ($ret = $function($form_values['defaults'], $form_values['settings']))) {
      if (!empty($ret['reason'])) {
        form_set_error('defaults', $ret['reason']);
      }
    }
  }
} // hose_xml_ui_profile_manage_edit_validate

/**
 * Edit field submission callback.
 */
function hose_xml_ui_profile_manage_edit_submit($form, &$form_state) {
  if ($form_state['hose_xml_skip_validation']) {
    return;
  }
  $form_values = $form_state['values'];
  $pid = $form_values['pid'];

  foreach ($form_values['attribute'] as $attribute) {
    if (!empty($attribute['attribute-attribute'])) {
      $attributes[] = $attribute;
    }
  }

  if (db_query("
    UPDATE {hose_xml_profile_data} 
    SET title = '%s', description = '%s', cck_match = '%s', tag = '%s', type = '%s', defaults = '%s', attributes = '%s', 
    settings = '%s', required = %d, relies_on = '%s', cdata = %d 
    WHERE pid = %d && id = %d", 
    $form_values['title'], 
    $form_values['desc'], 
    $form_values['cck_match'], 
    $form_values['tag'], 
    $form_values['type'],
    $form_values['defaults'],
    serialize($attributes),
    serialize($form_values['settings']), 
    $form_values['required'],
    $form_values['relies_on'],
    $form_values['cdata'], 
    $form_values['pid'], 
    $form_values['id'])) {
    drupal_set_message(t("Element saved to profile '@profile'.", array('@profile' => $form_values['name'])));
  }
  else {
    drupal_set_message(t('Error saving element. Please contact your <a href="mailto:!sysadmin">System Administrator</a>', array('!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  module_invoke_all('hose_xml_ui_profile_altered', $pid);
  $form_state['redirect'] = "hose_xml/profiles/$pid/view";
} // hose_xml_ui_profile_manage_edit_submit

/**
 * More attributes submit handler.
 */
function hose_xml_ui_more_attributes_submit($form, &$form_state) {
  unset($form_state['submit_handlers']);
  form_execute_handlers('submit', $form, $form_state);
  $hose_xml_form = $form_state['values'];
  $form_state['hose_xml_form'] = $hose_xml_form;
  $form_state['rebuild'] = TRUE;
  if ($form_state['values']['attribute_more']) {
    $form_state['attribute_count'] = count($form_state['values']['attribute']) + ($_GET['q'] == 'hose_xml/profiles/attributes/ahah' ? 1 : 2);
  }
  return $hose_xml_form;
} // hose_xml_ui_more_attributes_submit

/**
 * Delete field form.
 */
function hose_xml_ui_profile_manage_delete(&$form_state, $profile, $conf) {
  $form['display'] = array(
    '#type' => 'markup',
    '#value' => theme('hose_xml_ui_profile_config', $profile, $conf),
  );
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $profile->pid,
  );
  $form['id'] = array(
    '#type' => 'hidden',
    '#value' => $conf->id,
  );
  $form['name'] = array(
    '#type' => 'hidden',
    '#value' => $profile->name,
  );

  return confirm_form($form, t("Are you sure you want to delete this element from profile '@profile'?", array('@profile' => $profile->name)), "hose_xml/profiles/$profile->pid/view", NULL, t('Delete'), t('Cancel'));
} // hose_xml_ui_profile_manage_delete

/**
 * Delete field submission callback.
 */
function hose_xml_ui_profile_manage_delete_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  $pid = $form_values['pid'];
  $parent = db_result(db_query("SELECT did FROM {hose_xml_profile_data} WHERE pid = %d && id = %d", $form_values['pid'], $form_values['id']));
  if (db_query("UPDATE {hose_xml_profile_data} SET did = %d WHERE did = %d", $parent, $form_values['id'])) {
    drupal_set_message(t("The old parents are now grandparents")); 
  }
  else {
    drupal_set_message(t('Error deleting element from profile \'@profile\'. Please contact your <a href="mailto:!sysadmin">System Administrator</a>', array('@profile' => $form_values['name'], '!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  if (db_query("DELETE FROM {hose_xml_profile_data} WHERE pid = %d && id = %d", $form_values['pid'], $form_values['id'])) {
    drupal_set_message(t("Configuration has been deleted from profile '@profile' has been deleted.", array('@profile' => $form_values['name'])));
  }
  else {
    drupal_set_message(t('Error deleting element from profile \'@profile\'. Please contact your <a href="mailto:!sysadmin">System Administrator</a>', array('@profile' => $form_values['name'], '!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  module_invoke_all('hose_xml_ui_profile_altered', $pid);
  $form_state['redirect'] = "hose_xml/profiles/$pid/view";
} // hose_xml_ui_profile_manage_delete_submit

/**
 * Add elements to a profile from each tag in an XML file
 * or create a profile from all the fields in a content type
 * @param $form_state
 * @param $profile
 */
function hose_xml_ui_profile_manage_wizard(&$form_state, $profile) {
  $form['#attributes'] = array('enctype' => 'multipart/form-data');
  $types = drupal_map_assoc(hose_xml_export_fetch_types($profile->pid));
  if (empty($types)) {
  	drupal_set_message(t('You need to associate a content type with this profile'), 'warning');
  }
  else {

  	$form['content_type'] = array(
	  	'#type' => 'select',
  	  '#title' => t('Type'),
	  	'#description' => t('Choose a content type to use to create the profile. '),
	  	'#options' => $types,
      '#prefix' => t('<h2 class="title">Append elements to a profile using fields from a content type</h2>'),
	  );
	  $form['process'] = array(
    '#type' => 'submit',
    '#value' => t('Process'),
  );
  }
  
  $form['upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload'),
    '#description' => t('Click "Browse" to select an xml file for processing.  All XML tags in the file will be created as elements
    	in the profile.'),
    '#prefix' => t('<h2 class="title">Append elements to the profile using an XML file as a template.</h2>')
  );
  $form['bar']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Upload'),
  );
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $profile->pid,
  );
  $form['file_placeholder'] = array(
    '#type' => 'hidden',
    '#value' => '',
  );
  return $form;
} // hose_xml_ui_profile_manage_wizard

/**
 * Validate handler for the profile wizard
 * @param $form
 * @param $form_state
 */
function hose_xml_ui_profile_manage_wizard_validate(&$form, &$form_state) {
  switch ($form_state['clicked_button']['#value']) {
  	case t('Process'):
  		$type = $form_state['values']['content_type'];
  		if (empty($type)) {
  			form_set_error('content_type', t('Please choose a content type.'));
  		}
  		break;
    case t('Upload'):
      $validators = array(
        'hose_xml_is_xml_file' => array(),
      );
      if (!($file = file_save_upload('upload', $validators))) {
        // return an error on failure
        form_set_error('upload', t('File upload failed, please contact your system administrator.'));
      }
      else {
        // fill in placeholder variable so we get to pass our file variables into the submit function
        form_set_value(array('#parents' => array('file_placeholder')), $file, $form_state);
      }
      break;
  } // end switch
} // hose_xml_ui_profile_manage_wizard_validate

/**
 * Submit handler for the profile wizard
 * 
 * @param $form
 * @param $form_state
 */
function hose_xml_ui_profile_manage_wizard_submit($form, &$form_state) {
  $pid = $form_state['values']['pid'];
  $file = $form_state['values']['file_placeholder'];
	$type = $form_state['values']['content_type'];
	switch ($form_state['clicked_button']['#value']) {
    case t('Process'):
      _hose_xml_append_elements_from_content_type($pid, $type);
    	break;
    case t('Upload'):
    	_hose_xml_append_elements_from_file($pid, $file);
    	break;
	}
  //return to view page
  $form_state['redirect'] = "hose_xml/profiles/$pid/view";
} // hose_xml_ui_profile_manage_wizard_submit

//----------------------------------------------------------------------------
// Private functions.

/**
 * 
 * Create a default profile using all the fields in a content type
 * @param unknown_type $pid
 * @param unknown_type $type
 */
function _hose_xml_append_elements_from_content_type($pid, $type) {
  $weight = db_result(db_query("SELECT MAX(weight) FROM {hose_xml_profile_data} WHERE pid = %d", $pid));
	$type_info = node_get_types('type', $type);
	if ($type_info->has_title) {
		$fields[] = array(
      'label' => t('title'),
      'field_name' => 'title',
      'widget_type' => 'text', 
    );
	}
if ($type_info->has_body) {
    $fields[] = array(
      'label' => $type_info->body_label,
      'field_name' => 'body',
      'widget_type' => 'text', 
    );
  }
	$fields += hose_xml_content_fields(NULL, $type);
	// map cck types to hose_xml types
	foreach ($fields as $field) {
		switch ($field['widget_type']) {
			/* There is no hose_xml nodereference type yet
			case 'nodereference_select':
				$field_type = 'nodereference';
				break;
		*/
				default:
				$field_type = 'text';
		}
		$element = array(
		  'pid' => $pid,
		  'did' => 0,
		  'title' => $field['label'],
		  'cck_match' => $field['field_name'],
		  'tag' => str_replace('field_', '', $field['field_name']), // chop off field_ if it is there
		  'type' => $field_type, 
		  'weight' => ++$weight,
		);
		$value[] = "('". implode("','", $element ) ."')";
		$elements[] = $element;
	}
	$values = implode(',', $value);
	$columns = implode(',', array_keys($elements[0]));
	$query = "INSERT INTO {hose_xml_profile_data} ($columns) VALUES $values";
	if (!db_query($query)) {
		drupal_set_message(t('Could not write to profile database, please contact your system administrator.', 'error'));
	}
	else {
		drupal_set_message(t('Field elements appended to profile.'));
	}
}

/**
 * 
 * Create an XML profile using an XML file as a template
 * @param unknown_type $pid
 * @param unknown_type $file
 */
function _hose_xml_append_elements_from_file($pid, $file) {
  $parents = array();
  $parents[0] = 0;
  $level = 0;
  $last_id = 0;
  $xml = file_get_contents($file->filepath);
  $parser = xml_parser_create();
  xml_parser_set_option($parser, XML_OPTION_CASE_FOLDING, FALSE);
  xml_parse_into_struct($parser, $xml, $values, $index);
  $values = NULL;
  xml_parser_free($parser);
  if (is_array($values)) {
    foreach ($values as $key => $value) {
      $attributes = array();      
      if (in_array($value['type'], array('open', 'complete'))) {
        if ($value['level'] < $level) {
          //we have dropped so take the parents off the stack
          while ($level > $value['level']) {
            array_shift($parents);
            $level--;
          }
        }
        else if ($value['level'] > $level) {
          // we have gone up a level so put the last id on the parents stack
          // all new elements will use this as their did
          array_unshift($parents, $last_id);
        }
        $level = $value['level'];   
        // We're only interested in new tags.  // Collect attributes (if there are any?)
        if (is_array($value['attributes'])) {
          foreach ($value['attributes'] as $key => $attribute) {
            $attributes[] = array('attribute-attribute' => $key, 'attribute-value' => $attribute, 'attribute-required' => FALSE);
          }
        }
        // Write to db.
        db_query(
          "INSERT INTO {hose_xml_profile_data}
          (pid, did, title, tag, type, attributes, weight)
          VALUES (%d, %d, '%s', '%s', '%s', '%s', %d)",
          $pid,
          $parents[0],
          drupal_strtolower($value['tag']),
          drupal_strtolower($value['tag']),
          $value['type'] == 'open' ? 'container' : 'text',
          serialize($attributes),
          0
        );
        if ($value['type'] == 'open') {
          $last_id = db_last_insert_id('hose_xml_profile_data', 'id');
        }
      }
    }
  }
  else {
    drupal_set_message(t('Error processing XML file, please contact your system administrator.'), 'error');
  }

  // clean up
  file_delete($file->filepath);
  db_query("DELETE FROM {files} WHERE fid = %d", $file->fid);
}

/**
 * Attributes sub-form.
 */
function _hose_xml_ui_attributes_form($delta, $attribute = '', $value = '', $required = 0) {
  $form = array(
    '#tree' => TRUE,
  );
  $form['attribute-attribute'] = array(
    '#type' => 'textfield',
    '#title' => t("Attribute"),
    '#size' => 22,
    '#default_value' => $attribute,
    '#parents' => array('attribute', $delta, 'attribute-attribute'),
  );
  $form['attribute-value'] = array(
    '#type' => 'textfield',
    '#title' => t("Value"),
    '#default_value' => $value,
    '#parents' => array('attribute', $delta, 'attribute-value'),
  );
  $form['attribute-required'] = array(
    '#type' => 'checkbox',
    '#default_value' => $required,
    '#parents' => array('attribute', $delta, 'attribute-required'),
  );
  return $form;
} // _hose_xml_ui_attributes_form

/**
 * @} End of "ingroup hose_xml_ui_mod".
 */