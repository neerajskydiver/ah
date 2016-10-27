Hose XML Multigroup

This module is a Hose XML type for handling import and export of groups of fields using a linked
hose profile.

*** EXAMPLE ***

Consider a content type MYTYPE with one single two multi-value text fields

single value NAME
multi value TEXTFIELD_A = ('valueA1', 'valueA2', 'valueA3')
multi value TEXTFIELD_B = ('valueB1', 'valueB2', 'valueB3')


The desired XML output is:

<MYSTUFF>
  <NAME>foo</NAME>
  <THING>
    <TEXTFIELD_A>valueA1</TEXTFIELD_A>
    <TEXTFIELD_B>valueB1</TEXTFIELD_B>
  </THING>
  <THING>
    <TEXTFIELD_A>valueA2</TEXTFIELD_A>
    <TEXTFIELD_B>valueB2</TEXTFIELD_B>
  </THING>
  <THING>
    <TEXTFIELD_A>valueA3</TEXTFIELD_A>
    <TEXTFIELD_B>valueB3</TEXTFIELD_B>
  </THING>  
</MYSTUFF>

Set up a linked Hose profile SUBPROFILE for the multigroup with 2 tags
TEXTFIELD_A - text - field_TEXTFIELD_A
TEXTFIELD_B - field_TEXTFIELD_B

Set up a main Hose profile for MYTYPE with 3 tags
<MYSTUFF> - container - no field
  <NAME> - text - field_NAME
  <THING> - multigroup - use profile SUBPROFILE
  
  
During EXPORT Hose XML processes the node using the main profile, when it finds the multigroup it uses 
the linked profile to process the fields within the linked profile as groups of fields which are linked by 
their delta (array index).

*** USAGE ***
Works best with content_multigroup module which is part of CCK 3 but works fine with CCK 2+ but
you have to handle the UI stuff to link the fields in the node views and edits yourself