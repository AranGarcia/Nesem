#ifndef MAPPER_H
#define MAPPER_H

#include <cstdlib>

/**************************************
 *	Base class for all Mappers
 **************************************

   Upper bank: 0xC000 - 0xFFFF
   Lower bank: 0x8000 - 0xBFFF

 */
class Mapper {
public:
	Mapper(uint8_t *, uint8_t *, uint8_t *, size_t, size_t, size_t);
	~Mapper();

	uint8_t read(uint16_t) const;
protected:
	uint8_t *prgROM;
	uint8_t *chrROM;
	uint8_t *prgRAM;

	// Number of banks in the cartridge
	size_t prgROMBanks;		// Bank size: 16 KB
	size_t chrROMBanks;		// Bank size: 8 KB
	size_t prgRAMBanks;		// Bank size: 8 KB
};
#endif
