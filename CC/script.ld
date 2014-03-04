MEMORY {
	rom (rx)	: ORIGIN = 0, LENGTH = 2M
	ram (!rx)	: ORIGIN = 0x0C000000, LENGTH = 8M
}


ENTRY(_start);	/* inutile sauf si on utilise un loader (exception: gdb) */

_stack_start = ORIGIN(ram) + LENGTH(ram);
_ram_debut = ORIGIN(ram);

SECTIONS {
	.init : {
		crt0.o(.text)
	} > ram
	.text : {
		*(.text)
	} > ram
	
	.rodata : {
		*(.rodata* )
	} > ram
	
	.bss : {
		_sbss = .;
		*(.bss)
		*(COMMON)
		_ebss = .;
	} > ram

	.data 0x0c001000 : {
		_sdata = .;
		*(.data)
		_edata = .;
	}> ram

}
