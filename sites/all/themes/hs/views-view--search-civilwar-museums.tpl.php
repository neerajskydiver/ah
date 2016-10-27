<?php
// $Id: views-view.tpl.php,v 1.13.2.2 2010/03/25 20:25:28 merlinofchaos Exp $
/**
 * @file views-view.tpl.php
 * Main view template
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 * - $admin_links: A rendered list of administrative links
 * - $admin_links_raw: A list of administrative links suitable for theme('links')
 *
 * @ingroup views_templates
 */
?>
<?php
//dsm($view->result);
if(count($view->result) > 0)
{


?>
<div class="panel">
  <?php
if ($pager)
{
	$id = "result-set";
}
else
{
	$id = "no-result-set";
} 
  
   ?>
	
	<?php 
	/*------------ Code Added By Akshay:- For  1 to 10 - N  paging display  -------------*/
	print "<div id=\"$id\">";
	$itme_per_page_no = $view->pager['items_per_page'];
	$total_records_on_page = count($view->result);
	$page_no = 	$view->pager['current_page'];
	$result_cnt_var	.= "Results ".$start_record_no = (($page_no*$itme_per_page_no)+1 );
	$result_cnt_var	.= " to ".$end_record_no = (($page_no*$itme_per_page_no)+ $total_records_on_page );
	$result_cnt_var	.=	" - ".$view->total_rows;
	print $result_cnt_var;
	print "</div>";
	/*------------ END -------------*/	
	?>

  <?php if ($pager): ?>
 	<span id="pager-item-list">
    <?php print $pager; ?>
  	</span>
  <?php endif; ?>
						<hr>
						             <!-- <p class="sort_options">Sort by: 
							       <select>
								<option>Relevance</option>
								<option>Title (A-Z)</option>
								<option>Title (Z-A)</option>
								<option>Institution (A-Z)</option>
								<option>Institution (Z-A)</option>
								<option>Date (newest first)</option>
								<option>Date (oldest first)</option>								
							      </select>						
						             </p>-->
						<p class="select_options">
							<a href="#">Select All</a> | <a href="#">Clear All</a> | Save Selected to: 
							<select>
								<option>New List</option>
								<option>Existing List</option>
							</select>
						</p>
					</div>
<?php
}
?>

<div class="<?php print $classes; ?>">
  <?php if ($admin_links): ?>
    <div class="views-admin-links views-hide">
      <?php print $admin_links; ?>
    </div>
  <?php endif; ?>
  
  
  
  

  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

<?php
if(arg(0)=="search-civilwar-museum" && count($view->result) == 0 && (!strpos($_SERVER['REQUEST_URI'],"?")))
{
?>
  <?php if ($exposed): ?>
    <div class="view-filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>
<?php
}
?>

  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view-content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

<?php
if(strpos($_SERVER['REQUEST_URI'],"?") && count($view->result) != 0)
{
?>
<div class="panel">
	<div id="<?php echo $id;?>">
		<?php 	print $result_cnt_var;?>
	</div>	
		<?php if ($pager): ?>
		<?php print $pager; ?>
		<?php endif; ?>
</div>
<?php
}
?>



  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div> <?php /* class view */ ?>

<?php
global $user;
$index = 0;
$arr =array();
foreach($view->result as $var)
{
array_push($arr,$var->nid);
}

$string = "http://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
$_SESSION['path'] = $str;


//$_SESSION['search'][$md_var] = $arr;




$md_var = md5($string);
$session_id = session_id();
$timestamp = time();
$rec = implode(",",$arr);
$uid =  $user->uid;
$ip=$_SERVER['REMOTE_ADDR'];


if($rec != "")
{
	$sql_if_exist = "select count(pkey) as cnt from paging_full_record where session_id ="."'".$session_id."'"." and unique_url = "."'".$md_var."'";
	$eces_if_present = db_query($sql_if_exist);
	$res_if_present = db_fetch_object($eces_if_present);
}

if((!($res_if_present->cnt > 0)) && $rec !="")
{
	$sql = "insert into paging_full_record (unique_url,session_id,timestamp,records,uid,ip_add,page,url) values ('$md_var','$session_id',$timestamp,'$rec',$uid,'$ip','scwm','$string')";
	$sql_query = db_query($sql);
}
else
{
//echo "Already present";
}

//scwm - Search Civil War Museum
?>

