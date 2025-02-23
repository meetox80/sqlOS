CC          := x86_64-elf-gcc
ASM         := nasm
LD          := x86_64-elf-ld
OBJCOPY     := x86_64-elf-objcopy
DISK_IMG    := sqlOS.img

CFLAGS      := -m32 -ffreestanding -nostdlib -Wall -Wextra
LDFLAGS     := -melf_i386 -nostdlib -T linker.ld

C_SOURCES   := $(shell find kernel -name '*.c')
C_OBJECTS   := $(C_SOURCES:.c=.o)

.PHONY: all run clean

all: disk

bootloader/bootloader.bin: bootloader/bootloader.asm
	$(ASM) -f bin $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/kernel.elf: $(C_OBJECTS)
	$(LD) $(LDFLAGS) $(C_OBJECTS) -o $@

kernel/kernel.bin: kernel/kernel.elf
	$(OBJCOPY) -O binary $< $@

disk: bootloader/bootloader.bin kernel/kernel.bin
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880
	dd if=bootloader/bootloader.bin of=$(DISK_IMG) conv=notrunc
	dd if=kernel/kernel.bin of=$(DISK_IMG) bs=512 seek=1 conv=notrunc

run: 
	@if [ -f cleanup.sh ]; then bash cleanup.sh; fi
	$(MAKE) disk
	qemu-system-i386 -drive format=raw,file=$(DISK_IMG)

clean:
	rm -f $(C_OBJECTS) bootloader/bootloader.bin kernel/kernel.* $(DISK_IMG)
