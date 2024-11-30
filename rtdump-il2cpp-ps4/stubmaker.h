#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct SceKernelModuleSegmentInfo {
		void *address;
		uint32_t size;
		int32_t prot;
	} SceKernelModuleSegmentInfo;

	typedef struct SceKernelModuleInfo {
		size_t size;
		char name[256];
		SceKernelModuleSegmentInfo segmentInfo[4];
		uint32_t segmentCount;
		uint8_t fingerprint[20];
	} SceKernelModuleInfo;

	int sceKernelGetModuleList(int *arr, size_t size, size_t *available);
	int sceKernelGetModuleInfo(int handle, SceKernelModuleInfo *info);

#ifdef __cplusplus
}
#endif
