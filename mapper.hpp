#ifndef MAPPER_H
#define MAPPER_H

#include <cstdlib>

class NROM {
public:
	NROM(char *, char *, size_t, size_t);
    ~NROM();
private:
	char *prgROM;
	char *chrROM;
	size_t prgROMBanks;
	size_t chrROMBanks;
};

#endif
