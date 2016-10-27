<?php
   session_start(); 
  $here = end(array_filter(explode("/", $_SERVER['HTTP_REFERER'])));
  //$here = explode("?", $here);
  //$here =$here[0];
  $_SESSION['backpath']=$here; 

  /* echo "<pre>";
  print_r($_SESSION);
  //print $_SESSION['backnode'];
  echo $here;
  //echo $_SESSION['backpath'];
  echo "</pre>";
  exit;
  */

  if($here=='historic-sites'){
  $here1='Historic Sites';
  $values['titles'][] = $here1;
  $values['paths'][] = $here;
  $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';
  }
  else if($here=='search') {
  $here1='Collections';
  $values['titles'][] = $here1;
  $values['paths'][] = $here;
  $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';
  
  }
  else if($here=='search-national-parks')
  {
  $here1='National Parks';
  $values['titles'][] = Collections;
  $values['paths'][] = 'search';
  $values['titles'][] = $here1;
  $values['paths'][] = $here;
  $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';
  }
  else if ($here=='navy-museums')
  {
  $here1='Navy Museums';
  $values['titles'][] = Collections;
  $values['paths'][] = 'search';
  $values['titles'][] = $here1;
  $values['paths'][] = $here;
  $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';
  }
  else if($here=='count')
  {
  $here1='Themes';
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] = 'hitoric-sites';
  $values['titles'][] = $here1;
  $values['paths'][] = $here;
  $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';
  }
  else if($here=='types')
  {
  $here1='Types';
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] = 'hitoric-sites';
  $values['titles'][] = $here1;
  $values['paths'][] = $here;
  $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';
  }


  else{
  $here='search';
  $here1='Collections';
  $values['titles'][] = $here1;
  $values['paths'][] = $here;
  $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';

   }
  