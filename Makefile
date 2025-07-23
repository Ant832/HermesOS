CC=$$TARGET-gcc
CXX=$$TARGET-g++
CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -MMD -Icpp_kernel/include
HEADER=cpp_kernel/include/malloc.hpp cpp_kernel/include/terminal.hpp cpp_kernel/include/lib.hpp
OBJS=boot.o kernel.o terminal.o malloc.o lib.o

run: HermesOS.bin
	cp HermesOS.bin isodir/boot/HermesOS.bin
	grub2-mkrescue -o HermesOS.iso isodir
	qemu-system-i386 -kernel HermesOS.bin

HermesOS.bin: $(OBJS) linker.ld
	$(CC) -T linker.ld -o HermesOS.bin -ffreestanding -O2 -nostdlib $(OBJS) -lgcc

kernel.o: cpp_kernel/kernel.cpp $(HEADER)
	$(CXX) -c cpp_kernel/kernel.cpp -o kernel.o $(CFLAGS)

lib.o: cpp_kernel/lib.cpp cpp_kernel/include/lib.hpp
	$(CXX) -c cpp_kernel/lib.cpp -o lib.o $(CFLAGS)

terminal.o: cpp_kernel/terminal.cpp cpp_kernel/include/terminal.hpp
	$(CXX) -c cpp_kernel/terminal.cpp -o terminal.o $(CFLAGS)

malloc.o: cpp_kernel/malloc.cpp cpp_kernel/include/malloc.hpp
	$(CXX) -c cpp_kernel/malloc.cpp -o malloc.o $(CFLAGS)

# kernel.o: c_kernel/kernel.c
# 	$(CC) -c c_kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: boot.s
	$(CC) boot.s -o boot.o -nostdlib -nostartfiles -c

-include *.d

.PHONY : clean
clean :
	rm -f *.o *.bin isodir/boot/HermesOS.bin HermesOS.iso *.d