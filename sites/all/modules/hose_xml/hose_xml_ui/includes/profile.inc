<?php

/**
 * @file
 * Profile administration include file for the Hose XML UI module.
 * 
 * @ingroup hose_xml_ui_mod
 * @{
 */

/**
 * Add Profile callback.
 */
function hose_xml_ui_profile_add() {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t("The human-readable name of this profile. It is recommended that this name begin with a capital letter and contain only alphanumeric characters. This name should be unique."),
    '#required' => TRUE,
  );
  $form['desc'] = array(
    '#type' => 'textfield',
    '#title' => t("Description"),
    '#description' => t("Optional - a brief description of this profile."),
  );
  $form['xml'] = array(
    '#type' => 'fieldset',
    '#title' => t('XML Processing Instructions'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['xml']['xmlversion'] = array(
    '#type' => 'textfield',
    '#title' => t('XML Version'),
    '#description' => t('The version of XML this schema relates to.'),
    '#required' => TRUE,
    '#default_value' => '1.0',
  );
  $form['xml']['encoding'] = array(
    '#type' => 'textfield',
    '#title' => t('Character Encoding'),
    '#description' => t('The character encoding of your document, e.g. UTF-8'),
    '#required' => TRUE,
    '#default_value' => 'UTF-8',
  );
  $form['types'] = array(
    '#type' => 'select',
    '#title' => t('Node type associations'),
    '#description' => t('Please select which node types this profile can be used with.'),
    '#options' => array_map('filter_xss', node_get_types('names')),
    '#multiple' => TRUE,
  );
/*  if (variable_get('hose_xml_use_permissions', FALSE) && user_access('administer permissions')) {
    $form['roles'] = array(
      '#type' => 'select',
      '#title' => t('User Permissions'),
      '#description' => t('Allow user access to this profile only from these roles.<br /><strong>It is your responsibility to ensure you select a role you have access to, else you will not be able to access this profile after you click confirm.</strong>'),
      '#options' => user_roles(),
      '#multiple' => TRUE,
    );
  }*/
  if (module_exists('token')) {
    $form['filename_tokens'] = array(
      '#type' => 'textfield',
      '#title' => t('Filename replacement tokens'),
      '#description' => t('Include tokens for filename replacement.'),
      '#default_value' => '[title]',
      '#required' => TRUE,
    );
    $form['tokens'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available tokens'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['tokens']['values'] = array(
      '#type' => 'markup',
      '#value' => theme('token_help', 'node'),
    ); 
  }
  // add setting to switch on hose_soap for this profile
  if (module_exists('hose_soap')) {
  	$form['settings']['hose_soap_enabled'] = array(
  		'#type' => 'checkbox',
  		'#title' => t('Enable SOAP service'),
  		'#description' => t('The Hose Soap module will expose a SOAP method to get the contents of a node 
  			using this profile'),
  	);
  	$form['settings']['hose_soap_method'] = array(
  		'#type' => 'textfield',
  		'#title' => t('SOAP service method name'),
  		'#description' => t('The name of the SOAP method to get the contents of a node using this profile'),
  	);   		 
  }
  return confirm_form($form, t('Create New Profile'), 'admin/settings/hose_xml/profiles', ' ', t('Confirm'), t('Cancel'));
} // hose_xml_ui_profile_add

function hose_xml_ui_profile_add_validate(&$form, &$form_state) {
  $form_values = $form_state['values'];
  if (!preg_match("/^[0-9a-zA-Z._\- ]+$/", $form_values['name'])) {
    form_set_error('name', t("Error: Profile Name field contains invalid characters."));
  }
  if (db_result(db_query("SELECT pid FROM {hose_xml_profiles} WHERE name = '%s'", $form_values['name']))) {
    form_set_error('name', t("Error: Profile Name is not unique."));
  }
} // hose_xml_ui_profile_add_validate

/**
 * Add Profile submit callback.
 */
function hose_xml_ui_profile_add_submit($form, &$form_state) {
  global $user;
  $form_values = $form_state['values'];
 $elements = element_children($form['settings']);
	foreach ($elements as $name) {
  	$settings[$name] = $form_values[$name];
  }
  
  if ($flag = db_query("
  	INSERT INTO {hose_xml_profiles} (uid, name, description, created, changed, filename_tokens, settings) 
  	VALUES (%d, '%s', '%s', %d, %d, '%s', '%s')",
    $user->uid,
    $form_values['name'],
    $form_values['desc'],
    time(),
    time(),
    $form_values['filename_tokens'],
    serialize($settings)
  )) {
    $pid = db_last_insert_id('hose_xml_profiles', 'pid');
    if (!db_query("INSERT INTO {hose_xml_profile_data} (pid, title, description,	tag,	type,	required,	attributes,	weight) VALUES (%d, '%s', '%s', '%s', '%s', %d, '%s', %d)", $pid, 'XML Processing Instruction', 'The character encoding of your document.', 'xml', 'special', TRUE, serialize(array(array('attribute-attribute' => 'version', 'attribute-value' => $form_values['xmlversion'], 'attribute-required' => TRUE), array('attribute-attribute' => 'encoding', 'attribute-value' => $form_values['encoding'], 'attribute-required' => TRUE))))) {
      $flag = FALSE;
    }
    foreach ($form_values['types'] as $type) {
      if (!db_query("INSERT INTO {hose_xml_profile_association} (pid, type) VALUES (%d, '%s')", $pid, $type)) {
        $flag = FALSE;
      }
    }
  }
  if (!$flag) {
    drupal_set_message(t('Error creating new profile. Please contact your <a href="mailto:!sysadmin">System Administrator</a>', array('!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  else {
    // Success!
    drupal_set_message(t("Profile '@profile' created.", array('@profile' => $form_values['name'])));
  }


  if (isset($pid)) {
    // Pass pid back in so other modules know what we're working with
    $form_state['values']['pid'] = $pid;
  }
  $form_state['redirect'] = 'admin/settings/hose_xml/profiles';
} // hose_xml_ui_profile_add_submit

/**
 * Edit Profile callback.
 */
function hose_xml_ui_profile_edit(&$form_state, $profile) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t("The human-readable name of this profile. It is recommended that this name begin with a capital letter and contain only alphanumeric characters. This name should be unique."),
    '#required' => TRUE,
    '#default_value' => $profile->name,
  );
  $form['desc'] = array(
    '#type' => 'textfield',
    '#title' => t("Description"),
    '#description' => t("Optional - a brief description of this profile."),
    '#default_value' => $profile->description,
  );
  $types = hose_xml_export_fetch_types($profile->pid);
  $form['types'] = array(
    '#type' => 'select',
    '#title' => t('Node type associations'),
    '#description' => t('Please select which node types this profile can be used with.'),
    '#options' => array_map('filter_xss', node_get_types('names')),
    '#multiple' => TRUE,
    '#default_value' => $types,
  );
  if (variable_get('hose_xml_use_permissions', FALSE) && user_access('administer permissions')) {
    $form['roles'] = array(
      '#type' => 'select',
      '#title' => t('User Permissions'),
      '#description' => t('User access to this profile, to alter please follow this link to the <a href="@url">Drupal permissions</a> page.<br /><strong>It is your responsibility to ensure you select a role you have access to, else you will not be able to access this profile after you click confirm.</strong>', array('@url' => url('admin/user/permissions', array('fragment' => 'module-hose_xml')))),
      '#options' => user_roles(),
      '#multiple' => TRUE,
      '#default_value' => array_flip(user_roles(FALSE, _hose_xml_perm_export_profiles($profile->name))),
      '#disabled' => TRUE,
    );
  }
  if (module_exists('token')) {
    $form['filename_tokens'] = array(
      '#type' => 'textfield',
      '#title' => t('Filename replacement tokens'),
      '#description' => t('Include tokens for filename replacement.'),
      '#default_value' => isset($profile->filename_tokens) ? $profile->filename_tokens : '[title]',
      '#required' => TRUE,
    );
    $form['tokens'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available tokens'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['tokens']['values'] = array(
      '#type' => 'markup',
      '#value' => theme('token_help'),
    );
  }
	// add setting to switch on hose_soap for this profile
  if (module_exists('hose_soap')) {
  	$form['settings']['hose_soap_enabled'] = array(
  		'#type' => 'checkbox',
  		'#title' => t('Enable SOAP service'),
  		'#description' => t('The Hose Soap module will expose a SOAP method to get the contents of a node 
  			using this profile'),
  		'#default_value' => $profile->settings['hose_soap_enabled'],
  	);
  	$form['settings']['hose_soap_method'] = array(
  		'#type' => 'textfield',
  		'#title' => t('SOAP service method name'),
  		'#description' => t('The name of the SOAP method to get the contents of a node using this profile'),
  		'#default_value' => $profile->settings['hose_soap_method'],
  	);   		 
  }
  
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $profile->pid,
  );

  return confirm_form(
    $form, 
    t("Edit Profile '@profile'", array('@profile' => $profile->name)), 
    'admin/settings/hose_xml/profiles', 
    ' ', 
    t('Confirm'),
    t('Cancel')
  );
} // hose_xml_ui_profile_edit

function hose_xml_ui_profile_edit_validate(&$form, &$form_state) {
  $form_values = $form_state['values'];
  if (!preg_match("/^[0-9a-zA-Z._\- ]+$/", $form_values['name'])) {
    form_set_error('name', t("Error: Profile Name field contains invalid characters."));
  }
  if (($pid = db_result(db_query("SELECT pid FROM {hose_xml_profiles} WHERE name = '%s'", $form_values['name']))) && $pid != $form_values['pid']) {
    form_set_error('name', t("Error: Profile Name is not unique."));
  }
} // hose_xml_ui_profile_edit_validate

/**
 * Edit Profile submit callback.
 */
function hose_xml_ui_profile_edit_submit($form, &$form_state) {
	$form_values = $form_state['values'];
	$elements = element_children($form['settings']);
	foreach ($elements as $name) {
  	$settings[$name] = $form_values[$name];
  }
  if (db_query("
    UPDATE {hose_xml_profiles} 
    SET name = '%s', description = '%s', changed = %d, filename_tokens = '%s', settings = '%s' 
    WHERE pid = %d", 
      $form_values['name'], 
      $form_values['desc'], 
      time(), 
      $form_values['filename_tokens'], 
      serialize($settings),
      $form_values['pid'] )) {
    // Flush current values
    db_query("DELETE FROM {hose_xml_profile_association} WHERE pid = %d", $form_values['pid']);
    foreach ($form_values['types'] as $type) {
      db_query("INSERT INTO {hose_xml_profile_association} (pid, type) VALUES (%d, '%s')", $form_values['pid'], $type);
    }
    watchdog('hose_xml_ui', "Profile '@profile' successfully altered.", array('@profile' => $form_values['name']), WATCHDOG_INFO, l(t('view'), "hose_xml/profiles/". $form_values['pid'] ."/view"));
    drupal_set_message(t("Changes to profile '@profile' have been saved.", array('@profile' => $form_values['name'])));
  }
  else {
    watchdog('hose_xml_ui', "Error altering profile '@profile'.", array('@profile' => $form_values['name']), WATCHDOG_INFO, l(t('view'), "hose_xml/profiles/". $form_values['pid'] ."/view"));
    drupal_set_message(t('Error editing profile \'@profile\'. Please contact your <a href="mailto:!sysadmin">System Administrator</a>', array('@profile' => $form_values['name'], '!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  $form_state['redirect'] = 'admin/settings/hose_xml/profiles';
} // hose_xml_ui_profile_edit_submit

/**
 * Delete Profile callback.
 */
function hose_xml_ui_profile_delete(&$form_state, $profile) {
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $profile->pid,
  );
  $form['name'] = array(
    '#type' => 'hidden',
    '#value' => $profile->name,
  );

  return confirm_form($form, t("Are you sure you want to delete the profile '@profile'?", array('@profile' => $profile->name)), 'admin/settings/hose_xml/profiles', NULL, t('Delete'), t('Cancel'));
} // hose_xml_ui_profile_delete

/**
 * Delete Profile submit callback.
 */
function hose_xml_ui_profile_delete_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  if (db_query("DELETE FROM {hose_xml_profiles} WHERE pid = %d", $form_values['pid']) && db_query("DELETE FROM {hose_xml_profile_data} WHERE pid = %d", $form_values['pid'])) {
    drupal_set_message(t("Profile '@profile' has been deleted.", array('@profile' => $form_values['name'])));
  }
  else {
    drupal_set_message(t('Error deleting profile \'@profile\'. Please contact your <a href="mailto:!sysadmin">System Administrator</a>', array('@profile' => $form_values['name'], '!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  module_invoke_all('hose_xml_ui_profile_delete', $form_values['pid']);
  $form_state['redirect'] = 'admin/settings/hose_xml/profiles';
} // hose_xml_ui_profile_delete_submit

/**
 * Clone Profile callback.
 */
function hose_xml_ui_profile_clone(&$form_state, $profile) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t("The human-readable name of this profile. It is recommended that this name begin with a capital letter and contain only alphanumeric characters. This name should be unique."),
    '#required' => TRUE,
    '#default_value' => sprintf("Copy of %s", $profile->name),
  );
  $form['desc'] = array(
    '#type' => 'textfield',
    '#title' => t("Description"),
    '#description' => t("Optional - a brief description of this profile."),
    '#default_value' => $profile->description,
  );
  $form['types'] = array(
    '#type' => 'select',
    '#title' => t('Node type associations'),
    '#description' => t('Please select which node types this profile can be used with.'),
    '#options' => array_map('filter_xss', node_get_types('names')),
    '#multiple' => TRUE,
    '#default_value' => hose_xml_fetch_types($profile->pid),
  );
  if (module_exists('token')) {
    $form['filename_tokens'] = array(
      '#type' => 'textfield',
      '#title' => t('Filename replacement tokens'),
      '#description' => t('Include tokens for filename replacement.'),
      '#default_value' => isset($profile->filename_tokens) ? $profile->filename_tokens : '[title]',
      '#required' => TRUE,
    );
    $form['tokens'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available tokens'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['tokens']['values'] = array(
      '#type' => 'markup',
      '#value' => theme('token_help'),
    );
  }
  
  // add setting to switch on hose_soap for this profile
  if (module_exists('hose_soap')) {
  	$form['settings']['hose_soap_enabled'] = array(
  		'#type' => 'checkbox',
  		'#title' => t('Enable SOAP service'),
  		'#description' => t('The Hose Soap module will expose a SOAP method to get the contents of a node 
  			using this profile'),
  		'#default_value' => $profile->settings['hose_soap_enabled'],
  	);
  	$form['settings']['hose_soap_method'] = array(
  		'#type' => 'textfield',
  		'#title' => t('SOAP service method name'),
  		'#description' => t('The name of the SOAP method to get the contents of a node using this profile'),
  		'#default_value' => $profile->settings['hose_soap_method'],
  	);   		 
  }
  
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $profile->pid,
  );

  return confirm_form($form, t("Clone profile '@profile':", array('@profile' => $profile->name)), 'admin/settings/hose_xml/profiles', ' ', t('Create'), t('Cancel'));
} // hose_xml_ui_profile_clone

function hose_xml_ui_profile_clone_validate(&$form, &$form_state) {
  $form_values = $form_state['values'];
  if (!preg_match("/^[0-9a-zA-Z._\- ]+$/", $form_values['name'])) {
    form_set_error('name', t("Error: Profile Name field contains invalid characters."));
  }
  if (db_result(db_query("SELECT pid FROM {hose_xml_profiles} WHERE name = '%s'", $form_values['name']))) {
    form_set_error('name', t("Error: Profile Name is not unique."));
  }
} // hose_xml_ui_profile_clone_validate

/**
 * Clone Profile submit callback.
 */
function hose_xml_ui_profile_clone_submit($form, &$form_state) {
  global $user;
  $form_values = $form_state['values'];
  	$elements = element_children($form['settings']);
	foreach ($elements as $name) {
  	$settings[$name] = $form_values[$name];
  }
  
  if ($flag = db_query("
  	INSERT INTO {hose_xml_profiles} (uid, name, description, created, changed, filename_tokens) 
  	VALUES (%d, '%s', '%s', %d, %d, '%s')", 
  	$user->uid, 
  	$form_values['name'], 
  	$form_values['desc'], 
  	time(), 
  	time(), 
  	$form_values['filename_tokens'],
  	serialize($settings))) {
    $query = db_query("SELECT * FROM {hose_xml_profile_data} WHERE pid = %d", $form_values['pid']);
    $pid = db_last_insert_id('hose_xml_ui_profiles', 'pid');
    while ($fetch = db_fetch_object($query)) {
      $insert = db_query("
        INSERT INTO {hose_xml_profile_data} 
        (pid, did, title, description, cck_match, tag, type, settings, defaults, attributes, required, relies_on, weight, cdata) 
        VALUES (%d, %d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %d, '%s', %d, %d)",
        $pid,
        $sauce[$fetch->did] ? $sauce[$fetch->did] : 0,
        $fetch->title,
        $fetch->description,
        $fetch->cck_match,
        $fetch->tag,
        $fetch->type,
        $fetch->settings,
        $fetch->defaults,
        $fetch->attributes,
        $fetch->required,
        $fetch->relies_on,
        $fetch->weight,
        $fetch->cdata
      );
      $sauce[$fetch->id] = db_last_insert_id('hose_xml_ui_profile_data', 'id');
      // Was query successful?
      if (!$insert) {
        $flag = FALSE;
      }
    }
    // Now do the node associations - moved as this should ONLY take place if $flag is TRUE
    foreach ($form_values['types'] as $type) {
      if (!db_query("INSERT INTO {hose_xml_profile_association} (pid, type) VALUES (%d, '%s')", $pid, $type)) {
        $flag = FALSE;
      }
    }
  }
  if (!$flag) {
    drupal_set_message(t("Error cloning profile '@profile'. Please contact your <a href=\"mailto:!sysadmin\">System Administrator</a>.", array('@profile' => $form_values['name'], '!sysadmin' => variable_get('site_mail', ini_get('sendmail_from')))));
  }
  else {
    // Success!
    drupal_set_message(t("Profile '@profile' successfully created.", array('@profile' => $form_values['name'])));
  }
  
  if (isset($pid)) {
    // Pass pid back in so other modules know what we're working with
    $form_state['values']['pid'] = $pid;
  }
  $form_state['redirect'] = 'admin/settings/hose_xml/profiles';
} // hose_xml_ui_profile_clone_submit

/**
 * @} End of "ingroup hose_xml_ui_mod".
 */
