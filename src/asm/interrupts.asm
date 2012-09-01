[BITS 32]

[GLOBAL interruptDefaultHandler]

[GLOBAL keyboardASMHandler]
[EXTERN keyboardHandler]

[GLOBAL mouseASMHandler]
[EXTERN mouseHandler]

[GLOBAL timerASMHandler]
[EXTERN timerHandler]

[SECTION .text]

interruptDefaultHandler:
    mov al, 0x20
    out 0x20, al
    out 0xa0, al
    iret

keyboardASMHandler:
    pushad
    call keyboardHandler
    mov al, 0x20
    out 0x20, al
    out 0xa0, al
    popad
    iret

mouseASMHandler:
    pushad
    pushf
    call mouseHandler
    mov al, 0x20
    out 0x20, al
    out 0xa0, al
    popf
    popad
    iret

timerASMHandler:
    pushad
    pushf
    mov al, 0x20
    out 0x20, al
    out 0xa0, al
    call timerHandler
    popf
    popad
    iret
