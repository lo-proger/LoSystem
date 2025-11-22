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
\\     PCI.H     //

*/

#ifndef LOSYS_DRIVERS_PCI_H
#define LOSYS_DRIVERS_PCI_H

#include <stdint.h>

const uint16_t PCI_CONFIG_WRITE = 0xCF8;
const uint16_t PCI_CONFIG_READ = 0xCFC;

typedef struct {

} pci_device;

#ifdef __cplusplus
extern "C" {
#endif

uint32_t pci_generate_addr(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    return (1U << 31) | // Enable bit 
            //30-24 бит - Reserved bit(0)
           ((uint32_t)bus << 16) | // 8 бит
           ((uint32_t)slot << 11) | // 5 бит
           ((uint32_t)func << 8) | // 3 бита
           (offset & 0xFC); // 6 бит
           //1-0 бит - 0
}

pci_device* pci_scan() {
    for (size_t bus = 0; bus < 256; bus++) {
        for (size_t slot = 0; slot < 36; slot++) {
            for (size_t func = 0; func < 8; func++) {

            }
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif