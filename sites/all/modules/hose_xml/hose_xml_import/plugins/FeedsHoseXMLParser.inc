<?php
// $Id$

require_once './' . drupal_get_path('module', 'hose_xml_import') . "/hose_xml_to_array.inc";

/**
 * Parses a given file as an XML file.
 */
class FeedsHoseXMLParser extends FeedsParser {

  /**
   * Implementation of FeedsParser::parse().
   */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
    $filepath = realpath($batch->getFilePath());
    // Use XML Parser to parse the file and return a formatted PHP array.
    $xml_string = hose_xml_load_file($filepath);
    if ($xml_string === FALSE) {
      watchdog('FeedsHoseXMLParser', t('Could not open XML file: @file', array('@file' => $filepath)), array(), WATCHDOG_ERROR);
      return FALSE;
    }

    // convert the XML string into an array
    $rows = xml2array($xml_string);
    if (!empty($this->config['rows_parent_path'])) {
      $rows = get_value_by_path($rows, $this->config['rows_parent_path']);
      // get rid of metadata keys (keys starting with '#')
      $rows = array_intersect_key($rows, array_flip(element_children($rows)));
    }
    // Populate batch.
    $batch->setItems($rows);
  }

  /**
   * Define defaults.
   */
  public function configDefaults() {
    return array(
      'rows_parent_path' => NULL,
    );
  }

  /**
   * Return configuration form for this object. The keys of the configuration
   * form must match the keys of the array returned by configDefaults().
   *
   * @return
   *   FormAPI style form definition.
   */
  public function configForm(&$form_state) {
    $form = array();
    $form['rows_parent_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Rows parent path'),
      '#description' => t('In the form of "tag/subtag/subsubtag" specify where the elements should be looked for.'),
      '#default_value' => $this->config['rows_parent_path'],
    );
    return $form;
  }

  /**
   * Validation handler for configForm().
   *
   * Set errors with form_set_error().
   *
   * @param $values
   *   An array that contains the values entered by the user through configForm.
   */
  public function configFormValidate(&$values) {
    if (!empty($values['rows_parent_path'])) {
      $values['rows_parent_path'] = trim($values['rows_parent_path'], '/');
    }
  }
}