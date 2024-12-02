#pragma once

extern std::mutex dumper_lock;

typedef void *(*Assembly_Load_t)(void *, Il2CppString *, void *);
typedef Il2CppArray *(*Assembly_GetTypes_t)(void *, void *);

class il2cpp_dumper {
public:
    static void run();
};
