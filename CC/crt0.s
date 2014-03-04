.global _start
.global _followup
.global _start_data
.global _end_data

_start:
	/* Set up the stack pointer */
	ldr r0, =_ram_end	
	ldr r1, [r0]
	mov sp, r1
	
	/* Zeroes up the BSS section */
	ldr r0, =_bss_start
	ldr r0, [r0]
	ldr r1, =_bss_end
	ldr r1, [r1]
	mov r2, #0
_loop_zero_bss:
	cmp r0, r1
	beq _back_to_main 
	str r2, [r0]
	add r0, r0, #4
	bne _loop_zero_bss
	
_back_to_main:	
	/* Launch main with no args */
	mov r0, #0		/* no argc */
	mov r1, #0		/* no argv */
	bl main			/* Should return */
	bl end

end:
	b end

_ram_start:
	.word _ram_debut
_ram_end:
	.word _stack_start
_bss_start:
	.word _sbss
_bss_end:
	.word _ebss
_start_data:
	.word _sdata
_end_data:
	.word _edata
