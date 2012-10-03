[BITS 16]
[ORG 0x0000]

jmp main

BOOT_DRIVER db 0

VESA:
	times 512 db 0

gdt_descriptor:
	dw 0xffff
	dw gdt
	dw 0x0001
gdt:
	gdt_null:
		dw 0x0000
		dw 0x0000
		dw 0x0000
		dw 0x0000
	gdt_kernel_code:
		dw 0xffff
		dw 0x0000
		dw 0x9a00
		dw 0x00cf
	gdt_system_data:
		dw 0xffff
		dw 0x0000
		dw 0x9200
		dw 0x00cf

get_boot_driver:
	push fs
  
	mov ax, 0x8000
	mov fs, ax
	mov al, [fs:0]
	mov [BOOT_DRIVER], al
  
	pop fs
	ret

set_vesa_mode:
	push es
	push fs

	mov ax, 0x4f02
	mov bx, 0x4114
	int 0x10
  
	mov bx, 0x1000
	mov es, bx
	mov bx, 0x8000
	mov fs, bx
	mov di, VESA
	mov ax, 0x4f01
	mov cx, 0x114
	int 0x10
	mov eax, [es:VESA + 40]
	mov [fs:1], eax

	pop es
	pop fs
	ret

read_kernel:
	push es
read_kernel_start:
	mov ax, 0x9000
	mov es, ax
	mov bx, 0
	mov ah, 2
	mov dl, [BOOT_DRIVER]
	mov dh, 0
	mov ch, 0
	mov cl, 4
	mov al, 15
	int 0x13
	jc read_kernel_start
	add bx, 15 * 512
read_kernel_2:
	mov dh, 1
	mov dl, [BOOT_DRIVER]
	mov ch, 0
	mov cl, 1
	mov ah, 2
	mov al, 18
	int 0x13
	jc read_kernel_2
read_kernel_end:
	pop es
	ret

read_disk:
	push es
read_disk_start:
	mov es, ax
	mov bx, 0
read_disk_1:
	mov ah, 2
	mov dl, [BOOT_DRIVER]
	mov cl, 1
	mov al, 18
	int 0x13
	jc read_disk_1
	dec di
	cmp di, 0
	je read_disk_end
	add bx, 18 * 512
	xor dh, 1
	cmp dh, 0
	jne read_disk_1
	inc ch
	jmp read_disk_1
read_disk_end:
	pop es
	ret

main:
	mov ax, 0x1000 ; initial segment registers
	mov ds, ax
	mov ax, 0x8000
	mov ss, ax
	mov sp, 0xffff
	call get_boot_driver
	call set_vesa_mode
	mov ax, 0x5000 ; read font
	mov di, 7
	mov dh, 0
	mov ch, 2
	call read_disk
	call read_kernel ; read kernel
	lgdt [gdt_descriptor] ; load gdt, ready for enter protected mode
	cli ; close interrupt
	mov eax, cr0 ; now we will enter protected mode
	or eax, 1
	mov cr0, eax
	jmp dword 0x8:0x90000 ; okay, then jump to kernel (kernel/head.s)

times 1024-($-$$) db 0
