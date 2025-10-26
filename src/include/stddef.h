#ifndef LOSYS_STDDEF_H
#define LOSYS_STDDEF_H

typedef unsigned int size_t;
typedef int ptrdiff_t;

#ifndef __cplusplus
typedef int wchar_t;
#endif

#define NULL ((void*)0)
#define offsetof(type, member) ((size_t)&((type*)0)->member)

#endif