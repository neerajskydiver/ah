<?php
// $Id: views-exposed-form.tpl.php,v 1.4.4.1 2009/11/18 20:37:58 merlinofchaos Exp $
/**
 * @file views-exposed-form.tpl.php
 *
 * This template handles the layout of the views exposed filter form.
 *
 * Variables available:
 * - $widgets: An array of exposed form widgets. Each widget contains:
 * - $widget->label: The visible label to print. May be optional.
 * - $widget->operator: The operator for the widget. May be optional.
 * - $widget->widget: The widget itself.
 * - $button: The submit button for the form.
 *
 * @ingroup views_templates
 */

?>
<?php 
if (!empty($q)): 
    // This ensures that, if clean URLs are off, the 'q' is added first so that
    // it shows up first in the URL.
    print $q;
endif; ?>
<?php
$node = node_load(arg(1));
$site_name = $node->title;
$view->page_title = $node->title;

/********************/
$content='
<div class="views-exposed-form">
<div class="views-exposed-widgets">
<div class="views-exposed-widget" style="clear:left;">';

    foreach($widgets as $id => $widget) 
	{


  
          if (!empty($widget->label)) 
		  {
	      $content.='<div class="views-widget" style="width:100%;"><label for="'. 
$widget->id.'">';
          $content.=$widget->label;
          $content.='</label>';
      	  }
      if (!empty($widget->operator))
	    {
        $content.='<div class="views-operator">';
        $content.=$widget->operator;
        $content.='</div>';
        }
        $content.=$widget->widget;
    }
  		$content.=$button;
  		if (arg(0)!="historic-sites" )
		{
/*  		$content.='<div id="additional_search">
				   <a href="#"> &raquo; Advanced</a>
				   <br/>
				   <a href="#"> &raquo; Tips</a>
				   </div>';
*/  		}
		  $content.='</div></div></div></div>';
		  $element = array();
		  $element['#collapsible'] = false;
		  $element['#collapsed'] = false;
		  $element['#value'] = $content;
  
/*******************************/

if(arg(0)=='search-collections')
{

	if(arg(0)=="search-collections" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
	
print "<p id='descriptiontext'>Search the most comprehensive national collection of historic 
artifacts, photographs, paintings, and documents in the U.S.<br>  &nbsp; <br> Tens of thousands 
of never-before-seen treasures are at your fingertips. For the first time, you can access the 
internal collections data of many of America&rsquo;s leading museums, National Parks, and 
historical societies.&nbsp; <br> <br>  Discover. Collect. Share. The National Portal brings 
history to your desktop</p>";	$element['#title'] = t('Search All Collections ');
	}
	else
	{
	$element['#title'] = t('Search This Collection');
   	}
     print theme('fieldset', $element);
	if(arg(0)=="search-collections" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
	 echo "<fieldset><legend>Select a 
Collection</legend><table><tr><th>State</th><th>City</th><th>Sites</th></tr>";
$previous ='';
$selectid ="select DISTINCT(node_state.title) AS 
state_title,content_type_bookmarks_sites.field_city_value
,node_bookmarks_sites.title AS site ,content_type_bookmarks_sites.nid
from content_type_bookmarks_sites INNER JOIN node node_bookmarks_sites  ON 
node_bookmarks_sites.nid = content_type_bookmarks_sites.nid AND node_bookmarks_sites.type= 
'bookmarks_sites' 
LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND 
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
	if($state=="District of Columbia"){$state="DC";}else {$state=$All['state_title']; }
	}
	else {$state =''; }

	$sitesnid=$All['nid'];
	echo "<tr><td valign='top'> $state</td><td valign='top'>$city</td><td valign='top'><a 
href='node/$sitesnid?nid=$sitesnid'>$sites</a></td></tr>";
	$previous = $All['state_title'];

	}
	echo "</table></fieldset>";
       }
}

if(arg(0)=='search-smithsonian-museum')
{

	if(arg(0)=="search-smithsonian-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
print "<p id='descriptiontext'>Founded in 1846 from a bequest by British scientist John Smithson, the Smithsonian Institution is today the largest museum complex in the world. It comprises nineteen museums, nine research centers, and a zoo. Its 156 million collection items cover everything from biology and chemistry to American history and technological innovation.
<br /><br />
The Smithsonian's National Portal collection includes a number of prominent Civil War artifacts, such as Abraham Lincoln's top hat, George B.<br />
McClellan's sword, and JEB Stuart's pistol. It also features dozens of historic guitars, airplanes, and Native American relics.</p>";	
$element['#title'] = t('Search All Collections ');

}
else
	{
	//$element['#title'] = t('Search This Collection');
   	}
print theme('fieldset', $element);
	if(arg(0)=="search-smithsonian-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{  echo "<fieldset><legend>Select a 
Collection</legend><table><tr><th>Sites</th><th>City</th><th>State</th></tr>";
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
	if($sitesstate=="District of Columbia"){$sitesstate="DC";}else 
{$sitesstate=$rowid['state']; }
	}
	else {$sitesstate =''; }

	if ($sitescity=="Washington DC"){$sitescity="Washington";}

 	echo "<tr><td valign='top'><a href='node/$sitesnid?nid=$sitesnid'>$sitesid</a></td><td 
valign='top'>$sitescity</td><td valign='top'>$sitesstate</td></tr>";
	$previous = $All['state'];

 		//echo "<tr><td><a href='node/$sitesnid'>$sitesid</a></td></tr>";
	}
		echo "</table></fieldset>";
	}	
	
}


if(arg(0)=='search-civilwar-museum')
{

	if(arg(0)=="search-civilwar-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
print "<p id='descriptiontext'>The Civil War tore through the United States in 1861, dividing families and turning countrymen into mortal enemies. By the time it ended four years later, it had left behind hundreds of thousands of casualties, a ruined Southern economy, and a complicated legacy of emancipation.
 <br> <br> 
Yet it also produced countless artifacts and documents through which we may better understand the period. Search these Civil War collections to find the guns with which the war was fought, the uniforms that soldiers wore into battle, the letters they wrote home, and many other items from one of the most transformative periods of American history.

</p>";	
$element['#title'] = t('Search All Collections ');

}
else
	{
	//$element['#title'] = t('Search This Collection');
   	}
	print theme('fieldset', $element);
	if(arg(0)=="search-civilwar-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{  echo "<fieldset><legend>Select a 
Collection</legend><table><tr><th>Sites</th><th>City</th><th>State</th></tr>";
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
	if($sitesstate=="District of Columbia"){$sitesstate="DC";}else 
{$sitesstate=$rowid['state']; }
	}
	else {$sitesstate =''; }

	if ($sitescity=="Washington DC"){$sitescity="Washington";}

 	echo "<tr><td valign='top'><a href='node/$sitesnid?nid=$sitesnid'>$sitesid</a></td><td 
valign='top'>$sitescity</td><td valign='top'>$sitesstate</td></tr>";
	$previous = $All['state'];

 		//echo "<tr><td><a href='node/$sitesnid'>$sitesid</a></td></tr>";
	}
		echo "</table></fieldset>";
	}	
	
}






if(arg(0)=='search-navy-museum')
{
	if(arg(0)=="search-navy-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
print "<p id='descriptiontext'>The U.S. Navy&rsquo;s History and Heritage Command operates 12 
museums, maintains extensive collections, and offers a variety of public programs and 
publications. Its mission is to bring alive the history, legacy and traditions of the Navy.  
<p id='descriptiontext'>On this page you can search many of NHHC&rsquo;s historic artifacts, 
artworks and photographs&#8211;either for all collections at once or for individual collections 
by clicking on the institution below.
<p id='descriptiontext'>In addition to the official Navy museums, we offer access to a number of 
other important Naval and Maritime collections below.
</p>";	
$element['#title'] = t('Search All Collections ');

	}
	else
	{
	$element['#title'] = t('Search This Collection');
   	}
       print theme('fieldset', $element);
	if(arg(0)=="search-navy-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
 /* test */

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
if ($TestExplode){
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
}else{
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

}
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


/* test */
echo "<fieldset><legend>Select a Collection</legend>";
echo "<table><tr><td colspan='3'><font size=2><b>Official U.S. Navy 
Collections</b></font></td></tr>
<tr><th>Sites</th><th>City</th><th>State</th></tr>";

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

echo "<tr><td width='60%' valign='top'><a href='node/$sitesnid?nid=$sitesnid'>$sitesid</a></td><td width='20%' 
valign='top'>$sitescity</td><td width='20%' valign='top'>$sitesstate</td></tr>";	
$previous = $All['state'];

	}

echo "</table>";

echo "<table><tr><td colspan='3'><font size=2><b>Collections Related to Naval and Maritime 
History
</b></font></td></tr>";
echo "<tr><th>Sites</th><th>City</th><th>State</th></tr>";
echo "<tr><td colspan='3'></td></tr>";
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

echo "<tr><td width='60%' valign='top'><a href='node/$sitesnid?nid=$sitesnid'>$sitesid</a></td><td width='20%' 
valign='top'>$sitescity</td><td width='20%' valign='top'>$sitesstate</td></tr>";
$previous = $All['state'];

}
echo "</table></fieldset>";
  }

}


if(arg(0)=='search-national-parks')
{
	if(arg(0)=="search-national-parks" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
			print "<p id='descriptiontext'>The National Park Service operates one of 
the world&rsquo;s largest systems of 	museums. Now you can search through their historic 
artifacts and photographs from one convenient page.&nbsp; <br> <br> 
			Many of these historic treasures have never been seen before by the 
public. Go behind the exhibits in hallowed places such as Gettysburg, Shiloh and Valley Forge to 
discover America&rsquo;s fascinating past.
			</p>";
		$element['#title'] = t('Search All Collections ');
		 print theme('fieldset', $element);
	}
	else
	{
		//$element['#title'] = t('Search This Collection');
 	 }
      	
	if(arg(0)=="search-national-parks" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{

  echo "<fieldset><legend>Select a 
Collection</legend><table><tr><th>Sites</th><th>City</th><th>State</th></tr>";
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
	if($sitesstate=="District of Columbia"){$sitesstate="DC";}else 
{$sitesstate=$rowid['state']; }
	}
	else {$sitesstate =''; }

	if ($sitescity=="Washington DC"){$sitescity="Washington";}

 	echo "<tr><td valign='top'><a href='node/$sitesnid?nid=$sitesnid'>$sitesid</a></td><td 
valign='top'>$sitescity</td><td valign='top'>$sitesstate</td></tr>";
	$previous = $All['state'];

 		//echo "<tr><td><a href='node/$sitesnid'>$sitesid</a></td></tr>";
	}
		echo "</table></fieldset>";
	}	
	

}

if (arg(0)=='node')
{

	if (arg(0)=="search-collections" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
	print "<p id='descriptiontext'>For the first time, many of America&rsquo;s leading 
museums are now  at your fingertips!<br>  The shocking fact is that 99% of America&rsquo;s 
historical  treasures are hidden.&nbsp; Museums display  only a tiny fraction of their holdings, 
and very few have put their collections  online.&nbsp; <br> <br> Our team works with museum 
staff to obtain internal data on their  historic collections and add them to the National 
Portal.&nbsp; <br> <br>  Whether you&rsquo;re a researcher, collector, or tourist, you&rsquo;ll  
find thousands of historic photographs, paintings, letters, and artifacts here,  from ship 
models and swords to quilts and pottery.<br>   American Heritage&rsquo;s National Portal is 
growing rapidly, so  come back often!</p>";

	$element['#title'] = t('Search All Collections ');
	}
	else
	{
    	$element['#title'] = t('Search This Collection');
 	}
       print theme('fieldset', $element); 	

}

else if (arg(0)=="historic-sites" &&  arg(0)!="count" &&  arg(0)!="types" || arg(0)!='home' && 
arg(0)!='search-collections' && arg(0)!='search-national-parks' && arg(0)!='search-navy-museum' &&  arg(0)!='search-smithsonian-museum' && arg(0)!='search-civilwar-museum')
{

//&& (!(stripos($_SERVER['REQUEST_URI'],"?")))
	$element['#title'] = t('');
	print theme('fieldset', $element); 	

}

else if (arg(0)=="home" )
{
	$element['#title'] = t('');
	//print theme('table',$element); 	
print $element['#value']; 

}

else if (arg(0)!="search-collections" &&  arg(0)!="historic-sites" && arg(0)!="search-national-parks"  && 
arg(0)!="search-collections" && arg(0)!='search-navy-museum' &&  arg(0)!="count" &&  arg(0)!="types" &&  arg(0)!="search-smithsonian-museum" && arg(0)!="search-civilwar-museum")
{

	$element['#title'] = t('Filter');

	print theme('fieldset', $element); 	
}

  ?>
  
