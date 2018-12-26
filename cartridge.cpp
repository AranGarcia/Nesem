#include <cstring>
#include <cstdlib>
#include <iostream>
#include <exception>
#include <fstream>

#define PRG_ROM_BANK_SIZE 0x4000
#define CHR_ROM_BANK_SIZE 0x2000

#include "cartridge.hpp"
#include "mapper.hpp"

using namespace std;

char nesSign[4] = {'N', 'E', 'S', 0x1A};

Cartridge::Cartridge(string fn) {
	fname = fn;
	bool status = parse(fn);
	if(!status) {
		// TODO: Throw exception?
		throw invalid_argument("unable to parse cartridge data.");
	}
}

bool Cartridge::parse(string fname){
	ifstream gameFile(fname, ifstream::in | ifstream::binary);

	if(!gameFile) {
		return false;
	}

	char header[16];

	// Identify file with 0x4E 0x45 0x53 0x1A (NES\x1A) signature
	gameFile.read(header, 16);
	char *pos = strstr(header, nesSign);
	if(pos == nullptr || pos != header) {
		return false;
	}

	// ROM Sizes (amount of 16KB Banks)
	size_t prgROMsize = (size_t) header[4];
	size_t chrROMsize = (size_t) header[5];

	// Screen mirroring type (bit 3 overrides bit 1)
	if((header[6] & 8) == 8) {
		mirroringType = FOUR_SCREEN;
	} else{
		mirroringType = ((header[6] & 1) == 1 ? VERTICAL : HORIZONTAL);
	}
	// Battery backed RAM
	includesBatteryRAM = (header[6] & 2) == 2;
	// 512 byte trainer
	includesTrainer = (header[6] & 4) == 4;
	// Mapper number
	mapperNumber = (header[7] & 0xF0) | (header[6] >> 4);
	if(mapperNumber != 0) {
		throw invalid_argument("mapper not yet implemented.");
	}

	// Amount of 8KB RAM Banks, for backwards compatibility
	RAMBanks = header[8];
	if(!RAMBanks) {
		// 1 bank should always be assumed, even though
		// the value is 0.
		RAMBanks = 1;
	}

	if(includesTrainer) {
		trainer = new char[512];
		gameFile.read(trainer, 512);
	}

	char *prgROM = new char[PRG_ROM_BANK_SIZE * prgROMBanks];
	gameFile.read(prgROM, PRG_ROM_BANK_SIZE * prgROMBanks);
	char *chrROM = new char[CHR_ROM_BANK_SIZE * chrROMBanks];
	gameFile.read(chrROM, CHR_ROM_BANK_SIZE * chrROMBanks);

	mapper = new NROM(prgROM, chrROM, prgROMBanks, chrROMBanks);
	return true;
}

Cartridge::~Cartridge(){
	delete mapper;
}

size_t Cartridge::getPrgROMSize(){
	return prgROMBanks;
}

size_t Cartridge::getChrROMSize(){
	return chrROMBanks;
}

MIRRORING Cartridge::getMirroringType(){
	return mirroringType;
}

bool Cartridge::hasBatteryRAM(){
	return includesBatteryRAM;
}

bool Cartridge::has512Trainer(){
	return includesTrainer;
}

unsigned short int Cartridge::getMapperNumber(){
	return mapperNumber;
}

ostream &operator<<(ostream &out, const Cartridge &cart){
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

	out << "Rom: '" << cart.fname << "'" << endl <<
	    "PRG-ROM: " << cart.prgROMBanks << " banks of 16KB" << endl <<
	    "CHR-ROM: " << cart.chrROMBanks << " banks of 16KB" << endl <<
	    "Mirroring: " << mirroring << endl <<
	    "Battery backed RAM: " << (cart.includesBatteryRAM ? "Yes" : "No") << endl <<
	    "512 byte trainer: " << (cart.includesTrainer ? "Yes" : "No") << endl <<
	    "Mapper: " << cart.mapperNumber << endl;
	return out;
}

int main(int argc, char const *argv[]) {
	if(argc  < 2) {
		cerr << "Usage:\n\tcart [ROM]" << endl;
		exit(1);
	}

	string fname(argv[1]);
	Cartridge cart(fname);
	cout << cart;

	return 0;
}
