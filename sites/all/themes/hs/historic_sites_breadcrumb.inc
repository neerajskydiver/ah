<?php
   session_start(); 
 // drupal_get_breadcrumb();
  $here = end(array_filter(explode("/", $_SERVER['HTTP_REFERER'])));
  
  $nodes=node_load(array("nid" =>  $here));
  $nodetitle= $nodes->title;

  $_SESSION['backnodetitle']=$nodetitle;
  $_SESSION['backnodeid']='node/'.$nodes->nid;
   
  $theme   = explode("?", $here);
  $themes  = $theme[1];
  $themes1 = explode("?", $_SESSION['backpath']);

  $themes2 = explode("field_theme_nid", $themes1[1]);

  $themes3 = explode("field_theme_nid", $themes1[1]);


  /* echo "<pre>";
  print_r($_SESSION);
  //echo $theme[0]."<br>";
  //echo $themes1[0];
  //echo $themes1[1];
  echo $themes2[1];
  echo $themes3[1];
  echo "</pre>";
   exit; 
  */

  if($themes[0]=='count' && $themes1[0]=='historic-sites' && $themes2[1] ){
  $here1='Historic Sites';
  
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  
  if ($themes[1]!='All'){
  $values['titles'][] = 'Themes';
  $values['paths'][] = 'count';
  }
  else if ($themes[2]!='All'){
  $values['titles'][] = 'Types';
  $values['paths'][] = 'types';
  }
  else{
   }
  }
 
  else if($_SESSION['backpath']=='count'){
  $here1='Themes';
  if ($themes[1]!='All'){
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] = 'historic-sites'; 
  $values['titles'][] = 'Themes';
  $values['paths'][] = 'count';
  }
  else if ($themes[2]!='All'){
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] = 'historic-sites'; 
  $values['titles'][] = 'Types';
  $values['paths'][] = 'types';
  }
  else{
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] = 'historic-sites'; 
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  }
  }

  else if($_SESSION['backpath']=='types'){
  $here1='Types';
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] = 'historic-sites'; 
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  }
  else{
  $here1='Historic Sites';
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];

  }
  $values['titles'][] = $nodetitle;
  $values['paths'][] = '<none>';
  /* $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';*/
 
  
  
