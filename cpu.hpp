#ifndef CPU_H
#define CPU_H

#include <array>
#include <cstdint>
#include <string>

#include "cartridge.hpp"

class CPU {
public:
    CPU(std::string);
private:
    // Game Pak link
    Cartridge cart;

    // Registers
    uint8_t a;     // Accumulator
    uint8_t x;     // Index X
    uint8_t y;     // Index Y
    uint8_t p;     // Processor status
    uint16_t pc;   // Program counter
    uint8_t sp;    //Stack pointer
    std::array<uint8_t, 0x800> ram;
};

#endif
