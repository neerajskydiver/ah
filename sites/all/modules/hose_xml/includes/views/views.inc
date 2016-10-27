<?php

/**
 * @file
 * Handles integration with the views module.
 * 
 * @ingroup hose_xml_core
 */

/**
 * Implementation of hook_views_api().
 */
function hose_xml_views_api() {
  return array('api' => 2.0, 'path' => drupal_get_path('module', 'hose_xml') . '/includes/views');
} // hose_xml_views_api

/**
 * Implementation of hook_views_default_views().
 */
function hose_xml_views_default_views() {
  $files = file_scan_directory(drupal_get_path('module', 'hose_xml'). '/includes/views', '.view');
  foreach ($files as $absolute => $file) {
    require($absolute);
    if (isset($view)) {
      $views[substr($file->name, 5)] = $view;
    }
  }
  return $views;
} // hose_xml_views_default_views