<?php
// $Id: getdirections_box.tpl.php,v 1.1.2.1 2010/09/06 11:54:13 hutch Exp $
// $Name: DRUPAL-6--2-2 $

/**
 * @file getdirections_box.tpl.php
 * Template file for colorbox implementation
 */

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">
<!-- getdirections_box -->
<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
<style>
  body {
    width: 800px;
  }
  #page {
    min-width: 800px;
    width: 800px;
  }
</style>
</head>
<body class="<?php print $body_classes; ?>">
  <div id="page"><div id="page-inner">
    <div id="main"><div id="main-inner" class="clear-block">
      <div id="content"><div id="content-inner">
        <?php if ($title): ?>
          <h2 class="title"><?php print $title; ?></h2>
        <?php endif; ?>
        <div id="content-area">
          <?php print $content; ?>
        </div>
      </div></div>
    </div></div>
  </div></div>
  <?php print $closure; ?>
</body>
</html>
