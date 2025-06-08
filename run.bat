@echo off
for /r %%i in (*.img *.o *.bin *.iso *.elf) do del /q "%%i"
nasm -f bin bootloader\bootloader.asm -o bootloader\bootloader.bin
for /r "kernel" %%f in (*.c) do gcc -m32 -ffreestanding -nostdlib -Wall -Wextra -c "%%f" -o "%%~dpnf.o"
ld -mi386pe -nostdlib -T linker.ld kernel\*.o kernel\graphics\*.o kernel\graphics\shapes\*.o -o kernel\kernel.elf
objcopy -O binary kernel\kernel.elf kernel\kernel.bin
powershell -Command "$file = [io.file]::Create('sqlOS.img'); $file.SetLength(512 * 2880); $file.Close()"
powershell -Command "$bootloader = [System.IO.File]::ReadAllBytes('bootloader\bootloader.bin'); $img = [System.IO.File]::OpenWrite('sqlOS.img'); $img.Write($bootloader, 0, $bootloader.Length); $img.Close()"
powershell -Command "$kernel = [System.IO.File]::ReadAllBytes('kernel\kernel.bin'); $img = [System.IO.File]::OpenWrite('sqlOS.img'); $img.Position = 512; $img.Write($kernel, 0, $kernel.Length); $img.Close()"
qemu-system-i386 -drive format=raw,file=sqlOS.img 