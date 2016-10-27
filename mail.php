<?php


$conn = mysql_connect("localhost","root","m317sMKYEEOrlvcAax4p");

if($conn)
	echo "Connection Established";


$db = mysql_select_db("americanheritage",$conn);

if($db)
	echo "Database Selected";

$sql = "DELETE FROM paging_full_record
WHERE DATEDIFF( FROM_UNIXTIME( UNIX_TIMESTAMP( ) ) , FROM_UNIXTIME( `timestamp` ) ) > 2
";


mysql_query($sql);


mysql_close($conn);

$message = "Akshar First Cron";
// Send
mail('akshar.jamgaonkar@gmail.com', 'My Subject', $message);


?>
