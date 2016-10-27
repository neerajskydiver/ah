<?php
/**
 * @file views-view-table.tpl.php
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $rows: An array of row items. Each row is an array of content
 *   keyed by field ID.
 * - $header: an array of headers(labels) for fields.
 * - $themed_rows: a array of rows with themed fields.
 * @ingroup views_templates
 */
global $base_url;

?>
<?php foreach ($themed_rows as $count => $row): ?>
<?php 
$nod_id=$rows[0]->nid;
$pretty_path=drupal_get_path_alias('node/' . $nod_id);
?>
  <<?php print $item_node; ?> type="article" docID="<?php echo $nod_id;?>" link="<?php print $base_url."/".$pretty_path;?>">
<?php foreach ($row as $field => $content): ?>
    <<?php print $xml_tag[$field]; ?>><?php print $content; ?></<?php print $xml_tag[$field]; ?>>
<?php endforeach; ?>
  </<?php print $item_node; ?>>
<?php endforeach; ?>
