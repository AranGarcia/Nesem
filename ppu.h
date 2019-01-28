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

    uint8_t mapMemory(uint16_t);

    uint8_t getPpuctrl() const;

    uint8_t getPpumask() const;

    uint8_t getPpustatus() const;

    uint8_t getOamaddr() const;

    uint8_t getOamdata() const;

    uint8_t getPpuscrol() const;

    uint8_t getPpuaddr() const;

    uint8_t getPpudata() const;

    uint8_t getOamdma() const;

    void setPpuctrl(uint8_t ppuctrl);

    void setPpumask(uint8_t ppumask);

    void setPpustatus(uint8_t ppustatus);

    void setOamaddr(uint8_t oamaddr);

    void setOamdata(uint8_t oamdata);

    void setPpuscrol(uint8_t ppuscrol);

    void setPpuaddr(uint8_t ppuaddr);

    void setPpudata(uint8_t ppudata);

    void setOamdma(uint8_t oamdma);

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
