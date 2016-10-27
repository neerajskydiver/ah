<?php
// $Id: comment.tpl.php,v 1.10 2008/01/04 19:24:24 goba Exp $
?>
<div class="<?php print $classes; ?>" id="comment-wrapper"><div class="comment-inner clear-block">
  <?php if ($unpublished): ?>
    <div class="unpublished"><?php print t('Unpublished'); ?></div>
  <?php endif; ?>  
  <div class="submitted">
    <?php print $picture;?>
    <span class="author">
      <?php print $author; ?>
    </span>
    <span>
      <?php print $date; ?>
    </span>
  </div>
  <div class="content">
    <?php if ($title): ?>
      <h3 class="title"><?php print $title; ?></h3> 
    <?php endif; ?>
    <img src="<?php global $base_url; print $base_url .'/' . $directory; ?>/images/comment_arrow.png" class="comment_arrow" />
    <?php print $content; ?>
    <?php if ($signature): ?>
      <div class="user-signature clear-block"><?php print $signature; ?></div>
    <?php endif; ?> 
  </div>
  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>
</div></div> <!-- /comment-inner, /comment -->
<!--<div class="comment<?php print ($comment->new) ? ' comment-new' : ''; print ' '. $status; print ' '. $zebra; ?>">

  <div class="clear-block">
  <?php if ($submitted): ?>
    <span class="submitted"><?php print $submitted; ?></span>
  <?php endif; ?>

  <?php if ($comment->new) : ?>
    <span class="new"><?php print drupal_ucfirst($new) ?></span>
  <?php endif; ?>

  <?php print $picture ?>

    <h3><?php print $title ?></h3>

    <div class="content">
      <?php print $content ?>
      <?php if ($signature): ?>
      <div class="clear-block">
        <div>—</div>
        <?php print $signature ?>
      </div>
      <?php endif; ?>
    </div>
  </div>

  <?php if ($links): ?>
    <div class="links"><?php print $links ?></div>
  <?php endif; ?>
</div>-->
