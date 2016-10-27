<?php
// $Id: node.tpl.php,v 1.5 2007/10/11 09:51:29 goba Exp $
?>
<div id="article">
    <div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?> <?php if ($teaser): print 'teaser'; endif; ?>">
    
        <?php print $picture ?>
    
        <?php if ($page == 0): ?>
          <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
        <?php endif; ?>
    
        <?php if ($submitted): ?>
          <span class="submitted">
           <?php print $submitted; ?>
          </span>
        <?php endif; ?>
    
        <?php if ($links && !$teaser): ?>
        <div class="panel">
          <div class="magazine_tools">
            <?php print $links; ?>
          </div>
        </div>
        <?php endif; ?>
    
        <div>
          <div  class="drop_letter">
            <?php print $content ?>
          </div>
        </div>
    
        <div class="clear-block">
          <div class="meta">
            <?php if ($taxonomy): ?>
            <div class="terms">
              <?php print $terms ?>
            </div>
            <?php endif;?>
          </div>

        </div>
    
    </div>
</div>