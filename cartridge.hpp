#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <iostream>
#include <string>
#include "mapper.hpp"

enum MIRRORING {VERTICAL, HORIZONTAL, FOUR_SCREEN};

class Cartridge {
	friend std::ostream &operator<<(std::ostream &, const Cartridge &);
public:
	Cartridge(std::string);
	~Cartridge();

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
	size_t prgROMBanks;
	size_t chrROMBanks;
	size_t prgRAMBanks;

	MIRRORING mirroringType;
	bool includesBatteryRAM;
	bool includesTrainer;
	unsigned short int mapperNumber;

	char *trainer;
};

#endif
