#include "stdafx.h"

std::mutex dumper_lock;

std::string get_method_modifier(uint32_t flags) {
    std::stringstream output;
    uint32_t access = flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK;
    
    switch (access) {
    case METHOD_ATTRIBUTE_PRIVATE:
        output << "private ";
        break;
    case METHOD_ATTRIBUTE_PUBLIC:
        output << "public ";
        break;
    case METHOD_ATTRIBUTE_FAMILY:
        output << "protected ";
        break;
    case METHOD_ATTRIBUTE_ASSEM:
    case METHOD_ATTRIBUTE_FAM_AND_ASSEM:
        output << "internal ";
        break;
    case METHOD_ATTRIBUTE_FAM_OR_ASSEM:
        output << "protected internal ";
        break;
    }

    if (flags & METHOD_ATTRIBUTE_STATIC) {
        output << "static ";
    }
    if (flags & METHOD_ATTRIBUTE_ABSTRACT) {
        output << "abstract ";
        if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
            output << "override ";
        }
    }
    else if (flags & METHOD_ATTRIBUTE_FINAL) {
        if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
            output << "sealed override ";
        }
    }
    else if (flags & METHOD_ATTRIBUTE_VIRTUAL) {
        if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_NEW_SLOT) {
            output << "virtual ";
        }
        else {
            output << "override ";
        }
    }
    if (flags & METHOD_ATTRIBUTE_PINVOKE_IMPL) {
        output << "extern ";
    }

    return output.str();
}

bool _il2cpp_type_is_byref(const Il2CppType *type) {
    uint32_t byref = type->byref;
    if (il2cpp_type_is_byref) {
        byref = il2cpp_type_is_byref(type);
    }

    return byref;
}

const char *_il2cpp_class_get_name(Il2CppClass *klass) {
    const char *internal_name = il2cpp_class_get_name(klass);

    if (!strcmp(internal_name, "Object")) {
        return "object";
    }
    if (!strcmp(internal_name, "Void")) {
        return "void";
    }
    if (!strcmp(internal_name, "Boolean")) {
        return "bool";
    }
    if (!strcmp(internal_name, "Byte")) {
        return "byte";
    }
    if (!strcmp(internal_name, "SByte")) {
        return "sbyte";
    }
    if (!strcmp(internal_name, "Int16")) {
        return "short";
    }
    if (!strcmp(internal_name, "UInt16")) {
        return "ushort";
    }
    if (!strcmp(internal_name, "Int32")) {
        return "int";
    }
    if (!strcmp(internal_name, "UInt32")) {
        return "uint";
    }
    if (!strcmp(internal_name, "Int64")) {
        return "long";
    }
    if (!strcmp(internal_name, "UInt64")) {
        return "ulong";
    }
    if (!strcmp(internal_name, "Single")) {
        return "float";
    }
    if (!strcmp(internal_name, "Double")) {
        return "double";
    }
    if (!strcmp(internal_name, "Char")) {
        return "char";
    }
    if (!strcmp(internal_name, "String")) {
        return "string";
    }

    if (!strcmp(internal_name, "Object[]")) {
        return "object[]";
    }
    if (!strcmp(internal_name, "Boolean[]")) {
        return "bool[]";
    }
    if (!strcmp(internal_name, "Byte[]")) {
        return "byte[]";
    }
    if (!strcmp(internal_name, "SByte[]")) {
        return "sbyte[]";
    }
    if (!strcmp(internal_name, "Int16[]")) {
        return "short[]";
    }
    if (!strcmp(internal_name, "UInt16[]")) {
        return "ushort[]";
    }
    if (!strcmp(internal_name, "Int32[]")) {
        return "int[]";
    }
    if (!strcmp(internal_name, "UInt32[]")) {
        return "uint[]";
    }
    if (!strcmp(internal_name, "Int64[]")) {
        return "long[]";
    }
    if (!strcmp(internal_name, "UInt64[]")) {
        return "ulong[]";
    }
    if (!strcmp(internal_name, "Single[]")) {
        return "float[]";
    }
    if (!strcmp(internal_name, "Double[]")) {
        return "double[]";
    }
    if (!strcmp(internal_name, "Char[]")) {
        return "char[]";
    }
    if (!strcmp(internal_name, "String[]")) {
        return "string[]";
    }

    return internal_name;
}

std::string resolve_generic_type(Il2CppClass *klass) {
    if (!klass->generic_class) {
        return _il2cpp_class_get_name(klass);
    }

    // base type name
    std::string generic_name = klass->name;

    // remove placeholders
    size_t pos = generic_name.find("`");
    if (pos != std::string::npos) {
        generic_name.erase(pos, 2);
    }
    generic_name += "<";

    Il2CppGenericInst *generic_inst = klass->generic_class->context;
    for (size_t i = 0; i < generic_inst->type_argc; ++i) {
        if (i > 0) {
            generic_name += ", ";
        }

        const Il2CppType *arg_type = generic_inst->type_argv[i];
        Il2CppClass *arg_class = il2cpp_class_from_type(arg_type);

        generic_name += resolve_generic_type(arg_class);
    }

    generic_name += ">";
    return generic_name;
}

std::string resolve_type(const Il2CppType *type) {
    switch (type->type) {
    case IL2CPP_TYPE_SZARRAY: {
        std::string element_type = resolve_type(type->data.type);
        return element_type + "[]";
    }
    default:
        Il2CppClass *klass = il2cpp_class_from_type(type);
        return resolve_generic_type(klass);
    }
}

std::string dump_method(Il2CppClass *klass) {
    std::stringstream output;
    output << "\n\t// Methods\n";
    void *iter = nullptr;
    while (const MethodInfo *method = il2cpp_class_get_methods(klass, &iter)) {
        // TODO attribute
        if (method->methodPointer) {
            output << "\t// RVA: 0x";
            output << std::hex << (uint64_t)method->methodPointer - il2cpp_api::base_address; // @todo: make a option for base/rebased
            output << " VA: 0x";
            output << std::hex << (uint64_t)method->methodPointer;
        }
        else {
            output << "\t// RVA: 0x VA: 0x0";
        }
        /*if (method->slot != 65535) {
            outPut << " Slot: " << std::dec << method->slot;
        }*/
        output << "\n\t";
        uint32_t iflags = 0;
        uint32_t flags = il2cpp_method_get_flags(method, &iflags);
        output << get_method_modifier(flags);
        // TODO genericContainerIndex
        const Il2CppType *return_type = il2cpp_method_get_return_type(method);
        if (_il2cpp_type_is_byref(return_type)) {
            output << "ref ";
        }
        Il2CppClass *return_class = il2cpp_class_from_type(return_type);
        output << resolve_generic_type(return_class) << " " << il2cpp_method_get_name(method) << "(";
        uint32_t param_count = il2cpp_method_get_param_count(method);
        for (int32_t i = 0; i < param_count; ++i) {
            const Il2CppType *param = il2cpp_method_get_param(method, i);
            uint32_t attrs = param->attrs;
            if (_il2cpp_type_is_byref(param)) {
                if (attrs & PARAM_ATTRIBUTE_OUT && !(attrs & PARAM_ATTRIBUTE_IN)) {
                    output << "out ";
                }
                else if (attrs & PARAM_ATTRIBUTE_IN && !(attrs & PARAM_ATTRIBUTE_OUT)) {
                    output << "in ";
                }
                else {
                    output << "ref ";
                }
            }
            else {
                if (attrs & PARAM_ATTRIBUTE_IN) {
                    output << "[In] ";
                }
                if (attrs & PARAM_ATTRIBUTE_OUT) {
                    output << "[Out] ";
                }
            }
            Il2CppClass *parameter_class = il2cpp_class_from_type(param);
            output << resolve_generic_type(parameter_class) << " " << il2cpp_method_get_param_name(method, i);
            output << ", ";
        }
        if (param_count > 0) {
            output.seekp(-2, output.cur);
        }
        output << ") { }\n";
        // TODO GenericInstMethod
    }

    return output.str();
}

std::string dump_property(Il2CppClass *klass) {
    std::stringstream output;
    output << "\n\t// Properties\n";
    void *iter = nullptr;
    while (const PropertyInfo *prop_const = il2cpp_class_get_properties(klass, &iter)) {
        // TODO attribute
        PropertyInfo *prop = (PropertyInfo *)prop_const;
        const MethodInfo *get = il2cpp_property_get_get_method(prop);
        const MethodInfo *set = il2cpp_property_get_set_method(prop);
        const char *prop_name = il2cpp_property_get_name(prop);
        output << "\t";
        Il2CppClass *prop_class = nullptr;
        uint32_t iflags = 0;
        if (get) {
            output << get_method_modifier(il2cpp_method_get_flags(get, &iflags));
            prop_class = il2cpp_class_from_type(il2cpp_method_get_return_type(get));
        }
        else if (set) {
            output << get_method_modifier(il2cpp_method_get_flags(set, &iflags));
            const Il2CppType *param = il2cpp_method_get_param(set, 0);
            prop_class = il2cpp_class_from_type(param);
        }
        if (prop_class) {
            output << resolve_generic_type(prop_class) << " " << prop_name << " { ";
            if (get) {
                output << "get; ";
            }
            if (set) {
                output << "set; ";
            }
            output << "}\n";
        }
        else {
            if (prop_name) {
                output << " // unknown property " << prop_name;
            }
        }
    }

    return output.str();
}

std::string dump_field(Il2CppClass *klass) {
    std::stringstream output;
    output << "\n\t// Fields\n";
    void *iter = nullptr;
    while (FieldInfo *field = il2cpp_class_get_fields(klass, &iter)) {
        // TODO attribute
        output << "\t";
        int32_t attrs = il2cpp_field_get_flags(field);
        int32_t access = attrs & FIELD_ATTRIBUTE_FIELD_ACCESS_MASK;
        switch (access) {
        case FIELD_ATTRIBUTE_PRIVATE:
            output << "private ";
            break;
        case FIELD_ATTRIBUTE_PUBLIC:
            output << "public ";
            break;
        case FIELD_ATTRIBUTE_FAMILY:
            output << "protected ";
            break;
        case FIELD_ATTRIBUTE_ASSEMBLY:
        case FIELD_ATTRIBUTE_FAM_AND_ASSEM:
            output << "internal ";
            break;
        case FIELD_ATTRIBUTE_FAM_OR_ASSEM:
            output << "protected internal ";
            break;
        }
        if (attrs & FIELD_ATTRIBUTE_LITERAL) {
            output << "const ";
        }
        else {
            if (attrs & FIELD_ATTRIBUTE_STATIC) {
                output << "static ";
            }
            if (attrs & FIELD_ATTRIBUTE_INIT_ONLY) {
                output << "readonly ";
            }
        }

        const Il2CppType *field_type = il2cpp_field_get_type(field);
        std::string field_type_name = resolve_type(field_type);

        output << field_type_name << " " << il2cpp_field_get_name(field);

        // TODO Get the field value after the constructor is initialized
        if (attrs & FIELD_ATTRIBUTE_LITERAL && il2cpp_class_is_enum(klass)) {
            uint64_t val = 0;
            il2cpp_field_static_get_value(field, &val);
            output << " = " << std::dec << val;
        }
        output << "; // 0x" << std::hex << il2cpp_field_get_offset(field) << "\n";
    }

    return output.str();
}

std::string dump_type(const Il2CppType *type) {
    std::stringstream output;
    Il2CppClass *klass = il2cpp_class_from_type(type);
    output << "\n// Namespace: " << il2cpp_class_get_namespace(klass) << "\n";
    
    int32_t flags = il2cpp_class_get_flags(klass);
    if (flags & TYPE_ATTRIBUTE_SERIALIZABLE) {
        output << "[Serializable]\n";
    }

    // TODO attribute
    bool is_valuetype = il2cpp_class_is_valuetype(klass);
    bool is_enum = il2cpp_class_is_enum(klass);
    int32_t visibility = flags & TYPE_ATTRIBUTE_VISIBILITY_MASK;

    switch (visibility) {
    case TYPE_ATTRIBUTE_PUBLIC:
    case TYPE_ATTRIBUTE_NESTED_PUBLIC:
        output << "public ";
        break;
    case TYPE_ATTRIBUTE_NOT_PUBLIC:
    case TYPE_ATTRIBUTE_NESTED_FAM_AND_ASSEM:
    case TYPE_ATTRIBUTE_NESTED_ASSEMBLY:
        output << "internal ";
        break;
    case TYPE_ATTRIBUTE_NESTED_PRIVATE:
        output << "private ";
        break;
    case TYPE_ATTRIBUTE_NESTED_FAMILY:
        output << "protected ";
        break;
    case TYPE_ATTRIBUTE_NESTED_FAM_OR_ASSEM:
        output << "protected internal ";
        break;
    }

    if (flags & TYPE_ATTRIBUTE_ABSTRACT && flags & TYPE_ATTRIBUTE_SEALED) {
        output << "static ";
    }
    else if (!(flags & TYPE_ATTRIBUTE_INTERFACE) && flags & TYPE_ATTRIBUTE_ABSTRACT) {
        output << "abstract ";
    }
    else if (!is_valuetype && !is_enum && flags & TYPE_ATTRIBUTE_SEALED) {
        output << "sealed ";
    }
    if (flags & TYPE_ATTRIBUTE_INTERFACE) {
        output << "interface ";
    }
    else if (is_enum) {
        output << "enum ";
    }
    else if (is_valuetype) {
        output << "struct ";
    }
    else {
        output << "class ";
    }

    output << il2cpp_class_get_name(klass); // TODO genericContainerIndex
    std::vector<std::string> extends;
    Il2CppClass *parent = il2cpp_class_get_parent(klass);
    if (!is_valuetype && !is_enum && parent) {
        const Il2CppType *parent_type = il2cpp_class_get_type(parent);
        if (parent_type->type != IL2CPP_TYPE_OBJECT) {
            extends.emplace_back(il2cpp_class_get_name(parent));
        }
    }

    void *iter = nullptr;
    while (Il2CppClass *itf = il2cpp_class_get_interfaces(klass, &iter)) {
        extends.emplace_back(il2cpp_class_get_name(itf));
    }

    if (!extends.empty()) {
        output << " : " << extends[0];
        for (int32_t i = 1; i < extends.size(); ++i) {
            output << ", " << extends[i];
        }
    }

    output << "\n{";
    output << dump_field(klass);
    output << dump_property(klass);
    output << dump_method(klass);
    // TODO EventInfo
    output << "}\n";

    return output.str();
}

void il2cpp_dump() {
    size_t size;
    Il2CppDomain *domain = il2cpp_domain_get();
    const Il2CppAssembly **assemblies = il2cpp_domain_get_assemblies(domain, &size);
    printf("Dumping %li images...\n", size);

    std::stringstream image_output;
    for (int32_t i = 0; i < size; ++i) {
        const Il2CppImage *image = il2cpp_assembly_get_image(assemblies[i]);
        image_output << "// Image " << i << ": " << il2cpp_image_get_name(image) << "\n";
    }

    std::vector<std::string> output_array;
    if (il2cpp_image_get_class) {
        printf("Version greater than 2018.3\n");
        // using il2cpp_image_get_class
        for (int32_t i = 0; i < size; ++i) {
            printf("Dumping %i/%li ...\n", i + 1, size);

            const Il2CppImage *image = il2cpp_assembly_get_image(assemblies[i]);
            std::stringstream image_str;
            image_str << "\n// Dll : " << il2cpp_image_get_name(image);
            size_t class_count = il2cpp_image_get_class_count(image);
            for (int32_t j = 0; j < class_count; ++j) {
                const Il2CppClass *klass = il2cpp_image_get_class(image, j);
                const Il2CppType *type = il2cpp_class_get_type((Il2CppClass *)klass);
                //printf("type name : %s\n", il2cpp_type_get_name(type));
                std::string output = image_str.str() + dump_type(type);
                output_array.push_back(output);
            }
        }
    }
    else {
        printf("Version less than 2018.3\n");
        // using reflection
        const Il2CppImage *corlib = il2cpp_get_corlib();
        Il2CppClass *assembly_class = il2cpp_class_from_name(corlib, "System.Reflection", "Assembly");
        const MethodInfo *assembly_load = il2cpp_class_get_method_from_name(assembly_class, "Load", 1);
        const MethodInfo *assembly_get_types = il2cpp_class_get_method_from_name(assembly_class, "GetTypes", 0);
        if (assembly_load && assembly_load->methodPointer) {
            printf("Assembly::Load: %p\n", assembly_load->methodPointer);
        }
        else {
            printf("miss Assembly::Load\n");
            return;
        }
        if (assembly_get_types && assembly_get_types->methodPointer) {
            printf("Assembly::GetTypes: %p\n", assembly_get_types->methodPointer);
        }
        else {
            printf("miss Assembly::GetTypes\n");
            return;
        }
        for (int32_t i = 0; i < size; ++i) {
            printf("Dumping %i/%li ...\n", i + 1, size);

            const Il2CppImage *image = il2cpp_assembly_get_image(assemblies[i]);
            std::stringstream image_str;
            const char *image_name = il2cpp_image_get_name(image);
            image_str << "\n// Dll : " << image_name;
            //printf("image name : %s\n", image->name);
            std::string std_image_name = std::string(image_name);
            size_t pos = std_image_name.rfind('.');
            std::string image_name_no_ext = std_image_name.substr(0, pos);
            Il2CppString *assembly_file_name = il2cpp_string_new(image_name_no_ext.data());
            void *reflection_assembly = ((Assembly_Load_t)assembly_load->methodPointer)(nullptr, assembly_file_name, nullptr);
            Il2CppArray *reflection_types = ((Assembly_GetTypes_t)assembly_get_types->methodPointer)(reflection_assembly, nullptr);
            void **items = reflection_types->vector;
            for (int32_t j = 0; j < reflection_types->max_length; ++j) {
                Il2CppClass *klass = il2cpp_class_from_system_type((Il2CppReflectionType *)items[j]);
                const Il2CppType *type = il2cpp_class_get_type(klass);
                //printf("type name : %s\n", il2cpp_type_get_name(type));
                std::string output = image_str.str() + dump_type(type);
                output_array.push_back(output);
            }
        }
    }

    printf("Writing dump file...\n");
    std::ofstream out_stream("/data/il2cpp/dump.cs");
    out_stream << image_output.str();

    size_t count = output_array.size();
    for (int32_t i = 0; i < count; ++i) {
        out_stream << output_array[i];
    }

    out_stream.close();
    printf("Dump done!\n");
}



void il2cpp_dumper::run() {
    ScePthread dump_thread;
    scePthreadCreate(&dump_thread, nullptr, [](void *) -> void * {
        if (dumper_lock.try_lock()) {
            printf("Starting dumper...\n");
            il2cpp_dump();

            dumper_lock.unlock();
        }

        return nullptr;
    }, nullptr, "dump_thread");
}
