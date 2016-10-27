<?php
// $Id: views-view-table.tpl.php,v 1.8 2009/01/28 00:43:43 merlinofchaos Exp $
/**
 * @file views-view-table.tpl.php
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $class: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * @ingroup views_templates
 */

?>
<table class="<?php print $class; ?>"  cellspacing="0" cellpadding="0">
  <?php if (!empty($title)) : ?>
    <caption><?php print $title; ?></caption>
  <?php endif; ?>
  <thead>
    <tr>
      <?php //foreach ($header as $field => $label): ?>
        <th class="views-field views-field-<?php print $fields[$field]; ?>" colspan=2>
         <p> <?php 


$from = ($view->pager['current_page'] * $view->pager['items_per_page']) + 1;
$to = $from + count($view->result) - 1;
$total = $view->total_rows;
if ($total <= $to ) {
// no need to show where we are if everything fits on the first page
echo "Displaying " . $total ;
} else {
echo "Displaying " . $from . " - " . $to . " of " . $total ;
}



 //print $label;

 ?></p></th><th>


<?php
$block = module_invoke('sort_by', 'block',  'view', 0);
print $block['content'];
?>


        </th>
      <?php //endforeach; ?>
    </tr>
  </thead>
  <tbody><tr><td colspan=3>&nbsp;</td></tr>
    <?php foreach ($rows as $count => $row): ?>
      <tr class="<?php print implode(' ', $row_classes[$count]); ?>">
        <?php foreach ($row as $field => $content): ?>
          <td class="views-field views-field-<?php print $fields[$field]; ?>">
            <?php print $content; ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>

