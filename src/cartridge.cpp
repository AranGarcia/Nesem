#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>

#define PRG_ROM_BANK_SIZE 0x4000
#define CHR_ROM_BANK_SIZE 0x2000
#define PRG_RAM_BANK_SIZE 0X2000

#include "cartridge.hpp"

using namespace std;

char nesSign[4] = {'N', 'E', 'S', 0x1A};

Cartridge::Cartridge(string fn) {
    fname = fn;
    bool status = parse(fn);
    if (!status) {
        throw invalid_argument("unable to parse cartridge data.");
    }
}

bool Cartridge::parse(string fname) {
    ifstream gameFile(fname, ifstream::in | ifstream::binary);

    if (!gameFile) {
        cerr << "Unable to open input stream for cartridge data."
             << endl;
        return false;
    }

    char header[16];

    // Identify file with 0x4E 0x45 0x53 0x1A (NES\x1A) signature
    gameFile.read(header, 16);
    if (memcmp(header, nesSign, 4) != 0) {
        cerr << "Unrecognized header" << endl;
        return false;
    }

    // ROM Sizes (amount of 16KB Banks)
    prg_rom_banks = (size_t) header[4];
    chr_rom_banks = (size_t) header[5];

    // Screen mirroring type (bit 3 overrides bit 1)
    if ((header[6] & 8) == 8) {
        mirroringType = FOUR_SCREEN;
    } else {
        mirroringType = ((header[6] & 1) == 1 ? VERTICAL : HORIZONTAL);
    }
    // Battery backed RAM
    includesBatteryRAM = (header[6] & 2) == 2;
    // 512 byte trainer
    includesTrainer = (header[6] & 4) == 4;
    // Mapper number
    mapperNumber = static_cast<unsigned short>((header[7] & 0xF0) | (header[6] >> 4));
    if (mapperNumber != 0) {
        throw invalid_argument("mapper not yet implemented.");
    }

    // Amount of 8KB RAM Banks, for backwards compatibility
    prg_ram_banks = static_cast<size_t>(header[8]);
    if (!prg_ram_banks) {
        // 1 bank should always be assumed, even though
        // the value is 0.
        prg_ram_banks = 1;
    }

    // 0x07 - 0x0F should be all zeroes (used in the future?)

    if (includesTrainer) {
        trainer = new char[512];
        gameFile.read(trainer, 512);
    } else {
        trainer = nullptr;
    }

    // PRG-ROM
    uint8_t *prgROM = new uint8_t[PRG_ROM_BANK_SIZE * prg_rom_banks];
    gameFile.read((char *) prgROM, PRG_ROM_BANK_SIZE * prg_rom_banks);
    // CHR-ROM
    uint8_t *chrROM = new uint8_t[CHR_ROM_BANK_SIZE * chr_rom_banks];
    gameFile.read((char *) chrROM, CHR_ROM_BANK_SIZE * chr_rom_banks);
    // PRG-RAM
    uint8_t *prgRAM = new uint8_t[PRG_RAM_BANK_SIZE * prg_ram_banks];

    mapper = new Mapper(prgROM, chrROM, prgRAM, prg_rom_banks, chr_rom_banks,
                        prg_ram_banks);

    return true;
}

Cartridge::~Cartridge() {
    delete mapper;
}

/*
   Reads indirectly from the cartridge through the mapper
 */
uint8_t Cartridge::read_rom(uint16_t addr) {
    return mapper->read_prg_rom(addr);
}

uint8_t Cartridge::rw_ram(uint16_t addr, bool write, uint8_t data) {
    if (write) { mapper->w_prg_ram(addr, data); }
    else { return mapper->r_prg_ram(addr); }

    return 0;
}


size_t Cartridge::getPrgROMSize() {
    return prg_rom_banks;
}

size_t Cartridge::getChrROMSize() {
    return chr_rom_banks;
}

MIRRORING Cartridge::getMirroringType() {
    return mirroringType;
}

bool Cartridge::hasBatteryRAM() {
    return includesBatteryRAM;
}

bool Cartridge::has512Trainer() {
    return includesTrainer;
}

unsigned short int Cartridge::getMapperNumber() {
    return mapperNumber;
}

ostream &operator<<(ostream &out, const Cartridge &cart) {
    string mirroring;

    switch (cart.mirroringType) {
        case VERTICAL:
            mirroring = "Vertical";
            break;
        case HORIZONTAL:
            mirroring = "Horizontal";
            break;
        case FOUR_SCREEN:
            mirroring = "Four Screen";
    }

    out << "Rom: '" << cart.fname << "'" << endl
        << "\tPRG-ROM: " << cart.prg_rom_banks << " banks of 16KB" << endl
        << "\tCHR-ROM: " << cart.chr_rom_banks << " banks of 8KB" << endl
        << "\tMirroring: " << mirroring << endl
        << "\tBattery backed RAM: " << (cart.includesBatteryRAM ? "Yes" : "No") << endl
        << "\t512 byte trainer: " << (cart.includesTrainer ? "Yes" : "No") << endl
        << "\tMapper: " << cart.mapperNumber << endl;
    return out;
}