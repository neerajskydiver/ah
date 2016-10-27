// function load_login()
// {
// 	// alert(arguments.callee);
	
// 		$( "#user-register" ).dialog({
// 					autoOpen: true,
// 					width: 700,
//         			height: 500, 
// 	           		modal: true,
	           
// 	        });
// 	$( "#user-register" ).dialog( "open" );

// 	// }
// 	// else
// 	// {
// 	// 	$("#block-formblock-user_register").hide();
// 	// }
		
// 	 // $("#user-login-form").attr("action", );
// }



function load_login(msg_len)
{
	 	
	if (msg_len == 0) {

		$( "#user-register" ).dialog({
					autoOpen: true,
					width: 700,
        			height: 500, 
	           		modal: true,
	           
	        });
	$("#user-register").dialog("open");

	}
	else
	{
		$("#block-formblock-user_register").hide();
	}
		
	
}

function close_login()
{
	$("#user-register").dialog("close");
	return false;	
	
}

