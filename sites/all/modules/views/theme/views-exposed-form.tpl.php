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
 
 include ('func_views.php');

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
$exposed=arg(0);
 switch($exposed){
case 'search-collections' :
$content='
<div class="views-exposed-form">
<div class="views-exposed-widgets">';	

foreach($widgets as $id => $widget) 
	{
    $content .= '<div class="views-exposed-widget">';
	if (!empty($widget->label)) 
		{
	    $content.='<label for="'.$widget->id.'">';
        $content.= $widget->label;
        $content.='</label>';
      	}
     	if (!empty($widget->operator))
	 	{
//	    $content.='<div class="views-operator">';
       	$content.=$widget->operator;
//	    $content.='</div>';
       	}
//	    $content.= '<div class="views-widget">';
		$content.= $widget->widget;
//		$content.= '</div>';
		$content.= '</div>';

}
    
//  		$content.= '<div class="views-exposed-widget">';
		$content.= $button;
  	  	$content.='</div></div>';
		$element = array();
		$element['#collapsible'] = false;
		$element['#collapsed'] = false;
		$element['#value'] = $content;  
		break;

case 'historic-sites' :	
case 'historic-themes' :	
case 'types' :
$content='
<div class="views-exposed-form">
<div class="views-exposed-widgets">';	

foreach($widgets as $id => $widget) 
	{
    $content .= '<div class="views-exposed-widget">';
	if (!empty($widget->label)) 
		{
	    $content.='<label for="'.$widget->id.'">';
        $content.= $widget->label;
        $content.='</label>';
      	}
     	if (!empty($widget->operator))
	 	{
//	    $content.='<div class="views-operator">';
       	$content.=$widget->operator;
//	    $content.='</div>';
       	}
//	    $content.= '<div class="views-widget">';
		$content.= $widget->widget;
//		$content.= '</div>';
		$content.= '</div>';

}
    
//  		$content.= '<div class="views-exposed-widget">';
		$content.= $button;
  	  	$content.='</div></div>';
		$element = array();
		$element['#collapsible'] = false;
		$element['#collapsed'] = false;
		$element['#value'] = $content;  
		break;

case 'search-civilwar-museum' :
case 'search-smithsonian-museum' :	
case 'search-navy-museum' :	
case 'search-national-parks' :
case 'node' :
case 'home' :		
	
$content='
<div class="views-exposed-form">
<div class="views-exposed-widgets">
<div class="views-exposed-widget" style="clear:left;">';
	foreach($widgets as $id => $widget) 
	{
        if (!empty($widget->label)) 
		{
	    $content.='<div class="views-widget" style="width:100%;">
		<label for="'.$widget->id.'">';
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
  	  	$content.='</div></div></div></div>';
		$element = array();
		$element['#collapsible'] = false;
		$element['#collapsed'] = false;
		$element['#value'] = $content;	

				break;
default:	
	?>	
<div class="views-exposed-form">
  <div class="views-exposed-widgets clear-block">

    <?php foreach($widgets as $id => $widget): ?>
      <div class="views-exposed-widget">
        <?php if (!empty($widget->label)): ?>
          <label for="<?php print $widget->id; ?>">
            <?php print $widget->label; ?>
          </label>
        <?php endif; ?>
        <?php if (!empty($widget->operator)): ?>
          <div class="views-operator">
            <?php print $widget->operator; ?>
          </div>
        <?php endif; ?>
        <div class="views-widget">
          <?php print $widget->widget; ?>
        </div>
      </div>
    <?php endforeach; ?>
    <div class="views-exposed-widget">
      <?php print $button ?>
    </div>
  </div>
</div>
<?php break;
}			
		
/************* Search Collection *****************/

if(arg(0)=='search-collections')
{
if(arg(0)=="search-collections" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
    	print print_search();
	$element['#title'] = t('Search All Collections ');
	}
	else
	{
	$element['#title'] = t('Search This Collection');
   	}
	print '<div>';
	print  theme('fieldset', $element);
	print '</div>';
	print '<div>';
	print search_collections();
	print '</div>';
	
}
/*********** Search Smithsonian ********************/
if(arg(0)=='search-smithsonian-museum')
{
if(arg(0)=="search-smithsonian-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
	
	print print_smith();	
	$element['#title'] = t('Search All Collections ');
	}
	else
	{
	//$element['#title'] = t('Search This Collection');
   	}
	print theme('fieldset', $element);	
	print search_smithsonian_museum($element);
	
}

/************** Saarch Civilwar *****************/
if(arg(0)=='search-civilwar-museum')
{
if(arg(0)=="search-civilwar-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{

	print print_civil();	
	$element['#title'] = t('Search All Collections ');

	}
	else
	{
	//$element['#title'] = t('Search This Collection');
   	}
	print theme('fieldset', $element);
	print search_civilwar_museum($element);
	
}

/*************** Search Navy Mueseum ****************/

if(arg(0)=='search-navy-museum')
{
	if(arg(0)=="search-navy-museum" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
	print print_navy();		
	$element['#title'] = t('Search All Collections ');
	}
	else
	{
	$element['#title'] = t('Search This Collection');
   	}
	print theme('fieldset', $element);
	print search_navy_museum();
	
}

/************** Search National Parks  *****************/
if(arg(0)=='search-national-parks')
{
if(arg(0)=="search-national-parks" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
	print print_national();
	$element['#title'] = t('Search All Collections ');
	}
	else
	{
		//$element['#title'] = t('Search This Collection');
 	 }
	print theme('fieldset', $element);
	print search_national_parks($element);	

}
/************** node *****************/
if (arg(0)=='node')
{


	if (arg(0)=="search-collections" && (!(stripos($_SERVER['REQUEST_URI'],"?"))))
	{
	print "<p id='descriptiontext'>For the first time, many of America&rsquo;s leading museums
	are now  at your fingertips!<br>  The shocking fact is that 99% of America&rsquo;s historical 
	treasures are hidden.&nbsp; Museums display  only a tiny fraction of their holdings, and very 
	few have put their collections  online.&nbsp; <br> <br> Our team works with museum staff to 
	obtain internal data on their  historic collections and add them to the National Portal.&nbsp; 
	<br> <br>  Whether you&rsquo;re a researcher, collector, or tourist, you&rsquo;ll find thousands
	of historic photographs, paintings, letters, and artifacts here,  from ship models and swords to
	quilts and pottery.<br>   American Heritage&rsquo;s National Portal is growing rapidly, so  come
	back often!</p>";

	$element['#title'] = t('Search All Collections ');
	}
	else
	{
    	$element['#title'] = t('Search This Collection');
 	}
    print theme('fieldset', $element); 	

}
/************** Historic Sites *****************/
else if (arg(0)=="historic-sites" || arg(0)=="historic-themes" || arg(0)=="types" )
{

	$element['#title'] = t('');
	print theme('fieldset', $element); 	

}
else if (arg(0)!='home' &&	
	arg(0)!='search-collections' && 
	arg(0)!='search-national-parks' && 
	arg(0)!='search-navy-museum' && 
	arg(0)!='search-smithsonian-museum' &&
	arg(0)!='search-civilwar-museum')
{

	$element['#title'] = t('');
	//print theme('fieldset', $element); 	
	print $element['#value']; 


}
/************** Home *****************/
else if (arg(0)=="home" )
{
	
       $element['#title'] = t('');	
       print $element['#value']; 

}
/************** Extra *****************/
else if (arg(0)!="search-collections" &&  arg(0)!="historic-sites" 
		&& arg(0)!="search-national-parks"  
		&&  arg(0)!='search-navy-museum' &&  arg(0)!="historic-themes" 
		&&  arg(0)!="types" &&  arg(0)!="search-smithsonian-museum" 
		&& arg(0)!="search-civilwar-museum")
{


	$element['#title'] = t('Filter');
	print theme('fieldset', $element); 
	
}

  ?>
  
