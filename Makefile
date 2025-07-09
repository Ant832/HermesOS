CC=$$TARGET-gcc

run: HermesOS.bin
	cp HermesOS.bin isodir/boot/HermesOS.bin
	grub2-mkrescue -o HermesOS.iso isodir
	qemu-system-i386 -kernel HermesOS.bin

HermesOS.bin: boot.o kernel.o linker.ld crti.o crtn.o
	$(CC) -T linker.ld -o HermesOS.bin -ffreestanding -O2 -nostdlib boot.o kernel.o crti.o crtn.o -lgcc

kernel.o: cpp_kernel/kernel.cpp
	$$TARGET-g++ -c cpp_kernel/kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

# kernel.o: c_kernel/kernel.c
# 	$(CC) -c c_kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

crti.o: crti.c boot.o
	$(CC) -c crti.c -o crti.o -std=c99 -nostdlib

crtn.o: crtn.c boot.o
	$(CC) -c crtn.c -o crtn.o -std=c99 -nostdlib

boot.o: boot.s
	$(CC) boot.s -o boot.o -nostdlib -nostartfiles -c


CRTI_OBJ=crti.o
CRTBEGIN_OBJ:=$(shell $(CC) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC)  -print-file-name=crtend.o)
CRTN_OBJ=crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)

HermesOS.kernel: $(OBJ_LINK_LIST)
	$(CC) -o HermesOS.kernel $(OBJ_LINK_LIST) -nostdlib -lgcc

.PHONY : clean
clean :
	-rm *.o $(objects)
	-rm *.bin $(objects)
	-rm isodir/boot/HermesOS.bin
	-rm HermesOS.iso
	rm -f myos.kernel $(INTERNAL_OBJS)