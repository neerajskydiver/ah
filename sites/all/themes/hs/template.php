<?php

    // drupal_add_js(drupal_get_path('theme', 'hs') .'/js/jquery-1.10.2.js', 'theme');
  // drupal_add_js(drupal_get_path('theme', 'hs') .'/js/jquery-ui.js', 'theme');

// $Id: template.php,v 1.16.2.3 2010/05/11 09:41:22 goba Exp $

/**
 * Sets the body-tag class attribute.
 *
 * Adds 'sidebar-left', 'sidebar-right' or 'sidebars' classes as needed.
 */
function phptemplate_body_class($left, $right) {
  if ($left != '' && $right != '') {
    $class = 'sidebars';
  }
  else {
    if ($left != '') {
      $class = 'sidebar-left';
    }
    if ($right != '') {
      $class = 'sidebar-right';
    }
  }

  if (isset($class)) {
    print ' class="'. $class .'"';
  }
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function phptemplate_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    //return '<div class="breadcrumb">'. implode(' › ', $breadcrumb) .'</div>';
    return '<div class="breadcrumb">'. implode(' &raquo; ', $breadcrumb) .'</div>';

  }
}

/**
 * Override or insert PHPTemplate variables into the templates.
 */
function phptemplate_preprocess_page(&$vars) {
  $vars['tabs2'] = menu_secondary_local_tasks();



  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
	//template for articles
	  if ($vars['node']->type != "") {
    $vars['template_files'][] = "page-node-" . $vars['node']->type;
  }

	  if ((arg(0) == "historic-sites" || arg(0) == "historic-themes" || arg(0) == "types") && arg(1) == '') {
    $vars['template_files'][] = "page-view-historic-sites";
  }
  
   if (arg(0) == "getdirections" && arg(1)=="location" && arg(2)=="to" ){$vars['template_files'][] = "page-getdirections";}

/*
	  if (arg(0) == "home" && arg(1) == '') {

    $vars['template_files'][] = "page-home";
  }*/

  
 //added by prachi 
 if ($vars['node']->type == 'article') {
 $links = array();
 $title_article=$vars['node']->title;
 $articlenid=$vars['node']->nid;  
 $SelectArticle=db_query("select cs.field_volumenumber_value,cs.field_issuenumber_value,cs.field_year_value,cs.nid from node n inner join content_type_article ca on ca.nid=n.nid inner join content_type_issue cs on ca.field_issue_nid_nid=cs.nid where n.nid=$articlenid");
 while ($ResultArticle=db_fetch_array($SelectArticle)){
 $rowArticle1=$ResultArticle['field_volumenumber_value'];
 $rowArticle2=$ResultArticle['field_issuenumber_value'];
 $rowArticle3=$ResultArticle['field_year_value'];
 $rowArticle4=$ResultArticle['nid'];
 }
 $mag_title = check_plain($title_article);
 $mag_title = ucwords(strtolower($mag_title));



 $links[] = l('Home', '<front>');
 $links[] = l('Magazine','content/winter-2011');
 $links[] = l($rowArticle3,'volume/'.$rowArticle3.'/year');
 $links[] = l('Volume '.$rowArticle1.", Issue ".$rowArticle2,'node/'.$rowArticle4);

 // $links[] = $mag_title; //   removed from breadcrumb

 // lastly, overwrite the contents of the breadcrumbs variable in the page scope
 $vars['breadcrumb'] = theme('breadcrumb', $links);
 }

$theme= $_GET['field_theme_nid'];
$type= $_GET['field_type_nid'];
if (is_array($theme))
{
$themeid=$theme[0];
$thid=node_load($themeid);
$titletheme= $thid->title;
}
else if (is_array($type)){
$typeid=$type[0];
$tyid=node_load($typeid);
$titletype= $tyid->title;}

if (arg(0) == "historic-sites" && is_array($theme) || is_array($type)){
if (count($theme)==1 || count($type)==1){
$links = array();
 $links[] = l('Home', '<front>');
 $links[] = l('Historic Sites','historic-sites');
 $links[] = $titletheme.$titletype;
 $vars['breadcrumb'] = theme('breadcrumb', $links);
}
}

if (arg(0)== "search-landing-page" ){
$nid_nid=$_GET['nid'];
$nid_value=node_load($nid_nid);
$nid_title=$nid_value->title;

$vars['breadcrumb']=str_replace('[field_site_id-title]',$nid_title,$vars['breadcrumb']);

}
 //added by prachi 
	
}

/**
 * Add a "Comments" heading above comments except on forum pages.
 */
function garland_preprocess_comment_wrapper(&$vars) {
  if ($vars['content'] && $vars['node']->type != 'forum') {
    $vars['content'] = '<h2 class="comments">'. t('Comments') .'</h2>'.  $vars['content'];
  }
}


/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */
function phptemplate_menu_local_tasks() {
  return menu_primary_local_tasks();
}

/**
 * Returns the themed submitted-by string for the comment.
 */
function phptemplate_comment_submitted($comment) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $comment),
      '!datetime' => format_date($comment->timestamp, 'medium')
    ));
}

/**
 * Returns the themed submitted-by string for the node.
 */
function phptemplate_node_submitted($node) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $node),
      '!datetime' => format_date($node->created),
    ));
}

/**
* Override theme_username to display full username
*
*/

function hs_username($object) {

  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables.
    if (drupal_strlen($object->name) > 100) {
      $name = drupal_substr($object->name, 0, 100) .'...';
    }
    else {
      $name = $object->name;
    }

    if (user_access('access user profiles')) {
      $output = l($name, 'user/'. $object->uid, array('title' => t('View user profile.')));
    }
    else {
      $output = check_plain($name);
    }
  }
  else if ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if ($object->homepage) {
      $output = l($object->name, $object->homepage);
    }
    else {
      $output = check_plain($object->name);
    }

    $output .= ' ('. t('not verified') .')';
  }
  else {
    $output = variable_get('anonymous', t('Anonymous'));
  }

// $output .= ' ('. $object->uid .')';
  return $output;
}


/**
 * Generates IE CSS links for LTR and RTL languages.
 */
function phptemplate_get_ie_styles() {
  global $language;

  $iecss = '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . path_to_theme() .'/fix-ie.css" />';
  if ($language->direction == LANGUAGE_RTL) {
    $iecss .= '<style type="text/css" media="all">@import "'. base_path() . path_to_theme() .'/fix-ie-rtl.css";</style>';
  }

  return $iecss;
}

function hs_node_submitted($node) {
if($node->type == 'article' && !$node->teaser){
	$issueid = $node->field_issue_nid[0]['nid'];
	$issue = node_load($issueid);

	$ititle = $issue->title;
	$vnumber = $issue->field_volumenumber[0]['value'];
	$inumber = $issue->field_issuenumber[0]['value'];
	$author1 = theme('username', user_load($node->field_art_contributor[0]['uid']));
	if($node->field_art_contributor[1]['uid']){
  	$author2 = ' | ' . theme('username', user_load($node->field_art_contributor[1]['uid']));
	}
	if($node->field_art_contributor[2]['uid']){
  	$author3 = ' | ' . theme('username', user_load($node->field_art_contributor[2]['uid']));
	}
  $author = $author1 . $author2 . $author3;
	$issue_info = '<p class="date">' . $ititle . '&nbsp;&nbsp;|&nbsp;Volume ' . $vnumber . ',&nbsp; Issue ' . $inumber . '</p>';


if ($author=='Anonymous')
{
  $author='';
  
}
  return t('<p class="author"> !username </p><p class="date">!issue_info </p>', 
    array(
    '!username' => $author,//theme('username', $node), 
    '!issue_info' => $issue_info, 
//    '!datetime' => format_date($node->created, 'large'),
  ));
}
if($node->type == 'blog'){
  return t('<p class="blogTimeStamp">!datetime, by !username</p>', 
    array(
    '!username' => theme('username', $node), 
    '!datetime' => format_date($node->created, 'custom', 'F jS, Y'),
  ));
}

}




function phptemplate_links($links = array(), $delimiter = ' | ') {
  /**
* catches the theme_links function
*/
// Uncomment the following line to see the links and the indexes
// print '<pre>' . print_r($links, TRUE) . '</pre>';

$ordered_links = array();

// Indexes of links we want to force order for
// Links accounted for here will be in order in this array

$in_order = array('taxonomy_term_1', 'taxonomy_term_2');

// Move links we care about to $ordered_links array
//   Will be added in order index is found in $in_order array

foreach ( $in_order as $index ) {
// Make sure the link exists
if( isset($links[$index]) ) {
$ordered_links[] = $links[$index];
unset($links[$index]);
}
}

// Add any links not accounted for at end

foreach ( $links as $link ) {
$ordered_links[] = $link;
}

// Not really a best practice but it avoid copying
// the code in theme_links

return theme_links($ordered_links, $delimiter);
}
//Added by prachi for blogs landing page on sunday
function phptemplate_preprocess_node(&$vars) {

  if (arg(0) == 'taxonomy') {
    $suggestions = array(
      'node-taxonomy'
    );
    $vars['template_files'] = array_merge($vars['template_files'], $suggestions);
  }
}


/**
 * Comment Template
 */
function hs_preprocess_comment(&$vars, $hook) {
  // Add an "unpublished" flag.
  $vars['unpublished'] = ($vars['comment']->status == COMMENT_NOT_PUBLISHED);

  // If comment subjects are disabled, don't display them.
  if (variable_get('comment_subject_field_' . $vars['node']->type, 1) == 0) {
    $vars['title'] = '';
  }

  // Special classes for comments.
  $classes = array('comment');
  if ($vars['comment']->new) {
    $classes[] = 'comment-new';
  }
  $classes[] = $vars['status'];
  $classes[] = $vars['zebra'];
  if ($vars['id'] == 1) {
    $classes[] = 'first';
  }
  if ($vars['id'] == $vars['node']->comment_count) {
    $classes[] = 'last';
  }
  if ($vars['comment']->uid == 0) {
    // Comment is by an anonymous user.
    $classes[] = 'comment-by-anon';
  }
  else {
    if ($vars['comment']->uid == $vars['node']->uid) {
      // Comment is by the node author.
      $classes[] = 'comment-by-author';
    }
    if ($vars['comment']->uid == $GLOBALS['user']->uid) {
      // Comment was posted by current user.
      $classes[] = 'comment-mine';
    }
  }
  $vars['classes'] = implode(' ', $classes);
}

/* Alt Tag for All images on 28 Feb 2011 By Prachi */


function phptemplate_imagefield_formatter_image_plain($element, $print_desc = true) {
  // Inside a View this function may be called with null data.  In that case,
  // just return.

  if (empty($element['#item'])) {
    return '';
  }

  $field = content_fields($element['#field_name']);
  $item = $element['#item'];

  if (empty($item['fid']) && $field['use_default_image']) $item = $field['default_image'];
  if (empty($item['filepath']))  $item = array_merge($item, field_file_load($item['fid']));

  $class = 'imagefield imagefield-'. $field['field_name'];
  return  theme('imagefield_image', $item, $item['data']['alt'], $item['data']['title'], array('class' => $class)) . ($print_desc ? ($item['data']['description'] ? '<br/>'.$item['data']['description'] : '') : '');
}

function phptemplate_imagefield_formatter_image_nodelink($element) {
  // Inside a View this function may be called with null data.  In that case,
  // just return.
  if (empty($element['#item'])) {
    return '';
  }

  $node = $element['#node'];
  $item = $element['#item'];
  $imagetag = theme('imagefield_formatter_image_plain', $element, false);
  $class = 'imagefield imagefield-nodelink imagefield-'. $element['#field_name'];
  return l($imagetag, 'node/'. $node->nid, array('attributes' => array('class' => $class), 'html' => true)) . ($item['data']['description'] ? '<br/>'.$item['data']['description'] : 'No description');
}

function phptemplate_imagefield_formatter_image_imagelink($element) {
  // Inside a View this function may be called with null data.  In that case,
  // just return.
  if (empty($element['#item'])) {
    return '';
  }

  $item = $element['#item'];
  $imagetag = theme('imagefield_formatter_image_plain', $element, false);
  $original_image_url = file_create_url($item['filepath']);
  $class = 'imagefield imagefield-imagelink imagefield-'. $element['#field_name'];

  return l($imagetag, $original_image_url, array('attributes' => array('class' => $class), 'html' => true)) . ($item['data']['description'] ? '<br/>'.$item['data']['description'] : 'No description');
}



function phptemplate_imagecache($namespace, $path, $alt = '', $title = '', $attributes = NULL) {

$node=arg(1);
$nodevalue=node_load($node);
$nid=$nodevalue->title;

  if ($image = image_get_info(imagecache_create_path($namespace, $path))) {
    $attributes['width'] = $image['width'];
    $attributes['height'] = $image['height'];
  }
  // check is_null so people can intentionally pass an empty array of attributes to override
  // the defaults completely... if
  if (is_null($attributes)) {
    $attributes['class'] = 'imagecache imagecache-'. $namespace;
  }
  $attributes = drupal_attributes($attributes);
  $imagecache_url = imagecache_create_url($namespace, $path);
  return '<img src="'. $imagecache_url .'" alt="'. check_plain($nid) .'" title="'. check_plain($title) .'" '. $attributes .' />';
}

function phptemplate_imagecache_imagelink($namespace, $path, $alt = '', $title = '', $attributes = NULL) {
  $image = theme('imagecache', $namespace, $path, $alt, $title);
  $original_image_url = file_create_url($path);
  return l($image, $original_image_url, array('absolute' => FALSE, 'html' => TRUE));
}
/* Alt Tag for All images on 28 Feb 2011 By Prachi */

/**
 * Registers overrides for various functions.
 * Added on: 29th June 2016
 * In this case, overrides three user functions
 */
function hs_theme() {
  return array(
    'user_login' => array(
      'template' => 'user-login',
      'arguments' => array('form' => NULL),
    ),
    'user_register' => array(
      'template' => 'user-register',
      'arguments' => array('form' => NULL),
    ),    
  );
}

function hs_preprocess_user_register(&$variables) 
{
  $variables['intro_text'] = t('This is my super awesome reg form');
  $variables['rendered'] = drupal_render($variables['form']);
}

 // drupal_add_js(drupal_get_path('theme', 'hs') .'/js/jquery-ui.js', 'theme');
//drupal_add_js(drupal_get_path('theme', 'hs') .'/js/jquery-1.11.3.min.js', 'theme');



?>
