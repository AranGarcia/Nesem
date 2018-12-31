#include <iostream>
#include <exception>
#include <string>

#include "cpu.hpp"
#include "cartridge.hpp"

using namespace std;

CPU::CPU(string nesFile) : cart(nesFile){
}

int main(int argc, char const *argv[]) {
    CPU cpu("Super Mario Bros (E).nes");
}
