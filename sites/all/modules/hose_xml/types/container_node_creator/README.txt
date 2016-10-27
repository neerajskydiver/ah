
= Description =
This module is an attempt to provide a solution to the following requirement:
Having a XML structure as the one below, create nodes for each one of the <node> elements
  embedded in the <nodes> element.

<?xml version="1.0" encoding="UTF-8"?>
<nodes>
  <node>
    <title>My 1st node</title>
    <body>Description....</body>
    <cck_field_1>my value</cck_field_1>
  </node>
  <node>
    <title>My 2nd node</title>
    <body>Description....</body>
    <cck_field_1>my other value</cck_field_1>
  </node>
</nodes>


= Usage =
Create a hose xml profile and add a Container Node Creator with the tag "node". Choose the node type that this
 container node create field will create. Underneath/Within the "node" item profile add elements that describe
 the node structure that is going to be imported.