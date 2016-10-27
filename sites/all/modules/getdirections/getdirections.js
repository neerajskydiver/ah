// $Id: getdirections.js,v 1.3.2.2.2.3 2010/09/07 08:20:39 hutch Exp $
// $Name: DRUPAL-6--2-2 $

/**
 * @file
 * Javascript functions for getdirections module
 *
 * @author Bob Hutchinson http://drupal.org/user/52366
 * jquery stuff
*/

Drupal.behaviors.getdirections = function() {
  // check that colorbox is loaded
  if ((typeof($("a[rel='getdirectionsbox']").colorbox) == 'function') && Drupal.settings.getdirections_colorbox.enable == 1) {
    $("a[rel='getdirectionsbox']").colorbox({
      iframe:true,
      innerWidth: Drupal.settings.getdirections_colorbox.width,
      innerHeight: Drupal.settings.getdirections_colorbox.height
    });
  }
}

