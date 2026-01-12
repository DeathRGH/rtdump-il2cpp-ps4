#include "stdafx.h"

#include "stubmaker.h"

uint64_t resolve_module_base(const char *name) {
    SceDbgModule modules[30];
    size_t moduleCount;
    sceKernelGetModuleList(modules, 30, &moduleCount);
    for (int32_t i = 0; i < moduleCount; i++) {
        SceDbgModule &module = modules[i];
        if (module != 0) {
            SceKernelModuleInfo info;
            info.size = sizeof(SceKernelModuleInfo);
            sceKernelGetModuleInfo(module, &info);

            if (strstr(info.name, name)) {
                return (uint64_t)info.segmentInfo[0].address;
            }
        }
    }

    return 0;
}

int32_t get_size(const char *name) {
    int32_t size = 0;
    SceDbgModule modules[30];
    size_t moduleCount;
    sceKernelGetModuleList(modules, 30, &moduleCount);
    for (int32_t i = 0; i < moduleCount; i++) {
        SceDbgModule &module = modules[i];
        if (module != 0) {
            SceKernelModuleInfo info;
            info.size = sizeof(SceDbgModuleInfo);
            sceKernelGetModuleInfo(module, &info);

            if (strstr(info.name, name)) {
                for (int32_t i = 0; i < info.segmentCount; i++) {
                    if (info.segmentInfo[i].prot == 5) {
                        size += info.segmentInfo[i].size;
                    }
                }
            }
        }
    }

    return size;
}

uintptr_t find_pattern(const char *module_name, const char *pattern) {
    const auto get_module_size = [=](const char *module_name) {
        return get_size(module_name);
    };

    const uintptr_t module_start = (uintptr_t)resolve_module_base(module_name);
    if (module_start != 0) {
        const uintptr_t module_end = module_start + get_module_size(module_name);

        const char *pattern_current = pattern;
        uintptr_t current_match = 0;

        SceKernelVirtualQueryInfo page_information{};
        for (unsigned char *current_page = reinterpret_cast<unsigned char *>(module_start); current_page < reinterpret_cast<unsigned char *>(module_end); current_page = reinterpret_cast<unsigned char *>((uint64_t)page_information.start + ((uint64_t)page_information.end - (uint64_t)page_information.start))) {
            sceKernelVirtualQuery(reinterpret_cast<void *>(current_page), SCE_KERNEL_VQ_FIND_NEXT, reinterpret_cast<SceKernelVirtualQueryInfo *>(&page_information), sizeof(SceKernelVirtualQueryInfo));
            if (page_information.protection == 0) {
                continue;
            }

            for (unsigned char *current_address = reinterpret_cast<unsigned char *>(page_information.start); current_address < reinterpret_cast<unsigned char *>((uint64_t)page_information.start + ((uint64_t)page_information.end - (uint64_t)page_information.start) - 0x08); current_address++) {
                if (*current_address != GET_BYTE(pattern_current) && *pattern_current != '\?') {
                    current_match = 0;
                    pattern_current = pattern;
                    continue;
                }

                if (!current_match) {
                    current_match = reinterpret_cast<uintptr_t>(current_address);
                }

                pattern_current += 3;
                if (pattern_current[-1] == 0) {
                    return current_match;
                }
            }
        }
    }

    return 0;
}
