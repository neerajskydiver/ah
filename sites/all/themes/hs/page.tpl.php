<?php
// $Id: page.tpl.php,v 1.18.2.1 2009/04/30 00:13:31 goba Exp $

?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
	<head>
		
    <!--  <link href="http://code.jquery.com/ui/1.10.4/themes/ui-lightness/jquery-ui.css" rel="stylesheet"> -->
    			<meta name="SKYPE_TOOLBAR" content="SKYPE_TOOLBAR_PARSER_COMPATIBLE" /> 
		<?php print $head ?>
		<title><?php print $head_title ?></title>
		<?php print $styles ?>
		<?php print $scripts ?>
		<!--[if lt IE 7]>
			<?php print phptemplate_get_ie_styles(); ?>
		<![endif]-->

	

	 

	</head>
	<body<?php print phptemplate_body_class($left, $right); ?>>

<!-- Layout -->
 <!--  <div id="header-region" class="clear-block"><?php print $header; ?></div> -->

		<div id="container" class="clear-block">
	  <!--Top Advertisement Banner Right Side Start (AH IN-HOUSE CUSTOM BANNER (293 x 90))-->
			  <div id="ah_custom_banner">

        <!--<a href="<?php echo $base_path?>node/19046" title="image"><img alt="" src="<?php echo $base_path; ?>sites/all/themes/hs/images/heritage_traveler_placeholder.png" /></a>-->
         <!--<a href="<?php //echo $base_path?>node/19046" title="image"></a>-->
        <?php print $topright ?>
	     </div>
						<!--Top Advertisement Banner Right Side End-->
						<!--Top Advertisement Banner left Side Start (LEADERBOARD (728 x 90))-->
<!--			<div id="leaderboard"><img alt="" src="<?php echo $base_path; ?>sites/all/themes/hs/images/AmerClass_728x90.gif" /> -->
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
							<li><a href="http://www.twitter.com/!#/ameriheritage" target="_blank"><img alt="twitter"  src="<?php echo $base_path; ?>sites/all/themes/hs/images/twitter.png"></a></li>
							<li><a href="<?php echo $base_path."rss.xml"?>"><img alt="feed"  src="<?php echo $base_path; ?>sites/all/themes/hs/images/feed.png"></a></li>
						</ul>
  					<?php if ($search_box): ?><div id="search-box"><?php print $search_box ?></div><?php endif; ?>
					</div>
					<h1><span>A</span>merican <span>H</span>eritage</h1>
					<h2>
          		<?php if ($logo) {
					  		print '<img id="eagle" src="'. check_url($logo) .'" alt="'. $site_title .'" id="logo" usemap="#planetmap"/>';
						    } ?>
						  Collections, Travel, and Great Writing On History
					</h2>

				<map name="planetmap">
				<area shape="rect" coords="0,0,182,126" alt="Sun" href=<?php echo $base_path; ?> />
				</map>

			
				<div id="primary-navigation">        <?php if (isset($primary_links)) : ?>
						<?php print theme('ah_menus_primary_links', 'down'); ?>
						<?php // print theme('nice_menus_primary_links', 'down'); ?>
						<?php //print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
						<?php endif; ?>
				</div> <!--"primary-navigation" -->
	    </div><!--header_wrapper-->


				<?php if (isset($secondary_links)) : ?>
					<?php print theme('links', $secondary_links, array('class' => 'links secondary-links')) ?>
				<?php endif; ?>

			</div> <!-- /header -->


      <div class="main-cont" id="wrapper">
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
	      <?php endif; ?>
		      
				      <div id="squeeze">
				      <div class="right-corner">
					      <div class="left-corner">
						      <?php print $breadcrumb; ?>
						      <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
						      <?php if ($tabs): print ''; endif; ?>
						      <?php if ($title): print '<h1'. ($tabs ? ' class="with-tabs"' : '') .'>'. $title .'</h1>'; endif; ?>
								      <?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul>'; endif; ?>
						      <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
						      <?php if ($show_messages && $messages): print $messages; endif; ?>
						      <?php print $help; ?>
						       <div class="clear-block">

							       <?php print $accordion ?>

							       <?php print $content ?>

						      </div><!--clear block -->
						      <?php print $feed_icons ?>
						      </div> <!-- left corner -->
					      </div> <!-- right corner -->
				       </div> <!-- squeeze -->
				     </div>     <!-- main -->
	
			      <?php if ($right): ?>
				      <div id="right" class="sidebar">
					      <?php print $right ?>
				      </div>
			      <?php endif; ?>

      <?php if ($left || $right): ?>
      </div> <!-- main-cont-->
      <?php endif; ?>

      <div id="footer">
	       <?php print $footer ?>
	        <p class="tag"> <?php print $footer_message; ?> </p>
       </div> <!-- footer -->
 <!-- /.left-corner, /.right-corner, /#squeeze, /#center -->

</div> <!-- /container -->

<!-- /layout -->
<? /**/ ?>
	<?php print $closure ?>
	</body>

	
</html>


<!--  --------- START :- Added  by akshay for opeing the Gmap in new window for collection --------- -->
<script language="javascript" type="text/javascript">
	$(document).ready(function() {
		$('#block-gmap_location-0').click(function() {
              var path_base = '<?php echo base_path();?>';     
		window.open(path_base+'getdirections/location/to/<?php echo arg(1); ?>','GMAP','width=950,height=650,menubar=no,status=no,location=no,toolbar=no,scrollbars=yes,resizable=yes');
		return false;
		});

		// $( "#user-register" ).dialog({
		// 					autoOpen: true,
		// 					width: 700,
		//         			height: 500, 
		// 	           		modal: true,
			           
		// 	        });
		// 	$("#user-register").dialog("open");

		 // code modification 13/07/2016
		// var modal = document.getElementById('mymodal');
		// modal.style.display = "block";
		 // ends here
		/* Commented by Samrat aher 22 Aug 2016 
		var x = document.URL;
		if (x != 'http://www.americanheritage.com/admin/user/user/create') 
		{
			var modal = document.getElementById('mymodal');
			modal.style.display = "block";
		}
		else
		{
			// var modal = document.getElementById('normal_reg');
			// modal.style.display = "inline";

			$("#edit-submit").val("Create new account");
				
			$(".close").hide();
			$(".m_close").hide();
			$(".description").hide();
			$(".my_header").hide();
			$(".my_login").hide();
			$('.render').css('text-align','left');
			$('.my_submit').css('text-align','center');
			$( "div" ).removeClass( "modal");
		} 

		*/
	}


	);

	// Commented by Samrat Aher 22 Aug 2016
	//function close_module() 
	// {
	// 	var modal = document.getElementById('block-formblock-user_register');
	//     modal.style.display = "none";
	// }

	


	/********************************************************************/
	// var msg_len = <?php //echo strlen($messages) ?>;
	// var msg_len = 0 ;
	// window.onload = load_login(msg_len);
	// window.onload = load_login();

</script>

	



<!--  --------- END --------- -->