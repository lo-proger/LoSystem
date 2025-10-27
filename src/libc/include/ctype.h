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
\\       CTYPE.H       //

*/

#ifndef LOSYS_LIBC_CTYPE_H
#define LOSYS_LIBC_CTYPE_H

#define _UPPER   0x01 // большие буквы
#define _LOWER   0x02 // маленькие буквы
#define _DIGIT   0x04 //десятичные цифры
#define _SPACE   0x08 // пробелы
#define _HEX     0x10 // шестнадцатеричные цифры
#define _PUNCT   0x20 // знаки пунктуации
#define _CNTRL   0x40 // управляющие символы

#ifndef EOF
#define EOF (-1)
#endif

// функции проверки

int isalpha(int c);

int isdigit(int c);

int isalnum(int c);

int isspace(int c);

int isupper(int c);

int islower(int c);

int isxdigit(int c);

int ispunct(int c);

int iscntrl(int c);

int isgraph(int c);

int isprint(int c);

// функции преобразования

int tolower(int c);

int toupper(int c);

#endif