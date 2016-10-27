<?php
$con = mysql_connect('localhost','root','m317sMKYEEOrlvcAax4p');
//$con = mysql_connect('localhost','root','123456');
if($con){
	echo "connected";
}else{
	echo "problem in connection";
}
$db = mysql_select_db('americanheritage_29thmarch');
if($db){
	echo "db selected";
}else{
	echo "problem in selecting db";
}
echo "<br>";

/*
echo $q = "SELECT title,nid FROM node_revisions  ORDER BY nid LIMIT ".$_GET['start'].", 10000 ";
$r = mysql_query($q);
while($res = mysql_fetch_assoc($r)){
		$q_u = "UPDATE node_revisions SET title = '".ucwords(strtolower($res['title']))."' WHERE nid = ".$res['nid']." "; 
		$r_u = mysql_query($q_u);
}

 */

echo $q = "SELECT title,nid FROM node  ORDER BY nid LIMIT ".$_GET['start'].", 10000 ";
$r = mysql_query($q);
while($res = mysql_fetch_assoc($r)){
		$q_u = "UPDATE node SET title = '".ucwords(strtolower($res['title']))."' WHERE nid = ".$res['nid']." "; 
		$r_u = mysql_query($q_u);
}



?>