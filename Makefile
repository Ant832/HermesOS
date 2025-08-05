CC=$$TARGET-gcc
CXX=$$TARGET-g++
CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -MMD -Isrc/include
HEADER=src/include/malloc.hpp src/include/terminal.hpp src/include/lib.hpp
OBJS=boot.o kernel.o terminal.o malloc.o lib.o

run: HermesOS.bin
	cp HermesOS.bin isodir/boot/HermesOS.bin
	grub2-mkrescue -o HermesOS.iso isodir
	qemu-system-i386 -kernel HermesOS.bin

HermesOS.bin: $(OBJS) linker.ld
	$(CC) -T linker.ld -o HermesOS.bin -ffreestanding -O2 -nostdlib $(OBJS) -lgcc

kernel.o: src/kernel.cpp $(HEADER)
	$(CXX) -c src/kernel.cpp -o kernel.o $(CFLAGS)

lib.o: src/lib.cpp src/include/lib.hpp
	$(CXX) -c src/lib.cpp -o lib.o $(CFLAGS)

terminal.o: src/terminal.cpp src/include/terminal.hpp
	$(CXX) -c src/terminal.cpp -o terminal.o $(CFLAGS)

malloc.o: src/malloc.cpp src/include/malloc.hpp
	$(CXX) -c src/malloc.cpp -o malloc.o $(CFLAGS)

# kernel.o: c_kernel/kernel.c
# 	$(CC) -c c_kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: boot.s
	$(CC) boot.s -o boot.o -nostdlib -nostartfiles -c

-include *.d

.PHONY : clean
clean :
	rm -f *.o *.bin isodir/boot/HermesOS.bin HermesOS.iso *.d