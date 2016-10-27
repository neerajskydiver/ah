<?php
// $Id: getdirections.theme.inc,v 1.2.2.3.2.12 2011/01/12 18:45:49 hutch Exp $
// $Name: DRUPAL-6--2-2 $

/**
 * @file
 * getdirections module theming
 */


/**
 * Implementation of hook_theme().
 *
 * This lets us tell Drupal about our theme functions and their arguments.
 */
function getdirections_theme() {
  return array(
    'getdirections_show' => array(
      'arguments' => array(
        'form' => array(),
        'width' => '',
        'height' => '',
        'nid' => 0,
        'type' => '',
      ),
    ),
    'getdirections_show_locations' => array(
      'arguments' => array(
        'width' => '',
        'height' => '',
        'fromlocs' => '',
        'tolocs' => '',
      ),
    ),
    'getdirections_show_locations_via' => array(
      'arguments' => array(
        'width' => '',
        'height' => '',
        'locs' => NULL,
      ),
    ),
    'getdirections_direction_form' => array(
      'arguments' => array('form' => NULL),
    ),
    'getdirections_box' => array(
      'arguments' => array('content' => NULL),
      'template' => 'getdirections_box',
    ),
  );
}

/**
 * Theme to use for when one or no locations are supplied.
 *
 */
function theme_getdirections_show($form, $width, $height, $nid, $type) {
  $output = '';
  $getdirections_returnlink = variable_get('getdirections_returnlink', array(
    'page_enable' => 0,
    'page_link' => t('Return to page'),
    'user_enable' => 0,
    'user_link' => t('Return to page'),
  ));
  if ($getdirections_returnlink['page_enable'] && $nid > 0 && $type == 'node') {
    $output .= '<div class="getdirections_returnlink">'. l($getdirections_returnlink['page_link'], 'node/' . $nid) .'</div>';
  }
  elseif ($getdirections_returnlink['user_enable'] && $nid > 0 && $type == 'user') {
    $output .= '<div class="getdirections_returnlink">'. l($getdirections_returnlink['page_link'], 'user/' . $nid) .'</div>';
  }
  $output .= $form;

  $getdirections_misc = variable_get('getdirections_misc', array(
    'keep_title' => 0,
    'show_distance' => 0,
    'trafficinfo' => 0,
  ));
  if ($getdirections_misc['show_distance']) {
    $output .= '<div id="getdirections_show_distance"></div>';
  }
  $header = array();
  $rows[] = array(
    array(
      'data' => '<div  id="th1_gmap" >Map</div><div id="getdirections_map_canvas" style="width: '. $width .'; height: '. $height .'" ></div>',
      'valign' => 'top',
      'align' => 'center',
      'class' => 'getdirections-map',
    ),
    array(
      'data' => '<div  id="th2_gmap" >Formatted Directions</div><div id="getdirections_directions"></div>',
      'valign' => 'top' ,
      'align' => 'left',
      'class' => 'getdirections-list',
    ),
  );
  $output .= '<div class="getdirections">'. theme('table', $header, $rows) .'</div>';
  $help = '';
  if (getdirections_is_advanced()) {
    $getdirections_defaults = getdirections_defaults();
    if ($getdirections_defaults['waypoints'] > 0) {
      $help = 'Drag <img src="http://labs.google.com/ridefinder/images/mm_20_'. $getdirections_defaults['waypoint_color'] .'.png"> to activate a waypoint';
    }
  }
  $output .= '<div id="getdirections_help">'. $help .'</div>';
  return $output;
}

/**
 * Theme to use for when both locations are supplied.
 *
 */
function theme_getdirections_show_locations($width, $height, $fromlocs, $tolocs) {
  $output = "";
  $output .= "<div class='getdirections_display'><label>". t('From') .":</label> ". $fromlocs ."</div>";
  $output .= "<div class='getdirections_display'><label>". t('To') .":</label> ". $tolocs ."</div>";

  $getdirections_misc = variable_get('getdirections_misc', array(
    'keep_title' => 0,
    'show_distance' => 0,
    'trafficinfo' => 0,
  ));
  if ($getdirections_misc['show_distance']) {
    $output .= ''; 	/* ---- deleted the html <div id="getdirections_show_distance"></div>  and added it to below line no 261 ----*/
  }
  $header = array();
/*  $rows[] = array(
    array(
      'data' => 'Map',
      'valign' => 'top',
      'align' => 'left',
      'class' => 'gmap_head',
    ),
    array(
      'data' => 'Formatted Directions',
      'valign' => 'top' ,
      'align' => 'left',
      'class' => 'gmap_head',
    ),
 );*/
  $rows[] = array(
    array(
      'data' => '<div>Map</div><div id="getdirections_map_canvas" style="width: '. $width .'; height: '. $height .'" ></div>',
      'valign' => 'top',
      'align' => 'center',
      'class' => 'getdirections-map',
    ),
    array(
      'data' => '<div>Formatted Directions</div><div id="getdirections_directions"></div>',
      'valign' => 'top' ,
      'align' => 'left',
      'class' => 'getdirections-list',
    ),
  );

  $output .= '<div class="getdirections">'. theme('table', $header, $rows) .'</div>';
  return $output;
}

/**
 * Theme to use for when both locations are supplied with waypoints.
 *
 */
function theme_getdirections_show_locations_via($width, $height, $locs) {
  $output = "";
  foreach ($locs AS $key => $loc) {
    if ($key == 0) {
      $label = t('From');
    }
    elseif ($key == count($locs)-1) {
      $label = t('To');
    }
    else {
      $label = t('Via');
    }
    $output .= "<div class='getdirections_display'><label>". $label .":</label> ". $loc ."</div>";
  }

  $getdirections_misc = variable_get('getdirections_misc', array(
    'keep_title' => 0,
    'show_distance' => 0,
    'trafficinfo' => 0,
  ));
  if ($getdirections_misc['show_distance']) {
    $output .= '<div id="getdirections_show_distance"></div>';
  }
  $header = array();

  $rows[] = array(
    array(
      'data' => '<div id="getdirections_map_canvas" style="width: '. $width .'; height: '. $height .'" ></div>',
      'valign' => 'top',
      'align' => 'center',
      'class' => 'getdirections-map',
    ),
    array(
      'data' => '<div id="getdirections_directions"></div>',
      'valign' => 'top' ,
      'align' => 'left',
      'class' => 'getdirections-list',
    ),
  );
  $output .= '<div class="getdirections">'. theme('table', $header, $rows) .'</div>';
  return $output;
}


function theme_getdirections_direction_form($form) {
  // if you want to do fancy things with the form, do it here ;-)
  if (isset($form['mto'])) {
    $form['mto']['#prefix'] = '<div class="container-inline getdirections_display">';
    $form['mto']['#suffix'] = '</div>';
  }
  if (isset($form['mfrom'])) {
    $form['mfrom']['#prefix'] = '<div class="container-inline getdirections_display">';
    $form['mfrom']['#suffix'] = '</div>';
  }
  if (isset($form['travelmode'])) {
    $form['travelmode']['#prefix'] = '<div class="container-inline getdirections_display">';
    $form['travelmode']['#suffix'] = '</div>';
  }
  if (isset($form['travelextras'])) {
    $form['travelextras']['#prefix'] = '<div class="container-inline getdirections_display">';
    $form['travelextras']['#suffix'] = '</div>';
  }
  if (getdirections_is_advanced()) {
    if (isset($form['from']) && $form['from']['#type'] == 'textfield' ) {
      $form['from']['#suffix'] = '</div>';
    }
    if (isset($form['country_from'])) {
      $form['country_from']['#prefix'] = '<div id="getdirections_start"><div class="container-inline getdirections_display">';
     // $form['country_from']['#suffix'] = '</div>';  /* --- Commented by akshay and Prachi --- */
    }
    if (isset($form['to']) && $form['to']['#type'] == 'textfield' ) {
      $form['to']['#suffix'] = '</div>';
    }
    if (isset($form['country_to'])) {
      $form['country_to']['#prefix'] = '<div id="getdirections_end"><div class="container-inline getdirections_display">';
      $form['country_to']['#suffix'] = '</div>';
    }
   
     $desc = t('Select a country first, then type in a town.<br />You can also click on the map and move the marker.');
     
  }
  else {
    if (isset($form['country_from'])) {
      $form['country_from']['#prefix'] = '<div class="container-inline getdirections_display">';
      $form['country_from']['#suffix'] = '</div>';
    }
    if (isset($form['country_to'])) {
      $form['country_to']['#prefix'] = '<div class="container-inline getdirections_display">';
      $form['country_to']['#suffix'] = '</div>';
    }
    $desc = t('Fill in the form below.');
  }

  if (isset($form['trafficinfo'])) {
    $form['trafficinfo']['#prefix'] = '<div id="getdirections_trafficinfo">';
    $form['trafficinfo']['#suffix'] = '</div>';
  }
  if (isset($form['switchfromto'])) {
    $form['switchfromto']['#prefix'] = '<div id="getdirections_switchfromto">';
    $form['switchfromto']['#suffix'] = '</div>';
  }
  if (isset($form['next'])) {
  /* --- Commented by akshay and Prachi --- */
/*    $form['next']['#prefix'] = '<div id="getdirections_nextbtn">';
    $form['next']['#suffix'] = '</div>';
	*/
	$form['next']['#suffix'] = '</div>';
  }

  if (isset($form['submit'])) {
    $form['submit']['#prefix'] = '<div id="getdirections_btn">';
		/* ---- added the html <div id="getdirections_show_distance"></div> from the upper output code 
				and delete from the line no 121 ----*/
    $form['submit']['#suffix'] = '<div id="getdirections_show_distance"></div></div>';  /* --- Commented by akshay and Prachi --- */
  }
  $output = '<p class="description">'. $desc .'</p>';
  $output .= drupal_render($form);
  return $output;
}

function template_preprocess_getdirections_box(&$variables) {

  if(module_exists('admin_menu')) {
    admin_menu_suppress();
  }
  drupal_add_js(drupal_get_path('module', 'getdirections') .'/getdirections_box.js');

  // Construct page title
  if (drupal_get_title()) {
    $head_title = array(strip_tags(drupal_get_title()), variable_get('site_name', 'Drupal'));
  }
  else {
    $head_title = array(variable_get('site_name', 'Drupal'));
    if (variable_get('site_slogan', '')) {
      $head_title[] = variable_get('site_slogan', '');
    }
  }
  $variables['head_title']        = implode(' | ', $head_title);
  $variables['base_path']         = base_path();
  $variables['head']              = drupal_get_html_head();
  $variables['language']          = $GLOBALS['language'];
  $variables['language']->dir     = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $variables['css']               = drupal_add_css();
  $variables['styles']            = drupal_get_css();
  $variables['scripts']           = drupal_get_js();
  if (module_exists('jquery_update')) {
    jquery_update_preprocess_page($variables);
  }
  $variables['title']             = drupal_get_title();
  // Closure should be filled last.
  $variables['closure']           = theme('closure');
  // Compile a list of classes that are going to be applied to the body element.
  // This allows advanced theming based on context (home page, node of certain type, etc.).
  $body_classes = array();
  // Add a class that tells us whether we're on the front page or not.
  $body_classes[] = $variables['is_front'] ? 'front' : 'not-front';
  // Add a class that tells us whether the page is viewed by an authenticated user or not.
  $body_classes[] = $variables['logged_in'] ? 'logged-in' : 'not-logged-in';
  $body_classes[] = 'no-sidebars';
  // Implode with spaces.
  $variables['body_classes'] = implode(' ', $body_classes);

}


