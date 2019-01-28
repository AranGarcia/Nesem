//

#include <iostream>
#include "ppu.h"

using namespace std;

PPU::PPU() {}

uint8_t PPU::mapMemory(uint16_t addr) {
    cout << "\tPPU Memory access";
    if (addr < 0x2000) {
        cout << "\tPattern tables" << endl;
    } else if (addr < 0x3f00) {
        cout << "\tName tables" << endl;
    } else if (addr < 0x4000) {
        cout << "\tPalettes" << endl;
    } else {
        cout << "\tMirrors" << endl;
    }

    return 0;
}

uint8_t PPU::getPpuctrl() const {
    return ppuctrl;
}

void PPU::setPpuctrl(uint8_t ppuctrl) {
    PPU::ppuctrl = ppuctrl;
}

uint8_t PPU::getPpumask() const {
    return ppumask;
}

void PPU::setPpumask(uint8_t ppumask) {
    PPU::ppumask = ppumask;
}

uint8_t PPU::getPpustatus() const {
    return ppustatus;
}

void PPU::setPpustatus(uint8_t ppustatus) {
    PPU::ppustatus = ppustatus;
}

uint8_t PPU::getOamaddr() const {
    return oamaddr;
}

void PPU::setOamaddr(uint8_t oamaddr) {
    PPU::oamaddr = oamaddr;
}

uint8_t PPU::getOamdata() const {
    return oamdata;
}

void PPU::setOamdata(uint8_t oamdata) {
    PPU::oamdata = oamdata;
}

uint8_t PPU::getPpuscrol() const {
    return ppuscrol;
}

void PPU::setPpuscrol(uint8_t ppuscrol) {
    PPU::ppuscrol = ppuscrol;
}

uint8_t PPU::getPpuaddr() const {
    return ppuaddr;
}

void PPU::setPpuaddr(uint8_t ppuaddr) {
    PPU::ppuaddr = ppuaddr;
}

uint8_t PPU::getPpudata() const {
    return ppudata;
}

void PPU::setPpudata(uint8_t ppudata) {
    PPU::ppudata = ppudata;
}

uint8_t PPU::getOamdma() const {
    return oamdma;
}

void PPU::setOamdma(uint8_t oamdma) {
    PPU::oamdma = oamdma;
}
