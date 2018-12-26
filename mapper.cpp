#include <cstdlib>
#include "mapper.hpp"

using namespace std;

NROM::NROM(char *pr, char *cr, const size_t prb, const size_t crb){
    prgROM = pr;
    chrROM = cr;
    prgROMBanks = prb;
    chrROMBanks = crb;
}

NROM::~NROM(){
    delete prgROM;
    delete chrROM;
}
