//js for magazine customisation
$(document).ready(function() {
	 $('div.drop_letter').css("font-size","12px");  
		$('.magazine_tools a').click(function(){
			var ourText = $('.drop_letter, .blogEntry .drop_letter p');
			var currFontSize = ourText.css('fontSize');
			var finalNum = parseFloat(currFontSize, 10);
			var stringEnding = currFontSize.slice(-2);
			if(this.id == 'plus') {
				finalNum *= 1.2;
			}
			else if (this.id == 'minus'){
				finalNum /=1.2;
			}
			ourText.animate({fontSize: finalNum + stringEnding},600);
		});

    $('#magazine a[href*=#]').click(function() {
     if (location.pathname.replace(/^\//,'') == this.pathname.replace(/^\//,'')
     && location.hostname == this.hostname) {
       var $target = $(this.hash);
       $target = $target.length && $target
       || $('[name=' + this.hash.slice(1) +']');
       if ($target.length) {
      var targetOffset = $target.offset().top;
      $('html,body')
      .animate({scrollTop: targetOffset}, 1000);
        return false;
       }
     }
    });
    $('#comment-a').mousedown(function() {
        $(this).addClass('opened');
    });
    $('#comment-a').mousedown(function() {
        $('#comments').toggle('slow');
    });

    $('a.opened').click(function() {
        $('#comments').toggle();
        $(this).removeClass('opened');
    });
    
    $('#comments').hide();

    var hash = false; 
checkHash();

function checkHash(){ 
    if(window.location.hash != hash) { 
        hash = window.location.hash; 
        processHash(hash); 
    } //t=setTimeout("checkHash()",400); 
}

function processHash(hash){
    $('#comments').show();
}

	});

