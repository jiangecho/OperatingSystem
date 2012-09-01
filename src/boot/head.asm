[BITS 32]
[GLOBAL start]
[EXTERN main]

jmp start

start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x8ffff

    call main

    jmp $
