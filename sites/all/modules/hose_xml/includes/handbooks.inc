<?php

/**
 * @file
 * Handbook functionality for Hose XML module.
 */

/**
 * @defgroup hose_xml_handbooks_inc Handbooks
 * @{
 * Optionally allows display of export profiles in Handbook style, so users can search against tags
 * and receive all the associated relevant information for that tag.
 */

/**
 * Main handbook display page.
 */
function hose_xml_handbooks() {
  foreach (hose_xml_fetch_export_profiles() as $pid => $profile) {
    $list[] = l($profile, "hose_xml/handbooks/$pid");
  }
  return theme('item_list', $list);
} // hose_xml_handbooks

/**
 * Individual export handbook page.
 * 
 * @param $form_state
 *   Drupal form_state array.
 * @param $profile
 *   Hose XML export profile object.
 * 
 * @return
 *   Drupal form array for rendering.
 * 
 * @see hose_xml_export_handbooks_autocomplete()
 * @see theme_hose_xml_handbook_tag()
 */
function hose_xml_handbook($form_state, $profile) {
  drupal_set_title(t("Handbook for profile '@name'", array('@name' => $profile->name)));
  if ($tag = $form_state['post']['tag']) {
    $form['hose_xml_handbook']['info'] = array(
      '#type' => 'markup',
      '#value' => theme('hose_xml_handbook_tag', $profile->pid, $tag),
    );
  }
  $form['hose_xml_handbook']['tag'] = array(
    '#type' => 'textfield',
    '#title' => t('Tag'),
    '#description' => t('Enter a tag description here to learn more about it.'),
    '#autocomplete_path' => "hose_xml/handbooks/autocomplete/$profile->pid",
  );
  $form['hose_xml_handbook']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Display'),
  );
  $form['#redirect'] = FALSE;

  return $form;
} // hose_xml_handbook

/**
 * JSON callback for searching autocomplete in handbook pages.
 * 
 * @param $profile
 *   Hose XML export profile object.
 * @param $string
 *   Unescaped user input for searching through export titles.
 * 
 * @return
 *   Returns a JSON array of matches based on user search text.
 * 
 * @see hose_xml_handbook()
 */
function hose_xml_export_handbooks_autocomplete($profile, $string = '') {
  $matches = array();
  $result = db_query_range("SELECT title FROM {hose_xml_profile_data} WHERE LOWER(title) LIKE LOWER('%s%%') && pid = %d", $string, $profile->pid, 0, 10);
  if ($string) {
    while ($fetch = db_fetch_object($result)) {
      $matches[$fetch->title] = check_plain($fetch->title);
    }
  }
  drupal_json($matches);
} // hose_xml_export_handbooks_autocomplete

/**
 * Themes export tags.
 * 
 * @param $pid
 *   Numeric Hose XML export id.
 * @param $tag
 *   Unescaped user input tag match.
 * 
 * @return
 *   Rendered form output (HTML) containing tag information.
 * 
 * @see hose_xml_theme()
 * @see hose_xml_handbook()
 */
function theme_hose_xml_handbook_tag($pid, $tag) {
  drupal_add_css(drupal_get_path('module', 'hose_xml') .'/misc/handbooks.css');
  if (!($fetch = db_fetch_object(db_query("SELECT * FROM {hose_xml_profile_data} WHERE title = '%s' && pid = %d", $tag, $pid)))) {
    return '<div id="hose_xml-handbook" class="error">Invalid Tag</div>';
  }
  $output = '<div id="hose_xml-handbook">';
  $output .= '<div id="hose_xml-handbook-title">'. check_plain($fetch->title) .'</div>';
  $output .= '<div id="hose_xml-handbook-description">'. check_markup($fetch->description) .'</div>';
  $output .= '<div id="hose_xml-handbook-tag">Tag = '. check_plain($fetch->tag) .'</div>';

  if ($fetch->type == 'text' && $fetch->settings) {
    $output .= '<div id="hose_xml-handbook-char-limit">Character Limit = '. check_plain($fetch->settings) .'</div>';
  }
  if ($fetch->required) {
    $output .= '<div id="hose_xml-handbook-required">Required = '. theme_image('misc/watchdog-ok.png', t('Yes')) .'</div>';
  }
  else {
    $output .= '<div id="hose_xml-handbook-not-required">Required = '. theme_image('misc/watchdog-error.png', t('No')) .'</div>';
  }
  $output .= '</div>';
  // render any remaining output
  $output .= drupal_render($form);

  return $output;
} // theme_hose_xml_handbook_tag

/**
 * @} End of "defgroup hose_xml_handbooks_inc".
 */