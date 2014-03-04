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
	} > rom
	
	.auto 0x3000 : {
		chenillard.o(.text)
	} > rom
	
	.text : {
		*(.text)
	} > rom
	

	.rodata : {
		*(.rodata* )
	} > rom
	
	
	.data : {
		_sdata = .;
		*(.data)
		_edata = .;
	}>ram AT>rom 

	.bss : {
		_sbss = .;
		*(.bss)
		*(COMMON)
		_ebss = .;
	} > ram


	_free_space_start = ORIGIN(ram)+(_edata - _sdata) + (_ebss - _sbss);
	_free_space_end = _stack_start - 0x1000; /* on s'interdit de s'approcher trop près du début de la pile */

}
