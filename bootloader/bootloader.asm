; /bootloader/bootloader.asm
bits 16
org 0x7C00

KERNEL_OFFSET equ 0x1000

start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Get VBE mode info first
    mov ax, 0x4F01
    mov cx, 0x112
    mov di, mode_info
    int 0x10
    
    cmp ax, 0x004F
    jne vbe_fallback
    
    ; Set VBE mode 0x112 with LFB
    mov ax, 0x4F02
    mov bx, 0x4112
    int 0x10
    
    cmp al, 0x4F
    jne vbe_fallback
    cmp ah, 0x00
    jne vbe_fallback
    
    jmp load_kernel

vbe_fallback:
    mov ax, 0x13
    int 0x10

load_kernel:
    mov bx, KERNEL_OFFSET
    mov ah, 0x02
    mov al, 32
    mov ch, 0
    mov cl, 2
    mov dh, 0
    int 0x13
    jc disk_error

    cli
    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:pm_start

disk_error:
    mov si, error_msg
    call print
    jmp $

print:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print
.done:
    ret

bits 32
pm_start:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov esp, 0x9FC00
    call KERNEL_OFFSET
    jmp $

gdt:
    dq 0
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_desc:
    dw 24
    dd gdt

error_msg db "BOOT ERR",0

mode_info:
    times 256 db 0

times 510-($-$$) db 0
dw 0xAA55
