<div class="byarticles">
 <h2> Articles updated by: </h2>
<?php 
$uid=$_REQUEST['uid_touch'];
$update_author = user_load(array('uid' =>$uid));
?>
<h3 class="authorname"><?php echo $update_author->name;?></h3> 

</div>
 <?php 	
$selectquery1="SELECT nr.uid,nr.nid ,n.title,n.changed FROM node_revisions nr INNER JOIN node n ON n.vid = nr.vid WHERE nr.uid =". $uid;
$resultquery1=mysql_query($selectquery1);

$items = 40 ;

 
$num_rows = mysql_num_rows($resultquery1);
if($all == "all"){
$items = $num_rows;
}
$nrpage_amount = $num_rows/$items;
$page_amount = ceil($num_rows/$items);
$page_amount = $page_amount-1;
$page = mysql_real_escape_string($_GET['p']);
if($page < "1"){
	$page = "0";
	$first =$page;
}
$p_num = $items*$page;
//end paging code

/********************/
		if($num_rows != 0){
	        $total_records_on_page = $items;
			$item_per_page_no = $items;
			$page_no =  $page;
			
			$start_val	= $start_record_no = (($page_no*$total_records_on_page)+1 );
			if((($page_no*$items)+ $items) < $num_rows){
				$end_val = (($page_no*$items)+ $items);
			}else{
				$end_val = $num_rows;
			}
			$total_val  = $num_rows;			
			$result_cnt_var = "<p>Displaying results ".$start_val." to ".$end_val." - ".$total_val."</p>";
		}
/*********************/

?>
<div class="articleth">
<table class="articletable">
<tr class="tblheader"><th class="firstth">Articles</th><th class="secondth">Updated Date</th></tr>


<?php

$selectquery="SELECT nr.uid,nr.nid ,n.title,n.changed FROM node_revisions nr INNER JOIN node n ON n.vid = nr.vid WHERE nr.uid =". $uid." order by nr.nid ASC LIMIT $p_num , $items";
$resultquery=mysql_query($selectquery);


if($page_amount != "0" && $num_rows != 0){
			$pagination_code .= "<div class=panel>";
			$pagination_code1 = $result_cnt_var;
					if($page != "0"){
					$prev = $page-1;
					   $pagination_code .= "<a href=\"".$base_url."/content/view-updated-article/?uid_touch=$uid&p=$first\" style='padding-right:10px;'><< first</a>";
						$pagination_code .= "<a href=\"".$base_url."/content/view-updated-article/?uid_touch=$uid&p=$prev\" style='padding-right:10px;'>< prev</a>";
				}
				for ( $counter = 0; $counter <= $page_amount; $counter += 1) {
						if($page == $counter){
							$active = " class='active' ";
						}else{
							$active = "";
						}
				
						$pagination_code .= "<a ".$active." href=\"".$base_url."/content/view-updated-article/?uid_touch=$uid&p=$counter\" style='padding-right:10px;'>";
						$pagination_code .= $counter+1;
						$pagination_code .= "</a>";
				}
				if($page < $page_amount){
					$next = $page+1;
					$last = $page_amount;
					$pagination_code .= "<a href=\"".$base_url."/content/view-updated-article/?uid_touch=$uid&p=$next\" style='padding-right:10px;'>next ></a>";
					$pagination_code .= "<a href=\"".$base_url."/content/view-updated-article/?uid_touch=$uid&p=$last\" style='padding-right:10px;'>last >></a>";
				}
			
			$pagination_code .= "</div>";
		}
		if($pagination_code){
			echo $pagination_code1;
		}
	
?>

<?php 

while ($rowquery=mysql_fetch_object($resultquery)){

$update_author_uid = $rowquery->uid;
$update_author_nid = $rowquery->nid;
$update_author_title = $rowquery->title;
$update_author_date = $rowquery->changed;

$update_author = user_load(array('uid' => $update_author_uid));

echo "<tr><td>";
 if ($update_author_uid == '0') { // Check if author is anonymous
   // $update_author_output = variable_get('anonymous', 'Anonymous');
  }
  else {    
  echo  $update_author_output = l($update_author_title, 'node/'. $update_author_nid);
 
  }
//echo "<td>";
echo "<td>";
//print date("y-m-d",$update_author_date);
$formatted_date = format_date($update_author_date, 'custom', 'j M Y H:i');
print $formatted_date;
echo "<td></tr>";
 }?>

</table>
</div>
<?php

	if($pagination_code){  
	  echo $pagination_code;
	 }
?>