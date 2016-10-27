<?php
// $Id: page.tpl.php,v 1.18.2.1 2009/04/30 00:13:31 goba Exp $
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
<head>
<meta name="SKYPE_TOOLBAR" content="SKYPE_TOOLBAR_PARSER_COMPATIBLE" />
<?php print $head ?>
<title><?php print $head_title ?></title>
<?php print $styles ?><?php print $scripts ?>
<!--[if lt IE 7]>
			<?php print phptemplate_get_ie_styles(); ?>
		<![endif]-->
<meta content="The Source for American History. American Heritage Magazine, published since 1954, is now available both online and in print. Browse our archive and order a free trial issue now!" name="description"/>
<meta content="text/html; charset=iso-8859-1" http-equiv="Content-Type"/>
<meta content="american, history, heritage, magazine, articles, u.s., united states, invention, technology, forbes, archive, lincoln, roosevelt, cold war, civil war, vietnam, world war ii, wwii, 1964, 1968, 1960s, alamo, george washington, carver, john dos passos, ernie pyle, custer, boston massacre, truman, macarthur, charles cawthorn, andrew johnson, kennedy, eisenhower, nixon, lbj, jfk, fdr, thomas jefferson, sally hemings, great depression" name="keywords"/>
<meta content="Home" name="section"/>
<meta content="American Heritage" name="pubname"/>
<meta content="<?php print date('F d, Y')?>" name="pubdate"/>
<meta content="American Heritage Home" name="title"/>


<!-- <link href="http://code.jquery.com/ui/1.10.4/themes/ui-lightness/jquery-ui.css" rel="stylesheet"> -->

<script type="text/javascript" language="javascript">

/* Commented by Samrat aher 22 Aug 2016
 $(document).ready(function() {
       // var modal = document.getElementById('mymodal');
       // modal.style.display = "block";

    var x = document.URL;
    if (x != 'http://www.americanheritage.com/admin/user/user/create') 
    {
      var modal = document.getElementById('mymodal');
      modal.style.display = "block";
      // $("#edit-submit").val("Register");
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

  });

 function close_module() 
  {
    var modal = document.getElementById('block-formblock-user_register');
    modal.style.display = "none";
  }

  // function change_myval()
  // {
  //   $("#edit-submit").val("Create new account");
  // }
*/
</script>

</head>
<body<?php print phptemplate_body_class($left, $right); ?>>
<!-- Layout -->
<!--  <div id="header-region" class="clear-block"><?php print $header; ?></div> -->
<div>
<div id="container" class="clear-block">
<!--Top Advertisement Banner Right Side Start (AH IN-HOUSE CUSTOM BANNER (293 x 90))-->
<div id="ah_custom_banner"> <?php print $topright ?> </div>
<!--Top Advertisement Banner Right Side End-->
<!--Top Advertisement Banner left Side Start (LEADERBOARD (728 x 90))-->
<!--			<div id="leaderboard"><img alt="" src="<?php echo $base_path; ?>sites/all/themes/hs/images/AmerClass_728x90.gif" /> -->
<div id="leaderboard">
<!--<img alt="" src="<?php echo $base_path; ?>sites/all/themes/hs/images/NCC_20100914_ASLeaderboard_728x90_JPG_36K.JPG" />-->
  <?php print $topleft ?> </div>
<!--Top Advertisement Banner Left Side End-->
<div id="header">
  <div id="header_wrapper">
    <div id="search">
      <ul>
        <li>
		 <!--<a href="http://www.facebook.com/pages/American-Heritage-Publishing/129491773754888?v=info" target="_blank"> -->
		 <a href="https://www.facebook.com/AmericanHeritageMagazine" target="_blank">	
		 
		 <img alt="facebook"  src="<?php echo $base_path; ?>sites/all/themes/hs/images/facebook.png" /> </a> </li>
        <li> <a href="http://www.twitter.com/#!/AmeriHeritage" target="_blank"> <img alt="twitter"  src="<?php echo $base_path; ?>sites/all/themes/hs/images/twitter.png" /> </a> </li>
        <li> <a href="<?php echo $base_path."rss.xml"?>" target="_blank"> <img alt="rss feed"  src="<?php echo $base_path; ?>sites/all/themes/hs/images/feed.png" /> </a> </li>
      </ul>
      <?php if ($search_box): ?>
      <div id="search-box"><?php print $search_box ?></div>
      <?php endif; ?>
    </div>
    <h1><span>A</span>merican <span>H</span>eritage</h1>
    <h2>
      <?php if ($logo) {
							print '<img id="eagle" src="'. check_url($logo) .'" alt="American History Lives Here" usemap="#planetmap"/>';
						} ?>
      Collections, Travel, and Great Writing On American History</h2>
  </div>
  <map name="planetmap" id="planetmap">
    <area shape="rect" coords="0,0,182,126" alt="logo" href="<?php echo $base_path; ?>" />
  </map>
  <?php if (isset($secondary_links)) : ?>
  <?php print theme('links', $secondary_links, array('class' => 'links secondary-links')) ?>
  <?php endif; ?>
</div>
<!-- /header -->
<div id="primary-navigation">
  <?php if (isset($primary_links)) : ?>
  <?php print theme('ah_menus_primary_links', 'down'); ?>
  <?php // print theme('nice_menus_primary_links', 'down'); ?>
  <?php //print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
  <?php endif; ?>
</div>
<div class="main-cont home-wrapper" id="wrapper">
  <?php if ($left): ?>
  <div id="sidebar-left" class="sidebar"> <?php print $left ?> </div>
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
        
          <?php endif; ?>
          <div id="squeeze">
            <div class="right-corner">
              <div class="left-corner"> <?php print $breadcrumb; ?>
                <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
                <?php if ($tabs): print ''; endif; ?>
                <?php if ($title): print '<h1'. ($tabs ? ' class="with-tabs"' : '') .'>'. $title .'</h1>'; endif; ?>
                <?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul>'; endif; ?>
                <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
                <?php if ($show_messages && $messages): print $messages; endif; ?>
                <?php print $help; ?>
                <div class="clear-block"> <?php print $accordion ?> <?php print $content ?> </div>
                <?php print $feed_icons ?> </div>
              <!-- left corner -->
            </div>
            <!-- right corner -->
          </div>
          <!-- squeeze -->
        </div>
        <!-- main -->
        <?php if ($right): ?>
        <div id="right" class="sidebar"> <?php print $right ?> </div>
        <?php endif; ?>
      </div>
      <!-- main-cont-->
      <div id="footer"> <?php print $footer ?>
        <p class="tag"> <?php print $footer_message; ?> </p>
      </div>
    </div>
    <!-- /.left-corner, /.right-corner, /#squeeze, /#center -->
  </div>
  <!-- /container -->
</div>
<!--Frontpage Popup-->
<div style="display: none; width: 310px; height: 255px; position: fixed; left: 70px; bottom: 0pt; opacity: 1; z-index:500"  id="styled_popup">
  <div style="float: left; margin: 0px; width: 228px; height: 26px; "> <a target='_blank' href="https://w1.buysub.com/loc/AHE/javaad"> <img border="0" src="<?php echo $base_path; ?>sites/all/themes/hs/images/ah-ad-left.gif" alt="American Heritage: Free trial issues, Subscribe" /> </a> </div>
  <div style="float: right; margin: 0px; width: 82px; height: 26px;"> <a href="javascript:closePopup();"> <img border="0" src="<?php echo $base_path; ?>sites/all/themes/hs/images/ah-ad-close.gif" alt="Close"  /> </a> </div>
  <div> <a target='_blank' href="https://w1.buysub.com/loc/AHE/javaad"> <img border="0" src="<?php echo $base_path; ?>sites/all/themes/hs/images/ah-ad-bottom.gif" alt="American Heritage: Subscribe" /> </a> </div>
</div>
<script type="text/javascript" language="javascript">

 /* $(document).ready(function() {
        //$("#styled_popup").fadeIn(3000, function () {  //commented for removing popup on front page 18/6/2013
        });
    });
      var closePopup = function () {
        //$("#styled_popup").fadeOut(1000, function () {  //commented for removing popup on front page 18/6/2013
        });
      }

*/
    //$.noConflict();
    

</script>
<!--Frontpage Popup End -->
<!-- /layout -->
<?php print $closure ?>
</body>
</html>
