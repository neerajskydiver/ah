<?php

 // drupal_get_breadcrumb();
  $here = end(array_filter(explode("/", $_SERVER['HTTP_REFERER'])));
  $here = explode("?", $here);
  $here =$here[0];

  $nodes=node_load(array("nid" =>  $here));
  $nodetitle= $nodes->title;

  //$_SESSION['backnodetitle']=$nodetitle;
  //$_SESSION['backnodeid']='node/'.$nodes->nid;

   /* echo "<pre>";
     print_r($_SESSION);
     echo $here;
     echo "</pre>";
     exit; */

  if($here=='navy-museums'){
  $here1='Navy Museums';
  $values['titles'][] = Collections;
  $values['paths'][] = 'search'; 
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath']; 
  
  }
  else if($here=='search-national-parks')
  {
  $here1='National Parks';
  $values['titles'][] = Collections;
  $values['paths'][] = 'search'; 
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  
  }
  else if($here=='historic-sites'){
  $here1='Historic Sites';
  $values['titles'][] = $here1;
  $values['paths'][] ='historic-sites';
  $values['titles'][] = $_SESSION['backnodetitle'];
  $values['paths'][] = $_SESSION['backnodeid'];
  }
  else if($here=='count'){
  $here1='Themes';
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] ='historic-sites';
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  }
  else if($here=='types'){
  $here1='Types';
  $values['titles'][] = 'Historic Sites';
  $values['paths'][] ='historic-sites';
  $values['titles'][] = $here1;
  $values['paths'][] = $_SESSION['backpath'];
  }
  else if($here=='search') 
  {
   $here1='Collections';
   $values['titles'][] = $here1;
   $values['paths'][] ='search';
   //$values['titles'][] = $_SESSION['backnodetitle'];
  // $values['paths'][] = $_SESSION['backnodeid'];
  }

  else if($here=='search-landing-page') 
  {
   $here1='Collections';
   $values['titles'][] = $here1;
   $values['paths'][] ='search';
   //$values['titles'][] = $_SESSION['backnodetitle'];
  // $values['paths'][] = $_SESSION['backnodeid'];
  }


  else if($here=='search-landing-page' && $_SESSION['backpath']=='historic-sites') 
  {
   $here1='Historic Sites';
   $values['titles'][] = $here1;
   $values['paths'][] ='sites-data';
   $values['titles'][] = $_SESSION['backnodetitle'];
   $values['paths'][] = $_SESSION['backnodeid'];
  }
  else if($here=='search-landing-page' && $_SESSION['backpath']=='search') 
  {
   $here1='Collections';
   $values['titles'][] = $here1;
   $values['paths'][] ='sites-data';
   $values['titles'][] = $_SESSION['backnodetitle'];
   $values['paths'][] = $_SESSION['backnodeid'];
  }
  else if($here=='search-landing-page' && $_SESSION['backpath']=='navy-museums') 
  {
   $here1='Collections';
   $values['titles'][] = $here1;
   $values['paths'][] ='search';
   $values['titles'][] = "Navy Museums";
   $values['paths'][] = $_SESSION['backpath'];
   $values['titles'][] = $_SESSION['backnodetitle'];
   $values['paths'][] = $_SESSION['backnodeid'];

  }
  else if($here=='search-landing-page' && $_SESSION['backpath']=='count') 
  {
   $here1='Historic Sites';
   $values['titles'][] = $here1;
   $values['paths'][] ='historic-sites';
   $values['titles'][] = "Themes";
   $values['paths'][] = $_SESSION['backpath'];
   $values['titles'][] = $_SESSION['backnodetitle'];
   $values['paths'][] = $_SESSION['backnodeid'];

  }
  else if($here=='search-landing-page' && $_SESSION['backpath']=='types') 
  {
   $here1='Historic Sites';
   $values['titles'][] = $here1;
   $values['paths'][] ='historic-sites';
   $values['titles'][] = "Types";
   $values['paths'][] = $_SESSION['backpath'];
   $values['titles'][] = $_SESSION['backnodetitle'];
   $values['paths'][] = $_SESSION['backnodeid'];

  }
  
  else if($here=='search-landing-page' && $_SESSION['backpath']=='search-national-parks') 
  {
   $here1='Collections';
   $values['titles'][] = $here1;
   $values['paths'][] ='search';
   $values['titles'][] = "National Parks";
   $values['paths'][] = $_SESSION['backpath'];
   $values['titles'][] = $_SESSION['backnodetitle'];
   $values['paths'][] = $_SESSION['backnodeid'];

  }

  else if($here=='search-landing-page') 
  {
   $here1='Collections';
   $values['titles'][] = $here1;
   $values['paths'][] ='search';
   $values['titles'][] = $_SESSION['backpath'];
   $values['paths'][] = $_SESSION['backpath'];
   $values['titles'][] = $_SESSION['backnodetitle'];
   $values['paths'][] = $_SESSION['backnodeid'];
  }

  else {
    $values['titles'][] ='Collections';
    $values['paths'][] = 'search';

   } 
  $values['titles'][] = $node->title;
  $values['paths'][] = '<none>';
 
  
  






