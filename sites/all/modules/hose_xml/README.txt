Hose XML, Hose XML UI

Hose XML is an XML export system for nodes.  Node fields are mapped to XML elements by a profile that is held in the database.  
Hose XML UI allows editing of XML profiles through a GUI.  Hose XML implements validation and conversion for several data types 
filefields and dates.
Complex mappings of fields to values and attributes are possible using tokens and the optional PHP input setting.
  
Please note:  Hose XML has a lot of functionality but no documentation in it's current development state.  Please check the 
project page on Drupal.org (http://drupal.org/project/hose_xml) regularly for releases and docs.

GETTING STARTED

Enable Hose XML, Hose XML UI and at least one data type module e.g. Text
Set up the module at admin/settings/hose_xml/settings:
  Enable for at least one content type (e.g. Page)
Create a profile at admin/settings/hose_xml/profiles
  Add an element and choose 'Title' as the cck_match
Create a node of an enabled type (e.g. Page)
View the node, at the bottom are Hose XML export options choose View XML 
  See the wondrous xml output :-)
  
FUNCTIONS

Profile Configuration Wizard - Create a profile, click 'manage', click 'Use configuration Wizard'
An element is added to the profile for each tag in an XML file.  Attributes and structure are imported.  Very useful for creating
the skeleton of a profile.
  
Sponsored by Red Bee Media Ltd.
  

