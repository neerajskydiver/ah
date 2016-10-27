<?php
// $Id: ah_accordion.views.inc,v 1.1 2009/01/29 00:47:59 manuelgarcia Exp $
/**
 * @file
 * Provide an accordion style plugin for Views. This file is autoloaded by views.
 */

/**
  * Implementation of hook_views_plugin().
  */
function ah_accordion_views_plugins() {
  return array(
    'style' => array(
      'ah_accordion' => array(
        'title' => t('AH Accordion'),
        'theme' => 'views_view_accordion',
        'help' => t('Display a JQuery accordion with the results. The first field will be used as the header and trigger.'),
        'handler' => 'ah_accordion_style_plugin',
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}

