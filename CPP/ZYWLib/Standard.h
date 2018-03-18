#ifndef _STANDARD_H_
#define _STANDARD_H_

#ifdef __cplusplus
//typedef bool ZYW_BOOL;

//#define NAMESPACE_DEF_START(ns) namespace ns {
//#define NAMESPACE_DEF_END }
//#define USING_NAMESPACE(ns) using namespace ns

#else
typedef enum {
    FALSE = 0,
    TRUE
} bool;
#endif

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;




#endif

