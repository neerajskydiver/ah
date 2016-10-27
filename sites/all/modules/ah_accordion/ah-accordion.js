/*
 * 	easyAccordion 0.1 - jQuery plugin
 *	written by Andrea Cima Serniotti	
 *	http://www.madeincima.eu
 *
 *	Copyright (c) 2010 Andrea Cima Serniotti (http://www.madeincima.eu)
 *	Dual licensed under the MIT (MIT-LICENSE.txt) and GPL (GPL-LICENSE.txt) licenses.
 *	Built for jQuery library http://jquery.com
 */

// #quicktabs-tab-1-0
// #quicktabs-tab-1-1
// #quicktabs-tab-1-2
// #quicktabs-tab-1-3
// #quicktabs-tab-1-4

$(document).ready(function () {
							
	
	$('.accordion-1').easyAccordion({ 
			autoStart: true, 
			slideInterval: 8000
	});
	$('.accordion-2').easyAccordion({ 
			autoStart: true, 
			slideInterval: 8000
	});
	$('.accordion-3').easyAccordion({ 
			autoStart: true, 
			slideInterval: 8000
	});	
	$('.accordion-4').easyAccordion({ 
			autoStart: true, 
			slideInterval: 8000
	});
	$('.accordion-5').easyAccordion({ 
			autoStart: true, 
			slideInterval: 8000
	});	


/*
  $('#quicktabs-tab-1-0').click(function(){
  	$('.accordion-1').easyAccordion({ 
			  autoStart: true, 

	  });
	});

	
  $('#quicktabs-tab-1-1').click(function(){
  	$('.accordion-2').easyAccordion({ 
			  autoStart: true, 
	  });
	});

  $('#quicktabs-tab-1-2').click(function(){
		  $('.accordion-3').easyAccordion({ 
			  autoStart: true, 
	  });
	});

  $('#quicktabs-tab-1-3').click(function(){
		  $('.accordion-4').easyAccordion({ 
			  autoStart: true, 
	  });
	});

  $('#quicktabs-tab-1-4').click(function(){
		  $('.accordion-5').easyAccordion({ 
			  autoStart: true, 
	  });
	});
	*/
	
	
});
(function(jQuery) {
	jQuery.fn.easyAccordion = function(options) {
	
	var defaults = {			
		slideNum: true,
		autoStart: false,
		slideInterval: 8000
	};
			
	this.each(function() {
		
		var settings = jQuery.extend(defaults, options);		
		jQuery(this).find('dl').addClass('easy-accordion');
		
		
		// -------- Set the variables ------------------------------------------------------------------------------
		
		jQuery.fn.setVariables = function() {
			dlWidth = jQuery(this).width();
			dlHeight = jQuery(this).height();
			dtWidth = jQuery(this).find('dt').outerHeight();
			if (jQuery.browser.msie){ dtWidth = $(this).find('dt').outerWidth();}
			dtHeight = dlHeight - (jQuery(this).find('dt').outerWidth()-jQuery(this).find('dt').width());
			slideTotal = jQuery(this).find('dt').size();
			ddWidth = dlWidth - (dtWidth*slideTotal) - (jQuery(this).find('dd').outerWidth(true)-jQuery(this).find('dd').width());
			ddHeight = dlHeight - (jQuery(this).find('dd').outerHeight(true)-jQuery(this).find('dd').height());
		};
		jQuery(this).setVariables();
		
		// -------- Fix some weird cross-browser issues due to the CSS rotation -------------------------------------

//-commented by akshay-	 if (jQuery.browser.safari){ var dtTop = (dlHeight-dtWidth)/2; var dtOffset = -dtTop;  /* Safari and Chrome */ }
//-commented by akshay-  if (jQuery.browser.mozilla){ var dtTop = dlHeight - 20; var dtOffset = - 20; /* FF */ }
//-commented by akshay-  if (jQuery.browser.msie){ var dtTop = 0; var dtOffset = 0; /* IE */ }
		
		
		// -------- Getting things ready ------------------------------------------------------------------------------
		
		var f = 1;
		jQuery(this).find('dt').each(function(){
		/*------ START - Code added by akshay -----*/
			if (jQuery.browser.mozilla){ dtHeight = 230; dtTop = 225; dtOffset = -18 ;}
			if (jQuery.browser.msie){ dtHeight = 230; dtTop = 0;  dtOffset = 2;}
			if (jQuery.browser.safari){ dtHeight = 230; dtTop = 100;  dtOffset = -98;}
		/*------ END - Code added by akshay -----*/
	
			jQuery(this).css({'width':dtHeight,'top':dtTop,'margin-left':dtOffset});	
			
			if(settings.slideNum == true){
				jQuery('<span class="slide-number">'+f+'</span>').appendTo(this);
				if(jQuery.browser.msie){	
					var slideNumLeft = parseInt(jQuery(this).find('.slide-number').css('left')) - 14;
					jQuery(this).find('.slide-number').css({'left': slideNumLeft})
					if(jQuery.browser.version == 6.0 || jQuery.browser.version == 7.0){
						jQuery(this).find('.slide-number').css({'bottom':'auto'});
					}
					if(jQuery.browser.version == 8.0){
					var slideNumTop = jQuery(this).find('.slide-number').css('bottom');
					var slideNumTopVal = parseInt(slideNumTop) + parseInt(jQuery(this).css('padding-top'))  - 12; 
					jQuery(this).find('.slide-number').css({'bottom': slideNumTopVal}); 
					}
				} else {
					var slideNumTop = jQuery(this).find('.slide-number').css('bottom');
					var slideNumTopVal = parseInt(slideNumTop) + parseInt(jQuery(this).css('padding-top')); 
					jQuery(this).find('.slide-number').css({'bottom': slideNumTopVal}); 
				}
			}
			f = f + 1;
		});
		
		if(jQuery(this).find('.active').size()) { 
			jQuery(this).find('.active').next('dd').addClass('active');
		} else {
			jQuery(this).find('dt:first').addClass('active').next('dd').addClass('active');
		}
		
		/*------ START - Code added by akshay -----*/		
		dtWidth = 46;
		/*------ END - Code added by akshay -----*/
	
		jQuery(this).find('dt:first').css({'left':'0'}).next().css({'left':dtWidth});
		
		/*------ START - Code added by akshay -----*/	
		ddWidth = (537 -(slideTotal * 46));
		ddHeight = 243;
		/*------ END - Code added by akshay -----*/
		jQuery(this).find('dd').css({'width':ddWidth,'height':ddHeight});	
	

		
		// -------- Functions ------------------------------------------------------------------------------
		
		jQuery.fn.findActiveSlide = function() {
				var i = 1;
				this.find('dt').each(function(){
				if(jQuery(this).hasClass('active')){
					activeID = i; // Active slide
				} else if (jQuery(this).hasClass('no-more-active')){
					noMoreActiveID = i; // No more active slide
				}
				i = i + 1;
			});
		};
			
		jQuery.fn.calculateSlidePos = function() {
			var u = 2;	
			/*------ START - Code added by akshay -----*/		
			dtWidth = 46;
			/*------ END - Code added by akshay -----*/			
			
			jQuery(this).find('dt').not(':first').each(function(){	
				var activeDtPos = dtWidth*activeID;
				if(u <= activeID){
					var leftDtPos = dtWidth*(u-1);
					jQuery(this).animate({'left': leftDtPos});
					if(u < activeID){ // If the item sits to the left of the active element
						jQuery(this).next().css({'left':leftDtPos+dtWidth});	
					} else{ // If the item is the active one
						jQuery(this).next().animate({'left':activeDtPos});
					}
				} else {
					/*------ START - Code added by akshay -----*/		
					dlWidth = 540; 
					/*------ END - Code added by akshay -----*/						
					var rightDtPos = dlWidth-(dtWidth*(slideTotal-u+1));
					jQuery(this).animate({'left': rightDtPos});
					var rightDdPos = rightDtPos+dtWidth;
					jQuery(this).next().animate({'left':rightDdPos});	
				}
				u = u+ 1;
			});
			setTimeout( function() {
				jQuery('.easy-accordion').find('dd').not('.active').each(function(){ 
					jQuery(this).css({'display':'none'});
				});
			}, 400);
			
		};
	
		jQuery.fn.activateSlide = function() {
			this.parent('dl').setVariables();	
			this.parent('dl').find('dd').css({'display':'block'});
			this.parent('dl').find('dd.plus').removeClass('plus');
			this.parent('dl').find('.no-more-active').removeClass('no-more-active');
			this.parent('dl').find('.active').removeClass('active').addClass('no-more-active');
			this.addClass('active').next().addClass('active');	
			this.parent('dl').findActiveSlide();
			if(activeID < noMoreActiveID){
				this.parent('dl').find('dd.no-more-active').addClass('plus');
			}
			this.parent('dl').calculateSlidePos();	
		};
	
		jQuery.fn.rotateSlides = function(slideInterval, timerInstance) {
			var accordianInstance = jQuery(this);
			timerInstance.value = setTimeout(function(){accordianInstance.rotateSlides(slideInterval, timerInstance);}, slideInterval);
			jQuery(this).findActiveSlide();
			var totalSlides = jQuery(this).find('dt').size();
			var activeSlide = activeID;
			var newSlide = activeSlide + 1;
			if (newSlide > totalSlides) newSlide = 1;
			jQuery(this).find('dt:eq(' + (newSlide-1) + ')').activateSlide(); // activate the new slide
		}


		// -------- Let's do it! ------------------------------------------------------------------------------
		
		function trackerObject() {this.value = null}
		var timerInstance = new trackerObject();
		
		jQuery(this).findActiveSlide();
		jQuery(this).calculateSlidePos();
		
		if (settings.autoStart == true){
			var accordianInstance = jQuery(this);
			var interval = parseInt(settings.slideInterval);
			timerInstance.value = setTimeout(function(){
				accordianInstance.rotateSlides(interval, timerInstance);
				}, interval);
		} 

		jQuery(this).find('dt').not('active').click(function(){		
			jQuery(this).activateSlide();
			clearTimeout(timerInstance.value);
		});	
				
		if (!(jQuery.browser.msie && jQuery.browser.version == 6.0)){ 
			jQuery('dt').hover(function(){
				jQuery(this).addClass('hover');
			}, function(){
				jQuery(this).removeClass('hover');
			});
		}
	});
	};
})(jQuery);
