#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>

#define PRG_ROM_BANK_SIZE 0x4000
#define CHR_ROM_BANK_SIZE 0x2000
#define PRG_RAM_BANK_SIZE 0X2000

#include "cartridge.hpp"
#include "mapper.hpp"

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
    char *pos = strstr(header, nesSign);
    if (pos == nullptr || (strcmp(pos, header) != 0)) {
        cerr << "Unrecognized header" << endl;
        return false;
    }

    // ROM Sizes (amount of 16KB Banks)
    prgROMBanks = (size_t) header[4];
    chrROMBanks = (size_t) header[5];

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
    mapperNumber = (header[7] & 0xF0) | (header[6] >> 4);
    if (mapperNumber != 0) {
        throw invalid_argument("mapper not yet implemented.");
    }

    // Amount of 8KB RAM Banks, for backwards compatibility
    prgRAMBanks = header[8];
    if (!prgRAMBanks) {
        // 1 bank should always be assumed, even though
        // the value is 0.
        prgRAMBanks = 1;
    }

    // 0x07 - 0x0F should be all zeroes (used in the future?)

    if (includesTrainer) {
        trainer = new char[512];
        gameFile.read(trainer, 512);
    } else {
        trainer = nullptr;
    }

    // PRG-ROM
    uint8_t *prgROM = new uint8_t[PRG_ROM_BANK_SIZE * prgROMBanks];
    gameFile.read((char *) prgROM, PRG_ROM_BANK_SIZE * prgROMBanks);
    // CHR-ROM
    uint8_t *chrROM = new uint8_t[CHR_ROM_BANK_SIZE * chrROMBanks];
    gameFile.read((char *) chrROM, CHR_ROM_BANK_SIZE * chrROMBanks);
    // PRG-RAM
    uint8_t *prgRAM = new uint8_t[PRG_RAM_BANK_SIZE * prgRAMBanks];

    mapper = new Mapper(prgROM, chrROM, prgRAM, prgROMBanks, chrROMBanks,
                        prgRAMBanks);

    return true;
}

Cartridge::~Cartridge() {
    delete mapper;
}

/*
   Reads indirectly from the cartridge through the mapper
 */
uint8_t Cartridge::read(uint16_t addr) {
    return mapper->read(addr);
}

size_t Cartridge::getPrgROMSize() {
    return prgROMBanks;
}

size_t Cartridge::getChrROMSize() {
    return chrROMBanks;
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
        << "\tPRG-ROM: " << cart.prgROMBanks << " banks of 16KB" << endl
        << "\tCHR-ROM: " << cart.chrROMBanks << " banks of 8KB" << endl
        << "\tMirroring: " << mirroring << endl
        << "\tBattery backed RAM: " << (cart.includesBatteryRAM ? "Yes" : "No") << endl
        << "\t512 byte trainer: " << (cart.includesTrainer ? "Yes" : "No") << endl
        << "\tMapper: " << cart.mapperNumber << endl;
    return out;
}
