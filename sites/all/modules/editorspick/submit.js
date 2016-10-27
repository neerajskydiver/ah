$(document).ready(function() {

var site = $('#edit-site').val();

       if (!site){
		$('#edit-submit').attr('disabled', 'TRUE');
		$('#edit-collection').attr('disabled', 'TRUE');
	       return false;
	}
       if (site=='No Records'){
		$('#edit-submit').attr('disabled', 'TRUE');
		$('#edit-collection').attr('disabled', 'TRUE');
	       return false;
	}

				   
  $('#edit-submit').click(function() {
		 
	var site=$('#edit-site').val();
	//alert(site);

		//alert( $('#edit-collection').empty )
		// $('#edit-submit').attr('disabled', 'FALSE');

    	if ($('#edit-collection').val()==0)
   	{	
	    alert('No records exists');
	    return false;  

   	}
  	else	if ($('#edit-collection').val()==null)
  	 {	
	    alert('Please select '+site);
	    return false;  

  	 }
   
 	  else
  	 {
	   var answer = confirm("Do you want to delete selected options?")
	   if (answer){
		$('#editorspick-form').submit();
   	    }
	   return false;  
  	 }
   
   
  });

});
