ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    TOOLPREFIX  := x86_64-elf-
    RM          := del /Q
    FIND        := dir /S /B 
    DD          := dd
    QEMU        := qemu-system-i386
    CLEANUP     := cleanup.bat
    PATH_SEP    := \\
    EXEC_CLEANUP := if exist $(CLEANUP) call $(CLEANUP)
else
    DETECTED_OS := $(shell uname -s)
    TOOLPREFIX  := x86_64-elf-
    RM          := rm -f
    FIND        := find
    DD          := dd
    QEMU        := qemu-system-i386
    CLEANUP     := cleanup.sh
    PATH_SEP    := /
    EXEC_CLEANUP := if [ -f $(CLEANUP) ]; then bash $(CLEANUP); fi
endif

CC          := $(TOOLPREFIX)gcc
ASM         := nasm
LD          := $(TOOLPREFIX)ld
OBJCOPY     := $(TOOLPREFIX)objcopy
DISK_IMG    := sqlOS.img

CFLAGS      := -m32 -ffreestanding -nostdlib -Wall -Wextra
LDFLAGS     := -melf_i386 -nostdlib -T linker.ld

ifeq ($(DETECTED_OS),Windows)
    C_SOURCES  := $(shell $(FIND) kernel /C "*.c" | findstr /R "\.c$$")
    C_OBJECTS  := $(patsubst %.c,%.o,$(C_SOURCES))
else
    C_SOURCES  := $(shell $(FIND) kernel -name '*.c')
    C_OBJECTS  := $(C_SOURCES:.c=.o)
endif

.PHONY: all run clean

all: disk

bootloader$(PATH_SEP)bootloader.bin: bootloader$(PATH_SEP)bootloader.asm
	$(ASM) -f bin $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel$(PATH_SEP)kernel.elf: $(C_OBJECTS)
	$(LD) $(LDFLAGS) $(C_OBJECTS) -o $@

kernel$(PATH_SEP)kernel.bin: kernel$(PATH_SEP)kernel.elf
	$(OBJCOPY) -O binary $< $@

disk: bootloader$(PATH_SEP)bootloader.bin kernel$(PATH_SEP)kernel.bin
	$(DD) if=/dev/zero of=$(DISK_IMG) bs=512 count=2880
	$(DD) if=bootloader$(PATH_SEP)bootloader.bin of=$(DISK_IMG) conv=notrunc
	$(DD) if=kernel$(PATH_SEP)kernel.bin of=$(DISK_IMG) bs=512 seek=1 conv=notrunc

run: 
	@$(EXEC_CLEANUP)
	$(MAKE) disk
	$(QEMU) -drive format=raw,file=$(DISK_IMG)

clean:
	$(RM) $(C_OBJECTS) bootloader$(PATH_SEP)bootloader.bin kernel$(PATH_SEP)kernel.* $(DISK_IMG)
