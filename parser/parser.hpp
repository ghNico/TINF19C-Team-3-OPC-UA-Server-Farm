#pragma once
#include <string>
#include <vector>
#include "pugixml.hpp"

using namespace std;

//Start: Header_________________________________________________________
struct source_object_information
{
    string origin_id; //in node
    string source_obj_id; //in node
};

struct revision
{
    string revision_date;
    string old_version;
    string new_version;
    string author_name;
    string comment;

    //f�r rekursion
    vector<revision> revisions;
};


struct header_struct
{
    //Information
    string description;
    string copyright;
    vector<string> additional_information;

    //Source
    vector<source_object_information> source_object_informations;

    //Versioning
    string change_mode; //in Node
    string version;
    vector<revision> revisions;

    //Identification
    string name; //in Node
    string id; //in Node


};

//Start: Header_________________________________________________________
//Start: AttributeTypeLib_________________________________________________________

struct nominal_scaled_type_struct
{
    vector<string> required_values;
};

struct ordinal_scaled_type_struct
{
    double required_max_value;
    double required_value;
    double required_min_value;
};

struct unknown_scaled_type_struct
{
    string requirement;
};

struct constraint
{
    string name;
    nominal_scaled_type_struct nominal_scaled_type;
    ordinal_scaled_type_struct ordinal_scaled_type;
    unknown_scaled_type_struct unknown_scaled_type;
};

struct attribute
{
    header_struct header;

    vector<attribute> attributes;

    string ref_attribute_type;
    string type;
    string value;
    string default_value;
    string unit;
    vector<constraint> constraints;
};

//nicht als AML Block in AML Editior zu sehen, nur in XML Node
struct ref_semantic_struct
{
    string corresponding_attribute_path; //in Node
};

struct attribute_type
{
    header_struct header;

    string type;

    ref_semantic_struct ref_semantic;

    vector<attribute_type> attribute_types;
    vector<attribute> attributes;
    string value;
    string default_value;
    string unit;
    vector<constraint> constraints;
};

struct attribute_type_lib
{
    header_struct header;

    vector<attribute_type> attribute_types;
};
//End: AttributeTypeLib _________________________________________________________
//Start: SystemUnitClassLib______________________________________________________

//nicht als AML Block in AML Editior zu sehen, nur in XML Node
struct role_requirement
{
    string ref_base_role_class_path; //in Node
};

//nicht als AML Block in AML Editior zu sehen, nur in XML Node
struct internal_link
{
    string name; //in Node
    string ref_partner_side_a; //in Node
    string ref_partner_side_b; //in Node
};

//nicht als AML Block in AML Editior zu sehen, nur in XML Node
struct supported_role_class
{
    string ref_role_class_path; //in Node
};


struct external_interface
{
    header_struct header;

    string ref_base_class_path;

    vector<attribute> attributes;
    vector<external_interface> external_interfaces;

};


struct internal_element
{
    header_struct header;

    vector<supported_role_class> supported_role_classes;
    vector<internal_link> internal_links;
    vector<role_requirement> role_requirements;

    vector<attribute> attributes;
    vector<external_interface> external_interfaces;
    vector<internal_element> internal_elements;

};


struct system_unit_class
{
    header_struct header;

    vector<supported_role_class> supported_role_classes;
    vector<internal_link> internal_links;

    vector<attribute> attributes;
    vector<external_interface> external_interfaces;
    vector<internal_element> internal_elements;
};


struct system_unit_class_lib
{
    header_struct header;

    vector<system_unit_class> system_unit_classes;

};

//End: SystemUnitClassLib______________________________________________________
//Start: Role Class Lib________________________________________________________
struct role_class
{
    header_struct header;

    vector<attribute> attributes;
    vector<external_interface> external_interfaces;
    vector<role_class> role_classes;
};

struct role_class_lib
{
    header_struct header;

    vector<role_class> role_classes;
};

//End: RoleClassLib_____________________________________________________________
//Start: InterfaceClassLib______________________________________________________

struct interface_class
{
    header_struct header;

    vector<attribute> attributes;
    vector<external_interface> external_interfaces;
    vector<interface_class> interface_classes;
};

struct interface_class_lib
{
    header_struct header;

    vector<interface_class> interface_classes;
};

//End: InterfaceClassLib________________________________________________________
//Start: InstanceHierarchy______________________________________________________

struct instance_hierarchy
{
    header_struct header;

    vector<internal_element> internal_elements;
};

//End: InstanceHierarchy________________________________________________________

struct source_document_information_struct
{
    string origin_name;
    string origin_id;
    string origin_version;
    string last_writing_date_time;
    string origin_project_id;
    string origin_project_title;
    string origin_release;
    string origin_vendor;
    string origin_vendor_url;
};

//h�chster Node (CAEXFile)
struct file
{
    string schema_version;
    string file_name;
    string superior_standard_version;
    source_document_information_struct source_document_information;

    vector<attribute_type_lib> attribute_type_libs;
    vector<system_unit_class_lib> system_unit_class_libs;
    vector<role_class_lib> role_class_libs;
    vector<interface_class_lib> interface_class_libs;
    vector<instance_hierarchy> instance_hierarchies;
};

vector<interface_class> get_interface_classes(const pugi::xml_node);
vector<role_class> get_role_classes(const pugi::xml_node);
source_document_information_struct get_source_document_information(const pugi::xml_node);
vector<system_unit_class> get_system_unit_classes(const pugi::xml_node);
vector<internal_element> get_internal_elements(pugi::xml_node);
vector<role_requirement> get_role_requirements(const pugi::xml_node);
vector<external_interface> get_external_interfaces(const pugi::xml_node);
vector<internal_link> get_internal_links(const pugi::xml_node);
vector<supported_role_class> get_supported_role_classes(const pugi::xml_node);
vector<attribute_type> get_attribute_types(const pugi::xml_node node);
ref_semantic_struct get_ref_semantic(const pugi::xml_node);
vector<attribute> get_attributes(const pugi::xml_node);
vector<constraint> get_constraints(const pugi::xml_node);
header_struct get_header(pugi::xml_node);
vector<source_object_information> get_source_object_information(const pugi::xml_node);
vector<string> get_additional_information(const pugi::xml_node);
vector<revision> get_revisions(const pugi::xml_node);

file load_file(const string& path);