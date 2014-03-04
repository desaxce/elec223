Start:
	ldr 	r3, [pc, #92]
	mov	r2, #1			@ on met 1 à l'adresse 0x10000000
	str 	r2, [r3]		
	ldr	r2, [r3]
	mov	r0, #0			@ compteur de boucle
Loop:
	cmp	r2, r0			
	add 	r0, r0, #1
	bne	Loop			@ on retourne au point de depart
	sub	r0, r0, #1		@ un de trop
	add	r5, r0, lsl #1		
	lsl	r5, #2
	sub	r5, r5, #4		@ r5 contient le bon offset par
					@ rapport a pc (en supposant que
					@ chaque label .Cas$i contient deux
					@ instructions max)
	add	pc, pc, r5		@ on va a la bonne adresse (pas 
					@ classe mais efficace)
.Cas0:
	mov 	r4, #0
	b	Fin
.Cas1:
	mov	r4, #1
	b	Fin
.Cas2:
	mov	r4, #2
	b	Fin
.Cas3:
	mov	r4, #3
	b	Fin
.Cas4:
	mov	r4, #4
	b	Fin
.Cas5:
	mov	r4, #5
	b	Fin
@ Je n'ai pas mis les 256 cas possibles. De toutes facons cette methode ne semble pas etre tres bien puisqu'on est oblige de lister les possibilites.

Fin:
.word	0x10000000	@ c'est genant de devoir mettre un .word puisqu'on veut un uint8_t mais si je remplace par .byte j'ai une erreur d'alignement lors de la compilation.
