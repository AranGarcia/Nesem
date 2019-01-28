#ifndef CPU_H
#define CPU_H

#include <array>
#include <bitset>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "cartridge.hpp"
#include "ppu.h"

/**
 * Implementation of a 6502 microprocessor
 */
class CPU {
public:
    typedef void (CPU::*F)();

    explicit CPU(std::string);

    void exec();

private:
    // Game Pak link
    Cartridge cart;
    PPU ppu;

    // Registers
    uint8_t a;   // Accumulator
    uint8_t x;   // Index X
    uint8_t y;   // Index Y
    std::bitset<8> p;   // Processor status
    uint16_t pc; // Program counter
    uint8_t sp;  //Stack pointer
    std::array<uint8_t, 0x100> zero_page;
    std::array<uint16_t, 0x100> stack;
    std::array<uint8_t, 0x600> ram;

    uint8_t map_memory(uint16_t addr, bool = false, uint8_t = 0);

    // Signed byte extender

    int16_t ext_s16(int8_t value);

    // Stack functions

    uint16_t stack_peek();

    uint16_t stack_pop();

    void stack_push(uint16_t );

    // Instructions}
    std::array<F, 256> instructions;

    /* ----------------------
     * Instruction  suffixes:
     * ----------------------
     * ABS:     |   Absolute
     * IMD:     |   Immediate
     * IMPL:    |   Implied
     * IND:     |   Indirect
     * REL:     |   Relative
     * ZPG:     |   Zero Page
     */
    void BRK_IMPL();  //0x00
    void ORA_X_IND(); //0x01
    void ORA_ZPG();   //0x05
    void ASL_ZPG();   //0x06
    void PHP_IMPL();  //0x08
    void ORA_IMD();   //0x09
    void ASL_A();     //0x0A
    void ORA_ABS();   //0x0D
    void ASL_ABS();   //0x0E

    void BPL_REL();   //0x10
    void ORA_IND_Y(); //0x11
    void ORA_ZPG_X(); //0x15
    void ASL_ZPG_X(); //0x16
    void CLC_IMPL(); //0x18
    void ORA_ABS_Y(); //0x19
    void ORA_ABS_X(); //0x1D
    void ASL_ABS_X(); //0x1E

    void JSR_ABS();   //0x20
    void AND_X_IND(); //0x21
    void BIT_ZPG();   //0x24
    void AND_ZPG();   //0x25
    void ROL_ZPG();   //0x26
    void PLP_IMPL(); //0x28
    void AND_IMD();   //0x29
    void ROL_A();     //0x2A
    void BIT_ABS();   //0x2C
    void AND_ABS();   //0x2D
    void ROL_ABS();   //0x2E

    void BMI_REL();   //0x30
    void AND_IND_Y(); //0x31
    void AND_ZPG_X(); //0x35
    void ROL_ZPG_X(); //0x36
    void SEC_IMPL(); //0x38
    void AND_ABS_Y(); //0x39
    void AND_ABS_X(); //0x3D
    void ROL_ABS_X(); //0x3E

    void RTI_IMPL(); //0x40
    void EOR_X_IND(); //0x41
    void EOR_ZPG();   //0x45
    void LSR_ZPG();   //0x46
    void PHA_IMPL(); //0x48
    void EOR_IMD();   //0x49
    void LSR_A();     //0x4A
    void JMP_ABS();   //0x4C
    void EOR_ABS();   //0x4D
    void LSR_ABS();   //0x4E

    void BVC_REL();   //0x50
    void EOR_IND_Y(); //0x51
    void EOR_ZPG_X(); //0x55
    void LSR_ZPG_X(); //0x56
    void CLI_IMPL(); //0x58
    void EOR_ABS_Y(); //0x59
    void EOR_ABS_X(); //0x5D
    void LSR_ABS_X(); //0x5E

    void RTS_IMPL(); //0x60
    void ADC_X_IND(); //0x61
    void ADC_ZPG();   //0x65
    void ROR_ZPG();   //0x66
    void PLA_IMPL(); //0x68
    void ADC_IMD();   //0x69
    void ROR_A();     //0x6A
    void JMP_IND();   //0x6C
    void ADC_ABS();   //0x6D
    void ROR_ABS();   //0x6E

    void BVS_REL();   //0x70
    void ADC_IND_Y(); //0x71
    void ADC_ZPG_X(); //0x75
    void ROR_ZPG_X(); //0x76
    void SEI_IMPL(); //0x78
    void ADC_ABS_Y(); //0x79
    void ADC_ABS_X(); //0x7D
    void ROR_ABS_X(); //0x7E

    void STA_X_IND(); //0x81
    void STY_ZPG();   //0x84
    void STA_ZPG();   //0x85
    void STX_ZPG();   //0x86
    void DEY_IMPL(); //0x88
    void TXA_IMPL(); //0x8A
    void STY_ABS();   //0x8C
    void STA_ABS();   //0x8D
    void STX_ABS();   //0x8E

    void BCC_REL();   //0x90
    void STA_IND_Y(); //0x91
    void STY_ZPG_X(); //0x94
    void STA_ZPG_X(); //0x95
    void STX_ZPG_Y(); //0x96
    void TYA_IMPL(); //0x98
    void STA_ABS_Y(); //0x99
    void TXS_IMPL(); //0x9A
    void STA_ABS_X(); //0x9D

    void LDY_IMD();    //0xA0
    void LDA_X_IND(); //0xA1
    void LDX_IMD();   //0xA2
    void LDY_ZPG();   //0xA4
    void LDA_ZPG();   //0xA5
    void LDX_ZPG();   //0xA6
    void TAY_IMPL();  //0xA8
    void LDA_IMD();   //0xA9
    void TAX_IMPL();  //0xAA
    void LDY_ABS();   //0xAC
    void LDA_ABS();   //0xAD
    void LDX_ABS();   //0xAE

    void BCS_REL();   //0xB0
    void LDA_IND_Y(); //0xB1
    void LDY_ZPG_X(); //0xB4
    void LDA_ZPG_X(); //0xB5
    void LDX_ZPG_Y(); //0xB6
    void CLV_IMPL();  //0xB8
    void LDA_ABS_Y(); //0xB9
    void TSX_IMPL();  //0xBA
    void LDY_ABS_X(); //0xBC
    void LDA_ABS_X(); //0xBD
    void LDX_ABS_Y(); //0xBE

    void CPY_IMD();   //0xC0
    void CMP_X_IND(); //0xC1
    void CPY_ZPG();   //0xC4
    void CMP_ZPG();   //0xC5
    void DEC_ZPG();   //0xC6
    void INY_IMPL();  //0xC8
    void CMP_IMD();   //0xC9
    void DEX_IMPL();  //0xCA
    void CPY_ABS();   //0xCC
    void CMP_ABS();   //0xCD
    void DEC_ABS();   //0xCE

    void BNE_REL();   //0xD0
    void CMP_IND_Y(); //0xD1
    void CMP_ZPG_X(); //0xD5
    void DEC_ZPG_X(); //0xD6
    void CLD_IMPL();  //0xD8
    void CMP_ABS_Y(); //0xD9
    void CMP_ABS_X(); //0xDD
    void DEC_ABS_X(); //0xDE

    void CPX_IMD();   //0xE0
    void SBC_X_IND(); //0xE1
    void CPX_ZPG();   //0xE4
    void SBC_ZPG();   //0xE5
    void INC_ZPG();   //0xE6
    void INX_IMPL();  //0xE8
    void SBC_IMD();   //0xE9
    void NOP_IMPL();  //0xEA
    void CPX_ABS();   //0xEC
    void SBC_ABS();   //0xED
    void INC_ABS();   //0xEE

    void BEQ_REL();   //0xF0
    void SBC_IND_Y(); //0xF1
    void SBC_ZPG_X(); //0xF5
    void INC_ZPG_X(); //0xF6
    void SED_IMPL();  //0xF8
    void SBC_ABS_Y(); //0xF9
    void SBC_ABS_X(); //0xFD
    void INC_ABS_X(); //0xFE

};

#endif
