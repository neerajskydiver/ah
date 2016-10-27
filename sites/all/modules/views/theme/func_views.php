<?php 
function print_search(){
	$output="<p id='descriptiontext'>Search the most comprehensive national collection of historic 
	artifacts, photographs, paintings, and documents in the U.S.<br>  &nbsp; <br> Tens of thousands 
	of never-before-seen treasures are at your fingertips. For the first time, you can access the 
	internal collections data of many of America&rsquo;s leading museums, National Parks, and 
	historical societies.&nbsp; <br> <br>  Discover. Collect. Share. The National Portal brings 
	history to your desktop</p>";
	return $output;  
}
function print_civil(){
$output="<p id='descriptiontext'>The Civil War tore through the United States in 1861, dividing families and 
	turning countrymen into mortal enemies. By the time it ended four years later, it had left behind hundreds 
	of thousands of casualties, a ruined Southern economy, and a complicated legacy of emancipation.
	<br> <br> Yet it also produced countless artifacts and documents through which we may better understand the
	period. Search these Civil War collections to find the guns with which the war was fought, the uniforms that
	soldiers wore into battle, the letters they wrote home, and many other items from one of the most transformative
	periods of American history.</p>";
return $output;  
}
function print_smith(){
$output="<p id='descriptiontext'>Founded in 1846 from a bequest by British scientist John Smithson, 
	the Smithsonian Institution	is today the largest museum complex in the world. It comprises nineteen museums, 
	nine research centers, and a zoo. Its 156 million collection items cover everything from biology and chemistry 
	to American history and technological innovation.
	<br /><br />
	The Smithsonian's National Portal collection includes a number of prominent Civil War artifacts, such as Abraham
	Lincoln's top hat, George B.<br />
	McClellan's sword, and JEB Stuart's pistol. It also features dozens of historic guitars, airplanes, and 
	Native American relics.</p>";
return $output;  
}
function print_national(){
$output="<p id='descriptiontext'>The National Park Service operates one of the world&rsquo;s 
	largest systems of museums. Now you can search through their historic artifacts and photographs
	from one convenient page.&nbsp; <br> <br> Many of these historic treasures have never been seen
	before by the public. Go behind the exhibits in hallowed places such as Gettysburg, Shiloh and 
	Valley Forge to discover America&rsquo;s fascinating past.</p>";
	$element['#title'] = t('Search All Collections ');
return $output;  
}
function print_navy(){
$output="<p id='descriptiontext'>The U.S. Navy&rsquo;s History and Heritage Command operates 12 museums, 
	maintains extensive collections, and offers a variety of public programs and publications. 
	Its mission is to bring alive the history, legacy and traditions of the Navy. <p id='descriptiontext'>On
	this page you can search many of NHHC&rsquo;s historic artifacts, artworks and photographs&#8211;either
	for all collections at once or for individual collections by clicking on the institution below.<br> 
	In addition to the official Navy museums, we offer access to a number of other important Naval and
	Maritime collections below.</p>";
return $output;  
}


function search_collections(){

$node = node_load(arg(1));
$site_name = $node->title;
$view->page_title = $node->title;
$output="";
if(arg(0)=="search-collections" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
{
	$output.= "
	<fieldset><legend>Select a Collection</legend><table><tr><th>State</th><th>City</th><th>Sites</th></tr>";
	$previous ='';
	
	$selectid ="select DISTINCT(node_state.title) AS 
	state_title,content_type_bookmarks_sites.field_city_value
	,node_bookmarks_sites.title AS site ,content_type_bookmarks_sites.nid
	from content_type_bookmarks_sites INNER JOIN node node_bookmarks_sites  ON 
	node_bookmarks_sites.nid = content_type_bookmarks_sites.nid AND node_bookmarks_sites.type= 
	'bookmarks_sites' LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND 
	node_state.type = 'state' inner join content_type_collection on 
	content_type_collection.field_site_id_nid=content_type_bookmarks_sites.nid where 
	node_bookmarks_sites.status=1 order by 
	node_state.title,content_type_bookmarks_sites.field_city_value,node_bookmarks_sites.title asc";

	$resultid = db_query($selectid);
	while ($All = db_fetch_array($resultid)) 
	{
	$city=$All['field_city_value'];
	$sites=$All['site'];
	$state=$All['state_title'];
	
	if ($city=="Washington DC"){$city="Washington";}
	
	if ($All['state_title'] != $previous)
	{
	if($state=="District of Columbia"){$state="DC";}
	else {$state=$All['state_title']; }
	}
	
	else {$state =''; }

	$sitesnid=$All['nid'];
	/*$output.= "	<tr>
				<td valign='top'> $state</td>
				<td valign='top'>$city</td>
				<td valign='top'><a href='node/$sitesnid?nid=$sitesnid'>$sites</a>
				</td></tr>";
	*/
	$options = array(
    'query' => array(
      'nid' => $sitesnid
     )
  ); 
	$output.= "	<tr>
				<td valign='top'> $state</td>
				<td valign='top'>$city</td>
				<td valign='top'>";
	$output.= l($sites,"node/$sitesnid",$options);
	$output.= "</td></tr>";
	
	$previous = $All['state_title'];
	}
	$output.= "</table></fieldset>";
       }
	 	return $output;  
}

function search_smithsonian_museum(){
$output="";
$node = node_load(arg(1));
$site_name = $node->title;
$view->page_title = $node->title;


	if(arg(0)=="search-smithsonian-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{ 
	 $output.= "
	 <fieldset><legend>Select a Collection</legend><table><tr><th>Sites</th><th>City</th><th>State</th></tr>";
	$previous ='';
	
	$selectid ="SELECT DISTINCT(node_bookmarks_sites.title) as 
	site,node_bookmarks_sites.nid,node_state.title as 
	state,content_type_bookmarks_sites.field_city_value FROM node
	inner join term_node  ON node.vid = term_node.vid
	inner join term_data  ON term_node.tid = term_data.tid
	inner join content_type_collection  ON node.vid = content_type_collection.vid inner join 
	content_type_bookmarks_sites  on 
	content_type_bookmarks_sites.nid=content_type_collection.field_site_id_nid inner join node 
	node_bookmarks_sites on node_bookmarks_sites.nid=content_type_bookmarks_sites.nid and 
	node_bookmarks_sites.type='bookmarks_sites'
	LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND 
	node_state.type = 'state' 
	WHERE term_data.tid = 5084 and node_bookmarks_sites.status=1 ORDER BY node_bookmarks_sites.title 
	ASC";


	$resultid = db_query($selectid);
	while ($rowid = db_fetch_array($resultid))
	{
	 $sitesid=$rowid['site'];
	 $sitesnid=$rowid['nid'];
	$sitesstate=$rowid['state'];
   	$sitescity=$rowid['field_city_value'];
    
	if ($rowid['state'] != $previous)
	{
	if($sitesstate=="District of Columbia"){$sitesstate="DC";}
	else {$sitesstate=$rowid['state']; }
	}
	else {$sitesstate =''; }

	if ($sitescity=="Washington DC"){$sitescity="Washington";}

	$options = array(
			'query' => array(
			  'nid' => $sitesnid
			 )
	  ); 

    $output.= "<tr>
				<td valign='top'>";
	$output.= l($sitesid,"node/$sitesnid",$options);
				/*<a href='node/$sitesnid?nid=$sitesnid'>$sitesid</a>*/
	$output.= "</td><td valign='top'>$sitescity</td>
				<td valign='top'>$sitesstate</td>
				</tr>";
	$previous = $All['state'];
	}
	$output.= "</table></fieldset>";
	}	
	return $output;
}


function search_civilwar_museum(){
$output="";
$node = node_load(arg(1));
$site_name = $node->title;
$view->page_title = $node->title;


if(arg(0)=="search-civilwar-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
{ 

	$output.="
			<fieldset>
			<legend>Select a Collection</legend>
			<table>
			<tr><th>Sites</th><th>City</th><th>State</th></tr>";
	$previous ='';

	$selectid ="SELECT DISTINCT(node_bookmarks_sites.title) as 
	site,node_bookmarks_sites.nid,node_state.title as 
	state,content_type_bookmarks_sites.field_city_value FROM node
	inner join term_node  ON node.vid = term_node.vid
	inner join term_data  ON term_node.tid = term_data.tid
	inner join content_type_collection  ON node.vid = content_type_collection.vid inner join 
	content_type_bookmarks_sites  on 
	content_type_bookmarks_sites.nid=content_type_collection.field_site_id_nid inner join node 
	node_bookmarks_sites on node_bookmarks_sites.nid=content_type_bookmarks_sites.nid and 
	node_bookmarks_sites.type='bookmarks_sites'
	LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND 
	node_state.type = 'state' 
	WHERE term_data.tid = 5085 and node_bookmarks_sites.status=1 ORDER BY node_bookmarks_sites.title 
	ASC";


	$resultid = db_query($selectid);
	while ($rowid = db_fetch_array($resultid))
	{
	$sitesid=$rowid['site'];
	$sitesnid=$rowid['nid'];
	$sitesstate=$rowid['state'];
   	$sitescity=$rowid['field_city_value'];
    if ($rowid['state'] != $previous)
	{
	if($sitesstate=="District of Columbia"){$sitesstate="DC";}
	else {$sitesstate=$rowid['state']; }
	}
	else {$sitesstate =''; }

	if ($sitescity=="Washington DC"){$sitescity="Washington";}

/*	 $output.= "
	 <tr>
	 <td valign='top'><a href='node/$sitesnid?nid=$sitesnid'>$sitesid</a></td>
	 <td valign='top'>$sitescity</td>
	 <td valign='top'>$sitesstate</td>
	 </tr>";
*/

	$options = array(
			'query' => array(
			  'nid' => $sitesnid
			 )
	  ); 


	 $output.= "
	 <tr>
	 <td valign='top'>";
     $output .= l($sitesid,"node/$sitesnid",$options);
	 $output .= "</td><td valign='top'>$sitescity</td>
	 <td valign='top'>$sitesstate</td>
	 </tr>";



	$previous = $All['state'];

 		
	}
	$output.= "</table></fieldset>";
	}	
	
	return $output;
}

function search_navy_museum(){
$output="";
$node = node_load(arg(1));
$site_name = $node->title;
$view->page_title = $node->title;

if(arg(0)=="search-navy-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
{

/* commented by prachi 
	$selectTermTest ="SELECT DISTINCT(node_bookmarks_sites.title) as site 
	,node_bookmarks_sites.nid,node_state.title as state 
	,content_type_bookmarks_sites.field_city_value FROM node
	inner join term_node  ON node.vid = term_node.vid
	inner join term_data  ON term_node.tid = term_data.tid
	inner join content_type_collection  ON node.vid = content_type_collection.vid inner join 
	content_type_bookmarks_sites  on 
	content_type_bookmarks_sites.nid=content_type_collection.field_site_id_nid inner join node 
	node_bookmarks_sites on node_bookmarks_sites.nid=content_type_bookmarks_sites.nid and 
	node_bookmarks_sites.type='bookmarks_sites'
	LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND 
	node_state.type = 'state' 
	WHERE term_data.tid = 4452 and node_bookmarks_sites.status=1 ORDER BY node_bookmarks_sites.title 
	ASC";
	$resultTermTest = db_query($selectTermTest);
	while($rowTest=db_fetch_array($resultTermTest))
	{
	$NidArray[]=$rowTest['nid'];
	}

	$TestExplode=implode(",",$NidArray);
if ($TestExplode)
{
	$selectTerm1 ="SELECT DISTINCT(node_bookmarks_sites.title) as site 
	,node_bookmarks_sites.nid,node_state.title as state 
	,content_type_bookmarks_sites.field_city_value FROM node
	inner join term_node  ON node.vid = term_node.vid
	inner join term_data  ON term_node.tid = term_data.tid
	inner join content_type_collection  ON node.vid = content_type_collection.vid inner join 
	content_type_bookmarks_sites  on 
	content_type_bookmarks_sites.nid=content_type_collection.field_site_id_nid inner join node 
	node_bookmarks_sites on node_bookmarks_sites.nid=content_type_bookmarks_sites.nid and 
	node_bookmarks_sites.type='bookmarks_sites'
	LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND 
	node_state.type = 'state' 
	WHERE term_data.tid =4451 and node_bookmarks_sites.status=1 and node_bookmarks_sites.nid NOT IN 
	($TestExplode) ORDER BY node_bookmarks_sites.title ASC";
}
else
{ }
*/
	$selectTerm1 ="SELECT DISTINCT(node_bookmarks_sites.title) as site 
	,node_bookmarks_sites.nid,node_state.title as 
	state,content_type_bookmarks_sites.field_city_value FROM node
	inner join term_node  ON node.vid = term_node.vid
	inner join term_data  ON term_node.tid = term_data.tid
	inner join content_type_collection  ON node.vid = content_type_collection.vid inner join 
	content_type_bookmarks_sites  on 
	content_type_bookmarks_sites.nid=content_type_collection.field_site_id_nid inner join node 
	node_bookmarks_sites on node_bookmarks_sites.nid=content_type_bookmarks_sites.nid and 
	node_bookmarks_sites.type='bookmarks_sites'
	LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND 
	node_state.type = 'state' 
	WHERE term_data.tid =4451 and node_bookmarks_sites.status=1  ORDER BY node_bookmarks_sites.title 
	ASC";

	$resultTerm1 = db_query($selectTerm1);


	$selectTerm2 ="SELECT DISTINCT(node_bookmarks_sites.title) as site 
	,node_bookmarks_sites.nid,node_state.title as state 
	,content_type_bookmarks_sites.field_city_value FROM node
	inner join term_node  ON node.vid = term_node.vid
	inner join term_data  ON term_node.tid = term_data.tid
	inner join content_type_collection  ON node.vid = content_type_collection.vid inner join 
	content_type_bookmarks_sites  on 
	content_type_bookmarks_sites.nid=content_type_collection.field_site_id_nid inner join node 
	node_bookmarks_sites on node_bookmarks_sites.nid=content_type_bookmarks_sites.nid and 
	node_bookmarks_sites.type='bookmarks_sites'
	LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND 
	node_state.type = 'state' 
	WHERE term_data.tid = 4452 and node_bookmarks_sites.status=1 ORDER BY node_bookmarks_sites.title 
	ASC";
	$resultTerm2 = db_query($selectTerm2);



	$output.= "<fieldset>
	<legend>Select a Collection</legend>";
	$output.= "<table>
	<tr>
	<td colspan='3'><font size=2><b>Official U.S. Navy Collections</b></font>
	</td></tr>
	<tr>
	<th>Sites</th>
	<th>City</th>
	<th>State</th>
	</tr>";

	$previous ='';
	while($AllTerm1=db_fetch_array($resultTerm1 ))
	{
	$sitesid=$AllTerm1['site'];
	$sitesnid=$AllTerm1['nid'];
	$sitesstate=$AllTerm1['state'];
   	$sitescity=$AllTerm1['field_city_value'];

      if ($AllTerm1['state'] != $previous)
	{
	if($sitesstate=="District of Columbia"){$sitesstate="DC";}else 
	{$sitesstate=$AllTerm1['state']; }
	}
	else {$sitesstate =''; }

	if ($sitescity=="Washington DC"){$sitescity="Washington";}


	$options = array(
			'query' => array(
			  'nid' => $sitesnid
			 )
	  ); 

	$output.= "<tr>
	<td width='60%' valign='top'>";
    $output .= l($sitesid,"node/$sitesnid",$options);
	$output.= "</td>
	<td width='20%' valign='top'>$sitescity</td><td width='20%' valign='top'>$sitesstate</td>
	</tr>";	
	$previous = $All['state'];

	}

	$output.= "</table>";

	$output.= " <table>
				<tr>
				<td colspan='3'>
				<font size=2><b>Collections Related to Naval and Maritime History</b></font></td>
				</tr>";
	$output.="	<tr>
				<th>Sites</th>
				<th>City</th><th>State</th>
				</tr>";
	$output.="	<tr>
				<td colspan='3'></td>
				</tr>";
$previous ='';
while($AllTerm2=db_fetch_array($resultTerm2))
{
	
	$sitesid=$AllTerm2['site'];
	$sitesnid=$AllTerm2['nid'];
	$sitesstate=$AllTerm2['state'];
   	$sitescity=$AllTerm2['field_city_value'];
       if ($AllTerm2['state'] != $previous)
	{
	if($sitesstate=="District of Columbia"){$sitesstate="DC";}else 
	{$sitesstate=$AllTerm2['state']; }
	}
	else {$sitesstate =''; }

	if ($sitescity=="Washington DC"){$sitescity="Washington";}

/*	$output.= "	<tr>
				<td width='60%' valign='top'>
				<a href='node/$sitesnid?nid=$sitesnid'>$sitesid</a></td>
				<td width='20%' valign='top'>$sitescity</td>
				<td width='20%' valign='top'>$sitesstate</td></tr>";
*/

	$options = array(
			'query' => array(
			  'nid' => $sitesnid
			 )
	  ); 

	$output .= "<tr>
				<td width='60%' valign='top'>";
    $output .= l($sitesid,"node/$sitesnid",$options);
	$output .= "</td><td width='20%' valign='top'>$sitescity</td>
				<td width='20%' valign='top'>$sitesstate</td></tr>";



	$previous = $All['state'];

	}
	$output.= "</table></fieldset>";
  	}
	return $output;

}


function search_national_parks(){
$output="";
$node = node_load(arg(1));
$site_name = $node->title;
$view->page_title = $node->title;
	
	if(arg(0)=="search-national-parks" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{

	$output.= "	<fieldset>
				<legend>Select a Collection</legend>
				<table>
				<tr>
				<th>Sites</th>
				<th>City</th>
				<th>State</th>
				</tr>";
	$previous ='';
	$selectid ="SELECT DISTINCT(node_bookmarks_sites.title) as site,node_bookmarks_sites.nid,node_state.title as 
	state,content_type_bookmarks_sites.field_city_value FROM node inner join term_node  ON node.vid = term_node.vid
	inner join term_data  ON term_node.tid = term_data.tid
	inner join content_type_collection  ON node.vid = content_type_collection.vid inner join 
	content_type_bookmarks_sites  on 
	content_type_bookmarks_sites.nid=content_type_collection.field_site_id_nid inner join node 
	node_bookmarks_sites on node_bookmarks_sites.nid=content_type_bookmarks_sites.nid and 
	node_bookmarks_sites.type='bookmarks_sites'
	LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND 
	node_state.type = 'state' 
	WHERE term_data.tid = 4445 and node_bookmarks_sites.status=1 ORDER BY node_bookmarks_sites.title 
	ASC";


	$resultid = db_query($selectid);
	while ($rowid = db_fetch_array($resultid))
	{
	$sitesid=$rowid['site'];
	$sitesnid=$rowid['nid'];
	$sitesstate=$rowid['state'];
   	$sitescity=$rowid['field_city_value'];
    if ($rowid['state'] != $previous)
	{
	if($sitesstate=="District of Columbia"){$sitesstate="DC";}
	else {$sitesstate=$rowid['state']; }
	}
	else {$sitesstate =''; }

	if ($sitescity=="Washington DC"){$sitescity="Washington";}

	/*$output.= "
				<tr>
				<td valign='top'>
				<a href='node/$sitesnid?nid=$sitesnid'>$sitesid</a></td>
				<td valign='top'>$sitescity</td>
				<td valign='top'>$sitesstate</td></tr>";
	*/
	
	$options = array(
			'query' => array(
			  'nid' => $sitesnid
			 )
	  ); 

	
	$output .= "<tr>
				<td valign='top'>";
    $output .= l($sitesid,"node/$sitesnid",$options);
	$output .= "</td><td valign='top'>$sitescity</td>
				<td valign='top'>$sitesstate</td></tr>";
	
	$previous = $All['state'];
 		
	}
	$output.= "</table></fieldset>";
	}
	return $output;
	
}


?>