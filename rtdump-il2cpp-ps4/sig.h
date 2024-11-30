#pragma once

#define IN_RANGE(x,a,b)	(x >= a && x <= b)
#define GET_BITS(x)		(IN_RANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0x0A) : (IN_RANGE(x,'0','9') ? x - '0' : 0))
#define GET_BYTE(x)		(GET_BITS(x[0]) << 4 | GET_BITS(x[1]))

uint64_t resolve_module_base(const char *name);
uintptr_t find_pattern(const char *module_name, const char *pattern);
