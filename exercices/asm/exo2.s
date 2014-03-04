ldr 	r1, [pc, #44]		@ r1 = &a
ldr 	r2, [pc, #44]		@ r2 = &b
ldr 	r3, [pc, #44]		@ r3 = &c

ldr 	r4, [r1]		@ r4 = a
ldr 	r5, [r2]		@ r5 = b
ldr 	r6, [r3]		@ r6 = c

ldr	r1, [r4]		@ r1 = *a
ldr	r2, [r5]		@ r2 = *b
ldr	r3, [r6]		@ r3 = *c

add	r1, r1, r3
add	r2, r2, r3
str	r1, [r4]
str	r2, [r5]

.word 	0x10000000
.word 	0x10000004
.word 	0x10000008
