Start:
	mov	r0, #10		@ on va calculer 10!
	mov	r2, #1		@ r2 contiendra le resultat
Loop:
	mov	r3, r2
	mul 	r2, r3, r0
	sub 	r0, r0, #1	@ la on a un compteur qui decremente
				@ on a besoin d'un registre en moins 
				@ compare au cas ou on incremente
	cmp	r0, #0
	bne	Loop
	beq	Fin
Fin:

