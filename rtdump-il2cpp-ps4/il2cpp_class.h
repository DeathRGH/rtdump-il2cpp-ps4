#pragma once

typedef uint16_t Il2CppChar;
typedef uintptr_t il2cpp_array_size_t;
typedef int32_t TypeDefinitionIndex;
typedef int32_t GenericParameterIndex;
typedef char Il2CppNativeChar;

struct Il2CppMemoryCallbacks;
struct Il2CppImage;
struct Il2CppClass;
struct Il2CppArrayBounds;
struct Il2CppAssembly;
struct Il2CppArrayType;
struct Il2CppGenericClass;
struct Il2CppReflectionType;
struct MonitorData;
struct EventInfo;
struct FieldInfo;
struct PropertyInfo;
struct Il2CppDomain;
struct Il2CppException;
struct Il2CppObject;
struct Il2CppReflectionMethod;
struct Il2CppString;
struct Il2CppThread;
struct Il2CppStackFrameInfo;
struct Il2CppManagedMemorySnapshot;
struct Il2CppDebuggerTransport;
struct Il2CppMethodDebugInfo;
struct Il2CppCustomAttrInfo;
typedef Il2CppClass Il2CppVTable;
typedef const struct ___Il2CppMetadataTypeHandle *Il2CppMetadataTypeHandle;
typedef const struct ___Il2CppMetadataGenericParameterHandle *Il2CppMetadataGenericParameterHandle;

typedef void (*Il2CppMethodPointer)();
typedef void (*il2cpp_register_object_callback)(Il2CppObject **arr, int size, void *userdata);
typedef void *(*il2cpp_liveness_reallocate_callback)(void *ptr, size_t size, void *userdata);
typedef void (*Il2CppFrameWalkFunc)(const Il2CppStackFrameInfo *info, void *user_data);
typedef size_t(*Il2CppBacktraceFunc)(Il2CppMethodPointer *buffer, size_t maxSize);
typedef const Il2CppNativeChar *(*Il2CppSetFindPlugInCallback)(const Il2CppNativeChar *);
typedef void (*Il2CppLogCallback)(const char *);

enum Il2CppRuntimeUnhandledExceptionPolicy {
    IL2CPP_UNHANDLED_POLICY_LEGACY,
    IL2CPP_UNHANDLED_POLICY_CURRENT
};

enum Il2CppGCMode {
    IL2CPP_GC_MODE_DISABLED = 0,
    IL2CPP_GC_MODE_ENABLED = 1,
    IL2CPP_GC_MODE_MANUAL = 2
};

enum Il2CppStat {
    IL2CPP_STAT_NEW_OBJECT_COUNT,
    IL2CPP_STAT_INITIALIZED_CLASS_COUNT,
    IL2CPP_STAT_METHOD_COUNT,
    IL2CPP_STAT_CLASS_STATIC_DATA_SIZE,
    IL2CPP_STAT_GENERIC_INSTANCE_COUNT,
    IL2CPP_STAT_GENERIC_CLASS_COUNT,
    IL2CPP_STAT_INFLATED_METHOD_COUNT,
    IL2CPP_STAT_INFLATED_TYPE_COUNT
};

enum Il2CppTypeEnum {
    IL2CPP_TYPE_END = 0x00,
    IL2CPP_TYPE_VOID = 0x01,
    IL2CPP_TYPE_BOOLEAN = 0x02,
    IL2CPP_TYPE_CHAR = 0x03,
    IL2CPP_TYPE_I1 = 0x04,
    IL2CPP_TYPE_U1 = 0x05,
    IL2CPP_TYPE_I2 = 0x06,
    IL2CPP_TYPE_U2 = 0x07,
    IL2CPP_TYPE_I4 = 0x08,
    IL2CPP_TYPE_U4 = 0x09,
    IL2CPP_TYPE_I8 = 0x0A,
    IL2CPP_TYPE_U8 = 0x0B,
    IL2CPP_TYPE_R4 = 0x0C,
    IL2CPP_TYPE_R8 = 0x0D,
    IL2CPP_TYPE_STRING = 0x0E,
    IL2CPP_TYPE_PTR = 0x0F,
    IL2CPP_TYPE_BYREF = 0x10,
    IL2CPP_TYPE_VALUETYPE = 0x11,
    IL2CPP_TYPE_CLASS = 0x12,
    IL2CPP_TYPE_VAR = 0x13,
    IL2CPP_TYPE_ARRAY = 0x14,
    IL2CPP_TYPE_GENERICINST = 0x15,
    IL2CPP_TYPE_TYPEDBYREF = 0x16,
    IL2CPP_TYPE_I = 0x18,
    IL2CPP_TYPE_U = 0x19,
    IL2CPP_TYPE_FNPTR = 0x1B,
    IL2CPP_TYPE_OBJECT = 0x1C,
    IL2CPP_TYPE_SZARRAY = 0x1D,
    IL2CPP_TYPE_MVAR = 0x1E,
    IL2CPP_TYPE_CMOD_REQD = 0x1F,
    IL2CPP_TYPE_CMOD_OPT = 0x20,
    IL2CPP_TYPE_INTERNAL = 0x21,
    IL2CPP_TYPE_MODIFIER = 0x40,
    IL2CPP_TYPE_SENTINEL = 0x41,
    IL2CPP_TYPE_PINNED = 0x45,
    IL2CPP_TYPE_ENUM = 0x55,
    IL2CPP_TYPE_IL2CPP_TYPE_INDEX = 0xFF
};

struct MethodInfo;

struct VirtualInvokeData {
    Il2CppMethodPointer methodPtr;
    const MethodInfo *method;
};

struct Il2CppArrayType {
    const struct Il2CppType *etype;
    uint8_t rank;
    uint8_t numsizes;
    uint8_t numlobounds;
    int *sizes;
    int *lobounds;
};

struct Il2CppType {
    union {
        void *dummy;
        TypeDefinitionIndex klassIndex;
        const Il2CppType *type;
        Il2CppArrayType *array;
        GenericParameterIndex genericParameterIndex;
        Il2CppGenericClass *generic_class;
    } data;
    unsigned int attrs : 16;
    Il2CppTypeEnum type : 8;
    unsigned int num_mods : 6;
    unsigned int byref : 1;
    unsigned int pinned : 1;
};

struct Il2CppGenericInst {
    uint32_t type_argc;
    const Il2CppType **type_argv;
};

struct Il2CppGenericContext {
    const Il2CppGenericInst *class_inst;
    const Il2CppGenericInst *method_inst;
};

struct Il2CppGenericClass {
    Il2CppClass *type;
    Il2CppGenericInst *context;
    Il2CppClass *cached_class;
};

struct Il2CppObject {
    Il2CppClass *klass;
    void *monitor;
};

union Il2CppRGCTXData {
    void *rgctxDataDummy;
    const MethodInfo *method;
    const Il2CppType *type;
    Il2CppClass *klass;
};

struct Il2CppRuntimeInterfaceOffsetPair {
    Il2CppClass *interfaceType;
    int32_t offset;
};

struct Il2CppClass {
    void *image;
    void *gc_desc;
    const char *name;           // 0x10
    const char *namespaze;      // 0x18
    Il2CppType byval_arg;
    Il2CppType this_arg;
    Il2CppClass *element_class; // 0x40
    Il2CppClass *castClass;
    Il2CppClass *declaringType;
    Il2CppClass *parent;
    Il2CppGenericClass *generic_class;  // 0x60
    void *typeMetadataHandle;
    void *interopData;
    Il2CppClass *klass;         // 0x78
    void *fields;
    void *events;
    void *properties;
    void *methods;              // 0x98
    Il2CppClass **nestedTypes;
    Il2CppClass **implementedInterfaces;
    Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
    // new fields:
    void *static_fields;
    const Il2CppRGCTXData *rgctx_data;
    Il2CppClass **typeHierarchy;    // 0xC8

    uint32_t initializationExceptionGCHandle;

    uint32_t cctor_started;
    uint32_t cctor_finished;
    uint64_t cctor_thread;          // 0xE0

    char pad_0xE8[0x0C];

    // Remaining fields are always valid except where noted
    /*GenericContainerIndex*/int32_t genericContainerIndex;
    uint32_t instance_size;         // 0xF8
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;

    uint16_t method_count;          // 0x11C
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;          // 0x126
    uint16_t interfaces_count;
    uint16_t interface_offsets_count; // lazily calculated for arrays, i.e. when rank > 0

    uint8_t typeHierarchyDepth; // Initialized in SetupTypeHierachy
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment; // Alignment of this type
    uint8_t naturalAligment; // Alignment of this type without accounting for packing
    uint8_t packingSize;

    // this is critical for performance of Class::InitFromCodegen. Equals to initialized && !has_initialization_error at all times.
    // Use Class::UpdateInitializedAndNoError to update
    uint8_t initialized_and_no_error : 1;

    uint8_t valuetype : 1;
    uint8_t initialized : 1;
    uint8_t enumtype : 1;
    uint8_t is_generic : 1;
    uint8_t has_references : 1;
    uint8_t init_pending : 1;
    uint8_t size_inited : 1;
    uint8_t has_finalize : 1;
    uint8_t has_cctor : 1;
    uint8_t is_blittable : 1;
    uint8_t is_import_or_windows_runtime : 1;
    uint8_t is_vtable_initialized : 1;
    uint8_t has_initialization_error : 1;
    VirtualInvokeData vtable[0];
};

struct MethodInfo {
    Il2CppMethodPointer methodPointer;
    //InvokerMethod invoker_method;
    char pad_0x08[0x10];
    const char *name;
    Il2CppClass *klass;
    const Il2CppType *return_type;
    /*const ParameterInfo **/void *parameters;
};

struct Il2CppArray {
    Il2CppObject obj;
    Il2CppArrayBounds *bounds;
    il2cpp_array_size_t max_length;
    void *vector[32];
};
