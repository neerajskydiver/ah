$(document).ready(function(){
  $("#form_sort").show(); //Show the form (by default it is hidden with CSS)
  $("#site").change(function(){ //When a user changes the select field value
    var url
    url = $("#site").val(); //Get value of the option they've selected
    if (url != ''){ //If not the first option (-- Select --)
      window.location = url; //Send user to URL
    }
  });
});