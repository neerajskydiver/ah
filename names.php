<?php

set_time_limit(0);

$directory = ("D:\\xampp\\htdocs\\8may_good_6836");
$dir = opendir($directory);
$files = array();

$filecnt = scandir($directory);
$filecnt = count($filecnt);

while (($file = readdir($dir)) != false) {

  $files[] = $file;

}
$fil =array(2,4,5,6);



print_r($fil);
die;


