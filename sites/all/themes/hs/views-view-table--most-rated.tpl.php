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

    <?php foreach ($rows as $count => $row): ?>
<?php  print "<div  class=\"record\">";?>
	  <?php $i=1; ?>
        <?php foreach ($row as $field => $content)
			{ 
		
				if($i == 1)
				{
					print $content;
				}
				else
				{
					if($i == 2)
					{
						print 	"<ul><li class=\"title\">";
						print $content;
						print "</li>";
					}
					if($i == 3)
					{
						print 	"<li class=\"collection\">";
						print $content;
						print "</li></ul>";
					}
				}
				$i++;
    	   }
 	  ?>	
<?php print "</div>"; ?>
    <?php endforeach; ?>
