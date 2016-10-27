<?php
   session_start(); 
 // drupal_get_breadcrumb();
  $here = end(array_filter(explode("/", $_SERVER['HTTP_REFERER'])));
  
  $nodes=node_load(array("nid" =>  $here));
  $nodetitle= $nodes->title;

  $_SESSION['backnodetitle']=$nodetitle;
  $_SESSION['backnodeid']='node/'.$nodes->nid;
  $test=$_SESSION['backpath'];
  $testpath = explode("?",$test);
  $backpath=$testpath[0];

 /* echo "<pre>";
  print_r($_SESSION);
  //print $_SESSION['backnode'];
  echo $here;
  echo $_SESSION['backpath'];
  echo "</pre>";
  exit;*/
  



  if($_SESSION['backpath']=='navy-museums' || $backpath=='navy-museums'){
  $here1='Navy Museums';
  $values['titles'][] = 'Collections';
  $values['paths'][] = 'search'; 
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath']; 
  }
  else if($_SESSION['backpath']=='search-national-parks' || $backpath=='search-national-parks'){
  $here1='National Parks';
  $values['titles'][] = 'Collections';
  $values['paths'][] = 'search'; 
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  }
  else if($_SESSION['backpath']=='historic-sites' || $backpath=='historic-sites'){
  $here1='Historic Sites';
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  }
  
  else if($_SESSION['backpath']=='count' || $backpath=='count'){
  $here1='Themes';
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] = 'historic-sites'; 
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  }

  else if($_SESSION['backpath']=='types' || $backpath=='types'){
  $here1='Types';
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] = 'historic-sites'; 
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  }

  else if($_SESSION['backpath']=='search' || $backpath=='search')
  {
  $here1='Collections';
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];

  }
  
  $values['titles'][] = $nodetitle;
  $values['paths'][] = '<none>';
  /* $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';*/
 
  
  
