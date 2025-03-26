#include "stdafx.h"

uintptr_t il2cpp_api::base_address = 0;
int il2cpp_api::handle = 0;
bool il2cpp_api::has_error = false;



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
il2cpp_type_get_name_t il2cpp_type_get_name;
il2cpp_type_is_byref_t il2cpp_type_is_byref;

// property
il2cpp_property_get_get_method_t il2cpp_property_get_get_method;
il2cpp_property_get_set_method_t il2cpp_property_get_set_method;
il2cpp_property_get_name_t il2cpp_property_get_name;

uintptr_t il2cpp_api::resolve_function_by_name(const char *name, bool allow_fail) {
    if (il2cpp_api::handle <= 0) {
        return 0;
    }

    void *resolved_addr = 0;
    if (sceKernelDlsym(il2cpp_api::handle, name, &resolved_addr)) {
        if (!allow_fail) { // some functions are not available in older apis but this is accounted for
            il2cpp_api::has_error = true;
        }
        printf("[il2cpp_api::find_function_by_name] ERROR: Failed to resolve function \"%s\"\n", name);
        return 0;
    }

    return (uintptr_t)resolved_addr;
}

bool il2cpp_api::init() {
    il2cpp_api::has_error = false;
    il2cpp_api::base_address = resolve_module_base("Il2CppUserAssemblies");
    printf("[il2cpp_api::init] il2cpp_api::base_address 0x%lX\n", il2cpp_api::base_address);

    il2cpp_api::handle = sceKernelLoadStartModule("Il2CppUserAssemblies.prx", 0, 0, 0, 0, 0);
    if (il2cpp_api::handle <= 0) {
        printf("[il2cpp_api::init] ERROR: Failed to find handle for \"Il2CppUserAssemblies.prx\"!\n");
        return false;
    }

    il2cpp_get_corlib = (il2cpp_get_corlib_t)resolve_function_by_name("il2cpp_get_corlib");

    il2cpp_assembly_get_image = (il2cpp_assembly_get_image_t)resolve_function_by_name("il2cpp_assembly_get_image");

    il2cpp_domain_get = (il2cpp_domain_get_t)resolve_function_by_name("il2cpp_domain_get");
    il2cpp_domain_get_assemblies = (il2cpp_domain_get_assemblies_t)resolve_function_by_name("il2cpp_domain_get_assemblies");

    il2cpp_image_get_class = (il2cpp_image_get_class_t)resolve_function_by_name("il2cpp_image_get_class", true);
    il2cpp_image_get_class_count = (il2cpp_image_get_class_count_t)resolve_function_by_name("il2cpp_image_get_class_count", true);
    il2cpp_image_get_name = (il2cpp_image_get_name_t)resolve_function_by_name("il2cpp_image_get_name");

    il2cpp_class_from_name = (il2cpp_class_from_name_t)resolve_function_by_name("il2cpp_class_from_name");
    il2cpp_class_from_system_type = (il2cpp_class_from_system_type_t)resolve_function_by_name("il2cpp_class_from_system_type");
    il2cpp_class_from_type = (il2cpp_class_from_type_t)resolve_function_by_name("il2cpp_class_from_type");
    il2cpp_class_get_fields = (il2cpp_class_get_fields_t)resolve_function_by_name("il2cpp_class_get_fields");
    il2cpp_class_get_flags = (il2cpp_class_get_flags_t)resolve_function_by_name("il2cpp_class_get_flags");
    il2cpp_class_get_interfaces = (il2cpp_class_get_interfaces_t)resolve_function_by_name("il2cpp_class_get_interfaces");
    il2cpp_class_get_method_from_name = (il2cpp_class_get_method_from_name_t)resolve_function_by_name("il2cpp_class_get_method_from_name");
    il2cpp_class_get_methods = (il2cpp_class_get_methods_t)resolve_function_by_name("il2cpp_class_get_methods");
    il2cpp_class_get_name = (il2cpp_class_get_name_t)resolve_function_by_name("il2cpp_class_get_name");
    il2cpp_class_get_namespace = (il2cpp_class_get_namespace_t)resolve_function_by_name("il2cpp_class_get_namespace");
    il2cpp_class_get_parent = (il2cpp_class_get_parent_t)resolve_function_by_name("il2cpp_class_get_parent");
    il2cpp_class_get_properties = (il2cpp_class_get_properties_t)resolve_function_by_name("il2cpp_class_get_properties");
    il2cpp_class_get_type = (il2cpp_class_get_type_t)resolve_function_by_name("il2cpp_class_get_type");
    il2cpp_class_is_enum = (il2cpp_class_is_enum_t)resolve_function_by_name("il2cpp_class_is_enum");
    il2cpp_class_is_valuetype = (il2cpp_class_is_valuetype_t)resolve_function_by_name("il2cpp_class_is_valuetype");

    il2cpp_field_get_flags = (il2cpp_field_get_flags_t)resolve_function_by_name("il2cpp_field_get_flags");
    il2cpp_field_get_name = (il2cpp_field_get_name_t)resolve_function_by_name("il2cpp_field_get_name");
    il2cpp_field_get_offset = (il2cpp_field_get_offset_t)resolve_function_by_name("il2cpp_field_get_offset");
    il2cpp_field_get_type = (il2cpp_field_get_type_t)resolve_function_by_name("il2cpp_field_get_type");
    il2cpp_field_static_get_value = (il2cpp_field_static_get_value_t)resolve_function_by_name("il2cpp_field_static_get_value");

    il2cpp_method_get_flags = (il2cpp_method_get_flags_t)resolve_function_by_name("il2cpp_method_get_flags");
    il2cpp_method_get_name = (il2cpp_method_get_name_t)resolve_function_by_name("il2cpp_method_get_name");
    il2cpp_method_get_param = (il2cpp_method_get_param_t)resolve_function_by_name("il2cpp_method_get_param");
    il2cpp_method_get_param_count = (il2cpp_method_get_param_count_t)resolve_function_by_name("il2cpp_method_get_param_count");
    il2cpp_method_get_param_name = (il2cpp_method_get_param_name_t)resolve_function_by_name("il2cpp_method_get_param_name");
    il2cpp_method_get_return_type = (il2cpp_method_get_return_type_t)resolve_function_by_name("il2cpp_method_get_return_type");

    il2cpp_string_new = (il2cpp_string_new_t)resolve_function_by_name("il2cpp_string_new");

    il2cpp_type_get_name = (il2cpp_type_get_name_t)resolve_function_by_name("il2cpp_type_get_name");
    il2cpp_type_is_byref = (il2cpp_type_is_byref_t)resolve_function_by_name("il2cpp_type_is_byref");

    il2cpp_property_get_get_method = (il2cpp_property_get_get_method_t)resolve_function_by_name("il2cpp_property_get_get_method");
    il2cpp_property_get_set_method = (il2cpp_property_get_set_method_t)resolve_function_by_name("il2cpp_property_get_set_method");
    il2cpp_property_get_name = (il2cpp_property_get_name_t)resolve_function_by_name("il2cpp_property_get_name");

    return !il2cpp_api::has_error;
}
