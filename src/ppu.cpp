//

#include <iostream>
#include "ppu.hpp"

using namespace std;

PPU::PPU() {}

uint8_t PPU::read_ppustatus() const {
    return ppustatus;
}

uint8_t PPU::read_ppudata() const {
    return ppudata;
}
void PPU::access_registers(uint16_t addr, uint8_t data) {
    switch (addr) {
        case 0x2000: ppuctrl = data; break;
        case 0x2001: ppumask = data; break;
        case 0x2003: oamaddr = data; break;
        case 0x2004: oamdata = data; break;
        case 0x2005: ppuscrol = data; break;
        case 0x2006: ppuaddr = data; break;
        case 0x2007: ppudata = data; break;
        case 0x4014: oamdma = data; break;
        default: ;
    }
}
