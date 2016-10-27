<?php
// $Id: node.tpl.php,v 1.5 2007/10/11 09:51:29 goba Exp $
//drupal_add_css($directory.'/node-blog.css')
?>
<div id="node-<?php print $node->nid; ?>" class="blogEntry node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">

<?php print $picture ?>
<?php if ($page == 0): ?>
  <h2 class="blogh2"><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
<?php endif; ?>

	
  <div class="blog_deck">
	<?php print $node->field_blog_intro_text[0]['view'] ?>
  </div>

  <?php if ($submitted): ?>
    <span class="submitted">
		<?php print $submitted; ?>
	</span>
  <?php endif; ?>

  <div class="blog_body">
  <table width="100%" cellpadding="0" cellspacing="0">
  <tr><td>
    <?php // print $content ?>
	<div class="blogEntryImage">
		<?php print $node->field_blogs_image[0]['view'] ?>
	</div>
	<?php print $node->content['body']['#value'] ?>
  </td></tr>
  </table>
  </div>
<div class="clear-block">
    <div class="meta">
    <?php if ($taxonomy): ?>
      <div class="terms"><?php //print $terms ?></div>
    <?php endif;?>
    </div>

    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>






</div>
