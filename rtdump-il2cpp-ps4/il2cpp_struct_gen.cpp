#include "stdafx.h"

int32_t get_il2cpp_version() {
    const char *file_path = "/app0/Media/Metadata/global-metadata.dat";

    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        printf("Failed to open \"global-metadata.dat\"!\n");
        return -1;
    }

    file.seekg(0x04, std::ios::beg);
    if (!file) {
        printf("Error seeking in file \"global-metadata.dat\"!\n");
        return -1;
    }

    int32_t value = -1;
    file.read(reinterpret_cast<char *>(&value), sizeof(value));
    if (!file) {
        printf("Error reading from file \"global-metadata.dat\"!\n");
        return -1;
    }

    file.close();

    return value;
}

// might not need this
//bool is_custom_type(Il2CppType *type, Il2CppGenericContext *context) {
//    switch (type->type) {
//    case Il2CppTypeEnum::IL2CPP_TYPE_PTR: {
//        Il2CppType *original_type = (Il2CppType *)type->data.type;
//        return is_custom_type(original_type, context);
//    }
//    case Il2CppTypeEnum::IL2CPP_TYPE_STRING:
//    case Il2CppTypeEnum::IL2CPP_TYPE_CLASS:
//    case Il2CppTypeEnum::IL2CPP_TYPE_ARRAY:
//    case Il2CppTypeEnum::IL2CPP_TYPE_SZARRAY: {
//        return true;
//    }
//    case Il2CppTypeEnum::IL2CPP_TYPE_VALUETYPE: {
//        var typeDef = executor.GetTypeDefinitionFromIl2CppType(type);
//        if (typeDef.IsEnum) {
//            return is_custom_type(il2Cpp.types[typeDef.elementTypeIndex], context);
//        }
//        return true;
//    }
//    case Il2CppTypeEnum::IL2CPP_TYPE_GENERICINST: {
//        Il2CppGenericClass *generic_class = type->data.generic_class;
//        var typeDef = executor.GetGenericClassTypeDefinition(generic_class);
//        if (il2cpp_class_is_enum(generic_class->type)) {
//            return is_custom_type(il2Cpp.types[typeDef.elementTypeIndex], context);
//        }
//        return true;
//    }
//    case Il2CppTypeEnum::IL2CPP_TYPE_VAR: {
//        if (context) {
//            var genericParameter = executor.GetGenericParameteFromIl2CppType(type);
//            var genericInst = il2Cpp.MapVATR<Il2CppGenericInst>(context->class_inst);
//            var pointers = il2Cpp.MapVATR<ulong>(genericInst.type_argv, genericInst.type_argc);
//            var pointer = pointers[genericParameter.num];
//            var type = il2Cpp.GetIl2CppType(pointer);
//            return is_custom_type(type, 0);
//        }
//        return false;
//    }
//    case Il2CppTypeEnum::IL2CPP_TYPE_MVAR: {
//        if (context) {
//            var genericParameter = executor.GetGenericParameteFromIl2CppType(type);
//            var genericInst = il2Cpp.MapVATR<Il2CppGenericInst>(context->method_inst);
//            var pointers = il2Cpp.MapVATR<ulong>(genericInst.type_argv, genericInst.type_argc);
//            var pointer = pointers[genericParameter.num];
//            var type = il2Cpp.GetIl2CppType(pointer);
//            return is_custom_type(type, 0);
//        }
//        return false;
//    }
//    default:
//        return false;
//    }
//}

std::string resolve_full_type(Il2CppClass *klass) {
    std::string full_name = klass->namespaze;
    if (!full_name.empty()) {
        std::replace(full_name.begin(), full_name.end(), '.', '_');
        full_name += "_";
    }

    // add base name
    full_name += il2cpp_class_get_name(klass);

    // remove placeholders
    //size_t pos = generic_name.find("`");
    //if (pos != std::string::npos) {
    //    generic_name.erase(pos, 2);
    //}
    //generic_name += "<";
    //
    //Il2CppGenericInst *generic_inst = klass->generic_class->context;
    //for (size_t i = 0; i < generic_inst->type_argc; ++i) {
    //    if (i > 0) {
    //        generic_name += ", ";
    //    }
    //
    //    const Il2CppType *arg_type = generic_inst->type_argv[i];
    //    Il2CppClass *arg_class = il2cpp_class_from_type(arg_type);
    //
    //    generic_name += resolve_generic_type(arg_class);
    //}
    //
    //generic_name += ">";

    return full_name;
}

std::string il2cpp_class_get_name_cpp(Il2CppClass *klass) {
    std::string internal_name = il2cpp_class_get_name(klass);

    if (internal_name == "Object") {
        return "object";
    }
    if (internal_name == "Void") {
        return "void";
    }
    if (internal_name == "Boolean") {
        return "bool";
    }
    if (internal_name == "Byte") {
        return "uint8_t";
    }
    if (internal_name == "SByte") {
        return "int8_t";
    }
    if (internal_name == "Int16") {
        return "int16_t";
    }
    if (internal_name == "UInt16") {
        return "uint16_t";
    }
    if (internal_name == "Int32") {
        return "int32_t";
    }
    if (internal_name == "UInt32") {
        return "uint32_t";
    }
    if (internal_name == "Int64") {
        return "int64_t";
    }
    if (internal_name == "UInt64") {
        return "uint64_t";
    }
    if (internal_name == "Single") {
        return "float";
    }
    if (internal_name == "Double") {
        return "double";
    }
    if (internal_name == "Char") {
        return "char";
    }
    if (internal_name == "String") {
        return "struct System_String_o*";
    }

    if (internal_name == "Object[]") {
        return "object[]";
    }
    if (internal_name == "Boolean[]") {
        return "bool[]";
    }
    if (internal_name == "Byte[]") {
        return "byte[]";
    }
    if (internal_name == "SByte[]") {
        return "sbyte[]";
    }
    if (internal_name == "Int16[]") {
        return "short[]";
    }
    if (internal_name == "UInt16[]") {
        return "ushort[]";
    }
    if (internal_name == "Int32[]") {
        return "int[]";
    }
    if (internal_name == "UInt32[]") {
        return "uint[]";
    }
    if (internal_name == "Int64[]") {
        return "long[]";
    }
    if (internal_name == "UInt64[]") {
        return "ulong[]";
    }
    if (internal_name == "Single[]") {
        return "float[]";
    }
    if (internal_name == "Double[]") {
        return "double[]";
    }
    if (internal_name == "Char[]") {
        return "char[]";
    }
    if (internal_name == "String[]") {
        return "string[]";
    }

    //if (klass->this_arg.type == Il2CppTypeEnum::IL2CPP_TYPE_ENUM) {
    //    return "enum " + internal_name;
    //}
    //else if (klass->this_arg.type == Il2CppTypeEnum::IL2CPP_TYPE_PTR) {
    //    //Il2CppType *original_type = (Il2CppType *)klass->this_arg.data.type->type;
    //    //return is_custom_type(original_type, context);
    //    return "struct " + resolve_full_type(klass);
    //}

    // @todo: check for enum type
    //        the check above did not work
    //        also not when checking klass->declaringType
    return "struct " + resolve_full_type(klass);
}

std::string resolve_generic_type_cpp(Il2CppClass *klass) {
    if (!klass->generic_class) {
        return il2cpp_class_get_name_cpp(klass);
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

        generic_name += resolve_generic_type_cpp(arg_class);
    }

    generic_name += ">";
    return generic_name;
}

std::string resolve_type_cpp(const Il2CppType *type) {
    switch (type->type) {
    case IL2CPP_TYPE_SZARRAY: {
        std::string element_type = resolve_type_cpp(type->data.type);
        return element_type + "[]";
    }
    default:
        Il2CppClass *klass = il2cpp_class_from_type(type);
        return resolve_generic_type_cpp(klass);
    }
}

std::string generate_field(FieldInfo *field) {
    std::stringstream output;
    output << "\t";

    const Il2CppType *field_type = il2cpp_field_get_type(field);
    std::string field_type_name = resolve_type_cpp(field_type);

    output << field_type_name << " " << il2cpp_field_get_name(field);
    output << ";\n";

    return output.str();
}

std::string generate_fields(Il2CppClass *klass, std::string full_type_name) {
    std::stringstream output;

    Il2CppClass *parent_class = il2cpp_class_get_parent(klass);
    if (parent_class && (parent_class->field_count > 0)) {
        std::string full_parent_type = resolve_full_type(parent_class);
        output << "struct " << full_type_name << "_Fields : " << full_parent_type << "_Fields {\n";
    }
    else {
        output << "struct " << full_type_name << "_Fields {\n";
    }

    void *iter = nullptr;
    while (FieldInfo *field = il2cpp_class_get_fields(klass, &iter)) {
        int32_t flags = il2cpp_field_get_flags(field);
        if (flags & FIELD_ATTRIBUTE_LITERAL && il2cpp_class_is_enum(klass)) {
            continue; // skip enum values
        }
        if (flags & FIELD_ATTRIBUTE_STATIC) {
            continue; // skip static fields in fields gen
        }

        output << generate_field(field);
    }

    output << "};\n";

    return output.str();
}

std::string generate_vtable(Il2CppClass *klass, std::string full_type_name) {
    if (klass->vtable_count <= 0) {
        return "";
    }
    
    std::stringstream output;
    output << "struct " << full_type_name << "_VTable {\n";

    for (int32_t i = 0; i < klass->vtable_count; i++) {
        output << "\tVirtualInvokeData _" << i << "_";
        if (klass->vtable[i].method) {
            std::string method_name = il2cpp_method_get_name(klass->vtable[i].method);
            std::replace(method_name.begin(), method_name.end(), '.', '_');

            output << method_name;
        }
        output << ";\n";
    }

    //output << "\nklass: 0x" << klass << "\n";
    //output << "klass->vtable_count: " << klass->vtable_count << "\n";
    //output << "klass->vtable[0]: 0x" << &klass->vtable[0] << "\n";

    output << "};\n";

    return output.str();
}

std::string generate_struct_c(Il2CppClass *klass, std::string full_type_name) {
    std::stringstream output;
    output << "struct " << full_type_name << "_c {\n";

    output << "\tIl2CppClass_1 _1;\n";
    if (klass->static_fields_size > 0) {
        output << "\tstruct " << full_type_name << "_StaticFields* static_fields;\n";
    }
    else {
        output << "\tvoid *static_fields;\n";
    }
    
    // @todo: "_RGCTXs* rgctx_data;\n"
    output << "\tIl2CppRGCTXData* rgctx_data;\n";

    output << "\tIl2CppClass_2 _2;\n";
    if (klass->vtable_count > 0) {
        output << "\t" << full_type_name << "_VTable {\n";
    }

    output << "};\n";

    return output.str();
}

std::string generate_struct_o(Il2CppClass *klass, std::string full_type_name) {
    std::stringstream output;
    output << "struct " << full_type_name << "_o {\n";

    if (klass->declaringType && il2cpp_class_is_valuetype(klass->declaringType)) {
        output << "\t" << full_type_name << "_c *klass;\n";
        output << "\tvoid *monitor;\n";
    }
    output << "\t" << full_type_name << "_Fields fields;\n";

    output << "};\n";

    return output.str();
}

std::string generate_static_fields(Il2CppClass *klass, std::string full_type_name) {
    if (klass->static_fields_size <= 0) {
        return "";
    }

    std::stringstream output;
    output << "struct " << full_type_name << "_StaticFields {\n";

    void *iter = nullptr;
    while (FieldInfo *field = il2cpp_class_get_fields(klass, &iter)) {
        int32_t flags = il2cpp_field_get_flags(field);
        if (flags & FIELD_ATTRIBUTE_LITERAL && il2cpp_class_is_enum(klass)) {
            continue; // skip enum values
        }
        if (!(flags & FIELD_ATTRIBUTE_STATIC)) {
            continue; // skip non static fields in static fields gen
        }

        output << generate_field(field);
    }

    output << "};\n";

    return output.str();
}

std::string generate_type(const Il2CppType *type) {
    std::stringstream output;
    Il2CppClass *klass = il2cpp_class_from_type(type);

    //int32_t flags = il2cpp_class_get_flags(klass);
    //bool is_enum = il2cpp_class_is_enum(klass);
    bool is_valuetype = il2cpp_class_is_valuetype(klass);

    if (!is_valuetype) {
        return "";
    }

    //output << "struct ";
    //output << resolve_full_type(klass);
    std::string full_type = resolve_full_type(klass);



    //std::vector<std::string> extends;
    //Il2CppClass *parent = il2cpp_class_get_parent(klass);
    //if (!is_valuetype && !is_enum && parent) {
    //    const Il2CppType *parent_type = il2cpp_class_get_type(parent);
    //    if (parent_type->type != IL2CPP_TYPE_OBJECT) {
    //        extends.emplace_back(il2cpp_class_get_name(parent));
    //    }
    //}
    //
    //void *iter = nullptr;
    //while (Il2CppClass *itf = il2cpp_class_get_interfaces(klass, &iter)) {
    //    extends.emplace_back(il2cpp_class_get_name(itf));
    //}
    //
    //if (!extends.empty()) {
    //    output << " : " << extends[0];
    //    for (int32_t i = 1; i < extends.size(); ++i) {
    //        output << ", " << extends[i];
    //    }
    //}

    //output << " {";
    output << generate_fields(klass, full_type);
    // @todo: some vtables dont have names, figure out why
    //        does not matter as the size of the structure is correct anyways
    output << generate_vtable(klass, full_type);
    output << generate_struct_c(klass, full_type);
    output << generate_struct_o(klass, full_type);
    output << generate_static_fields(klass, full_type);
    //output << "};\n";

    return output.str();
}

void il2cpp_structs_generate() {
    int32_t il2cpp_version = get_il2cpp_version();
    if (il2cpp_version == -1) {
        printf("Failed to detect metadata version!\n");
    }
    printf("Detected metadata version %i\n", il2cpp_version);

    std::vector<std::string> output_array;

    size_t size;
    Il2CppDomain *domain = il2cpp_domain_get();
    const Il2CppAssembly **assemblies = il2cpp_domain_get_assemblies(domain, &size);
    printf("Generating header for %li images...\n", size);





    
    if (il2cpp_image_get_class) {
        printf("Version greater than 2018.3\n");
        // using il2cpp_image_get_class
        for (int32_t i = 0; i < size; ++i) {
            printf("Generating %i/%li ...\n", i + 1, size);
    
            const Il2CppImage *image = il2cpp_assembly_get_image(assemblies[i]);
            std::stringstream image_str;
            size_t class_count = il2cpp_image_get_class_count(image);
            for (int32_t j = 0; j < class_count; ++j) {
                const Il2CppClass *klass = il2cpp_image_get_class(image, j);
                const Il2CppType *type = il2cpp_class_get_type((Il2CppClass *)klass);
                std::string output = image_str.str() + generate_type(type);
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
            printf("Generating %i/%li ...\n", i + 1, size);

            const Il2CppImage *image = il2cpp_assembly_get_image(assemblies[i]);
            std::stringstream image_str;
            const char *image_name = il2cpp_image_get_name(image);
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
                std::string output = image_str.str() + generate_type(type);
                output_array.push_back(output);
            }
        }
    }





    printf("Writing header file...\n");
    std::ofstream out_stream("/data/il2cpp/il2cpp.h");

    // add constant generic header
    out_stream << generic_header;

    switch (il2cpp_version) {
    case 29:
        out_stream << header_v29;
        break;
    default:
        printf("ERROR Unsupported il2cpp_version = %i (0x%X)\nSkipping header generation!\n", il2cpp_version, il2cpp_version);
        out_stream.close();
        return;
    }

    size_t count = output_array.size();
    for (int32_t i = 0; i < count; ++i) {
        out_stream << output_array[i];
    }

    out_stream.close();
    printf("Header generation done!\n");
}



void il2cpp_struct_gen::run() {
    ScePthread struct_gen_thread;
    scePthreadCreate(&struct_gen_thread, nullptr, [](void *) -> void * {
        std::lock_guard<std::mutex> _(dumper_lock);
        printf("Starting struct generator...\n");
        il2cpp_structs_generate();

        return nullptr;
    }, nullptr, "struct_gen_thread");
}
