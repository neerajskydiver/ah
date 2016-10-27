<?php
// $Id: comment-wrapper.tpl.php,v 1.1 2010/04/24 13:24:34 antsin Exp $
?>

<?php if ($content): ?>
  <div id="comments">
    <?php if ($node->type != 'forum'): ?>
      <h2 class="title"><?php print t('Comments'); ?></h2>
    <?php endif; ?>
    <?php print $content; ?>
  </div>
<?php endif; ?>
