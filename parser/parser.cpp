#include "pugixml.hpp"
#include <iostream>
#include "parser.hpp"

vector<revision> get_revisions(const pugi::xml_node node)
{
	vector<revision> revisions{};
	for (const auto revision_path : node.select_nodes("Revision"))
	{
		const auto revision_node = revision_path.node();
		revision revision
		{
			revision_node.select_node("RevisionDate").node().text().get(),
			revision_node.select_node("OldVersion").node().text().get(),
			revision_node.select_node("NewVersion").node().text().get(),
			revision_node.select_node("AuthorName").node().text().get(),
			revision_node.select_node("Comment").node().text().get(),
			get_revisions(revision_node)
		};
		revisions.push_back(revision);
	}
	return revisions;
}

vector<string> get_additional_information(const pugi::xml_node node)
{
	vector<string> information{};
	for (const auto information_node : node.select_nodes("AdditionalInformation"))
		information.emplace_back(information_node.node().text().get());
	return information;
}

vector<source_object_information> get_source_object_information(const pugi::xml_node node)
{
	vector<source_object_information> information{};
	for (const auto information_path : node.select_nodes("SourceObjectInformation"))
	{
		source_object_information source_object_information{
			information_path.node().attribute("OriginID").value(),
			information_path.node().attribute("SourceObjID").value(),
		};
		information.push_back(source_object_information);
	}
	return information;
}

header_struct get_header(const pugi::xml_node node)
{
	return header_struct{
		node.select_node("Description").node().text().get(),
		node.select_node("Copyright").node().text().get(),
		get_additional_information(node),
		get_source_object_information(node),
		node.attribute("ChangeMode").value(),
		node.select_node("Version").node().text().get(),
		get_revisions(node),
		node.attribute("Name").value(),
		node.attribute("ID").value()
	};
}

vector<constraint> get_constraints(const pugi::xml_node node)
{
	vector<constraint> constraints;
	for (const auto constraint_path : node.select_nodes("Constraint"))
	{
		const auto constraint_node = constraint_path.node();
		constraint constraint{};
		constraint.name = constraint_node.attribute("Name").value();
		const auto type_node = constraint_node.first_child();
		const string type = type_node.name();

		if (type == "NominalScaledType")
		{
			for (const auto& required_value_node : type_node.children())
				constraint.nominal_scaled_type.required_values.emplace_back(required_value_node.text().get());
		}
		else if (type == "OrdinalScaledType")
		{
			try
			{
				constraint.ordinal_scaled_type.required_max_value = std::stod(type_node.select_node("RequiredMaxValue").node().text().get());
				constraint.ordinal_scaled_type.required_value = std::stod(type_node.select_node("RequiredValue").node().text().get());
				constraint.ordinal_scaled_type.required_min_value = std::stod(type_node.select_node("RequiredMinValue").node().text().get());
			}
			catch (exception) {}
		}
		else
			constraint.unknown_scaled_type.requirement = type_node.select_node("Requirements").node().text().get();

		constraints.push_back(constraint);
	}
	return constraints;
}

vector<attribute> get_attributes(const pugi::xml_node node)
{
	vector<attribute> attributes;
	for (const auto attribute_path : node.select_nodes("Attribute"))
	{
		const auto attribute_node = attribute_path.node();
		attribute attribute = {
			get_header(attribute_node),
			get_attributes(attribute_node),
			attribute_node.attribute("RefAttributeType").value(),
			attribute_node.attribute("AttributeDataType").value(),
			attribute_node.select_node("Value").node().text().get(),
			attribute_node.select_node("DefaultValue").node().text().get(),
			attribute_node.attribute("Unit").value(),
			get_constraints(attribute_node)
		};

		attributes.push_back(attribute);
	}
	return attributes;
}

ref_semantic_struct get_ref_semantic(const pugi::xml_node node)
{
	return ref_semantic_struct{ node.select_node("RefSemantic").node().attribute("CorrespondingAttributePath").value() };
}

vector<attribute_type> get_attribute_types(const pugi::xml_node node)
{
	vector<attribute_type> attribute_types{};
	for (const auto attribute_type_path : node.select_nodes("AttributeType"))
	{
		const auto attribute_type_node = attribute_type_path.node();
		attribute_type attribute_type = {
			get_header(attribute_type_node),
			attribute_type_node.attribute("AttributeDataType").value(),
			get_ref_semantic(attribute_type_node),
			get_attribute_types(attribute_type_node),
			get_attributes(attribute_type_node),
			attribute_type_node.select_node("Value").node().text().get(),
			attribute_type_node.select_node("DefaultValue").node().text().get(),
			attribute_type_node.attribute("Unit").value(),
			get_constraints(attribute_type_node)
		};
		attribute_types.push_back(attribute_type);
	}
	return attribute_types;
}

vector<supported_role_class> get_supported_role_classes(const pugi::xml_node node)
{
	vector<supported_role_class> supported_role_classes{};
	for (const auto supported_role_class_path : node.select_nodes("SupportedRoleClass"))
		supported_role_classes.push_back(supported_role_class{ supported_role_class_path.node().attribute("RefRoleClassPath").value() });
	return supported_role_classes;
}

vector<internal_link> get_internal_links(const pugi::xml_node node)
{
	vector<internal_link> internal_links{};
	for (const auto internal_link_path : node.select_nodes("InternalLink"))
	{
		const auto internal_link_node = internal_link_path.node();
		internal_link internal_link{
			internal_link_node.attribute("Name").value(),
			internal_link_node.attribute("RefPartnerSideA").value(),
			internal_link_node.attribute("RefPartnerSideB").value()
		};
		internal_links.push_back(internal_link);
	}
	return internal_links;
}

vector<external_interface> get_external_interfaces(const pugi::xml_node node)
{
	vector<external_interface> external_interfaces{};
	for (const auto external_interface_path : node.select_nodes("ExternalInterface"))
	{
		const auto external_interface_node = external_interface_path.node();
		external_interface external_interface{
			get_header(external_interface_node),
			external_interface_node.attribute("RefBaseClassPath").value(),
			get_attributes(external_interface_node),
			get_external_interfaces(external_interface_node)
		};
		external_interfaces.push_back(external_interface);
	}
	return external_interfaces;
}

vector<role_requirement> get_role_requirements(const pugi::xml_node node)
{
	vector<role_requirement> role_requirements{};
	for (const auto role_requirement_path : node.select_nodes("SupportedRoleClass"))
		role_requirements.push_back(role_requirement{ role_requirement_path.node().attribute("RefBaseRoleClassPath").value() });
	return role_requirements;
}

vector<internal_element> get_internal_elements(pugi::xml_node node)
{
	vector<internal_element> internal_elements{};
	for (const auto internal_element_path : node.select_nodes("InternalElement"))
	{
		const auto internal_element_node = internal_element_path.node();
		internal_element internal_element{
			get_header(internal_element_node),
			get_supported_role_classes(internal_element_node),
			get_internal_links(internal_element_node),
			get_role_requirements(internal_element_node),
			get_attributes(internal_element_node),
			get_external_interfaces(internal_element_node),
			get_internal_elements(internal_element_node)
		};
		internal_elements.push_back(internal_element);
	}
	return internal_elements;
}

vector<system_unit_class> get_system_unit_classes(const pugi::xml_node node)
{
	vector<system_unit_class> system_unit_classes{};
	for (const auto system_unit_class_path : node.select_nodes("SystemUnitClass"))
	{
		const auto system_unit_class_node = system_unit_class_path.node();
		system_unit_class system_unit_class{
			get_header(system_unit_class_node),
			get_supported_role_classes(system_unit_class_node),
			get_internal_links(system_unit_class_node),
			get_attributes(system_unit_class_node),
			get_external_interfaces(system_unit_class_node),
			get_internal_elements(system_unit_class_node)
		};
		system_unit_classes.push_back(system_unit_class);
	}
	return system_unit_classes;
}

source_document_information_struct get_source_document_information(const pugi::xml_node node)
{
	return source_document_information_struct{
		node.attribute("OriginName").value(),
		node.attribute("OriginID").value(),
		node.attribute("OriginVersion").value(),
		node.attribute("LastWritingDateTime").value(),
		node.attribute("OriginProjectID").value(),
		node.attribute("OriginProjectTitle").value(),
		node.attribute("OriginRelease").value(),
		node.attribute("OriginVendor").value(),
		node.attribute("OriginVendorURL").value(),
	};
}

vector<role_class> get_role_classes(const pugi::xml_node node)
{
	vector<role_class> role_classes{};
	for (const auto role_class_path : node.select_nodes("RoleClass"))
	{
		const auto role_class_node = role_class_path.node();
		role_class role_class{
			get_header(role_class_node),
			get_attributes(role_class_node),
			get_external_interfaces(role_class_node),
			get_role_classes(role_class_node)
		};
		role_classes.push_back(role_class);
	}
	return role_classes;
}

vector<interface_class> get_interface_classes(const pugi::xml_node node)
{
	vector<interface_class> interface_classes{};
	for (const auto interface_class_path : node.select_nodes("RoleClass"))
	{
		const auto interface_class_node = interface_class_path.node();
		interface_class interface_class{
			get_header(interface_class_node),
			get_attributes(interface_class_node),
			get_external_interfaces(interface_class_node),
			get_interface_classes(interface_class_node)
		};
		interface_classes.push_back(interface_class);
	}
	return interface_classes;
}


file load_file(const string& path)
{
	pugi::xml_document doc;
	const auto result = doc.load_file(path.c_str());
	const auto root = doc.child("CAEXFile");

	const auto attribute_type_lib_nodes = root.select_nodes("AttributeTypeLib");
	const auto system_unit_class_lib_nodes = root.select_nodes("SystemUnitClassLib");
	const auto role_class_lib_nodes = root.select_nodes("RoleClassLib");
	const auto interface_class_lib_nodes = root.select_nodes("InterfaceClassLib");
	const auto instance_hierarchy_nodes = root.select_nodes("InstanceHierarchy");

	file file = {
		root.attribute("SchemaVersion").value(),
		root.attribute("FileName").value(),
		root.select_node("SuperiorStandardVersion").node().text().get(),
		get_source_document_information(root),
		vector<attribute_type_lib> {},
		vector<system_unit_class_lib> {},
		vector<role_class_lib> {},
		vector<interface_class_lib> {},
		vector<instance_hierarchy> {},
	};

	for (const auto attribute_type_lib_path : attribute_type_lib_nodes)
	{
		const auto attribute_type_lib_node = attribute_type_lib_path.node();
		attribute_type_lib attribute_type_lib = {
			get_header(attribute_type_lib_node),
			get_attribute_types(attribute_type_lib_node)
		};
		file.attribute_type_libs.push_back(attribute_type_lib);
	}

	for (const auto system_unit_class_lib_path : system_unit_class_lib_nodes)
	{
		const auto system_unit_class_lib_node = system_unit_class_lib_path.node();
		system_unit_class_lib system_unit_class_lib = {
			get_header(system_unit_class_lib_node),
			get_system_unit_classes(system_unit_class_lib_node)
		};
		file.system_unit_class_libs.push_back(system_unit_class_lib);
	}

	for (const auto role_class_lib_path : role_class_lib_nodes)
	{
		const auto role_class_lib_node = role_class_lib_path.node();
		role_class_lib role_class_lib{
			get_header(role_class_lib_node),
			get_role_classes(role_class_lib_node)
		};
		file.role_class_libs.push_back(role_class_lib);
	}

	for (const auto interface_class_lib_path : interface_class_lib_nodes)
	{
		const auto interface_class_lib_node = interface_class_lib_path.node();
		interface_class_lib interface_class_lib{
			get_header(interface_class_lib_node),
			get_interface_classes(interface_class_lib_node)
		};
		file.interface_class_libs.push_back(interface_class_lib);
	}

	for (const auto instance_hierarchy_path : instance_hierarchy_nodes)
	{
		const auto instance_hierarchy_node = instance_hierarchy_path.node();
		instance_hierarchy instance_hierarchy{
			get_header(instance_hierarchy_node),
			get_internal_elements(instance_hierarchy_node)
		};
		file.instance_hierarchies.push_back(instance_hierarchy);
	}

	return file;
}