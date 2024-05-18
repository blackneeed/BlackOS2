; Created by Blackneeed

section .multiboot
align 4
dd 0x1BADB002
dd (1 << 0) | (1 << 1)
dd -(0x1BADB002 + ((1 << 0) | (1 << 1)))
 
extern _start
section .text
global loadKernel
loadKernel:
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