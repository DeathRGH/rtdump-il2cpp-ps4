#include "stdafx.h"

int get_il2cpp_version() {
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

    int value = -1;
    file.read(reinterpret_cast<char *>(&value), sizeof(value));
    if (!file) {
        printf("Error reading from file \"global-metadata.dat\"!\n");
        return -1;
    }

    file.close();

    return value;
}

void il2cpp_structs_generate() {
    int il2cpp_version = get_il2cpp_version();
    if (il2cpp_version == -1) {
        printf("Failed to detect metadata version!\n");
    }
    printf("Detected metadata version %i\n", il2cpp_version);

    std::vector<std::string> output_array;

    size_t size;
    Il2CppDomain *domain = il2cpp_domain_get();
    const Il2CppAssembly **assemblies = il2cpp_domain_get_assemblies(domain, &size);
    printf("Generating header for %li images...\n", size);





    
    //if (il2cpp_image_get_class) {
    //    printf("Version greater than 2018.3\n");
    //    // using il2cpp_image_get_class
    //    for (int i = 0; i < size; ++i) {
    //        printf("Generating %i/%li ...\n", i + 1, size);
    //
    //        const Il2CppImage *image = il2cpp_assembly_get_image(assemblies[i]);
    //        std::stringstream image_str;
    //        image_str << "\n// Dll : " << il2cpp_image_get_name(image);
    //        size_t class_count = il2cpp_image_get_class_count(image);
    //        for (int j = 0; j < class_count; ++j) {
    //            const Il2CppClass *klass = il2cpp_image_get_class(image, j);
    //            const Il2CppType *type = il2cpp_class_get_type(const_cast<Il2CppClass *>(klass));
    //            //printf("type name : %s\n", il2cpp_type_get_name(type));
    //            std::string outPut = image_str.str() + dump_type(type);
    //            output_array.push_back(outPut);
    //        }
    //    }
    //}
    //else {
    //    // for testing we stick to newer versions
    //}





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
    for (int i = 0; i < count; ++i) {
        out_stream << output_array[i];
    }

    out_stream.close();
    printf("Header generation done!\n");
}



void il2cpp_struct_gen::run() {
    ScePthread struct_gen_thread;
    scePthreadCreate(&struct_gen_thread, nullptr, [](void *) -> void * {
        il2cpp_structs_generate();

        return nullptr;
    }, nullptr, "struct_gen_thread");
}
