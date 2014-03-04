Start:
	mov	r0, #10		@ on va calculer 10!
	mov	r1, #1		@ r1 sera le compteur
	mov	r2, #1		@ r2 contiendra le resultat
Loop:
	mov	r3, r2
	mul 	r2, r3, r1
	add 	r1, r1, #1	@ la on a un compteur qui incremente
	cmp	r0, r1
	bne	Loop
	beq	Fin
Fin:

