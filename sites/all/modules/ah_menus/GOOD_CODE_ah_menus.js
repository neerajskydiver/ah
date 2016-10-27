// $Id: ah_menus.js,v 1.21 2010/06/18 06:14:12 vordude Exp $

// This uses Superfish 1.4.8
// (http://users.tpg.com.au/j_birch/plugins/superfish)

// Add Superfish to all ah menus with some basic options.
(function ($) {
  $(document).ready(function() {
	$('ul.sf-menu').superfish({
      // Apply a generic hover class.
      hoverClass: 'sfHover',
      // Disable generation of arrow mark-up.
      autoArrows: false,
      // Disable drop shadows.
      dropShadows: false,
      // Mouse delay.
      delay: Drupal.settings.ah_menus_options.delay,
      // Animation speed.
      speed: Drupal.settings.ah_menus_options.speed
    // Add in Brandon Aaron’s bgIframe plugin for IE select issues.
    // http://plugins.jquery.com/node/46/release
    }).find('ul').bgIframe({opacity:false});
    $('ul.sf-menu ul').css('display', 'none');
  });
})(jQuery);


 $(document).ready(function() {
							
							
	
		var $alink = $('#ah-menu-0 a.active',this);
		$alink.each(function(i){
			var $li = $alink.eq(i).parents('li');

			$li.addClass('current');		
			$li.find('>ul:hidden').css('visibility','visible');
			$li.find('>ul:hidden').css('display','block');
			
		});	
	
	
	
	
	
	
	
	// alter default so arrow mark-up is not generated for this demo.
	// so many menu items (total of all examples) could slow initialisation performance
	// so arrow mark-up will be generated manually. Could go without arrows altogether
	// but that would risk people not finding the examples that show arrow support.
	$.fn.superfish.defaults.autoArrows = false;
	$('#ah-menu-0').superfish({
		pathClass: 'current'
	});	

	/*$('.sf-menu a').addClass('sf-with-ul');*/
	
	
	
	
	
	
/*
		var $acurrent = $('#ah-menu-0 a.active',this);
		$acurrent.each(function(i){
			var $li = $alink.eq(i).parents('li');

			$li.find('>ul:hidden').css('visibility','visible');
			$li.find('>ul:hidden').css('display','block');
		});	
*/
	
	
	
	
	
	});