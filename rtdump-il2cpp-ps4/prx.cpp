#include "stdafx.h"

extern "C" {
    int __cdecl module_start(size_t argc, const void *args) {
        ScePthread entry_thread;
        scePthreadCreate(&entry_thread, nullptr, [](void *) -> void * {
            printf("         __       ___                    \n");
            printf("________/  |_  __| _/_ __  _____ ______  \n");
            printf("\\_  __ \\   __\\/ __ |  |  \\/     \\\\____ \\ \n");
            printf(" |  | \\/|  | / /_/ |  |  /  Y Y  \\  |_> >\n");
            printf(" |__|   |__| \\____ |____/|__|_|  /   __/ \n");
            printf("                  \\/           \\/|__|    \n");
            printf("rtdump-il2cpp-ps4\n");
            printf("A runtime il2cpp dumper for Unity games!\n\n");

            // make dumping directory
            sceKernelMkdir("/data/il2cpp", 0777);

            printf("[il2cpp] Initializing...\n");
            if (il2cpp_api::init()) {
                printf("Starting dumper...\n");
                il2cpp_dumper::run();

                //printf("Starting struct generator...\n");
                //il2cpp_struct_gen::run();
            }
            else {
                printf("[il2cpp] Failed to initialize!\nNot dumping anything :(\n");
            }

            scePthreadExit(nullptr);

            return nullptr;
        }, nullptr, "module_start");

        scePthreadJoin(entry_thread, nullptr);

        return SCE_OK;
    }

    int __cdecl module_stop(size_t argc, const void *args) {
        ScePthread exit_thread;
        scePthreadCreate(&exit_thread, nullptr, [](void *) -> void * {
            printf("Unloading...\n");

            scePthreadExit(nullptr);

            return nullptr;
        }, nullptr, "module_stop");

        scePthreadJoin(exit_thread, nullptr);

        return SCE_OK;
    }
}
