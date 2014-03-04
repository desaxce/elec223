MEMORY {
	rom (rx)	: ORIGIN = 0, LENGTH = 2M
	ram (!rx)	: ORIGIN = 0x0C000000, LENGTH = 8M
}


_stack_start = ORIGIN(ram) + LENGTH(ram);

SECTIONS {
	.init 0x0c001000 : {
		chenillard.o(.text)
	} > ram

	.text : {
		*(.text)
	} > ram
	
	.rodata : {
		*(.rodata* )
	} > ram
	
	.data : {
		_sdata = .;
		*(.data)
		_edata = .;
	}> ram

	.bss : {
		_sbss = .;
		*(.bss)
		*(COMMON)
		_ebss = .;
	} > ram

}
