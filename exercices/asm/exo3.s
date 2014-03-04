Start:
	ldr	r0, [pc, #32] 
	mov	r2, #3
	str	r2, [r0]
	ldr	r2, [r0]	@ ligne inutile en realite mais
				@ c'est juste pour bien comprendre
				@ ce qu'on fait
	mov	r1, #0
Loop:
	cmp	r1, r2
	beq	Fin
	bl	g
	add	r1, r1, #1
	b	Loop

g:	@ fonction mytho qui ne fait rien
	@ on a quand meme besoin d'une instruction
	@ pour rendre la main a la ligne 12. Comment faire ?
Fin:
.word 	0x10000000

@ toujours le meme probleme avec les uint32_t et uint8_t. Ici je pourrais ajouter une condition pour verifier que i ne depasse pas 256  mais ca fait un peu bizarre.
