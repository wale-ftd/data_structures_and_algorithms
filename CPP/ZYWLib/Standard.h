#ifndef _STANDARD_H_
#define _STANDARD_H_

#ifdef __cplusplus
typedef bool ZYW_BOOL;

#define NAMESPACE_DEF_START(ns) namespace ns {
#define NAMESPACE_DEF_END }
#define USING_NAMESPACE(ns) using namespace ns

#else
typedef enum {
    FALSE = 0,
    TRUE
} ZYW_BOOL;
#endif

typedef char ZYW_INT8;
typedef unsigned char ZYW_UINT8;
typedef short ZYW_INT16;
typedef unsigned short ZYW_UINT16;
typedef int ZYW_INT32;
typedef unsigned int ZYW_UINT32;
typedef long long ZYW_INT64;
typedef unsigned long long ZYW_UINT64;




#endif

