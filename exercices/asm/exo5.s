ldr	r0, [pc, #56]	@ r0 contient l'adresse de i
ldr	r1, [pc, #56]	@ r1 contient &a
ldr	r2, [pc, #56]	@ r2 contient &b
mov 	r3, #5		@ i = 5
str	r3, [r0]
ldr 	r3, [r0]	@ inutile mais on le met qd meme
ldr	r4, [r1]	@ r4 contient a
ldr	r5, [r2]	@ r5 contient b

add	r0, r4, r3, lsl #2	@ r0 contient a + 4*i
add	r1, r5, r3, lsl #2	@ r1 contient b + 4*i
ldr	r6, [r0]		@ r6 contient a[i]
ldr	r7, [r1]		@ r7 contient b[i]

add	r2, r4, r7, lsl #2 	@ r2 contient a+4*b[i]
add	r3, r5, r6, lsl #2 	@ r3 contient b+4*a[i]

ldr	r8, [r2]		@ la valeur a[b[i]]...
str	r8, [r3]		@ ... qu'on stocke dans b[a[i]]

.word	0x10000000
.word	0x20000000
.word	0x30000000
