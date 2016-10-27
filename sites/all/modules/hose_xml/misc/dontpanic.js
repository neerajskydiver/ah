
Drupal.behaviors.hose_xmlDontPanic = function(context) {
  var useID = '';
  var popupStatus = 0;

  $('table.content-multiple-table input.form-text.text').click(function() {
    // set variable for use elsewhere
    useID = this.id;
    // messily check each field in turn
    match = this.value.split(/(?:\[name:)(.+?)(?:\])/);
    $('.popup-name').val(match[1] ? match[1] : "");
    match = this.value.split(/(?:\[display:)(.+?)(?:\])/);
    $('.popup-display').val(match[1] ? match[1] : "");
    match = this.value.split(/(?:\[amg_artist_id:)(.+?)(?:\])/);
    $('.popup-amg').val(match[1] ? match[1] : "");
    match = this.value.split(/(?:\[billing:)(.+?)(?:\])/);
    $('.popup-billing').val(match[1] ? match[1] : "");
    // match the last one @TODO needs work, no case for blank fields above?
    // two ways to handle, one account for blankness, two utilise required fields?
    match = this.value.split(/(?:\])([^\]]+)$/);
//    blank = this.value.split(/([^]])(.*)$/);
    $('.popup-extra').val(match[1] ? match[1] : "");
    centerPopup();
    loadPopup();
  });

  $(".popup-submit").click(function() {
    // messily build a load of variables
    name = $('.popup-name').val() ? '[name:' + $('.popup-name').val() + ']' : '';
    display = $('.popup-display').val() ? '[display:' + $('.popup-display').val() + ']' : '';
    amg = $('.popup-amg').val() ? '[amg_artist_id:' + $('.popup-amg').val() + ']' : '';
    billing = $('.popup-billing').val() ? '[billing:' + $('.popup-billing').val() + ']' : '';
    extra = $('.popup-extra').val();
    // apply them to the clicked input fields
    $('#'+useID).val(name + display + amg + billing + extra);
    disablePopup();
  		return false;
	 });

  $("#popupContactClose").click(function() {
    disablePopup();
  });
  $("#backgroundPopup").click(function() {
    disablePopup();
  });
  $(document).keypress(function(e) {
    if(e.keyCode==27 && popupStatus == 1){
      disablePopup();
    }
  });

  // Hit this if anything in our div is altered...
  $('div.form-item :input').focus(function() {
	  $(this).parents().filter('div').addClass('hose_xml-highlight');

    // Turn on our confirm message for every 'input' form element which could navigate away
    $(':input', document).bind("change", function() {
      setConfirmUnload(true);
    });

  });

  // Turn off our confirm message if it's the "Save" or "Preview" buttons which have been clicked
  $('#edit-submit-popup').click(function() {
    setConfirmUnload(false);
  });
  $('#edit-submit').click(function() {
    setConfirmUnload(false);
  });
  $('#edit-preview').click(function() {
    setConfirmUnload(false);
  });

  function setConfirmUnload(on) {
    window.onbeforeunload = (on) ? unloadMessage : null;
  }
  function unloadMessage() {
    return Drupal.t('If you navigate away from this page without first saving your data, your changes will be lost.');
  }
  function loadPopup() {
    if (popupStatus == 0) {
      $("#backgroundPopup").css({
        "opacity": "0.7"
      });
      $("#backgroundPopup").fadeIn("slow");
      $("#popupContact").fadeIn("slow");
      popupStatus = 1;
    }
  }
  function disablePopup() {
    if (popupStatus == 1) {
      $("#backgroundPopup").fadeOut("slow");
      $("#popupContact").fadeOut("slow");
      popupStatus = 0;
    }
  }
  function centerPopup() {
    var windowWidth = document.documentElement.clientWidth;
    var windowHeight = document.documentElement.clientHeight;
    var popupHeight = $("#popupContact").height();
    var popupWidth = $("#popupContact").width();
    $("#popupContact").css({
      "position": "absolute",
      "top": windowHeight-popupHeight/2,
      "left": windowWidth/2-popupWidth/2
    });
    $("#backgroundPopup").css({
      "height": windowHeight
    });
  }
}
