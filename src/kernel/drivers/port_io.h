/*

LLLL           OOOOO      SSSS     Y       Y     SSSS
LLLL          OO   OO    SS   S     Y     Y     SS   S
LLLL          OO   OO     SS         Y   Y       SS
LLLL          OO   OO      SS         Y Y         SS
LLLL          OO   OO       SS         Y           SS
LLLLLLLLL     OO   OO    S   SS        Y        S   SS
LLLLLLLLL      OOOOO      SSSS         Y         SSSS

//   Драйверы    \\
||  Драйверы для  ||
||разных устройств||
\\     PORTS_IO.H     //

*/

#ifndef LOSYS_DRIVERS_PORTS_IO_H
#define LOSYS_DRIVERS_PORTS_IO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void outbyte(uint16_t port, uint8_t val);

uint8_t inbyte(uint16_t port);

void outword(uint16_t port, uint16_t val);

uint16_t inword(uint16_t port);

void outdword(uint16_t port, uint32_t val);

uint32_t indword(uint16_t port);

#ifdef __cplusplus
}
#endif

#endif