#ifndef MAPPER_H
#define MAPPER_H

#include <iostream>
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

    uint8_t read_prg_rom(uint16_t) const;

    uint8_t read_chr_rom(uint16_t) const;

    void w_prg_ram(uint16_t, uint8_t);

    uint8_t r_prg_ram(uint16_t);

protected:
    uint8_t *prg_rom;
    uint8_t *chr_rom;
    uint8_t *prg_ram;

    // Number of banks in the cartridge
    size_t prg_rom_banks;        // Bank size: 16 KB
    size_t chr_rom_banks;        // Bank size: 8 KB
    size_t prg_ram_banks;        // Bank size: 8 KB
};

#endif
