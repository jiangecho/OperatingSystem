[BITS 32]

[GLOBAL timer_interrupt]
[EXTERN doTimer]

[SECTION .text]

timer_interrupt:
    pushad
    pushf
    mov al, 0x20
    out 0x20, al
    out 0xa0, al
    call doTimer
    popf
    popad
    iret
