#include <cstdlib>
#include <exception>
#include <iostream>
#include "mapper.hpp"

using namespace std;

Mapper::Mapper(uint8_t *prom, uint8_t *crom, uint8_t *pram, const size_t pro, const size_t crb, const size_t pra){
	prgROM = prom;
	chrROM = crom;
	prgRAM = pram;

	prgROMBanks = pro;
	chrROMBanks = crb;
	prgRAMBanks = pra;
}

Mapper::~Mapper(){
	delete prgROM;
	delete chrROM;
	delete prgRAM;
}

uint8_t Mapper::read(uint16_t addr) const {
	/*
	 * Does no bank switching
	 */
	addr -= 0x8000;
	return prgROM[addr];
}
