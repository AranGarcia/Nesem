#include <cstdlib>

#include "mapper.hpp"

using namespace std;

Mapper::Mapper(uint8_t *prom, uint8_t *crom, uint8_t *pram, const size_t pro, const size_t crb, const size_t pra) {
    prg_rom = prom;
    chr_rom = crom;
    prg_ram = pram;

    prg_rom_banks = pro;
    chr_rom_banks = crb;
    prg_ram_banks = pra;
}

Mapper::~Mapper() {
    delete prg_rom;
    delete chr_rom;
    delete prg_ram;
}

/**
 * This mapper does no bank switching.
 *
 * @param addr
 * @return Data in the ROM's address
 */
uint8_t Mapper::read_prg_rom(uint16_t addr) const {
    return prg_rom[addr];
}

uint8_t Mapper::read_chr_rom(uint16_t addr) const {
    return chr_rom[addr];
}

void Mapper::w_prg_ram(uint16_t addr, uint8_t data) {
    prg_ram[addr] = data;
}

uint8_t Mapper::r_prg_ram(uint16_t addr) {
    return prg_ram[addr];
}
