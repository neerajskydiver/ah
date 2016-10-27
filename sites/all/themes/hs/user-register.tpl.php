<head>
	<link href="\sites\all\themes\hs\user-register.css" rel="stylesheet">
	

</head>

<?php //drupal_add_js('sites/all/js/semicontacts.js');

/*
<!-- <p> <?php echo "<div id ='cnt' class = 'hdr' ><img src='/sites/all/themes/hs/images/eagle.png' height = '50'>
					<h1 id = 'red_text'> Register for Free Access</h1>
				</div>"; 
?></p>

<div class="my-form-wrapper" >
<?php
//print drupal_render($form['account']['pass']);
echo "<br>";
 echo "<h3  id ='cnt'>Already have an account? <a id ='clr' href = 'user' onclick = 'close_login()'><u> Login </u></a></h3>";
?>
  <?php echo "<div  id ='cnt'>"; print $rendered; echo "</div>";
  
    ?>
<?php
  echo "<br>";
  // echo '<input type="checkbox" name="free_sub" value="1">';
 echo "<h3  id ='cnt' > <input type='checkbox' name='free_sub' value='1'>Also sign me up for a free one-year subscription to the new digital version of American Heritage Magazine, launching in September!</h3>";
 echo "<br>";
 echo "<br>";

 echo "<h3  id ='cnt' >We won't sell your email to third parties. By clicking on the Register button above, you agree to our  <a id ='clr' href = '/content/terms-of-use' > privacy policy </a> and  <a id ='clr' href = '/content/terms-of-use' > terms of service </a></h3>";
 ?>
  
</div> -->
*/

// new code 04-07-2016
?>

<div id="mymodal" class="modal">
	<span class="close" ><button type="button" id = "close_btn"onclick="close_module()">X</button></span>
		<div class="my-form-wrapper" >
			<p><?php echo "<div id ='cnt' class = 'my_header'><img src='/sites/all/themes/hs/images/eagle.png' height = '50' ><h1> Register for Free Access</h1> </div>"; 
			?></p>
			<?php
//print drupal_render($form['account']['pass']);
				echo "<br>";
					 echo "<h3  id ='cnt' class = 'my_login'>Already have an account? <a id ='clr' href = 'user' onclick = 'close_module()'><u> Login </u></a></h3>";
					?>
					  <?php  echo "<div  id ='cnt' class='render'>"; print $rendered; echo "</div>";
					  			
					    ?>
					<?php
					  echo "<br>";
					  // echo '<input type="checkbox" name="free_sub" value="1">';
					 echo "<h3  id ='cnt' > <input type='checkbox' name='free_sub' value='1'>Also sign me up for a free subscription to the new digital version of American Heritage Magazine, launching soon!</h3>";
					 echo "<br>";
					 echo "<br>";

					 echo "<h3  id ='cnt' >We won't sell your email to third parties. By clicking on the Register button above, you agree to our  <a id ='clr' href = '/content/terms-of-use' > privacy policy </a> and  <a id ='clr' href = '/content/terms-of-use' > terms of service </a></h3>";
					 ?>
							  
		</div>

</div>
<!-- new code ends here -->
<!--   
 code for new block -->

  <!-- <div id="normal_reg">
	<?php   // echo "<div  id ='cnt1'>"; print $rendered; echo "</div>"; ?>
</div> -->   

<!--  code for new block -->

