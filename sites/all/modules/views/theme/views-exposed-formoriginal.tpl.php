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
mysql_connect("localhost","root","123456");
mysql_select_db('ah-dev3');
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


function bookmark_block(){


if(arg(0)=="search-national-parks" && (!(stripos($_SERVER['REQUEST_URI'],"?")))){

echo "<fieldset><legend>Select a Collection</legend><table>
<tr><th>Sites</th></tr>";
/* 
SELECT DISTINCT(node_bookmarks_sites.title),node_bookmarks_sites.nid FROM node
inner join term_node  ON node.vid = term_node.vid
inner join term_data  ON term_node.tid = term_data.tid
inner join content_type_collection  ON node.vid = content_type_collection.vid inner join content_type_bookmarks_sites  on content_type_bookmarks_sites.nid=content_type_collection.field_site_id_nid inner join node node_bookmarks_sites on node_bookmarks_sites.nid=content_type_bookmarks_sites.nid and node_bookmarks_sites.type='bookmarks_sites'
WHERE term_data.tid = 4445 ORDER BY node_bookmarks_sites.title ASC
*/
$selectid = "SELECT DISTINCT(node_bookmarks_sites.title),node_bookmarks_sites.nid FROM node
inner join term_node  ON node.vid = term_node.vid
inner join term_data  ON term_node.tid = term_data.tid
inner join content_type_collection  ON node.vid = content_type_collection.vid inner join content_type_bookmarks_sites  on content_type_bookmarks_sites.nid=content_type_collection.field_site_id_nid inner join node node_bookmarks_sites on node_bookmarks_sites.nid=content_type_bookmarks_sites.nid and node_bookmarks_sites.type='bookmarks_sites'
WHERE term_data.tid = 4445 ORDER BY node_bookmarks_sites.title ASC";
$resultid = mysql_query($selectid);
while ($rowid = mysql_fetch_row($resultid))
{
 $sitesid=$rowid[0];
 $sitesnid=$rowid[1];

echo "<tr><td><a href='node/$sitesnid'>$sitesid</a></td></tr>";
}

}

if(arg(0)=="search" && (!(stripos($_SERVER['REQUEST_URI'],"?")))){
echo "<fieldset><legend>Select a Collection</legend><table>
<tr><th>State </th><th>City</th><th>Sites</th></tr>";


/* select DISTINCT(node_state.title) AS state_title,node_bookmarks_sites.title AS site 
, content_type_bookmarks_sites.field_city_value
from content_type_bookmarks_sites INNER JOIN node node_bookmarks_sites  ON node_bookmarks_sites.nid = content_type_bookmarks_sites.nid AND node_bookmarks_sites.type= 'bookmarks_sites' 
LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND node_state.type = 'state' inner join content_type_collection on content_type_collection.field_site_id_nid=content_type_bookmarks_sites.nid order by node_state.title,content_type_bookmarks_sites.field_city_value,node_bookmarks_sites.title asc*/

$selectid ="select DISTINCT(node_state.title) AS state_title,content_type_bookmarks_sites.field_city_value
,node_bookmarks_sites.title AS site ,content_type_bookmarks_sites.nid
from content_type_bookmarks_sites INNER JOIN node node_bookmarks_sites  ON node_bookmarks_sites.nid = content_type_bookmarks_sites.nid AND node_bookmarks_sites.type= 'bookmarks_sites' 
LEFT JOIN node node_state ON node_state.nid =content_type_bookmarks_sites.field_state_nid AND node_state.type = 'state' inner join content_type_collection on content_type_collection.field_site_id_nid=content_type_bookmarks_sites.nid order by node_state.title,content_type_bookmarks_sites.field_city_value,node_bookmarks_sites.title asc";

$resultid = mysql_query($selectid);
while ($All = mysql_fetch_row($resultid)) 
{
$city=$All[1];
$sites=$All[2];
$state=$All[0];
if ($state=="District of Columbia"){$state="D.C.";}
$sitesnid=$All[3];
echo "<tr><td> $state</td><td>$city</td><td><a href='node/$sitesnid'>$sites</a></td></tr>";
}
 }

echo "</table></fieldset>";
}//function

/*******end of function *************/
$content='<div class="views-exposed-form">
<div class="views-exposed-widgets">
   <div class="views-exposed-widget" style="clear:left;">';
    foreach($widgets as $id => $widget) {
          if (!empty($widget->label)) {
	        $content.='<div class="views-widget" style="width:100%;"><label for="'. $widget->id;
		 $content.='">';
               $content.=$widget->label;
               $content.='</label>';
      }
      if (!empty($widget->operator)) {
        $content.='<div class="views-operator">';
        $content.=$widget->operator;
        $content.='</div>';
        }
        $content.=$widget->widget;
    }
  $content.=$button;
  if (arg(0)!="sites-data" ){
  $content.='<div id="additional_search">
	<a href="#"> &raquo; Advanced</a>
	<br/>
	<a href="#"> &raquo; Tips</a>
	</div>';
  }
  $content.='</div></div></div></div>';
  $element = array();
  $element['#collapsible'] = false;
  $element['#collapsed'] = false;
  $element['#value'] = $content;
  
/*******************************/

if(arg(0)=='search')
{
	if(arg(0)=="search" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
	//print "<p>For the first time, many of America&rsquo;s leading museums are now  at your fingertips!<br>  The shocking fact is that 99% of America&rsquo;s historical  treasures are hidden.&nbsp; Museums display  only a tiny fraction of their holdings, and very few have put their collections  online.&nbsp; <br> <br> Our team works with museum staff to obtain internal data on their  historic collections and add them to the National Portal.&nbsp; <br> <br>  Whether you&rsquo;re a researcher, collector, or tourist, you&rsquo;ll  find thousands of historic photographs, paintings, letters, and artifacts here,  from ship models and swords to quilts and pottery.<br>   American Heritage&rsquo;s National Portal is growing rapidly, so  come back often!</p>";
print "<p>Search the most comprehensive national collection of historic artifacts, photographs, paintings, and documents in the U.S.<br>  &nbsp; <br> Tens of thousands of never-before-seen treasures are at your fingertips. For the first time, you can access the internal collections data of many of America&rsquo;s leading museums, National Parks, and historical societies.&nbsp; <br> <br>  Discover. Collect. Share. The National Portal brings history to your desktop</p>";	$element['#title'] = t('Search All Collections ');
	}else{
	/*  $element['#title'] = t('Search '. $site_name);*/
	$element['#title'] = t('Search This Collection');
       }
       print theme('fieldset', $element);
	bookmark_block();
}

else if(arg(0)=='search-national-parks')
{
	if(arg(0)=="search-national-parks" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
print "<p>The National Park Service operates one of the world&rsquo;s largest systems of museums. Now you can search through their historic artifacts and photographs from one convenient page.&nbsp; <br> <br> 
Many of these historic treasures have never been seen before by the public. Go behind the exhibits in hallowed places such as Gettysburg, Shiloh and Valley Forge to discover America&rsquo;s fascinating past.
</p>";
	$element['#title'] = t('Search All Collections ');
	}else{
	$site_name= truncate_utf8($site_name, 30, TRUE, TRUE);
	/*  $element['#title'] = t('Search '. $site_name);*/
	$element['#title'] = t('Search This Collection');
 	 }
       print theme('fieldset', $element);
	bookmark_block();
}
else if (arg(0)=="sites-data" )
{
	$element['#title'] = t('');
	print theme('fieldset', $element); 	
}
else 
{
 if(arg(0)=="search" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
	print "<p>For the first time, many of America&rsquo;s leading museums are now  at your fingertips!<br>  The shocking fact is that 99% of America&rsquo;s historical  treasures are hidden.&nbsp; Museums display  only a tiny fraction of their holdings, and very few have put their collections  online.&nbsp; <br> <br> Our team works with museum staff to obtain internal data on their  historic collections and add them to the National Portal.&nbsp; <br> <br>  Whether you&rsquo;re a researcher, collector, or tourist, you&rsquo;ll  find thousands of historic photographs, paintings, letters, and artifacts here,  from ship models and swords to quilts and pottery.<br>   American Heritage&rsquo;s National Portal is growing rapidly, so  come back often!</p></p>";

	$element['#title'] = t('Search All Collections ');
	}else{
       $site_name= truncate_utf8($site_name, 30, TRUE, TRUE);
	/*  $element['#title'] = t('Search '. $site_name);*/
	$element['#title'] = t('Search This Collection');
 	}
        print theme('fieldset', $element); 	
	
}
  ?>
  