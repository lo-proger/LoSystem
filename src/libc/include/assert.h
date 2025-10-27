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
\\      ASSERT.H       //

*/

#ifndef LOSYS_ASSERT_H
#define LOSYS_ASSERT_H

#ifdef NDEBUG
    /* Режим release - assert игнорируется */
    #define assert(ignore) ((void)0)
#else
    /* Режим debug - assert активен */
    #define assert(condition) \
        ((condition) ? (void)0 : \
         __assert_fail(#condition, __FILE__, __LINE__)) // требуется реализация stdlib - abort и stdio - printf
#endif

#endif