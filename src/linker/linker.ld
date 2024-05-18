ENTRY(loadKernel)

SECTIONS {
    . = 1M;

    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)       
    }

    .bss BLOCK(4K) : ALIGN(4K) {
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

    .note.gnu.build-id BLOCK(4K) : ALIGN(4K) {
		*(.note.gnu.build-id)
	}
}