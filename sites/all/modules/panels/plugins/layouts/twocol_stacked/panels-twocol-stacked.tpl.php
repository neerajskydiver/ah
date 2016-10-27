<?php
// $Id: panels-twocol-stacked.tpl.php,v 1.1.2.2 2010/07/20 19:06:04 merlinofchaos Exp $
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * additional areas for the top and the bottom.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left']: Content in the left column.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>
<div class="panel-2col-stacked clear-block panel-display" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <?php if ($content['top']): ?>
    <div class="panel-col-top panel-panel">
      <div class="inside"><?php print $content['top']; ?></div>
    </div>    
  <?php endif; ?>

  <div class="center-wrapper">
    <div class="panel-col-first panel-panel">
      <div class="inside"><?php
// print $content['left'];

/* Prachi Code */
	  $node=arg(1);
	  $nodes=node_load(array("nid" => $node));
	  $nodetype= $nodes->type;
         $nodesite= $nodes->field_site_id[0]['nid'];
	  if ($nodetype=="bookmarks_sites"){
	  echo "<div class='bookdiv'>";	
	  print $content['left']; 
	  echo "</div>"; 
	  }
	  else if ($nodetype=="collection"){
	  echo "<div class='colldiv'>";	
	  print $content['left'];
echo "<p class='disclaimer'>Advertisements for specific products, services or destinations on this website are for the information of the public, and do not constitute an endorsement or recommendation by this institution, its officers, employees or agents.</p>";
	    
	  echo "</div>"; 
	  }
	  else {
	  print $content['left']; 
	  }
	/* Prachi Code */ 



 ?></div>
    </div>
    <div class="panel-col-last panel-panel">
      <div class="inside"><?php 
print $content['right'];
/* Prachi added for More link */
 if ($nodetype=="collection"){ 
	
 //$options1 = array('query' => array('nid' => $nodesite),'html' => TRUE); 
 //echo "<div id='more_link'>".l(t('More from this collection &raquo;'), 'node/'.$nodesite,$options1)."</div>";
 
 $options1 = array('query' => array('keys'=>'','field_institution_value'=>'','nid' => $nodesite),'html' => TRUE); 
 echo "<div id='more_link'>".l(t('More from this collection &raquo;'), 'search-landing-page',$options1)."</div>";
 


}
/* Prachi added for More link */
 ?></div>
    </div>
  </div>

  <?php if ($content['bottom']): ?>
    <div class="panel-col-bottom panel-panel">
      <div class="inside"><?php print $content['bottom']; ?></div>
    </div>    
  <?php endif; ?>
</div>
