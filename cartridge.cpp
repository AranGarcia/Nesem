#include <cstring>
#include <cstdlib>
#include <iostream>
#include <exception>
#include <fstream>

#define ROM_BANK_SIZE 0x4000

#include "cartridge.hpp"

using namespace std;

char nesSign[4] = {'N', 'E', 'S', 0x1A};

Cartridge::Cartridge(string fn){
	fname = fn;
	bool status = parse(fn);
	if(!status) {
		// TODO: Throw exception?
		throw invalid_argument("unable to parse cartridge data.");
	}

	string mirroring;
	switch (mirroringType) {
		case VERTICAL:
			mirroring = "Vertical";
			break;
		case HORIZONTAL:
			mirroring = "Horizontal";
			break;
		case FOUR_SCREEN:
			mirroring = "Four Screen";
	}
	cout << "Rom: '" << fname << "'" << endl <<
	    "PRG-ROM: " << prgROMsize << " banks of 16KB" << endl <<
	    "CHR-ROM: " << chrROMsize << " banks of 16KB" << endl <<
	    "Mirroring: " << mirroring << endl <<
	    "Battery backed RAM: " << (includesBatteryRAM ? "Yes" : "No") << endl <<
	    "512 byte trainer: " << (includesTrainer ? "Yes" : "No") << endl <<
	    "Mapper: " << mapper << endl;
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
	prgROMsize = (unsigned short int) header[4];
	chrROMsize = (unsigned short int) header[5];

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
	mapper = (header[7] & 0xF0) | (header[6] >> 4);

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

	cout << "\tPOS: " << gameFile.tellg() << endl;
	prgROM = new char[ROM_BANK_SIZE * prgROMsize];
	gameFile.read(prgROM, ROM_BANK_SIZE * prgROMsize);
	cout << "\tPOS: " << gameFile.tellg() << endl;
	chrROM = new char[ROM_BANK_SIZE * chrROMsize];
	gameFile.read(chrROM, ROM_BANK_SIZE * chrROMsize);
	cout << "\tPOS: " << gameFile.tellg() << endl;
	return true;
}

unsigned short int Cartridge::getPrgROMSize(){
	return prgROMsize;
}

unsigned short int Cartridge::getChrROMSize(){
	return chrROMsize;
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
	return mapper;
}

int main(int argc, char const *argv[]) {
	Cartridge cart("Mega Man 6 (U).nes");

	return 0;
}
