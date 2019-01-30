#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <iostream>
#include <string>
#include "mapper.hpp"

enum MIRRORING {VERTICAL, HORIZONTAL, FOUR_SCREEN};

class Cartridge {
    friend std::ostream &operator<<(std::ostream &, const Cartridge &);
public:
    Cartridge(std::string);
    ~Cartridge();

    uint8_t read_rom(uint16_t);
    uint8_t rw_ram(uint16_t, bool = false, uint8_t = 0);

    size_t getPrgROMSize();
    size_t getChrROMSize();
    MIRRORING getMirroringType();
    bool hasBatteryRAM();
    bool has512Trainer();
    unsigned short int getMapperNumber();
private:
    bool parse(std::string);
    Mapper *mapper;

    std::string fname;

    // ROM sizes in KB
    size_t prg_rom_banks;
    size_t chr_rom_banks;
    size_t prg_ram_banks;

    MIRRORING mirroringType;
    bool includesBatteryRAM;
    bool includesTrainer;
    unsigned short int mapperNumber;

    char *trainer;
};

#endif
