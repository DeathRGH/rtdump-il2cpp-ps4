#pragma once

typedef const Il2CppImage *(*il2cpp_get_corlib_t)();
extern il2cpp_get_corlib_t il2cpp_get_corlib;



// assembly
typedef const Il2CppImage *(*il2cpp_assembly_get_image_t)(const Il2CppAssembly *assembly);
extern il2cpp_assembly_get_image_t il2cpp_assembly_get_image;



// domain
typedef Il2CppDomain *(*il2cpp_domain_get_t)();
extern il2cpp_domain_get_t il2cpp_domain_get;

typedef const Il2CppAssembly **(*il2cpp_domain_get_assemblies_t)(const Il2CppDomain *domain, size_t *size);
extern il2cpp_domain_get_assemblies_t il2cpp_domain_get_assemblies;



// image
typedef const Il2CppClass *(*il2cpp_image_get_class_t)(const Il2CppImage *image, size_t index);
extern il2cpp_image_get_class_t il2cpp_image_get_class;

typedef size_t(*il2cpp_image_get_class_count_t)(const Il2CppImage *image);
extern il2cpp_image_get_class_count_t il2cpp_image_get_class_count;

typedef const char *(*il2cpp_image_get_name_t)(const Il2CppImage *image);
extern il2cpp_image_get_name_t il2cpp_image_get_name;



// class
typedef Il2CppClass *(*il2cpp_class_from_name_t)(const Il2CppImage *image, const char *namespaze, const char *name);
extern il2cpp_class_from_name_t il2cpp_class_from_name;

typedef Il2CppClass *(*il2cpp_class_from_system_type_t)(Il2CppReflectionType *type);
extern il2cpp_class_from_system_type_t il2cpp_class_from_system_type;

typedef Il2CppClass *(*il2cpp_class_from_type_t)(const Il2CppType *type);
extern il2cpp_class_from_type_t il2cpp_class_from_type;

typedef FieldInfo *(*il2cpp_class_get_fields_t)(Il2CppClass *klass, void **iter);
extern il2cpp_class_get_fields_t il2cpp_class_get_fields;

typedef int(*il2cpp_class_get_flags_t)(const Il2CppClass *klass);
extern il2cpp_class_get_flags_t il2cpp_class_get_flags;

typedef Il2CppClass *(*il2cpp_class_get_interfaces_t)(Il2CppClass *klass, void **iter);
extern il2cpp_class_get_interfaces_t il2cpp_class_get_interfaces;

typedef const MethodInfo *(*il2cpp_class_get_method_from_name_t)(Il2CppClass *klass, const char *name, int argsCount);
extern il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name;

typedef const MethodInfo *(*il2cpp_class_get_methods_t)(Il2CppClass *klass, void **iter);
extern il2cpp_class_get_methods_t il2cpp_class_get_methods;

typedef const char *(*il2cpp_class_get_name_t)(Il2CppClass *klass);
extern il2cpp_class_get_name_t il2cpp_class_get_name;

typedef const char *(*il2cpp_class_get_namespace_t)(Il2CppClass *klass);
extern il2cpp_class_get_namespace_t il2cpp_class_get_namespace;

typedef Il2CppClass *(*il2cpp_class_get_parent_t)(Il2CppClass *klass);
extern il2cpp_class_get_parent_t il2cpp_class_get_parent;

typedef const PropertyInfo *(*il2cpp_class_get_properties_t)(Il2CppClass *klass, void **iter);
extern il2cpp_class_get_properties_t il2cpp_class_get_properties;

typedef const Il2CppType *(*il2cpp_class_get_type_t)(Il2CppClass *klass);
extern il2cpp_class_get_type_t il2cpp_class_get_type;

typedef bool(*il2cpp_class_is_enum_t)(const Il2CppClass *klass);
extern il2cpp_class_is_enum_t il2cpp_class_is_enum;

typedef bool(*il2cpp_class_is_valuetype_t)(const Il2CppClass *klass);
extern il2cpp_class_is_valuetype_t il2cpp_class_is_valuetype;



// field
typedef int(*il2cpp_field_get_flags_t)(FieldInfo *field);
extern il2cpp_field_get_flags_t il2cpp_field_get_flags;

typedef const char *(*il2cpp_field_get_name_t)(FieldInfo *field);
extern il2cpp_field_get_name_t il2cpp_field_get_name;

typedef size_t(*il2cpp_field_get_offset_t)(FieldInfo *field);
extern il2cpp_field_get_offset_t il2cpp_field_get_offset;

typedef const Il2CppType *(*il2cpp_field_get_type_t)(FieldInfo *field);
extern il2cpp_field_get_type_t il2cpp_field_get_type;

typedef void(*il2cpp_field_static_get_value_t)(FieldInfo *field, void *value);
extern il2cpp_field_static_get_value_t il2cpp_field_static_get_value;



// method
typedef uint32_t(*il2cpp_method_get_flags_t)(const MethodInfo *method, uint32_t *iflags);
extern il2cpp_method_get_flags_t il2cpp_method_get_flags;

typedef const char *(*il2cpp_method_get_name_t)(const MethodInfo *method);
extern il2cpp_method_get_name_t il2cpp_method_get_name;

typedef const Il2CppType *(*il2cpp_method_get_param_t)(const MethodInfo *method, uint32_t index);
extern il2cpp_method_get_param_t il2cpp_method_get_param;

typedef uint32_t(*il2cpp_method_get_param_count_t)(const MethodInfo *method);
extern il2cpp_method_get_param_count_t il2cpp_method_get_param_count;

typedef const char *(*il2cpp_method_get_param_name_t)(const MethodInfo *method, uint32_t index);
extern il2cpp_method_get_param_name_t il2cpp_method_get_param_name;

typedef const Il2CppType *(*il2cpp_method_get_return_type_t)(const MethodInfo *method);
extern il2cpp_method_get_return_type_t il2cpp_method_get_return_type;



// string
typedef Il2CppString *(*il2cpp_string_new_t)(const char *str);
extern il2cpp_string_new_t il2cpp_string_new;



// type
typedef char *(*il2cpp_type_get_name_t)(const Il2CppType *type);
extern il2cpp_type_get_name_t il2cpp_type_get_name;

typedef bool(*il2cpp_type_is_byref_t)(const Il2CppType *type);
extern il2cpp_type_is_byref_t il2cpp_type_is_byref;



// property
typedef const MethodInfo *(*il2cpp_property_get_get_method_t)(PropertyInfo *prop);
extern il2cpp_property_get_get_method_t il2cpp_property_get_get_method;

typedef const MethodInfo *(*il2cpp_property_get_set_method_t)(PropertyInfo *prop);
extern il2cpp_property_get_set_method_t il2cpp_property_get_set_method;

typedef const char *(*il2cpp_property_get_name_t)(PropertyInfo *prop);
extern il2cpp_property_get_name_t il2cpp_property_get_name;



class il2cpp_api {
public:
	static uintptr_t base_address;

	static bool init();

private:
	static uintptr_t find_function_by_name(const char *name);
};
