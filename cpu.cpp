#include <iostream>
#include <exception>
#include <string>

#include "cpu.hpp"
#include "cartridge.hpp"

using namespace std;

CPU::CPU(string nesFile) : cart(nesFile),
    instructions {
                  &CPU::BRK_IMPL, &CPU::ORA_X_IND, nullptr, nullptr, nullptr,
                  &CPU::ORA_ZPG, &CPU::ASL_ZPG, nullptr, nullptr,
                  &CPU::PHP_IMPL, &CPU::ORA_NUM, &CPU::ASL_A, nullptr,
                  nullptr, &CPU::ORA_ABS, &CPU::ASL_ABS, &CPU::SEI_IMPL,
                  &CPU::CLD_IMPL}
{}

void CPU::exec(){ ( this->*instructions[cart.read(pc)] )(); }

/*
   Op. code: 0x00
 */
void CPU::BRK_IMPL(){}

/*
   Op. code: 0x01
 */
void CPU::ORA_X_IND(){}

/*
   Op. code: 0x05
 */
void CPU::ORA_ZPG(){}

/*
   Op. code: 0x06
 */
void CPU::ASL_ZPG(){}

/*
   Op. code: 0x08
 */
void CPU::PHP_IMPL(){}

/*
   Op. code: 0x09
 */
void CPU::ORA_NUM(){}

/*
   Op. code: 0x0A
 */
void CPU::ASL_A(){}

/*
   Op. code: 0x0D
 */
void CPU::ORA_ABS(){}

/*
   Op. code: 0x0E
 */
void CPU::ASL_ABS(){}

/*
   Op. code: 0x78
 */
void CPU::SEI_IMPL(){}

/*
   Op. code: 0xD8
 */
void CPU::CLD_IMPL(){}

int main(int argc, char const *argv[]) {
    CPU cpu("Super Mario Bros (E).nes");
    cout << "Finished constructing " << endl;
    cpu.exec();
}
