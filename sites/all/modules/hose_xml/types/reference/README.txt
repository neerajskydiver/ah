Hose XML Reference 

This module is a Hose XML type for handling import and export of node references using a linked
hose profile.

Reference supports using unique_field module on import to update referenced nodes by their unique
fields.

*** EXAMPLE ***

Content type TYPE1 with one single value text field and one node reference

single value NAME


Content type TYPE2 with two single value text fields

multi value TEXTFIELD_A = 'valueA'
multi value TEXTFIELD_B = 'valueB'


The desired XML output is:

<MYSTUFF>
  <NAME>foo</NAME>
  <THING>
    <TEXTFIELD_A>valueA</TEXTFIELD_A>
    <TEXTFIELD_B>valueB</TEXTFIELD_B>
  </THING>
</MYSTUFF>

Set up a linked Hose profile SUBPROFILE for the referenced TYPE2 with 2 tags
TEXTFIELD_A - text - field_TEXTFIELD_A
TEXTFIELD_B - field_TEXTFIELD_B

Set up a main Hose profile for TYPE1 with 3 tags
<MYSTUFF> - container - no field
  <NAME> - text - field_NAME
  <THING> - reference - use profile SUBPROFILE
  
During EXPORT Hose XML processes the node using the main profile, when it finds the reference it uses 
the linked profile and the referenced node and the resulting XML is inserted into the main node.

