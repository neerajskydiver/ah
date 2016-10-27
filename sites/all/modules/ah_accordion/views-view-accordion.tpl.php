<?php
// $Id: views-view-accordion.tpl.php,v 1.1.2.3 2009/02/26 20:25:59 manuelgarcia Exp $
/**
 * @file
 * Displays the items of the accordion.
 *
 * @ingroup views_templates
 *
 *  Note that the accordion NEEDS <?php print $row ?> to be wrapped by an element, or it will hide all fields on all rows under the first field.
 *  Also, if you use field grouping and use the headers of the groups as the accordion headers, these NEED to be inside h3 tags exactly as below (though u can add classes)
 * 
 *  The current div wraping each row gets two css classes, which should be enough for most cases:
 *     "views-accordion-item"
 *      and a unique per row class like item-0
 *
 */
?>
  <?php if (!empty($title)): ?>
                 <dt><?php print $title; ?>
                 </dt>
  <?php endif; ?>
                <dd>
                  <?php foreach ($rows as $id => $row): ?>
                      <?php print $row ?>
                  <?php endforeach; ?>

                </dd>


