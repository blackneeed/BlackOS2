; Created by Blackneeed
global GDTNullDescriptor
global GDTCodeDescriptor
global GDTDataDescriptor

GDTNullDescriptor:
	dd 0
	dd 0	
GDTCodeDescriptor:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10011010b		
	db 11001111b
	db 0x00
GDTDataDescriptor:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

GDTEnd:

GDTDescriptor:
	GDTSize: 
		dw GDTEnd - GDTNullDescriptor - 1
		dq GDTNullDescriptor

CodeSeg equ GDTCodeDescriptor - GDTNullDescriptor
DataSeg equ GDTDataDescriptor - GDTNullDescriptor

section .multiboot
align 4
dd 0x1BADB002
dd (1 << 0) | (1 << 1)
dd -(0x1BADB002 + ((1 << 0) | (1 << 1)))
 
extern _start
section .text
global loadKernel
loadKernel:
	lgdt [GDTDescriptor]
	jmp CodeSeg:fix_segs

fix_segs:
	mov ax, DataSeg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

    mov esp, stack_end
	call _start
	cli

.loop:
	hlt
    jmp .loop

section .bss
align 16
stack_start:
resb 8192
stack_end: