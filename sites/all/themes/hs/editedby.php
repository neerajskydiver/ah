<table id="editedby">

<?php 

global $base_url;

 $value_set_order = $_REQUEST['order'];
 $value_set_user  =  $_REQUEST['user'];
 $value_set_title  = $_REQUEST['title'];

if(!isset($_REQUEST['page'])){
$limit = 1;
$page = 1;
$curr_page = 1;
}else{

$page = $_REQUEST['page'];
$curr_page = $_REQUEST['page'];
$limit = (($page * 75) - 75 ) + 1;

}

if ($value_set_order == 'DESC'){

if ($value_set_user == 'OK' || $value_set_user =='' && $value_set_user != ''){

?>
<th><a id="ascedit" class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=ASC&user=OK"> Edited BY</a>
<div id="arrow-down"></div></th>
<th> <a class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=ASC&title=OK"> Title </a>
</th>
<?php }
else if($value_set_title == 'OK' || $value_set_title =='' && $value_set_title !='' ){
?>
<th><a class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=ASC&user=OK"> Edited BY</a>
</th>
<th> <a class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=ASC&title=OK"> Title </a>
<div id="arrow-downtitle"></div></th>
<?php }?>
<th>Updated on </th>
<?php 
}

else if ($value_set_order == '' || $value_set_order == 'ASC') {

if ($value_set_user == 'OK' || $value_set_user =='' && $value_set_user !=''){
?>
<th><a id="ascedit" class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=DESC&user=OK"> Edited BY</a> 
<div id="arrow-up"></div></th>
<th> <a class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=DESC&title=OK"> Title </a>
</th>

<?php }
else if($value_set_title == 'OK' || $value_set_title =='' && $value_set_title != '' ){
?>
<th><a id="ascedit" class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=DESC&user=OK"> Edited BY</a>
</th>
<th> <a class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=DESC&title=OK"> Title </a>
<div id="arrow-uptitle"></div></th>

<?php }

else if( $value_set_title =='' && $value_set_user == ''){

?>
<th><a id="ascedit" class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=DESC&user=OK"> Edited BY</a><div id="arrow-up"></div></th>
<th> <a class="edtby" href="<?php echo $base_url; ?>/content/edited-user?page=<?php echo $page; ?>&order=DESC&title=OK"> Title </a></th>
<?php }
?>

<th>Updated on </th>
 <?php 		
} 
 
 if ($value_set_user == 'OK' && $value_set_order == 'DESC' ){
  
$selectquery="select u.name ,n.title, n.nid ,n.changed ,r.uid from node n inner join node_revisions r on n.nid=r.nid inner join users u on u.uid = r.uid inner join users_roles ur on u.uid =ur.uid where ur.rid = 5 and n.type='article' and r.uid !='' and n.status=1 order by u.name DESC LIMIT {$limit},74 ";
 }
 else if ($value_set_user == 'OK' && $value_set_order == 'ASC' || $value_set_user == '' && $value_set_order == '' ){
$selectquery="select u.name ,n.title, n.nid ,n.changed ,r.uid from node n inner join node_revisions r on n.nid=r.nid inner join users u on u.uid = r.uid inner join users_roles ur on u.uid =ur.uid where ur.rid = 5 and n.type='article' and r.uid !='' and n.status=1 order by u.name ASC  LIMIT {$limit},74 ";
  }
 else if ($value_set_title == 'OK' && $value_set_order == 'DESC' ){
$selectquery="select u.name ,n.title, n.nid ,n.changed ,r.uid from node n inner join node_revisions r on n.nid=r.nid inner join users u on u.uid = r.uid inner join users_roles ur on u.uid =ur.uid where ur.rid = 5 and n.type='article' and r.uid !='' and n.status=1 order by n.title DESC  LIMIT {$limit},74 ";
 }
 else if ($value_set_title== 'OK' && $value_set_order == 'ASC') {
 $selectquery="select u.name ,n.title, n.nid ,n.changed ,r.uid from node n inner join node_revisions r on n.nid=r.nid inner join users u on u.uid = r.uid inner join users_roles ur on u.uid =ur.uid where ur.rid = 5 and n.type='article' and r.uid !='' and n.status=1 order by  n.title ASC  LIMIT {$limit},74 ";
  }
  
  
 //else {
 
// $selectquery="select u.name ,n.title,n.nid ,n.changed ,r.uid from node n inner join node_revisions r on n.nid=r.nid inner join users u on u.uid = r.uid where n.type='article' and r.uid !='' and n.status=1 order by u.name ASC";
 
// }
 
 $get_row_num = "select u.name ,n.title, n.nid ,n.changed ,r.uid from node n inner join node_revisions r on n.nid=r.nid inner join users u on u.uid = r.uid inner join users_roles ur on u.uid =ur.uid where ur.rid = 5 and n.type='article' and r.uid !='' and n.status=1 order by u.name DESC";

$result_row = mysql_query($get_row_num);
    
$resultquery=mysql_query($selectquery);
 
while ($rowquery=mysql_fetch_object($resultquery)){
$node_data=$rowquery;
?>
 <?php
 
   $update_author = $rowquery->name;
   $title = $rowquery->title;
    $nid = $rowquery->nid;
   $updated = $rowquery->changed;
   $update_author_uid = $rowquery->uid;
   
   $row_num = mysql_num_rows($result_row);

   $page = ($row_num / 75);
   
   if(is_float($page)){
		$page = $page + 1;
	}
	
	$last = $limit + 74; 
?>

<tr>
<td width="25%"> <?php

print l($update_author, 'content/view-updated-article', array('query' => array('uid_touch' => $update_author_uid))); 

 ?>
</td>
<td width="50%">
<?php 
$article_node = l($title, drupal_get_path_alias( 'node/' . $nid));
echo $article_node;?>
</td>
<td width="25%">
<?php echo format_date($updated, 'custom', "Y - d - M") ;
?>
</td>
</tr>
<?php
 }?>
</table>

<table id="pagination">
	<tr>
		<td> Displaying results <?php echo $limit; ?> to <?php if($last > $row_num){ echo $row_num ; }else{echo $last;} ?> - <?php echo $row_num;  ?></td>	
		
		<!-- First and Previous logic -->
		<?php if($curr_page > 1){				
		 ?>		
				  <td class="firstandprev"> <a class="first" href="?page=1&order=<?php echo $value_set_order; if(isset($_REQUEST['user'])){ ?>&user=OK <?php }else{ ?>&title=OK <?php } ?>" > << first </a> <a class="prev" href="?page=<?php echo $curr_page - 1; ?>&order=<?php echo $value_set_order; if(isset($_REQUEST['user'])){ ?>&user=OK <?php }else{ ?>&title=OK <?php } ?>"> < previous </a> </td>
		<?php
			  }    
		 ?>
		
		<?php for($i = 1; $i<=$page; $i++){ 
		
				if($curr_page == $i){
					$class = "active";
				}else{
					$class = "pageno";
				}
					
				if ($value_set_order == '' || $value_set_order == 'DESC'){
	
					if(isset($_REQUEST['user'])){
		?>		
					<td><a class="<?php echo $class; ?>" href="?page=<?php echo $i; ?>&order=DESC&user=OK"> <?php  echo $i;  ?> </a> </td>					
		<?php 
					}else{
			?>
					<td><a class="<?php echo $class; ?>" href="?page=<?php echo $i; ?>&order=DESC&title=OK"> <?php  echo $i;  ?> </a> </td>			
			<?php 
					}
		
				}else{
		
					if(isset($_REQUEST['user'])){
		
		?>
					<td><a class="<?php echo $class; ?>" href="?page=<?php echo $i; ?>&order=DESC&user=OK"> <?php  echo $i;  ?> </a> </td>
			
		<?php 
					}else{
		?>		
					<td><a class="<?php echo $class; ?>" href="?page=<?php echo $i; ?>&order=DESC&title=OK"> <?php  echo $i;  ?> </a> </td>		
		<?php		
					}
				}
				
				$last_page = $i;		
			}
	 
	 	if($curr_page < $last_page){ 
	?>	
			<td> <a class="next" href="?page=<?php echo $curr_page + 1; ?>&order=<?php echo $value_set_order; if(isset($_REQUEST['user'])){ ?>&user=OK <?php }else{ ?>&title=OK <?php } ?>" > next > </a> <a class="last" href="?page=<?php echo $last_page; ?>&order=<?php echo $value_set_order; if(isset($_REQUEST['user'])){ ?>&user=OK <?php }else{ ?>&title=OK <?php } ?>">  last >> </a> </td>	
	<?php	
		} ?>
		
	</tr>
</table>