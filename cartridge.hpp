#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>

enum MIRRORING {VERTICAL, HORIZONTAL, FOUR_SCREEN};

class Cartridge {
public:
    Cartridge(std::string);

    unsigned short int getPrgROMSize();
    unsigned short int getChrROMSize();
    MIRRORING getMirroringType();
    bool hasBatteryRAM();
    bool has512Trainer();
    unsigned short int getMapperNumber();
private:
    bool parse(std::string);

    std::string fname;
    // ROM sizes in KB
    unsigned short int prgROMsize;
    unsigned short int chrROMsize;
    MIRRORING mirroringType;
    bool includesBatteryRAM;
    bool includesTrainer;
    unsigned short int mapper;
    unsigned short int RAMBanks;

    char *trainer;
    char *prgROM;
    char *chrROM;
};

#endif
