#ifndef CPU_H
#define CPU_H

#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "cartridge.hpp"

class CPU {
public:
    typedef void (CPU::*F)();
    CPU(std::string);

    void exec();
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

    // Instructions
    void BRK_IMPL();    //0x00
    void ORA_X_IND();   //0x01
    void ORA_ZPG();     //0x05
    void ASL_ZPG();     //0x06
    void PHP_IMPL();    //0x08
    void ORA_NUM();     //0x09
    void ASL_A();       //0x0A
    void ORA_ABS();     //0x0D
    void ASL_ABS();     //0x0E
    void SEI_IMPL();    //0x78
    void CLD_IMPL();    //0xD8

    std::array<F, 18> instructions;
};

#endif
