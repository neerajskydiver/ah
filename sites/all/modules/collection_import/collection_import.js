/* Created date : 09 March 2011
*  Created by : Akshay Sardar / Akshar
*  Aim : Collection Import Form Validation 
*/
$(document).ready(function() {
	$('#edit-upload-wrapper').append("<span style=\"color:red\" id=\"e1\"></span>");
	$('#edit-select-list-wrapper').append("<span style=\"color:red\" id=\"e2\"></span>");
	$('#import-collection-form').submit(function() {
		var error = 0; 
		var file_val = $('#edit-upload').val();
		var sel_val = $('#edit-select-list').val()
		if(file_val == ''){
				error = 1;
				$('#e1').text('Please uplaod a file');
		}else{
				$('#e1').text('');
		 }
		if(sel_val == -1){
				error = 1 ;
				$('#e2').text('Please select a site');
		}else{
				$('#e2').text('');
		 }
		if(error == 1){
				return false;
		}
	});
});