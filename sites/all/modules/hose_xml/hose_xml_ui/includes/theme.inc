<?php

/**
 * @file
 * Theme functions include file for the Hose XML UI module.
 * 
 * @ingroup hose_xml_ui_mod
 * @{
 */

/**
 * Returns a table containing all profiles.
 */
function theme_hose_xml_ui_profiles() {
  drupal_add_css(drupal_get_path('module', 'hose_xml') .'/misc/admin.css');

  // Define the table header
  $header = array(
    array('data' => t('Creator'), 'field' => 'u.name', 'id' => 'hose_xml-creator'),
    array('data' => t('Title'), 'field' => 'd.name', 'id' => 'hose_xml-name', 'sort' => 'asc'),
    array('data' => t('Description'), 'id' => 'hose_xml-description'),
    array('data' => t('Operations'), 'colspan' => 4, 'id' => 'hose_xml-operations'),
  );

  $query = db_query("SELECT d.*, u.name AS username FROM {hose_xml_profiles} d LEFT JOIN {users} u ON d.uid = u.uid". tablesort_sql($header));
  while ($profile = db_fetch_object($query)) {
    $rows[] = array(
      array('data' => l($profile->username, "user/$profile->uid"), 'class' => 'hose_xml-profile-uid'),
      array('data' => $profile->name, 'class' => 'hose_xml-profile-name'),
      array('data' => $profile->description, 'class' => 'hose_xml-profile-description'),
      array('data' => l(t('Manage'), "hose_xml/profiles/$profile->pid/view"), 'class' => 'hose_xml-operations-view'),
      array('data' => l(t('Edit'), "hose_xml/profiles/edit/$profile->pid"), 'class' => 'hose_xml-operations-edit'),
      array('data' => l(t('Delete'), "hose_xml/profiles/delete/$profile->pid"), 'class' => 'hose_xml-operation-delete'),
      array('data' => l(t('Clone'), "hose_xml/profiles/clone/$profile->pid"), 'class' => 'hose_xml-operation-delete'),
    );
  }
  if (!$rows) {
    return;
  }

  return theme('table', $header, $rows, array('id' => 'hose_xml-profile-table'));
} // theme_hose_xml_ui_profiles

/**
 * Plain theme function for the delete configuration row page.
 */
function theme_hose_xml_ui_profile_config($profile, $conf) {
  drupal_add_css(drupal_get_path('module', 'hose_xml') .'/misc/admin.css');

  // Define the table header
  $header = array(
    t('Title'),
    t('Description'),
    t('CCK Field'),
    t('Tag'),
    t('Type'),
    t('Ignore'),
    t('Container'),
    t('Required'),
    t('Attributes'),
    t('Settings'),
  );

  $conf = db_fetch_object(db_query("SELECT * FROM {hose_xml_profile_data} WHERE pid = %d && id = %d", $profile->pid, $conf->id));
  $row[] = array(
    array('data' => $conf->title, 'class' => 'hose_xml-config-title'),
    array('data' => check_plain($conf->description), 'class' => 'hose_xml-config-description'),
    array('data' => $conf->cck_match, 'class' => 'hose_xml-config-cck-match'),
    array('data' => check_plain($conf->tag), 'class' => 'hose_xml-config-tag'),
    array('data' => $conf->type, 'class' => 'hose_xml-config-type'),
    array('data' => hose_xml_ui_print_boolean($conf->ignore_field), 'class' => 'hose_xml-config-ignore-field'),
    array('data' => hose_xml_ui_print_boolean($conf->container), 'class' => 'hose_xml-config-container'),
    array('data' => hose_xml_ui_print_boolean($conf->required), 'class' => 'hose_xml-config-required'),
    array('data' => $conf->attributes ? $conf->attributes : '', 'class' => 'hose_xml-config-attributes'),
    array('data' => $conf->settings ? $conf->settings : '', 'class' => 'hose_xml-config-settings'),
  );

  return theme('table', $header, $row, array('id' => 'hose_xml-view-config'));
} // theme_hose_xml_ui_profile_config

function theme_hose_xml_ui_profile_view($form) {
  drupal_add_css(drupal_get_path('module', 'hose_xml') .'/misc/admin.css');
  drupal_add_tabledrag('hose_xml-view-table', 'match', 'parent', 'settings-did', 'settings-did', 'settings-id');
  drupal_add_tabledrag('hose_xml-view-table', 'order', 'sibling', 'settings-weight');
  $pid = $form['pid']['#value'];

  // Define the table header
  $header = array(
    t('Title'),
    t('Field Name'),
    t('Type'),
    t("Required/ Relies On"),
    t('Weight'),
    array('data' => t('Operations'), 'colspan' => 2, 'id' => 'hose_xml-operations'),
  );
  $tree = hose_xml_get_export_config_flat($pid);
  foreach (element_children($tree) as $index) {
    $form['settings'][$index]['id']['#attributes']['class'] = 'settings-id';
    $form['settings'][$index]['did']['#attributes']['class'] = 'settings-did';
    $form['settings'][$index]['weight']['#attributes']['class'] = 'settings-weight';
    $form['settings'][$index]['id']['#type'] = 'hidden';
    $type = drupal_render($form['settings'][$index]['type']);
    if (variable_get('hose_xml_ui_use_icons', FALSE) && $icon = module_invoke("hose_xml_$type", "hose_xml_field_icon")) {
      $name = module_invoke("hose_xml_$type", "hose_xml_field_name");
      $type = theme('image', $icon, "$name[$type] icon", $name[$type]);
    }

    $row = array(
      theme('indentation', $tree[$index]->depth) . drupal_render($form['settings'][$index]['title']) ." <em>&lt;". drupal_render($form['settings'][$index]['tag']) ."&gt;</em>",
      drupal_render($form['settings'][$index]['cck_match']),
      $type,
      array('data' => drupal_render($form['settings'][$index]['required']) . drupal_render($form['settings'][$index]['relies_on'])),
      drupal_render($form['settings'][$index]['weight']) . drupal_render($form['settings'][$index]['did']) . drupal_render($form['settings'][$index]['id']),
      array('data' => l(t('Edit'), "hose_xml/profiles/$pid/edit/$index"), 'class' => 'hose_xml-operations-edit'),
      array('data' => l(t('Delete'), "hose_xml/profiles/$pid/delete/$index"), 'class' => 'hose_xml-operation-delete'),

    );
    $rows[] = array(
      'data' => $row,
      'class' => $form['settings'][$index]['required']['#value'] ? 'draggable hose_xml-required' : 'draggable',
    );
  }

  if (!empty($rows)) {
    $output = '<p>'. theme('table', $header, $rows, array('id' => 'hose_xml-view-table'), drupal_render($form['description'])) .'</p>';
    $output .= drupal_render($form['bar']['save']);
  }
  else {
    $output = t('<p><strong>This profile has not yet been configured.</strong></p>');
    $form['bar']['#type'] = 'hidden';
  }

  $output .= '<div id="hose_xml-operations-new">';
  $output .= l(t('Add element'), "hose_xml/profiles/$pid/add");
  $output .= l(t('Use configuration wizard'), "hose_xml/profiles/$pid/wizard");
  if (module_exists('pimport')) {
    $output .= l(t('Export profile as CSV'), "hose_xml/profiles/$pid/export", array('query' => drupal_get_destination()));
    $output .= l(t('Import profile from CSV'), "hose_xml/profiles/$pid/import", array('query' => drupal_get_destination()));
  }
  $output .= '</div>';
  // render remaining form output
  $output .= drupal_render($form);

  return $output;
} // theme_hose_xml_ui_profile_view

function theme_hose_xml_ui_settings_profiles($form) {
  $output = drupal_render($form['profiles']);
  $output .= '<div id="hose_xml-operations-new">';
  if (user_access('create export profiles')) {
    $output .= l(t('Create new profile'), 'hose_xml/profiles/add');
  }
  $output .= '</div>';
  // render remaining form output
  $output .= drupal_render($form);

  return $output;
} // theme_hose_xml_ui_settings_profiles

function theme_hose_xml_ui_ahah_form($form) {
  // Change the button title to reflect the behavior when using JavaScript.
  drupal_add_js('if (Drupal.jsEnabled) { $(document).ready(function() { $("#edit-attribute-more").val("'. t('Add another attribute') .'"); }); }', 'inline');
  drupal_add_js(drupal_get_path('module', 'hose_xml_ui') .'/misc/delete.js');

  $rows = array();
  $headers = array(
    t('Attribute'),
    t('Value'),
    t('Required'),
  );

  foreach (element_children($form) as $key) {
    // No need to print the field title every time.
    unset($form[$key]['attribute-attribute']['#title'], $form[$key]['attribute-value']['#title']);
    // Build the table row.
    $row = array(
      'data' => array(
        array('data' => drupal_render($form[$key]['attribute-attribute']), 'class' => 'attribute-attribute'),
        array('data' => drupal_render($form[$key]['attribute-value']), 'class' => 'attribute-value'),
        array('data' => drupal_render($form[$key]['attribute-required']), 'class' => 'attribute-required'),
      ),
    );

    // Add additional attributes to the row, such as a class for this row.
    if (isset($form[$key]['#attributes'])) {
      $row = array_merge($row, $form[$key]['#attributes']);
    }
    $rows[] = $row;
  }

  $output = theme('table', $headers, $rows);
  // render any remaining form output
  $output .= drupal_render($form);
  return $output;
} // theme_hose_xml_ui_ahah_form

/**
 * @} End of "ingroup hose_xml_ui_mod".
 */