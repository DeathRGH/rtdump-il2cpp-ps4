#include "stdafx.h"

void *module_start_thread_func(void *) {
    printf("\n\n         __       ___                    \n");
    printf("________/  |_  __| _/_ __  _____ ______  \n");
    printf("\\_  __ \\   __\\/ __ |  |  \\/     \\\\____ \\ \n");
    printf(" |  | \\/|  | / /_/ |  |  /  Y Y  \\  |_> >\n");
    printf(" |__|   |__| \\____ |____/|__|_|  /   __/ \n");
    printf("                  \\/           \\/|__|    \n");
    printf("rtdump-il2cpp\n");
    printf("A runtime il2cpp dumper for Unity games!\n\n");

    // create dumping directory
    sceKernelMkdir("/data/il2cpp", SCE_KERNEL_S_IRWU);

    printf("[il2cpp] Initializing...\n");
    if (il2cpp_api::init()) {
        il2cpp_dumper::run();
        il2cpp_struct_gen::run();
    }
    else {
        printf("[il2cpp] Failed to initialize!\nNot dumping anything :(\n");
    }

    return nullptr;
}

void *module_stop_thread_func(void *) {
    printf("Unloading rtdump-il2cpp...\n");

    return nullptr;
}

extern "C" {
    int32_t module_start(size_t argc, const void *args) {
        ScePthread module_start_thread;
        scePthreadCreate(&module_start_thread, nullptr, module_start_thread_func, nullptr, nullptr);
        scePthreadJoin(module_start_thread, nullptr);
        return 0;
    }

    int32_t module_stop(size_t argc, const void *args) {
        ScePthread module_stop_thread;
        scePthreadCreate(&module_stop_thread, nullptr, module_stop_thread_func, nullptr, nullptr);
        scePthreadJoin(module_stop_thread, nullptr);
        return 0;
    }
}
