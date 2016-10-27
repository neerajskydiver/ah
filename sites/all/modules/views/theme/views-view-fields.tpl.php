<?php
// $Id: views-view-fields.tpl.php,v 1.6 2008/09/24 22:48:21 merlinofchaos Exp $
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */


?>
<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <<?php print $field->inline_html;?> class="views-field-<?php print $field->class; ?>">
    <?php if ($field->label): ?>
      <label class="views-label-<?php print $field->class; ?>">
        <?php print $field->label; ?>:
      </label>
    <?php endif; ?>
      <?php
      // $field->element_type is either SPAN or DIV depending upon whether or not
      // the field is a 'block' element type or 'inline' element type.
      ?>
      <<?php print $field->element_type; ?> class="field-content"><?php print $field->content; ?></<?php print $field->element_type; ?>>
  </<?php print $field->inline_html;?>>
<?php endforeach; ?>


<?php
/* Added By Akshar, the following block of code does
	1) Stores the Path of search page in seesion so that on the node template customisation page
		it can be used.
	2) Contains the logic for Paging.
*/
?>


<?php
/*  Logic that keeps the search page path in session,
	so that this is retrived in tha panel UI, of editing node template
	where this link is assigned to Back To Search Results
*/

$index = 0;
$arr =array();
foreach($view->result as $var)
{
/*	if($index == 0)
	{

	$str .= $var->nid;
	}
	else
	{
	$str .= ",".$var->nid;
	$index++;
	}
*/
//echo $var->nid;
array_push($arr,$var->nid);
}
?>
<?php
$str = "http://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
session_start();
$_SESSION['path'] = $str;

?>
<?php

//$str = "http://localhost/ah-2010-new/".$_SERVER['REQUEST_URI'];
//echo parse_url($str, PHP_URL_PATH);
//parse_str($str, $output);
//print_r($output);
//count($output['term_node_tid_depth']);
//$arr[] = $arr_val;

$_SESSION['node-list'] = $arr;
$_SESSION['arr_index'] = 0;
$curr_val = arg(1);

?>