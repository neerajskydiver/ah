$(document).ready(function() {
		/*$('#node-form').validate({
		  rules: {
			edit-upload: {
				required : true,
				accept: "xls|csv"
			}
		  }
		});*/
	});   
function check(){
var select_type=$('#edit-adtype-select').val();

if (select_type==0)
{
	
    var error_msg = "Please select type.<a href='#edit-adtype-select-wrapper'>click here</a> to select type";
	$('#file_error').html(error_msg);
 	$('#edit-attach').attr("disabled", true);
	return false;
}
else if($('#edit-upload').val()!= ''){
		if(Validate($('#edit-upload').val()) == false){
				$('#edit-attach').attr("disabled", true); 	return false;
			}else{
				$('#edit-attach').attr("disabled", false); 	return true;
			}	
	}
	


}



function Validate(file_name) {
	
	var type = document.getElementById('edit-adtype-select').value;
	
	 if(type == 'html'){
		var _validFileExtensions = [".jpg", ".jpeg", ".bmp", ".gif", ".png", ".swf", ".flv"];	
	}else if(type == 'image'){
		var _validFileExtensions = [".jpg", ".jpeg", ".bmp", ".gif", ".png"];
	}else if(type == 'flash'){
		var _validFileExtensions = [".swf", ".flv"];
	}
	
	

		var sFileName = file_name;
		if (sFileName.length > 0) {
			var blnValid = false;
			for (var j = 0; j < _validFileExtensions.length; j++) {
				var sCurExtension = _validFileExtensions[j];
				if (sFileName.substr(sFileName.length - sCurExtension.length, sCurExtension.length).toLowerCase() == sCurExtension.toLowerCase()) {
					blnValid = true;
					break;
				}
			}
	
			if (!blnValid) {
				//alert("Sorry, " + sFileName + " is invalid, allowed extensions are: " + _validFileExtensions.join(", "));
				var error_msg = "Sorry, " + sFileName + " is invalid, allowed extensions are: " + _validFileExtensions.join(", ");
				$('#file_error').html(error_msg);
				return false;
			}
		}
	$('#file_error').html('');	
    return true;
}