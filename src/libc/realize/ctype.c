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
\\       CTYPE.C       //

*/

#include <ctype.h>

static const unsigned char ascii_char[256] = {
    [0] = _CNTRL, // NULL
    [1] = _CNTRL, // SOH
    [2] = _CNTRL, // STX
    [3] = _CNTRL, // ETX
    [4] = _CNTRL, // EOT
    [5] = _CNTRL, // ENQ
    [6] = _CNTRL, // ACK
    [7] = _CNTRL, // BEL
    [8] = _CNTRL, // BS
    [9] = _SPACE | _CNTRL, // TAB (табуляция)
    [10] = _SPACE | _CNTRL, // LF (новая строка)
    [11] = _SPACE | _CNTRL, // VT (вертикальная табуляция)
    [12] = _SPACE | _CNTRL, // FF (новая страница)
    [13] = _SPACE | _CNTRL, // CR (возврат каретки)
    [14] = _CNTRL, // SO
    [15] = _CNTRL, // SI
    [16] = _CNTRL, // DLE
    [17] = _CNTRL, // DC1
    [18] = _CNTRL, // DC2
    [19] = _CNTRL, // DC3
    [20] = _CNTRL, // DC4
    [21] = _CNTRL, // NAK
    [22] = _CNTRL, // SYN
    [23] = _CNTRL, // ETB
    [24] = _CNTRL, // CAN
    [25] = _CNTRL, // EM
    [26] = _CNTRL, // SUB
    [27] = _CNTRL, // ESC
    [28] = _CNTRL, // FS
    [29] = _CNTRL, // GS
    [30] = _CNTRL, // RS
    [31] = _CNTRL, // US
    [32] = _SPACE, // пробел
    [33] = _PUNCT, // !
    [34] = _PUNCT, // "
    [35] = _PUNCT, // #
    [36] = _PUNCT, // $
    [37] = _PUNCT, // %
    [38] = _PUNCT, // &
    [39] = _PUNCT, // '
    [40] = _PUNCT, // (
    [41] = _PUNCT, // )
    [42] = _PUNCT, // *
    [43] = _PUNCT, // +
    [44] = _PUNCT, // ,
    [45] = _PUNCT, // -
    [46] = _PUNCT, // .
    [47] = _PUNCT, // /
    [48] = _DIGIT | _HEX, // 0
    [49] = _DIGIT | _HEX, // 1
    [50] = _DIGIT | _HEX, // 2
    [51] = _DIGIT | _HEX, // 3
    [52] = _DIGIT | _HEX, // 4
    [53] = _DIGIT | _HEX, // 5
    [54] = _DIGIT | _HEX, // 6
    [55] = _DIGIT | _HEX, // 7
    [56] = _DIGIT | _HEX, // 8
    [57] = _DIGIT | _HEX, // 9
    [58] = _PUNCT, // :
    [59] = _PUNCT, // ;
    [60] = _PUNCT, // <
    [61] = _PUNCT, // =
    [62] = _PUNCT, // >
    [63] = _PUNCT, // ?
    [64] = _PUNCT, // @
    [65] = _UPPER | _HEX, // A
    [66] = _UPPER | _HEX, // B
    [67] = _UPPER | _HEX, // C
    [68] = _UPPER | _HEX, // D
    [69] = _UPPER | _HEX, // E
    [70] = _UPPER | _HEX, // F
    [71] = _UPPER, // G
    [72] = _UPPER, // H
    [73] = _UPPER, // I
    [74] = _UPPER, // J
    [75] = _UPPER, // K
    [76] = _UPPER, // L
    [77] = _UPPER, // M
    [78] = _UPPER, // N
    [79] = _UPPER, // O
    [80] = _UPPER, // P
    [81] = _UPPER, // Q
    [82] = _UPPER, // R
    [83] = _UPPER, // S
    [84] = _UPPER, // T
    [85] = _UPPER, // U
    [86] = _UPPER, // V
    [87] = _UPPER, // W
    [88] = _UPPER, // X
    [89] = _UPPER, // Y
    [90] = _UPPER, // Z
    [91] = _PUNCT, // [
    [92] = _PUNCT, // backslash
    [93] = _PUNCT, // ]
    [94] = _PUNCT, // ^
    [95] = _PUNCT, // _
    [96] = _PUNCT, // `
    [97] = _LOWER | _HEX, // a
    [98] = _LOWER | _HEX, // b
    [99] = _LOWER | _HEX, // c
    [100] = _LOWER | _HEX, // d
    [101] = _LOWER | _HEX, // e
    [102] = _LOWER | _HEX, // f
    [103] = _LOWER, // g
    [104] = _LOWER, // h
    [105] = _LOWER, // i
    [106] = _LOWER, // j
    [107] = _LOWER, // k
    [108] = _LOWER, // l
    [109] = _LOWER, // m
    [110] = _LOWER, // n
    [111] = _LOWER, // o
    [112] = _LOWER, // p
    [113] = _LOWER, // q
    [114] = _LOWER, // r
    [115] = _LOWER, // s
    [116] = _LOWER, // t
    [117] = _LOWER, // u
    [118] = _LOWER, // v
    [119] = _LOWER, // w
    [120] = _LOWER, // x
    [121] = _LOWER, // y
    [122] = _LOWER, // z
    [123] = _PUNCT, // {
    [124] = _PUNCT, // |
    [125] = _PUNCT, // }
    [126] = _PUNCT, // ~
    [127] = _CNTRL, // DEL
};

// функции проверки

int isalpha(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & (_UPPER | _LOWER)) != 0;
}

int isdigit(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & _DIGIT) != 0;
}

int isalnum(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & (_UPPER | _LOWER | _DIGIT)) != 0;
}

int isspace(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & _SPACE) != 0;
}

int isupper(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & _UPPER) != 0;
}

int islower(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & _LOWER) != 0;
}

int isxdigit(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & _HEX) != 0;
}

int ispunct(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & _PUNCT) != 0;
}

int iscntrl(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & _CNTRL) != 0;
}

int isgraph(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & (_UPPER | _LOWER | _DIGIT | _PUNCT)) != 0;
}

int isprint(int c) {
    if (c == EOF) return 0;
    return (ascii_char[(unsigned char)c] & (_UPPER | _LOWER | _DIGIT | _PUNCT | _SPACE)) != 0;
}

// функции преобразования

int tolower(int c) {
    if (c == EOF) return EOF;
    if (isupper(c)) {
        return c + ('a' - 'A');
    }
    return c;
}

int toupper(int c) {
    if (c == EOF) return EOF;
    if (islower(c)) {
        return c - ('a' - 'A');
    }
    return c;
}