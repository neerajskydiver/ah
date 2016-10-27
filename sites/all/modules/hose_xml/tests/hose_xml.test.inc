<?php
// $Id: hose_xml.test,v 1.1 2010/11/15 15:19:43 rayvaughn Exp $

/**
 * @file
 * Simpletest file for Hose XML module.
 *
 * These are simple add and delete profiles for;
 *  - Import profiles
 *  - Export profiles
 *  - Buckets
 * 
 * @ingroup hose_xml_core
 * @{
 */
require_once(drupal_get_path('module', 'feeds') . '/tests/feeds_mapper_test.inc');

class HoseXMLWebTestCase extends FeedsMapperTestCase {

  protected $hose_content_type;
  protected $url_hose_content_type;

  // A lookup map to select the widget for each field type.
  private static $field_widgets = array(
    'date' => 'date_text',
    'datestamp' => 'date_text',
    'datetime' => 'date_text',
    'number_decimal' => 'number',
    'email' => 'email_textfield',
    'emimage' => 'emimage_textfields',
    'emaudio' => 'emaudio_textfields',
    'filefield' => 'filefield_widget',
    'image' => 'imagefield_widget',
    'link' => 'link',
    'number_float' => 'number',
    'number_integer' => 'number',
    'nodereference' => 'nodereference_select',
    'text' => 'text_textfield',
    'userreference' => 'userreference_select',
   );

  protected $default_enabled_modules = array(
    'token', 'content', 'schema', 'fieldgroup', 'number', 'text',
    'nodereference', 'hose_xml',
    'hose_xml_ui', 'hose_xml_container', 'hose_xml_attribute', 'hose_xml_raw',
    'hose_xml_special', 'hose_xml_numeric', 'hose_xml_text',
    'hose_xml_boolean',
  );

  /**
   * Add XDEBUG_SESSION cookie, used for debugging.
   *
   * @return void
   */
  protected function curlInitialize() {
    $cookie_value = 'XDEBUG_PHPSTORM_SIMPLETEST';
    $cookie_string = 'XDEBUG_SESSION=' . $cookie_value . '; path=/';

    $this->additionalCurlOptions = array(
      CURLOPT_COOKIE => $cookie_string,
    );
    parent::curlInitialize();
  }

  protected function setUp() {
    $args = func_get_args();
    $modules = array_merge($this->default_enabled_modules, $args);
    call_user_func_array(array('parent','setUp'), $modules);
    module_load_include('inc', 'content', 'includes/content.crud');
  }

  /**
   * Creates a user / role with certain permissions and then logs in as that user
   */
  public function loginWithPermissions() {
    $args = func_get_args();
    $permissions = array_merge(array(
      'access content',
      'administer content types',
      'administer nodes',
      'administer filters',
      'administer site configuration',
      'administer permissions',
    ), hose_xml_ui_perm(), hose_xml_perm(), $args);
    $user = $this->drupalCreateUser($permissions);
    $this->drupalLogin($user);
  }


  public function createHoseProfile($edit = array()) {
    $this->drupalGet('admin/settings/hose_xml/profiles');
    $this->clickLink('Create new profile');
    $edit += array(
      'name' => $this->randomName(32),
      'desc' => $this->randomName(64),
    );
    // Create an export profile.
    $this->drupalPost('hose_xml/profiles/add', $edit, t('Confirm'));
    $this->assertText(t("Profile '@profile' created.", array('@profile' => $edit['name'])), t('Export profile successfully created.'));
    // Check profile exists...
    $pid = db_result(db_query("SELECT pid FROM {hose_xml_profiles} WHERE name = '%s'", $edit['name']));
    // ...and report.
    $this->assertNotNull($pid, t("Export profile '@pid' found in database", array('@pid' => $pid)));
    return hose_xml_profile_load($pid);
  }

  public function deleteHoseProfile($pid) {
    $profile = hose_xml_profile_load($pid);
    $this->drupalGet('admin/settings/hose_xml/profiles');

    $this->clickLinkUrl("/hose_xml/profiles/delete/$pid");
    $this->drupalPost(NULL, array(), 'Delete');
    $this->assertText(t("Profile '@profile' has been deleted.", array('@profile' => $profile->name)), t('Export profile successfully deleted.'));
  }

  public function hoseProfileAddMappings($pid, $mappings) {
    $this->drupalGet("hose_xml/profiles/$pid/view");
    $this->_hoseProfileAddMappings($pid, $mappings);
    $this->drupalGet("hose_xml/profiles/$pid/view");
  }

  private function _hoseProfileAddMappings($pid, $mappings, $parent_id = NULL) {
    $edit = $this->mappingGetFormEditSettings($mappings);
    if (!empty($edit)) {
      $this->clickLinkUrlSpecial("hose_xml/profiles/$pid/add");
      $this->drupalPost(NULL, $edit, 'Create');

      $last_insert_id = db_result(db_query("SELECT id FROM {hose_xml_profile_data} ORDER BY id DESC LIMIT 0,1"));
      if (!empty($parent_id)) {
        db_query("UPDATE {hose_xml_profile_data} SET did = %d WHERE id = %d", $parent_id, $last_insert_id);
      }

      // update parent_id only after the update the last inserted row
      $parent_id = $last_insert_id;
    }
    foreach(element_children($mappings) as $key) {
      if (is_array($mappings[$key])) {
        $this->_hoseProfileAddMappings($pid, $mappings[$key], $parent_id);
      }
    }
  }

  public function getLastNid($current_nid = NULL) {
    if (!empty($current_nid)) {
      return db_result(db_query("SELECT nid FROM {node} WHERE nid < %d ORDER BY nid DESC LIMIT 0,1", $current_nid));
    }

    return db_result(db_query("SELECT nid FROM {node} ORDER BY nid DESC LIMIT 0,1"));
  }

  public function mappingGetFormEditSettings($mapping) {
    $settings = array();
    if (!is_array($mapping)) {
      return $settings;
    }
    foreach($mapping as $key => $setting) {
      if (!element_child($key)) {
        // remove the '#' character from the start of the key
        $key = substr($key, 1);
        $settings[$key] = $setting;
      }
    }
    return $settings;
  }

  public function clickLinkUrl($url, $index = 0) {
    $url_before = $this->getUrl();
    $urls = $this->xpath('//a[@href="'. $url .'"]');

    if (isset($urls[$index])) {
      $url_target = $this->getAbsoluteUrl($urls[$index]['href']);
    }

    $this->assertTrue(isset($urls[$index]), t('Clicked link (!url_target) from !url_before', array('!url_target' => $url_target, '!url_before' => $url_before)), t('Browser'));

    if (isset($urls[$index])) {
      return $this->drupalGet($url_target);
    }
    return FALSE;
  }

  /**
   * Special version of clickLinkUrl. It uses Xpath functions.
   * $function can be 'contains', 'starts-with', 'substring', etc.
   * See http://www.w3.org/TR/xpath/#function-contains
   */
  public function clickLinkUrlSpecial($url, $function = 'contains', $index = 0) {
    $url_before = $this->getUrl();
    $urls = $this->xpath("//a[$function(@href, '". $url ."')]");

    if (isset($urls[$index])) {
      $url_target = $this->getAbsoluteUrl($urls[$index]['href']);
    }

    $this->assertTrue(isset($urls[$index]), t('Clicked link (!url_target) from !url_before', array('!url_target' => $url_target, '!url_before' => $url_before)), t('Browser'));

    if (isset($urls[$index])) {
      return $this->drupalGet($url_target);
    }
    return FALSE;
  }


  /**
   * Absolute path to Drupal root.
   */
  public function absolute() {
    return realpath(getcwd());
  }

  /**
   * Get the absolute directory path of the hose_xml module.
   */
  public function absolutePath() {
    return  $this->absolute() .'/'. drupal_get_path('module', 'hose_xml');
  }

  public function assetPath($filename) {
    return $this->absolutePath() . '/tests/test_assets/' . $filename;
  }


  /********
   * CCK Functions
   *******/

  /**
   * Create a new content-type, and add a field to it. Mostly copied from
   * cck/tests/content.crud.test ContentUICrud::testAddFieldUI
   *
   * We can't override the feeds createContentType method as it is defined as final
   *
   * @param string $typename
   *   (Optional) the name of the content-type to create, defaults to a random name.
   * @param array $fields
   *   (Optional) an keyed array of $field_name => $field_type used to add additional
   *   fields to the new content type.
   *
   * @return string
   *   The name of the new typename.
   */
  protected function newContentType($typename = NULL, $fields = array()) {
    $this->createContentType($typename, $fields);
    // node_load will return the node without
    // the CCK fields if this is not ran
    content_clear_type_cache();
    return $typename;
  }

  /**
   * Select the widget for the field. Default implementation provides widgets
   * for Date, Number, Text, Node reference, User reference, Email, Emfield,
   * Filefield, Image, and Link.
   *
   * Extracted as a method to allow test implementations to add widgets for
   * the tested CCK field type(s). $field_name allow to test the same
   * field type with different widget (is this useful ?)
   *
   * @param $field_name
   *   The name of the field.
   * @param $field_type
   *   The CCK type of the field.
   *
   * @return
   *   The widget for this field, or NULL if the field_type is not
   *   supported by this test class.
   */
  protected function selectFieldWidget($field_name, $field_type) {
    $field_widgets = HoseXMLWebTestCase::$field_widgets;
    return isset($field_widgets[$field_type]) ? $field_widgets[$field_type] : NULL;
  }

  /**
   * Updates a field instance.
   * @return The updated field instance.
   */
  protected function updateField($settings) {
    return content_field_instance_update($settings);
  }

} // HoseXMLWebTestCase

/**
 * @} End of "ingroup hose_xml_core".
 */