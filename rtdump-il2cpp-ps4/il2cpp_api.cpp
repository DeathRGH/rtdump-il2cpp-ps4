#include "stdafx.h"

uintptr_t il2cpp_api::base_address;



il2cpp_get_corlib_t il2cpp_get_corlib;

// assembly
il2cpp_assembly_get_image_t il2cpp_assembly_get_image;

// domain
il2cpp_domain_get_t il2cpp_domain_get;
il2cpp_domain_get_assemblies_t il2cpp_domain_get_assemblies;

// image
il2cpp_image_get_class_t il2cpp_image_get_class;
il2cpp_image_get_class_count_t il2cpp_image_get_class_count;
il2cpp_image_get_name_t il2cpp_image_get_name;

// class
il2cpp_class_from_name_t il2cpp_class_from_name;
il2cpp_class_from_system_type_t il2cpp_class_from_system_type;
il2cpp_class_from_type_t il2cpp_class_from_type;
il2cpp_class_get_fields_t il2cpp_class_get_fields;
il2cpp_class_get_flags_t il2cpp_class_get_flags;
il2cpp_class_get_interfaces_t il2cpp_class_get_interfaces;
il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name;
il2cpp_class_get_methods_t il2cpp_class_get_methods;
il2cpp_class_get_name_t il2cpp_class_get_name;
il2cpp_class_get_namespace_t il2cpp_class_get_namespace;
il2cpp_class_get_parent_t il2cpp_class_get_parent;
il2cpp_class_get_properties_t il2cpp_class_get_properties;
il2cpp_class_get_type_t il2cpp_class_get_type;
il2cpp_class_is_enum_t il2cpp_class_is_enum;
il2cpp_class_is_valuetype_t il2cpp_class_is_valuetype;

// field
il2cpp_field_get_flags_t il2cpp_field_get_flags;
il2cpp_field_get_name_t il2cpp_field_get_name;
il2cpp_field_get_offset_t il2cpp_field_get_offset;
il2cpp_field_get_type_t il2cpp_field_get_type;
il2cpp_field_static_get_value_t il2cpp_field_static_get_value;

// method
il2cpp_method_get_flags_t il2cpp_method_get_flags;
il2cpp_method_get_name_t il2cpp_method_get_name;
il2cpp_method_get_param_t il2cpp_method_get_param;
il2cpp_method_get_param_count_t il2cpp_method_get_param_count;
il2cpp_method_get_param_name_t il2cpp_method_get_param_name;
il2cpp_method_get_return_type_t il2cpp_method_get_return_type;

// string
il2cpp_string_new_t il2cpp_string_new;

// type
il2cpp_type_is_byref_t il2cpp_type_is_byref;

// property
il2cpp_property_get_get_method_t il2cpp_property_get_get_method;
il2cpp_property_get_set_method_t il2cpp_property_get_set_method;
il2cpp_property_get_name_t il2cpp_property_get_name;



uintptr_t api_register_addr;

// the offset between two strings being read in the function
int index_offset;

// the offset from function start to the end of the first instruction reading a string
int string_end_offset;

// the offset between the string and the corrosponding function being read
int string_function_offset;

// the offset between the string end and the next allocator size instruction
int string_alloc_size_offset;

// size of memory allocation for one api function
// seems to be always 0x30
int allocation_size = 0x30;

// to add another sig if your game is not found
// search for a reference to the string "il2cpp_init"
// it should have exactly 1 xref close to the start of a function
uintptr_t find_register_symbols_addr() {
	uintptr_t addr = 0;

	// push    rbp
	// mov     rbp, rsp
	// push    rbx
	// sub     rsp, ??
	// ??
	// mov     edi, 0x30
	addr = find_pattern("Il2CppUserAssemblies", "55 48 89 E5 53 48 83 EC ?? ?? ?? ?? ?? ?? ?? ?? BF 30 00 00 00");
	if (addr) {
		index_offset = 0x48;
		string_end_offset = 0x2F;
		string_function_offset = 0x00;
		string_alloc_size_offset = 0x30;
		return addr;
	}

	// push    rbp
	// mov     rbp, rsp
	// push    r14
	// push    rbx
	// sub     rsp, ??
	// ??
	// mov     edi, 0x30
	addr = find_pattern("Il2CppUserAssemblies", "55 48 89 E5 41 56 53 48 83 EC ?? ?? ?? ?? ?? ?? ?? ?? BF 30 00 00 00");
	if (addr) {
		index_offset = 0x50;
		string_end_offset = 0x38;
		string_function_offset = 0x22;
		string_alloc_size_offset = 0x38;
		return addr;
	}

	return 0;
}

uintptr_t il2cpp_api::find_function_by_name(const char *name) {
	if (!api_register_addr) {
		return 0;
	}

	uintptr_t cur_addr = api_register_addr + string_end_offset;
	while (true) {
		const char *func_name = (const char *)(cur_addr + *(int *)(cur_addr - 4));
		if (!strcmp(func_name, name)) {
			return cur_addr + string_function_offset + *(int *)(cur_addr + string_function_offset + 3) + 7;
		}

		if (*(int *)(cur_addr + string_alloc_size_offset + 1) != allocation_size) {
			break;
		}

		cur_addr += index_offset;

		// failsafe in case something went very wrong
		// most games have a function size of ~0x5000
		if ((cur_addr - api_register_addr) > 0x10000) {
			break;
		}
	}

	return 0;
}

bool il2cpp_api::init() {
	il2cpp_api::base_address = resolve_module_base("Il2CppUserAssemblies");
	printf("[il2cpp_api::init] il2cpp_api::base_address 0x%lX\n", il2cpp_api::base_address);

	api_register_addr = find_register_symbols_addr();
	if (!api_register_addr) {
		printf("[il2cpp_api::init] ERROR: Failed to find valid sig!\n");
		return false;
	}

	printf("[il2cpp_api::init] api_register_addr 0x%lX\n", api_register_addr);

	// @todo: add error handling for the following
	//        possibly re-use macro from original git

	il2cpp_get_corlib = (il2cpp_get_corlib_t)find_function_by_name("il2cpp_get_corlib");

	il2cpp_assembly_get_image = (il2cpp_assembly_get_image_t)find_function_by_name("il2cpp_assembly_get_image");

	il2cpp_domain_get = (il2cpp_domain_get_t)find_function_by_name("il2cpp_domain_get");
	il2cpp_domain_get_assemblies = (il2cpp_domain_get_assemblies_t)find_function_by_name("il2cpp_domain_get_assemblies");

	il2cpp_image_get_class = (il2cpp_image_get_class_t)find_function_by_name("il2cpp_image_get_class");
	il2cpp_image_get_class_count = (il2cpp_image_get_class_count_t)find_function_by_name("il2cpp_image_get_class_count");
	il2cpp_image_get_name = (il2cpp_image_get_name_t)find_function_by_name("il2cpp_image_get_name");

	il2cpp_class_from_name = (il2cpp_class_from_name_t)find_function_by_name("il2cpp_class_from_name");
	il2cpp_class_from_system_type = (il2cpp_class_from_system_type_t)find_function_by_name("il2cpp_class_from_system_type");
	il2cpp_class_from_type = (il2cpp_class_from_type_t)find_function_by_name("il2cpp_class_from_type");
	il2cpp_class_get_fields = (il2cpp_class_get_fields_t)find_function_by_name("il2cpp_class_get_fields");
	il2cpp_class_get_flags = (il2cpp_class_get_flags_t)find_function_by_name("il2cpp_class_get_flags");
	il2cpp_class_get_interfaces = (il2cpp_class_get_interfaces_t)find_function_by_name("il2cpp_class_get_interfaces");
	il2cpp_class_get_method_from_name = (il2cpp_class_get_method_from_name_t)find_function_by_name("il2cpp_class_get_method_from_name");
	il2cpp_class_get_methods = (il2cpp_class_get_methods_t)find_function_by_name("il2cpp_class_get_methods");
	il2cpp_class_get_name = (il2cpp_class_get_name_t)find_function_by_name("il2cpp_class_get_name");
	il2cpp_class_get_namespace = (il2cpp_class_get_namespace_t)find_function_by_name("il2cpp_class_get_namespace");
	il2cpp_class_get_parent = (il2cpp_class_get_parent_t)find_function_by_name("il2cpp_class_get_parent");
	il2cpp_class_get_properties = (il2cpp_class_get_properties_t)find_function_by_name("il2cpp_class_get_properties");
	il2cpp_class_get_type = (il2cpp_class_get_type_t)find_function_by_name("il2cpp_class_get_type");
	il2cpp_class_is_enum = (il2cpp_class_is_enum_t)find_function_by_name("il2cpp_class_is_enum");
	il2cpp_class_is_valuetype = (il2cpp_class_is_valuetype_t)find_function_by_name("il2cpp_class_is_valuetype");

	il2cpp_field_get_flags = (il2cpp_field_get_flags_t)find_function_by_name("il2cpp_field_get_flags");
	il2cpp_field_get_name = (il2cpp_field_get_name_t)find_function_by_name("il2cpp_field_get_name");
	il2cpp_field_get_offset = (il2cpp_field_get_offset_t)find_function_by_name("il2cpp_field_get_offset");
	il2cpp_field_get_type = (il2cpp_field_get_type_t)find_function_by_name("il2cpp_field_get_type");
	il2cpp_field_static_get_value = (il2cpp_field_static_get_value_t)find_function_by_name("il2cpp_field_static_get_value");

	il2cpp_method_get_flags = (il2cpp_method_get_flags_t)find_function_by_name("il2cpp_method_get_flags");
	il2cpp_method_get_name = (il2cpp_method_get_name_t)find_function_by_name("il2cpp_method_get_name");
	il2cpp_method_get_param = (il2cpp_method_get_param_t)find_function_by_name("il2cpp_method_get_param");
	il2cpp_method_get_param_count = (il2cpp_method_get_param_count_t)find_function_by_name("il2cpp_method_get_param_count");
	il2cpp_method_get_param_name = (il2cpp_method_get_param_name_t)find_function_by_name("il2cpp_method_get_param_name");
	il2cpp_method_get_return_type = (il2cpp_method_get_return_type_t)find_function_by_name("il2cpp_method_get_return_type");

	il2cpp_string_new = (il2cpp_string_new_t)find_function_by_name("il2cpp_string_new");

	il2cpp_type_is_byref = (il2cpp_type_is_byref_t)find_function_by_name("il2cpp_type_is_byref");

	il2cpp_property_get_get_method = (il2cpp_property_get_get_method_t)find_function_by_name("il2cpp_property_get_get_method");
	il2cpp_property_get_set_method = (il2cpp_property_get_set_method_t)find_function_by_name("il2cpp_property_get_set_method");
	il2cpp_property_get_name = (il2cpp_property_get_name_t)find_function_by_name("il2cpp_property_get_name");

	return true;
}
