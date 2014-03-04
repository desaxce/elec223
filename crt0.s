.global _start
.global _followup
.global branch
.global _available_start
.global _available_end

.macro mww A,B
	ldr r0, =\B
	ldr r1, =\A
	str r0,[r1]
.endm

_start:
	/* Initialization of openocd */

        # SVC32 mode 
	ldr r0, =0x800000d3
	msr cpsr, r0 

        # WTCON : disable watchdog
        mww 0x01d30000 0
        # INTMSK
        mww 0x01e0000c 0x03fffeff
        # INTCON
        mww 0x01e00000 0x5
        # LOCKTIME
        mww 0x01d8000c 0xf0
        # PLLCON
        mww 0x01d80000 0x0003a031
        # CLKCON
        mww 0x01d80004 0x00007ff8
        
        # PCONA
        mww 0x01d20000 0x000003ff
        # PDATB
        mww 0x01d2000c 0x7cf
        # PCONB
        mww  0x01d20008 0x07ff
        # PDATC
        mww 0x01d20014 0x0100
        # PCONC
        mww 0x01d20010 0xfff5ff54
        # PUPC
        mww 0x01d20018 0x00000000
        # PCOND
        mww 0x01d2001c 0x0000aaaa
        # PUPD
        mww 0x01d20024 0x00000000
        # PCONE
        mww 0x01d20028 0x00021569
        # PDATE
        mww 0x01d2002c 0x00000000
        # PUPE
        mww 0x01d20030 0x00000000
        # PCONF
        mww 0x01d20034 0x24900a
        # PUPF
        mww 0x01d2003c 0x00000000
        # PCONG
        mww 0x01d20040 0xff3c
        # PUPG
        mww 0x01d20048 0x00000000
        # SPUCR	       
        mww 0x01d2004c 0x6
        # INTMSK
        mww 0x01e0000c 0x03fffeff
        # INTCON
        mww 0x01e00000 0x05
        # INTMOD
        mww 0x01e00008 0x0
        # EXTINT
        mww 0x01d20050 0x00040440
        
        # SDRAM init
        mww  0x1c80000 0x01001102
        mww  0x1c80004 0x00007ff4
        mww  0x1c80008 0x00000a40
        mww  0x1c8000C 0x00001480
        mww  0x1c80010 0x00007ffc
        mww  0x1c80014 0x00007ffc
        mww  0x1c80018 0x00000c40
        mww  0x1c8001C 0x00018004
        mww  0x1c80020 0x00000a40
        mww  0x1c80024 0x008603fb
        mww  0x1c80028 0x00000010
        mww  0x1c8002C 0x00000020
        mww  0x1c80030 0x00000020
	
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
	beq _paste_data 
	str r2, [r0]
	add r0, r0, #4
	bne _loop_zero_bss
	
	/* Pastes the data section to the start of ram */
_paste_data:
	ldr r0, =_data_start
	ldr r0, [r0]
	ldr r1, =_data_end
	ldr r1, [r1]
	ldr r3, =_ram_start
	ldr r3, [r3]
_loop_paste_data:
	cmp r0, r1
	beq _back_to_main
	ldr r2, [r0]
	str r2, [r3]
	add r0, r0, #4
	add r3, r3, #4
	bne _loop_paste_data

_back_to_main:	
	/* Launch main with no args */
	mov r0, #0		/* no argc */
	mov r1, #0		/* no argv */
	bl main			/* Should return */
	.word 0xDEEEDEEE	/* Set a soft break point */
	bl end

end:
	b end

branch:
	mov pc, r0

_data_start:
	.word _sdata
_data_end:
	.word _edata
_ram_start:
	.word _ram_debut
_ram_end:
	.word _stack_start
_bss_start:
	.word _sbss
_bss_end:
	.word _ebss
_available_start:
	.word _free_space_start
_available_end:
	.word _free_space_end
        
