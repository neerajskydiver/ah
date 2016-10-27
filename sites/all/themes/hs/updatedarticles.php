<div id = "updatedarticles">

<fieldset><legend> Articles updated by  </legend>

<?php 
global $base_url;

$uid=$_REQUEST['uid_touch'];
$update_author = user_load(array('uid' =>$uid));

 //echo $update_author->name; 
?>
<h3 class="authorname"><?php echo $update_author->name; ?></h3></fieldset>

<table id="updatedby">
<th>Articles</th><th class="secondth">Updated Date</th>
 <?php 	
 
if(!isset($_REQUEST['page'])){
$curr_page = 1;
	$page = 1;
	$limit = 1; 

}else{
	
	$curr_page = $_REQUEST['page'];
	$page = $_REQUEST['page'];
	$limit = (($page * 50) - 50) + 1;

}
 
$selectquery="SELECT nr.uid,nr.nid ,n.title,n.changed FROM node_revisions nr INNER JOIN node n ON n.vid = nr.vid WHERE n.type = 'article' and nr.uid =". $uid." LIMIT {$limit}, 49";

$selectquery_all="SELECT nr.uid,nr.nid ,n.title,n.changed FROM node_revisions nr INNER JOIN node n ON n.vid = nr.vid WHERE n.type = 'article' and nr.uid =". $uid;

$resultquery=mysql_query($selectquery);
$resultquery_all=mysql_query($selectquery_all);

$row_count = mysql_num_rows($resultquery_all);

$page = $row_count / 50;

if(is_float($page)){
	$page = $page + 1;
}

$last = $limit + 49; 

while ($rowquery=mysql_fetch_object($resultquery)){

$update_author_uid=$rowquery->uid;
$update_author_nid=$rowquery->nid;
$update_author_title=$rowquery->title;
$update_author_date=$rowquery->changed;

$update_author = user_load(array('uid' => $update_author_uid));

echo "<tr><td width='70%'>";
 if ($update_author_uid == '0') { // Check if author is anonymous
   // $update_author_output = variable_get('anonymous', 'Anonymous');
  }
  else {    
  
  	$select_dst = "SELECT dst FROM url_alias WHERE src LIKE '%node/".$update_author_nid."%'";
	$result_dst = mysql_query($select_dst);	
	$row_dst = mysql_fetch_row($result_dst);	  
	echo  $update_author_output = l($update_author_title, 'http://192.168.0.100/AH-2012-backup/'.$row_dst[0]);
 
  }
echo "</td>";
echo "<td width='30%'>";
echo format_date($update_author_date, 'custom', "Y - d - M") ;
echo "</td></tr>";
 }?>

</table>
<?php
/* $nodeid =61297;
    if (isset($nodeid)) {
    $result = db_query("SELECT u.name AS last_editor
                                        FROM node_revisions nr, users u
                                           WHERE    nr.uid = u.uid
                                           AND    nr.nid = " .$nodeid. "
                                           ORDER BY timestamp DESC
                                           LIMIT 1");
    $resultset = db_fetch_object($result);
    print "Zuletzt bearbeitet von " . l($resultset->last_editor, 'users/' . $resultset->last_editor) . " am " .format_date($changed);
    } */
?>


<table id="pagingarticle">
	<tr>
			<td> Displaying results <?php echo $limit; ?> to <?php if($last > $row_count){ echo $row_count ; }else{echo $last;} ?> - <?php echo $row_count;  ?></td>
			
		<?php //if($page < 10 ) { 
		
				if($curr_page > 1 ) {?>
				
					<td> <a class="first" href="view-updated-article?uid_touch=<?php echo $uid;?>&page=1" > << first </a> <a class="prev" href="view-updated-article?uid_touch=<?php echo $uid;?>&page=<?php echo $curr_page - 1; ?>"> < previous </a> </td>
					
		<?php 	}
		
				for($i = 1; $i<=$page; $i++){
					if($curr_page == $i){
						$class = "active";
					}else{
						$class = "pageno";
					}?>
				
					<td><a class="<?php echo $class; ?>" href="view-updated-article?uid_touch=<?php echo $uid;?>&page=<?php echo $i; ?>"> <?php  echo $i;  ?> </a> </td>
						
		<?php 		$last_page = $i;
				}
		
				if($curr_page < floor($page)) {
		 ?>
					<td> <a class="next" href="view-updated-article?uid_touch=<?php echo $uid;?>&page=<?php echo $curr_page + 1; ?>" > next > </a> <a class="last" href="view-updated-article?uid_touch=<?php echo $uid;?>&page=<?php echo $last_page; ?>">  last >> </a> </td>
		<?php 
				}
				
				/*
				
			}else{
			
				if($curr_page > 1 ) {		
		 ?>		
					<td> <a href="view-updated-article?uid_touch=<?php echo $uid;?>&page=1" > << first </a> <a href="view-updated-article?uid_touch=<?php echo $uid;?>&page=<?php echo $curr_page - 1; ?>"> < previous </a> </td>
		<?php 	
				}		
				
				for($i = 1; $i<=$page; $i++){ 
				
					if($i <= 10){	
		?>			
						<td><a href="view-updated-article?uid_touch=<?php echo $uid;?>&page=<?php echo $i; ?>"> <?php  echo $i;  ?> </a> </td>
			<?php
					}else{ ?>
					
						<td>...</td>	
			<?php 
					}
					
					$last_page = $i;
					
				}				
		 	
				if($curr_page < floor($page) ) {
			?>
					<td> <a href="view-updated-article?uid_touch=<?php echo $uid;?>&page=<?php echo $curr_page + 1; ?>" > next > </a> <a href="view-updated-article?uid_touch=<?php echo $uid;?>&page=<?php echo $last_page; ?>">  last >> </a> </td>
					
			<?php	
				}
				
			}*/// else if $page>5 ?>
	</tr>
</table>
</div>