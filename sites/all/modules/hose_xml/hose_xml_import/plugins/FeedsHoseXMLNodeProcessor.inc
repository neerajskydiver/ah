<?php

require_once './' . drupal_get_path('module', 'feeds') . "/plugins/FeedsNodeProcessor.inc";

class FeedsHoseXMLNodeProcessor extends FeedsNodeProcessor {

  protected $hose_profile;
  protected $field_map_import_hooks = array();

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'hosexml_profile' => NULL,
      'rows_parent_path' => NULL,
    ) + parent::configDefaults();
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = array();
    $hosexml_profiles = array();
    foreach (hose_xml_fetch_profiles () as $profile_id => $profile) {
      $hosexml_profiles[$profile_id] = $profile->name;
    }
    $form['hosexml_profile'] = array(
      '#type' => 'select',
      '#title' => t('Hose XML Profile'),
      '#description' => t('Select the hose xml profile to manage this import.'),
      '#options' => $hosexml_profiles,
      '#default_value' => $this->config['hosexml_profile'],
    );
    $form += parent::configForm($form_state);
    return $form;
  }

  /**
   * Implementation of FeedsProcessor::process().
   */
  public function process(FeedsImportBatch $batch, FeedsSource $source) {
    $this->init_field_map_import_hooks();

    $this->transformHoseXMLConfigMappings();

    parent::process($batch, $source);
  }

  /**
   *
   * @param FeedsImportBatch $batch
   *   The batch
   * @param <type> $target_item
   *  In this case $target_item is a $node object
   */
  protected function map(FeedsImportBatch $batch, $target_item = NULL) {
    /**
     * This is really really ugly... But we need to make the built node global
     * so that other hooks in hose_xml_import can use it.
     * Normally this is used by the hose_xml_reference submodule so that
     * nodes created by it are added to the {feeds_node_item} table by feeds.
     */
    _hose_feeds_blank_node_instance($target_item);

    $current_item = $batch->currentItem();
    // $target_item is the $node
    hose_xml_import_node_map_recurse($target_item, $current_item, $this->hose_profile);
  }

  public function transformHoseXMLConfigMappings() {
    $this->loadHoseProfile($this->config['hosexml_profile']);
    foreach ($this->hose_profile as $hose_field) {
      $this->config['mappings'][] = array(
        'source' => $hose_field->tag,
        'target' => $hose_field->cck_match,
        'unique' => FALSE,
      );
    }
  }

  public function loadHoseProfile($pid) {
    $this->hose_profile = hose_xml_get_export_config_flat($pid, 0, -1, NULL, FALSE, TRUE);
    return $this->hose_profile;
  }

  private function init_field_map_import_hooks() {
    foreach(module_implements('hose_xml_field_map_import') as $module) {
      $this->field_map_import_hooks[] = $module . '_hose_xml_field_map_import';
    }
  }

}

function hose_xml_import_node_map_recurse($node, $current_item, $hose_profile) {
  static $import_hooks;

  if (!isset($import_hooks)) {
    $import_hooks = array();
    foreach(module_implements('hose_xml_field_map_import') as $module) {
      $import_hooks[] = $module . '_hose_xml_field_map_import';
    }
  }

  // loop through all the hose_profile items and search the tag_path in the request_arr
  foreach($hose_profile as $item_profile) {
    if ($item_profile->type == 'special' && $item_profile->tag_path == 'xml') {
      continue;
    }

    $value_by_path = xml_array_get_value_by_path($current_item, $item_profile->tag_path);
    if ($value_by_path === FALSE) {
      continue;
    }

      foreach($import_hooks as $function) {
      $function($node, $value_by_path, $current_item, $item_profile);
      }
    if (is_array($value_by_path)) {
      hose_xml_import_node_map_recurse($node, $value_by_path, $hose_profile);
    }
  }
  }

function hose_xml_import_value_mapping_profile(array &$import_item, stdClass $item_profile) {
  // first check for attributes
  if (!empty($item_profile->attributes) && !empty($import_item['#attributes'])) {
    foreach($item_profile->attributes as $profile_attrs) {
      $profile_attr_name = $profile_attrs['attribute-attribute'];
      if (!empty($import_item['#attributes'][$profile_attr_name])) {
        return $import_item['#attributes'][$profile_attr_name];
      }
    }
  }

  // check for value
  if (!empty($import_item['#value'])) {
    return $import_item['#value'];
  }

  return NULL;
}

/**
 * FeedsHoseXMLNodeProcessor->map
 */
function _hose_feeds_blank_node_instance($new_node = NULL) {
  static $node;
  if (!empty($new_node)) {
    // drupal_clone doesn't work here. We need to perform a deep copy.
    $new_node = unserialize(serialize($new_node));
    unset($new_node->feeds_node_item->hash);
    $node = $new_node;
  }
  return !empty($node) ? unserialize(serialize($node)) : new stdClass();
}

