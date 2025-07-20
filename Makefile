CC=$$TARGET-gcc
CXX=$$TARGET-g++

run: HermesOS.bin
	cp HermesOS.bin isodir/boot/HermesOS.bin
	grub2-mkrescue -o HermesOS.iso isodir
	qemu-system-i386 -kernel HermesOS.bin

HermesOS.bin: boot.o kernel.o linker.ld
	$(CC) -T linker.ld -o HermesOS.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

kernel.o: cpp_kernel/kernel.cpp cpp_kernel/malloc.hpp cpp_kernel/lib.hpp cpp_kernel/string.hpp
	$(CXX) -c cpp_kernel/kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -MMD


# kernel.o: c_kernel/kernel.c
# 	$(CC) -c c_kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: boot.s
	$(CC) boot.s -o boot.o -nostdlib -nostartfiles -c

-include *.d

.PHONY : clean
clean :
	rm -f *.o *.bin isodir/boot/HermesOS.bin HermesOS.iso *.d