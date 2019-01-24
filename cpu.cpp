#include <iostream>
#include <iomanip>

#include "cpu.hpp"

using namespace std;

CPU::CPU(string nesFile) : cart(nesFile), p(0), instructions{
        &CPU::BRK_IMPL, &CPU::ORA_X_IND, nullptr, nullptr, nullptr, &CPU::ORA_ZPG, &CPU::ASL_ZPG, nullptr,
        &CPU::PHP_IMPL, &CPU::ORA_IMD, &CPU::ASL_A, nullptr, nullptr, &CPU::ORA_ABS, &CPU::ASL_ABS, nullptr,

        &CPU::BPL_REL, &CPU::ORA_IND_Y, nullptr, nullptr, nullptr, &CPU::ORA_ZPG_X, &CPU::ASL_ZPG_X, nullptr,
        &CPU::CLC_IMPL, &CPU::ORA_ABS_Y, nullptr, nullptr, nullptr, &CPU::ORA_ABS_X, &CPU::ASL_ABS_X, nullptr,

        &CPU::JSR_ABS, &CPU::AND_X_IND, nullptr, nullptr, &CPU::BIT_ZPG, &CPU::AND_ZPG, &CPU::ROL_ZPG, nullptr,
        &CPU::PLP_IMPL, &CPU::AND_IMD, &CPU::ROL_A, nullptr, &CPU::BIT_ABS, &CPU::AND_ABS, &CPU::ROL_ABS, nullptr,

        &CPU::BMI_REL, &CPU::AND_IND_Y, nullptr, nullptr, nullptr, &CPU::AND_ZPG_X, &CPU::ROL_ZPG_X, nullptr,
        &CPU::SEC_IMPL, &CPU::AND_ABS_Y, nullptr, nullptr, nullptr, &CPU::AND_ABS_X, &CPU::ROL_ABS_X, nullptr,

        &CPU::RTI_IMPL, &CPU::EOR_X_IND, nullptr, nullptr, nullptr, &CPU::EOR_ZPG, &CPU::LSR_ZPG, nullptr,
        &CPU::PHA_IMPL, &CPU::EOR_IMD, &CPU::LSR_A, nullptr, &CPU::JMP_ABS, &CPU::EOR_ABS, &CPU::LSR_ABS, nullptr,

        &CPU::BVC_REL, &CPU::EOR_IND_Y, nullptr, nullptr, nullptr, &CPU::EOR_ZPG_X, &CPU::LSR_ZPG_X, nullptr,
        &CPU::CLI_IMPL, &CPU::EOR_ABS_Y, nullptr, nullptr, nullptr, &CPU::EOR_ABS_X, &CPU::LSR_ABS_X, nullptr,

        &CPU::RTS_IMPL, &CPU::ADC_X_IND, nullptr, nullptr, nullptr, &CPU::ADC_ZPG, &CPU::ROR_ZPG, nullptr,
        &CPU::PLA_IMPL, &CPU::ADC_IMD, &CPU::ROR_A, nullptr, &CPU::JMP_IND, &CPU::ADC_ABS, &CPU::ROR_ABS, nullptr,

        &CPU::BVS_REL, &CPU::ADC_IND_Y, nullptr, nullptr, nullptr, &CPU::ADC_ZPG_X, &CPU::ROR_ZPG_X, nullptr,
        &CPU::SEI_IMPL, &CPU::ADC_ABS_Y, nullptr, nullptr, nullptr, &CPU::ADC_ABS_X, &CPU::ROR_ABS_X, nullptr,

        nullptr, &CPU::STA_X_IND, nullptr, nullptr, &CPU::STY_ZPG, &CPU::STA_ZPG, &CPU::STX_ZPG, nullptr,
        &CPU::DEY_IMPL, nullptr, &CPU::TXA_IMPL, nullptr, &CPU::STY_ABS, &CPU::STA_ABS, &CPU::STX_ABS, nullptr,

        &CPU::BCC_REL, &CPU::STA_IND_Y, nullptr, nullptr, &CPU::STY_ZPG_X, &CPU::STA_ZPG_X, &CPU::STX_ZPG_Y, nullptr,
        &CPU::TYA_IMPL, &CPU::STA_ABS_Y, &CPU::TXS_IMPL, nullptr, nullptr, &CPU::STA_ABS_X, nullptr, nullptr,

        &CPU::LDY_IMD, &CPU::LDA_X_IND, &CPU::LDX_IMD, nullptr, &CPU::LDY_ZPG, &CPU::LDA_ZPG, &CPU::LDX_ZPG, nullptr,
        &CPU::TAY_IMPL, &CPU::LDA_IMD, &CPU::TAX_IMPL, nullptr, &CPU::LDY_ABS, &CPU::LDA_ABS, &CPU::LDX_ABS, nullptr,

        &CPU::BCS_REL, &CPU::LDA_IND_Y, nullptr, nullptr, &CPU::LDY_ZPG_X, &CPU::LDA_ZPG_X, &CPU::LDX_ZPG_Y, nullptr,
        &CPU::CLV_IMPL, &CPU::LDA_ABS_Y, &CPU::TSX_IMPL, nullptr, &CPU::LDY_ABS_X, &CPU::LDA_ABS_X, &CPU::LDX_ABS_Y,
        nullptr,

        &CPU::CPY_IMD, &CPU::CMP_X_IND, nullptr, nullptr, &CPU::CPY_ZPG, &CPU::CMP_ZPG, &CPU::DEC_ZPG, nullptr,
        &CPU::INY_IMPL, &CPU::CMP_IMD, &CPU::DEX_IMPL, nullptr, &CPU::CPY_ABS, &CPU::CMP_ABS, &CPU::DEC_ABS, nullptr,

        &CPU::BNE_REL, &CPU::CMP_IND_Y, nullptr, nullptr, nullptr, &CPU::CMP_ZPG_X, &CPU::DEC_ZPG_X, nullptr,
        &CPU::CLD_IMPL, &CPU::CMP_ABS_Y, nullptr, nullptr, nullptr, &CPU::CMP_ABS_X, &CPU::DEC_ABS_X, nullptr,

        &CPU::CPX_IMD, &CPU::SBC_X_IND, nullptr, nullptr, nullptr, &CPU::CPX_ZPG, &CPU::SBC_ZPG, &CPU::INC_ZPG,
        nullptr, &CPU::INX_IMPL, &CPU::SBC_IMD, &CPU::NOP_IMPL, &CPU::CPX_ABS, &CPU::SBC_ABS, &CPU::INC_ABS, nullptr,

        &CPU::BEQ_REL, &CPU::SBC_IND_Y, nullptr, nullptr, nullptr, &CPU::SBC_ZPG_X, &CPU::INC_ZPG_X, nullptr,
        &CPU::SED_IMPL, &CPU::SBC_ABS_Y, nullptr, nullptr, nullptr, &CPU::SBC_ABS_X, &CPU::INC_ABS_X, nullptr} {
    // Reset program counter and processor status to 0
    pc = 0x00;
}

void CPU::exec() {
    cout << "PC: " << pc << "\tInstruction: " << (int) cart.read(pc) << "(0x" << hex << (int) cart.read(pc) << ")"
         << resetiosflags(ios::basefield) << "\tP:" << p.to_string() << "\tA:" << (unsigned int) a
         << "\tX:" << (unsigned int) x << "\tY:" << (unsigned int) y << "\tSP:" << (unsigned int) sp << endl;
    (this->*instructions[cart.read(pc++)])();
}

/**
 * Gives access to different components through the memory map. If
 * write is true, then the third parameter, data, shall be written in
 * the mapped component.
 *
 * @param addr
 * @param write
 * @param data
 * @return
 */
uint8_t CPU::mapMemory(uint16_t addr, bool write, uint8_t data) {
    string op = write ? "WRITE" : "READ";
    cout << "\tMemory access (" << op << "): " << hex << "0x" << addr << resetiosflags(ios::basefield);

    if (addr < 0x100) {
        // Zero page
        cout << "\tZero Page" << endl;
        if (write) {
            zeroPage[addr] = data;
        } else {
            return zeroPage[addr];
        }
    } else if (addr < 0x200) {
        //Stack
        cout << "\tStack" << endl;
    } else if (addr < 0x800) {
        // RAM
        cout << "\tRAM" << endl;
        if (write) {
            ram[addr - 0x200] = data;
        } else {
            return ram[addr - 0x200];
        }
    } else if (addr < 0x2000) {
        // Mirrors of the last three sections
    } else if (addr < 0x2008) {
        cout << "\tI/O Registers" << endl;
        // I/O Registers
        //TODO: Probably should implement PPU Registers
        if (write) {
        } else {
        }
    } else if (addr < 0x4000) {
        // Mirrors of 0x2000 - 0x2007
    } else if (addr < 0x4020) {
        // I/O Registers
        // TODO: Implement APU
    } else if (addr < 0x6000) {
        // Expansion ROM
        cout << "\tExpansion ROM" << endl;
    } else if (addr < 0x8000) {
        // SRAM
        cout << "\tSRAM" << endl;
    } else {
        // PRG-ROM, lower and upper bank
        return cart.read(addr);
    }

    return 0;
}

// Op. Code: 0x00
void CPU::BRK_IMPL() {}

// Op. Code: 0x01
void CPU::ORA_X_IND() {
    a |= mapMemory(cart.read(pc++));
    p.set(1, a == 0);
    p.set(7, a & 0x800);
}

// Op. Code: 0x05
void CPU::ORA_ZPG() {}

// Op. Code: 0x06
void CPU::ASL_ZPG() {}

// Op. Code: 0x08
void CPU::PHP_IMPL() {}

// Op. Code: 0x09
void CPU::ORA_IMD() {}

// Op. Code: 0x0A
void CPU::ASL_A() {}

// Op. Code: 0x0D
void CPU::ORA_ABS() {}

// Op. Code: 0x0E
void CPU::ASL_ABS() {}

// Op. Code: 0x10
void CPU::BPL_REL() {
    if (!p.test(7)) {
        int8_t jump = cart.read(pc++);
        pc += jump;
    } else {
        ++pc;
    }
}

// Op. Code: 0x11
void CPU::ORA_IND_Y() {}

// Op. Code: 0x15
void CPU::ORA_ZPG_X() {}

// Op. Code: 0x16
void CPU::ASL_ZPG_X() {}

// Op. Code: 0x18
void CPU::CLC_IMPL() {}

// Op. Code: 0x19
void CPU::ORA_ABS_Y() {}

// Op. Code: 0x1D
void CPU::ORA_ABS_X() {}

// Op. Code: 0x1E
void CPU::ASL_ABS_X() {}

// Op. Code: 0x20
void CPU::JSR_ABS() {}

// Op. Code: 0x21
void CPU::AND_X_IND() {}

// Op. Code: 0x24
void CPU::BIT_ZPG() {}

// Op. Code: 0x25
void CPU::AND_ZPG() {}

// Op. Code: 0x26
void CPU::ROL_ZPG() {}

// Op. Code: 0x28
void CPU::PLP_IMPL() {}

// Op. Code: 0x29
void CPU::AND_IMD() {}

// Op. Code: 0x2A
void CPU::ROL_A() {}

// Op. Code: 0x2C
void CPU::BIT_ABS() {}

// Op. Code: 0x2D
void CPU::AND_ABS() {}

// Op. Code: 0x2E
void CPU::ROL_ABS() {}

// Op. Code: 0x30
void CPU::BMI_REL() {}

// Op. Code: 0x31
void CPU::AND_IND_Y() {}

// Op. Code: 0x35
void CPU::AND_ZPG_X() {}

// Op. Code: 0x36
void CPU::ROL_ZPG_X() {}

// Op. Code: 0x38
void CPU::SEC_IMPL() {}

// Op. Code: 0x39
void CPU::AND_ABS_Y() {}

// Op. Code: 0x3D
void CPU::AND_ABS_X() {}

// Op. Code: 0x3E
void CPU::ROL_ABS_X() {}

// Op. Code: 0x40
void CPU::RTI_IMPL() {}

// Op. Code: 0x41
void CPU::EOR_X_IND() {}

// Op. Code: 0x45
void CPU::EOR_ZPG() {}

// Op. Code: 0x46
void CPU::LSR_ZPG() {}

// Op. Code: 0x48
void CPU::PHA_IMPL() {}

// Op. Code: 0x49
void CPU::EOR_IMD() {}

// Op. Code: 0x4A
void CPU::LSR_A() {}

// Op. Code: 0x4C
void CPU::JMP_ABS() {}

// Op. Code: 0x4D
void CPU::EOR_ABS() {}

// Op. Code: 0x4E
void CPU::LSR_ABS() {}

// Op. Code: 0x50
void CPU::BVC_REL() {}

// Op. Code: 0x51
void CPU::EOR_IND_Y() {}

// Op. Code: 0x55
void CPU::EOR_ZPG_X() {}

// Op. Code: 0x56
void CPU::LSR_ZPG_X() {}

// Op. Code: 0x58
void CPU::CLI_IMPL() {}

// Op. Code: 0x59
void CPU::EOR_ABS_Y() {}

// Op. Code: 0x5D
void CPU::EOR_ABS_X() {}

// Op. Code: 0x5E
void CPU::LSR_ABS_X() {}

// Op. Code: 0x60
void CPU::RTS_IMPL() {}

// Op. Code: 0x61
void CPU::ADC_X_IND() {}

// Op. Code: 0x65
void CPU::ADC_ZPG() {}

// Op. Code: 0x66
void CPU::ROR_ZPG() {}

// Op. Code: 0x68
void CPU::PLA_IMPL() {}

// Op. Code: 0x69
void CPU::ADC_IMD() {}

// Op. Code: 0x6A
void CPU::ROR_A() {}

// Op. Code: 0x6C
void CPU::JMP_IND() {}

// Op. Code: 0x6D
void CPU::ADC_ABS() {}

// Op. Code: 0x6E
void CPU::ROR_ABS() {}

// Op. Code: 0x70
void CPU::BVS_REL() {}

// Op. Code: 0x71
void CPU::ADC_IND_Y() {}

// Op. Code: 0x75
void CPU::ADC_ZPG_X() {}

// Op. Code: 0x76
void CPU::ROR_ZPG_X() {}

// Op. Code: 0x78
void CPU::SEI_IMPL() { p.set(2); }

// Op. Code: 0x79
void CPU::ADC_ABS_Y() {}

// Op. Code: 0x7D
void CPU::ADC_ABS_X() {}

// Op. Code: 0x7E
void CPU::ROR_ABS_X() {}

// Op. Code: 0x81
void CPU::STA_X_IND() {}

// Op. Code: 0x84
void CPU::STY_ZPG() {}

// Op. Code: 0x85
void CPU::STA_ZPG() {}

// Op. Code: 0x86
void CPU::STX_ZPG() {}

// Op. Code: 0x88
void CPU::DEY_IMPL() {}

// Op. Code: 0x8A
void CPU::TXA_IMPL() {}

// Op. Code: 0x8C
void CPU::STY_ABS() {}

// Op. Code: 0x8D
void CPU::STA_ABS() { mapMemory(cart.read(pc++) | (cart.read(pc++) << 8), true, a); }

// Op. Code: 0x8E
void CPU::STX_ABS() {}

// Op. Code: 0x90
void CPU::BCC_REL() {}

// Op. Code: 0x91
void CPU::STA_IND_Y() {}

// Op. Code: 0x94
void CPU::STY_ZPG_X() {}

// Op. Code: 0x95
void CPU::STA_ZPG_X() {}

// Op. Code: 0x96
void CPU::STX_ZPG_Y() {}

// Op. Code: 0x98
void CPU::TYA_IMPL() {}

// Op. Code: 0x99
void CPU::STA_ABS_Y() {}

// Op. Code: 0x9A
void CPU::TXS_IMPL() { sp = x; }

// Op. Code: 0x9D
void CPU::STA_ABS_X() {}

// Op. Code: 0xA0
void CPU::LDY_IMD() {}

// Op. Code: 0xA1
void CPU::LDA_X_IND() {}

// Op. Code: 0xA2}
void CPU::LDX_IMD() {
    x = cart.read(pc++);
    p.set(1, x == 0);
    p.set(7, x & 0x80);
}

// Op. Code: 0xA4
void CPU::LDY_ZPG() {}

// Op. Code: 0xA5
void CPU::LDA_ZPG() {}

// Op. Code: 0xA6
void CPU::LDX_ZPG() {}

// Op. Code: 0xA8
void CPU::TAY_IMPL() {}

// Op. Code: 0xA9
void CPU::LDA_IMD() {
    a = cart.read(pc++);
    p.set(1, a == 0);
    p.set(7, a & 0x80);
}

// Op. Code: 0xAA
void CPU::TAX_IMPL() {}

// Op. Code: 0xAC
void CPU::LDY_ABS() {}

// Op. Code: 0xAD
void CPU::LDA_ABS() {
    a = mapMemory(cart.read(pc++) | (cart.read(pc++) << 8));
    p.set(1, a == 0);
    p.set(7, a & 0x80);
}

// Op. Code: 0xAE
void CPU::LDX_ABS() {}

// Op. Code: 0xB0
void CPU::BCS_REL() {}

// Op. Code: 0xB1
void CPU::LDA_IND_Y() {}

// Op. Code: 0xB4
void CPU::LDY_ZPG_X() {}

// Op. Code: 0xB5
void CPU::LDA_ZPG_X() {}

// Op. Code: 0xB6
void CPU::LDX_ZPG_Y() {}

// Op. Code: 0xB8
void CPU::CLV_IMPL() {}

// Op. Code: 0xB9
void CPU::LDA_ABS_Y() {}

// Op. Code: 0xBA
void CPU::TSX_IMPL() {}

// Op. Code: 0xBC
void CPU::LDY_ABS_X() {}

// Op. Code: 0xBD
void CPU::LDA_ABS_X() {
    x = cart.read(pc++) | (cart.read(pc++) << 8);
    p.set(1, x == 0);
    p.set(7, x & 0x80);
}

// Op. Code: 0xBE
void CPU::LDX_ABS_Y() {}

// Op. Code: 0xC0
void CPU::CPY_IMD() {}

// Op. Code: 0xC1
void CPU::CMP_X_IND() {}

// Op. Code: 0xC4
void CPU::CPY_ZPG() {}

// Op. Code: 0xC5
void CPU::CMP_ZPG() {}

// Op. Code: 0xC6
void CPU::DEC_ZPG() {}

// Op. Code: 0xC8
void CPU::INY_IMPL() {}

// Op. Code: 0xC9
void CPU::CMP_IMD() {}

// Op. Code: 0xCA
void CPU::DEX_IMPL() {}

// Op. Code: 0xCC
void CPU::CPY_ABS() {}

// Op. Code: 0xCD
void CPU::CMP_ABS() {}

// Op. Code: 0xCE
void CPU::DEC_ABS() {}

// Op. Code: 0xD0
void CPU::BNE_REL() {}

// Op. Code: 0xD1
void CPU::CMP_IND_Y() {}

// Op. Code: 0xD5
void CPU::CMP_ZPG_X() {}

// Op. Code: 0xD6
void CPU::DEC_ZPG_X() {}

// Op. Code: 0xD8
void CPU::CLD_IMPL() { p.set(3, false); }

// Op. Code: 0xD9
void CPU::CMP_ABS_Y() {}

// Op. Code: 0xDD
void CPU::CMP_ABS_X() {}

// Op. Code: 0xDE
void CPU::DEC_ABS_X() {
    uint16_t addr = cart.read(pc++) | (cart.read(pc++) << 8);
    mapMemory(addr, true, mapMemory(addr) - 1);
}

// Op. Code: 0xE0
void CPU::CPX_IMD() {}

// Op. Code: 0xE1
void CPU::SBC_X_IND() {}

// Op. Code: 0xE4
void CPU::CPX_ZPG() {}

// Op. Code: 0xE5
void CPU::SBC_ZPG() {}

// Op. Code: 0xE6
void CPU::INC_ZPG() {}

// Op. Code: 0xE8
void CPU::INX_IMPL() {}

// Op. Code: 0xE9
void CPU::SBC_IMD() {}

// Op. Code: 0xEA
void CPU::NOP_IMPL() {}

// Op. Code: 0xEC
void CPU::CPX_ABS() {}

// Op. Code: 0xED
void CPU::SBC_ABS() {}

// Op. Code: 0xEE
void CPU::INC_ABS() {}

// Op. Code: 0xF0
void CPU::BEQ_REL() { p.test(1) ? pc += cart.read(pc++) : ++pc; }

// Op. Code: 0xF1
void CPU::SBC_IND_Y() {}

// Op. Code: 0xF5
void CPU::SBC_ZPG_X() {}

// Op. Code: 0xF6
void CPU::INC_ZPG_X() {}

// Op. Code: 0xF8
void CPU::SED_IMPL() {}

// Op. Code: 0xF9
void CPU::SBC_ABS_Y() {}

// Op. Code: 0xFD
void CPU::SBC_ABS_X() {}

// Op. Code: 0xFE
void CPU::INC_ABS_X() {}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cerr << "Usage\n\tcpu <ROM>" << endl;
        exit(1);
    }
    string testRom(argv[1]);
    cout << "Testing ROM: " << testRom << endl;
    CPU cpu(testRom);
    for (int i = 0; i < 20; ++i) {
        cpu.exec();
    }

    cout << "CPU test finished." << endl;
    return 0;
}
