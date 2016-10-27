<?php


/**
 * Edit feed configuration.
 */
function hose_feeds_ui_edit_page($importer_id, $active = 'help', $plugin_key = '') {
  $importer = feeds_importer_load($importer_id);
  // Get plugins and configuration.
  $plugins = feeds_get_plugins();
  $config = $importer->config;
  // Base path for changing the active container.
  $path = 'admin/build/feeds/edit/'. $importer->id;

  $active_container = array(
    'class' => 'active-container',
    'actions' => array(l(t('Help'), $path)),
  );
  switch ($active) {
    case 'mapping':
      require_once(drupal_get_path('module', 'hose_xml_ui') . '/includes/admin.inc');
      $active_container['title'] = t('Mapping for !processor', array('!processor' => $plugins[$config['processor']['plugin_key']]['name']));

      $hose_xml_profile = hose_xml_profile_load($config['processor']['config']['hosexml_profile']);
      if ($hose_xml_profile) {
        $active_container['body'] = drupal_get_form('hose_xml_ui_profile_view', $hose_xml_profile);
      }
      else {
        $active_container['body'] = t(
          'No Hose XML profile selected or it doesn\'t exist.<br />' .
          'Please go to !settings_link and select a Hose XML Profile',
          array('!settings_link' => l(t('Settings page'), 'admin/build/feeds/edit/'. $importer_id .'/settings/'. $config['processor']['plugin_key']))
        );
      }
      break;
  }

  // Build config info.
  $config_info = $info = array();
  $info['class'] = 'config-set';

  // Basic information.
  $items = array();
  $items[] = t('Attached to: !type', array('!type' => $importer->config['content_type'] ? node_get_types('name', $importer->config['content_type']) : t('[none]')));
  if ($importer->config['import_period'] == FEEDS_SCHEDULE_NEVER) {
    $import_period = t('never');
  }
  elseif ($importer->config['import_period'] == 0) {
    $import_period = t('as often as possible');
  }
  else {
    $import_period = t('every !interval', array('!interval' => format_interval($importer->config['import_period'])));
  }
  $items[] = t('Refresh: !import_period', array('!import_period' => $import_period));
  $items[] = $importer->config['import_on_create'] ? t('Import on create') : t('Do not import on create');

  $info['title'] = t('Basic settings');
  $info['body'] = array(
    array(
      'body' => theme('item_list', $items),
      'actions' => array(l(t('Settings'), $path .'/settings')),
    ),
  );
  $config_info[] = $info;

  // Fetcher.
  $fetcher = $plugins[$config['fetcher']['plugin_key']];
  $actions = array();
  if (feeds_get_form($importer->fetcher, 'configForm')) {
    $actions = array(l(t('Settings'), $path .'/settings/'. $config['fetcher']['plugin_key']));
  }
  $info['title'] = t('Fetcher');
  $info['body'] = array(
    array(
      'title' => $fetcher['name'],
      'body' => $fetcher['description'],
      'actions' => $actions,
    ),
  );
  $info['actions'] = array(l(t('Change'), $path .'/fetcher'));
  $config_info[] = $info;

  // Parser.
  $parser = $plugins[$config['parser']['plugin_key']];
  $actions = array();
  if (feeds_get_form($importer->parser, 'configForm')) {
    $actions = array(l(t('Settings'), $path .'/settings/'. $config['parser']['plugin_key']));
  }
  $info['title'] = t('Parser');
  $info['body'] = array(
    array(
      'title' => $parser['name'],
      'body' => $parser['description'],
      'actions' => $actions,
    )
  );
  $info['actions'] = array(l(t('Change'), $path .'/parser'));
  $config_info[] = $info;

  // Processor.
  $processor = $plugins[$config['processor']['plugin_key']];
  $actions = array();
  if (feeds_get_form($importer->processor, 'configForm')) {
    $actions[] = l(t('Settings'), $path .'/settings/'. $config['processor']['plugin_key']);
  }
  $actions[] = l(t('Mapping'), $path .'/mapping');
  $info['title'] = t('Processor');
  $info['body'] = array(
    array(
      'title' => $processor['name'],
      'body' => $processor['description'],
      'actions' => $actions,
    )
  );
  $info['actions'] = array(l(t('Change'), $path .'/processor'));
  $config_info[] = $info;

  return theme('feeds_ui_edit_page', $config_info, $active_container);
}

function hose_feeds_ui_mapping_form(&$form_state, $importer) {
  require_once(drupal_get_path('module', 'feeds_ui') . '/feeds_ui.admin.inc');
  drupal_add_js(drupal_get_path('module', 'feeds_ui') .'/feeds_ui.js');

  $form = array();
  $form['#importer'] = $importer;
  $form['#mappings'] = $mappings = $importer->processor->getMappings();
  $form['help']['#value'] = feeds_ui_mapping_help();

  // Get mapping sources from parsers and targets from processor, format them
  // for output.
  // Some parsers do not define mapping sources but let them define on the fly.
  if ($sources = $importer->parser->getMappingSources()) {
    $source_options = _feeds_ui_format_options($sources);
    foreach ($sources as $k => $source) {
      $legend['sources'][$k]['name']['#value'] = empty($source['name']) ? $k : $source['name'];
      $legend['sources'][$k]['description']['#value'] = empty($source['description']) ? '' : $source['description'];
    }
  }
  else {
    $legend['sources']['#value'] = t('This parser supports free source definitions. Enter the name of the source field in lower case into the Source text field above.');
  }
  $targets = $importer->processor->getMappingTargets();
  $target_options = _feeds_ui_format_options($targets);
  foreach ($targets as $k => $target) {
    $legend['targets'][$k]['name']['#value'] = empty($target['name']) ? $k : $target['name'];
    $legend['targets'][$k]['description']['#value'] = empty($target['description']) ? '' : $target['description'];
  }

  // Legend explaining source and target elements.
  $form['legendset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Legend'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );
  $form['legendset']['legend'] = $legend;

  // Add unique and remove forms to mappings.
  $form['unique_flags'] = $form['remove_flags'] = array(
    '#tree' => TRUE,
  );
  if (is_array($mappings)) {
    foreach ($mappings as $i => $mapping) {
      $param = array(
        'processor' => $importer->processor,
        'mapping' => $mapping,
      );
      if (isset($targets[$mapping['target']]['optional_unique']) && $targets[$mapping['target']]['optional_unique'] === TRUE) {
        $form['unique_flags'][$i] = array(
          '#type' => 'checkbox',
          '#default_value' => !empty($mapping['unique']),
          '#attributes' => array('class' => 'feeds-ui-trigger-submit'),
        );
      }
      $form['remove_flags'][$i] = array(
        '#type' => 'checkbox',
        '#title' => t('Remove'),
        '#prefix' => '<div class="feeds-ui-checkbox-link">',
        '#suffix' => '</div>',
      );
    }
  }

  if ($source_options) {
    $form['source'] = array(
      '#type' => 'select',
      '#options' => array('' => t('Select a source')) + $source_options,
    );
  }
  else {
    $form['source'] = array(
      '#type' => 'textfield',
      '#size' => 20,
      '#default_value' => t('Name of source field'),
      '#attributes' => array('class' => 'hide-text-on-focus'),
    );
  }
  $form['target'] = array(
    '#type' => 'select',
    '#options' => array('' => t('Select a target')) + $target_options,
  );
  $form['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#submit' => array('hose_feeds_ui_mapping_form_add_submit'),
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array('class' => 'feeds-ui-hidden-submit'),
  );
  return $form;
}

/**
 * Submit handler for add button on feeds_ui_mapping_form().
 */
function hose_feeds_ui_mapping_form_add_submit($form, &$form_state) {
  $importer = $form['#importer'];
  try {
    $mappings = $form['#mappings'];
    $mappings[] = array(
      'source' => $form_state['values']['source'],
      'target' => $form_state['values']['target'],
      'unique' => FALSE,
    );
    $importer->processor->addConfig(array('mappings' => $mappings));
    $importer->processor->save();
    drupal_set_message(t('Mapping has been added.'));
  }
  catch (Exception $e) {
    drupal_set_message($e->getMessage(), 'error');
  }
}

/**
 * Submit handler for save button on feeds_ui_mapping_form().
 */
function hose_feeds_ui_mapping_form_submit($form, &$form_state) {
  $processor = $form['#importer']->processor;
  // We may set some unique flags to mappings that we remove in the subsequent
  // step, that's fine.
  $mappings = $form['#mappings'];
  if (isset($form_state['values']['unique_flags'])) {
    foreach ($form_state['values']['unique_flags'] as $k => $v) {
      $mappings[$k]['unique'] = $v;
    }
  }

  foreach ($form_state['values']['remove_flags'] as $k => $v) {
    if ($v) {
      unset($mappings[$k]);
      // Keep our keys clean.
      $mappings = array_values($mappings);
    }
  }
  $processor->addConfig(array('mappings' => $mappings));
  $processor->save();
  drupal_set_message(t('Your changes have been saved.'));
}

/**
 * Theme function for feeds_ui_mapping_form().
 */
function theme_hose_feeds_ui_mapping_form($form) {

  // Build the actual mapping table.
  $header = array(
    t('Source'),
    t('Target'),
    t('Unique target'),
    '&nbsp;',
  );
  $rows = array();
  if (is_array($form['#mappings'])) {
    foreach ($form['#mappings'] as $i => $mapping) {
      // Some parsers do not define source options.
      $source = isset($form['source']['#options'][$mapping['source']]) ? $form['source']['#options'][$mapping['source']] : $mapping['source'];
      $rows[] = array(
        check_plain($source),
        check_plain($form['target']['#options'][$mapping['target']]),
        drupal_render($form['unique_flags'][$i]),
        drupal_render($form['remove_flags'][$i]),
      );
    }
  }
  if (!count($rows)) {
    $rows[] = array(
      array(
        'colspan' => 4,
        'data' => t('No mappings defined.'),
      ),
    );
  }
  $rows[] = array(
    drupal_render($form['source']),
    drupal_render($form['target']),
    '',
    drupal_render($form['add']),
  );
  $output = '<div class="help feeds-admin-ui""'. drupal_render($form['help']) .'</div>';
  $output .= theme('table', $header, $rows);

  // Build the help table that explains available sources.
  $legend = '';
  $rows = array();
  foreach (element_children($form['legendset']['legend']['sources']) as $k) {
    $rows[] = array(
      check_plain(drupal_render($form['legendset']['legend']['sources'][$k]['name'])),
      check_plain(drupal_render($form['legendset']['legend']['sources'][$k]['description'])),
    );
  }
  if (count($rows)) {
    $legend .= '<h4>'. t('Sources') .'</h4>';
    $legend .= theme('table', array(t('Name'), t('Description')), $rows);
  }

  // Build the help table that explains available targets.
  $rows = array();
  foreach (element_children($form['legendset']['legend']['targets']) as $k) {
    $rows[] = array(
      check_plain(drupal_render($form['legendset']['legend']['targets'][$k]['name'])),
      check_plain(drupal_render($form['legendset']['legend']['targets'][$k]['description'])),
    );
  }
  $legend .= '<h4>'. t('Targets') .'</h4>';
  $legend .= theme('table', array(t('Name'), t('Description')), $rows);

  // Stick tables into collapsible fieldset.
  $form['legendset']['legend'] = array(
    '#value' => '<div>'. $legend .'</div>',
  );

  $output .= drupal_render($form['legendset']);

  $output .= drupal_render($form);
  return $output;
}

