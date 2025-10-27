/*

LLLL           OOOOO      SSSS     Y       Y     SSSS
LLLL          OO   OO    SS   S     Y     Y     SS   S
LLLL          OO   OO     SS         Y   Y       SS
LLLL          OO   OO      SS         Y Y         SS
LLLL          OO   OO       SS         Y           SS
LLLLLLLLL     OO   OO    S   SS        Y        S   SS
LLLLLLLLL      OOOOO      SSSS         Y         SSSS

//C Standart Lybrary 17\\
||  ISO/IEC 9899:2018   ||
\\      STDDEF.H       //

*/

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