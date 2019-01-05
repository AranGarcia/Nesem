objects = cpu.o cartridge.o mapper.o

esemm : $(objects)
	g++ -o nes $(objects)
cpu.o : cartridge.o mapper.o
cartridge.o : mapper.hpp
mapper.o :


.PHONY : clean
clean :
	rm *.o
