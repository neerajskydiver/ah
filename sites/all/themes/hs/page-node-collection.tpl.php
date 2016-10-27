<?php
// $Id: page.tpl.php,v 1.18.2.1 2009/04/30 00:13:31 goba Exp $

?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
  <meta name="SKYPE_TOOLBAR" content="SKYPE_TOOLBAR_PARSER_COMPATIBLE" /> 
    <?php print $head ?>
    <title><?php print $head_title ?></title>
    <?php print $styles ?>
    <?php print $scripts ?>
    <!--[if lt IE 7]>
      <?php print phptemplate_get_ie_styles(); ?>
    <![endif]-->
  	<script language="javascript">
      $(document).ready(function() {
			$("#collection_comment_id_form").hide();
			$("#collection_star_rating_id_form").hide();
			$("#collection_share_id_form").hide();			
			$("#comment_id").click(function () {
				$("#collection_comment_id_form").toggle();
			});
			$("#rate_id").click(function () {
				$("#collection_star_rating_id_form").toggle();
			});
			$("#share_id").click(function () {
				$("#collection_share_id_form").toggle();
			});								
      });
	</script>
  </head>
  <body<?php print phptemplate_body_class($left, $right); ?>>

<!-- Layout -->
 <!--  <div id="header-region" class="clear-block"><?php print $header; ?></div> -->

    <div id="wrapper">
    <div id="container" class="clear-block">



	<!--Top Advertisement Banner Right Side Start (AH IN-HOUSE CUSTOM BANNER (293 x 90))-->
            <div id="ah_custom_banner">
<!--<a href="<?php //echo $base_path?>node/19046" title="image"></a>-->
<?php print $topright ?>

<!--<img alt="" src="<?php echo $base_path; ?>sites/all/themes/hs/images/heritage_traveler_placeholder.png" />-->


			</div>
            <!--Top Advertisement Banner Right Side End-->
 <!--Top Advertisement Banner left Side Start (LEADERBOARD (728 x 90))-->
			<div id="leaderboard">
<!--<img alt="" src="<?php echo $base_path; ?>sites/all/themes/hs/images/NCC_20100914_ASLeaderboard_728x90_JPG_36K.JPG" />-->
<?php print $topleft ?>
			</div>
            <!--Top Advertisement Banner Left Side End-->    
       




      <div id="header">
    
        <div id="header_wrapper">
					<div id="search">
						<ul>
							<li>
							<!--<a href="http://www.facebook.com/pages/American-Heritage-Publishing/129491773754888?v=info" target="_blank">-->
<a href="https://www.facebook.com/AmericanHeritageMagazine" target="_blank">								
							<img alt="facebook"  src="<?php echo $base_path; ?>sites/all/themes/hs/images/facebook.png"></a></li>
							<li><a href="#"><img alt="twitter"  src="<?php echo $base_path; ?>sites/all/themes/hs/images/twitter.png"></a></li>
							<li><a href="<?php echo $base_path."rss.xml"?>"><img alt="feed"  src="<?php echo $base_path; ?>sites/all/themes/hs/images/feed.png"></a></li>
						</ul>
  					<?php if ($search_box): ?><div id="search-box"><?php print $search_box ?></div><?php endif; ?>
					</div>
					<h1><span>A</span>merican <span>H</span>eritage</h1>
					<h2>
    <?php if ($logo) {
              print '<img id="eagle" src="'. check_url($logo) .'" alt="'. $site_title .'" id="logo" usemap="#planetmap"/>';
            } ?>Collections, Travel, and Great Writing On History</h2>

		<map name="planetmap">
		<area shape="rect" coords="0,0,182,126" alt="Sun" href=<?php echo $base_path; ?> />
		</map>

        <?php if (isset($secondary_links)) : ?>
          <?php print theme('links', $secondary_links, array('class' => 'links secondary-links')) ?>
        <?php endif; ?>
        </div>
      </div> <!-- /header -->
					<div id="primary-navigation">        <?php if (isset($primary_links)) : ?>
							<?php print theme('ah_menus_primary_links', 'down'); ?>
							<?php // print theme('nice_menus_primary_links', 'down'); ?>
							<?php //print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
							<?php endif; ?>
					</div>

<div class="main-cont">
      <?php if ($left): ?>
        <div id="sidebar-left" class="sidebar">
          <?php print $left ?>
        </div>
      <?php endif; ?>

<!-- class for liquid layout -->
	<?php if ($left || $right): ?>

			<?php if ($left && $right): ?>
			<div id="main" class="with-both">
			<?php endif; ?>
			
			<?php if ($left && !$right): ?>
			<div id="main" class="no-right">
			<?php endif; ?>
			
			<?php if (!$left && $right): ?>
			<div id="main" class="no-left">
			<?php endif; ?>
			<?php	else: ?>
			<div id="main">
	<?php endif; ?>

			<div id="squeeze">
				<div class="right-corner">
					<div class="left-corner">
						<div id="collection_banner">
					<?php
					$title=$node->title;
					$SelectSite=db_query("select field_site_id_nid from content_type_collection where nid =$node->nid  ");
					$ResultSite=db_fetch_array($SelectSite);
					$sitenid=$ResultSite['field_site_id_nid'];
					
					$SelectSiteTitle=db_query("select title from node where nid =$sitenid");
					$ResultSiteTitle=db_fetch_array($SelectSiteTitle);
					$siteTitle=$ResultSiteTitle['title'];
					
					$siteTitle=addslashes($siteTitle);      
					//echo "select n.nid  from node n inner join ad_image a on a.aid=n.nid where n.title= '$siteTitle' and n.type='ad'";
					$SelectAd=db_query("select n.nid  from node n inner join ad_image a on a.aid=n.nid where n.title= '$siteTitle' and n.type='ad'");
					$ResultAd=db_fetch_array($SelectAd);
					$imgAd= $ResultAd['nid'];
					if($imgAd!=''){
					print ad(5127, 1, array('nids' => $imgAd));
					}
					?>
						</div> <?php print $breadcrumb; ?>
						<?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
						<?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
						<?php if ($title): print '<h1'. ($tabs ? ' class="with-tabs"' : '') .'>'. $title .'</h1>'; endif; ?>
						<?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul>'; endif; ?>
						<?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
						<?php if ($show_messages && $messages): print $messages; endif; ?>
						<?php print $help; ?>
							<div class="clear-block">
							 <?php print $content ?>
							</div>
	
							<?php print $feed_icons ?>
						<?php if ($tabs): print '</div>'; endif; ?>
				 </div> <!--.left-corner-->
				</div> <!--.right-corner-->
				</div> <!--#squeeze-->
		</div> <!-- .#main -->

           <?php if ($right): ?>
        <div id="right" class="sidebar">
          <?php print $right ?>
        </div>
      <?php endif; ?>
</div>

<div id="footer">
	 <?php print $footer ?>
	  <p class="tag"> <?php print $footer_message; ?> </p>
	 </div>
</div> <!-- /.left-corner, /.right-corner, /#squeeze, /#center -->

    </div> <!-- /container -->
  </div>
<!-- /layout -->

  <?php print $closure ?>
  </body>
</html>
