Hose XML Import - Feeds integration for Hose XML

Hose XML Import is an XML import system for nodes. In terms of mapping XML struncture to Drupal's object struncture it works in the same way as the parent module Hose XML.
This module works by intergrating Feeds API system with Hose XML to provide a flexible way of importing XML structured data into Drupal.

GETTING STARTED

Enable Hose XML, Hose XML UIi, Hose XML Import, Feeds and at least one data type module e.g. Text
Create a new node type at admin/content/types/add 
Create a profile at admin/settings/hose_xml/profiles (eg. 'hose_test')
  Add an element and choose 'Title' as the cck_match
Create a new Feeds Importer at admin/build/feeds/createi
  If you want to upload a file, change the Fetcher to 'File Upload'
  Select 'Hose XML Parser' as a Parser
  Select 'Hose XML Node Processor' as a Processor
    At 'Hose XML Profile' select the previously created Hose XML Profile ('hose_test')
    At 'Content Type' select the previously created Node Type
Go to import/hose_test and upload your XML file

FUNCTIONS
Almost the same as Hose XML.

Sponsored by Red Bee Media Ltd.


