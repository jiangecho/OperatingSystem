[BITS 16]
[ORG 0x7C00]

jmp main

BOOT_DRIVER db 0
VESA:
	times 256 db 0

read_setup:
	push es

	.read_setup_1:
	mov ax, 0x1000
	mov es, ax
	mov bx, 0
	mov ah, 2
	mov dl, [BOOT_DRIVER]
	mov ch, 0
	mov cl, 2
	mov al, 2
	int 0x13
	jc .read_setup_1

	pop es
	ret

save_boot_driver:
	push es

	mov ax, 0x8000
	mov es, ax
	mov al, [BOOT_DRIVER]
	mov [es:0], ax

	pop es
	ret

open_a_20:
	mov ax, 0x2401
	int 0x15
	ret

main:
	mov ax, 0x0
	mov ds, ax
	mov [BOOT_DRIVER], dl
	call open_a_20
	call save_boot_driver
	call read_setup
	jmp dword 0x1000:0

times 510-($-$$) db 0
db 0x55
db 0xAA
