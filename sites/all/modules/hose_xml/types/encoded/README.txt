
This type is designed to enable the storage of more complex data structures, e.g. an address,
or a number of key / value pairs etc.

The data is stored in a json_encoded format, and it is expected that a developer will create 
the means by which to display the content appropriately.

This module has only been tested with the xml snippets below, further testing is required.


An example of the settings for this type are:

Global WSDL definitions:
------------------------

This would be a complex type to describe how data would be stored. 

The WSDL snippet here would be displayed at the top of the WSDL.


<xsd:element name="taskDetailPairs">
  <xsd:complexType>
    <xsd:sequence>
      <xsd:element name="taskDetailKey" type="xsd:string"/>
      <xsd:element name="taskDetailValue" type="xsd:string"/>
    </xsd:sequence>
  </xsd:complexType>
</xsd:element>
         
         
WSDL Definition:
----------------

The WSDL definition to describe how the complex type fits within an element is
entered here, and example would be:

<xsd:element name="ArrayOftaskDetailPairs">
  <xsd:complexType>
    <xsd:restriction base="soapenc:Array">
      <xsd:attribute ref="soapenc:arrayType" arrayType="xsd:taskDetailPairs[]"/>
    </xsd:restriction>
  </xsd:complexType>
</xsd:element>
         
         
Hose XML Configuration:
-----------------------
In the above example, the hose xml configurtation would need to have a container, e.g. 'taskDetails'.

The element in the WSDL would then be rendered as:

<xsd:element name="taskDetails">
  <xsd:complexType>
    <xsd:sequence>
      <xsd:element name="ArrayOftaskDetailPairs">
        <xsd:complexType>
          <xsd:restriction base="soapenc:Array">
            <xsd:attribute ref="soapenc:arrayType" arrayType="xsd:taskDetailPairs[]"/>
          </xsd:restriction>
        </xsd:complexType>
      </xsd:element>
    </xsd:sequence>
  </xsd:complexType>
</xsd:element>
         