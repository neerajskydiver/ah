$(document).ready(function(){
	$(".left_mag dd ").hide();
	$("li.active").parents().filter('dd').show();

	$("dt a").click(function(){
		$("dd:visible").slideUp("slow");
		$(this).parent().next().slideDown("slow");
		return false;
	});
});
