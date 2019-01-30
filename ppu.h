#ifndef NESEM_PPU_H
#define NESEM_PPU_H

#include <cstdint>
#include <array>

/**
 * Pixel Processing Unit
 * 2C02
 */
class PPU {
public:
    PPU();

    void access_registers(uint16_t addr, uint8_t);

    uint8_t read_ppustatus() const;

    uint8_t read_ppudata() const;

private:
    // Registers:       Addresses in CPU Memory Map:
    uint8_t ppuctrl;    // $2000
    uint8_t ppumask;    // $2001
    uint8_t ppustatus;  // $2002
    uint8_t oamaddr;    // $2003
    uint8_t oamdata;    // $2004
    uint8_t ppuscrol;   // $2005
    uint8_t ppuaddr;    // $2006
    uint8_t ppudata;    // $2007
    uint8_t oamdma;     // $4014
};


#endif //NESEM_PPU_H
