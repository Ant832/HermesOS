CC=$$TARGET-gcc

run: HermesOS.bin
	cp HermesOS.bin isodir/boot/HermesOS.bin
	grub2-mkrescue -o HermesOS.iso isodir
	qemu-system-i386 -kernel HermesOS.bin

HermesOS.bin: boot.o kernel.o linker.ld
	$(CC) -T linker.ld -o HermesOS.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

kernel.o: c_kernel/kernel.c
	$(CC) -c c_kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra


boot.o: boot.s
	$(CC) -o boot.o boot.s -nostdlib -nostartfiles -c