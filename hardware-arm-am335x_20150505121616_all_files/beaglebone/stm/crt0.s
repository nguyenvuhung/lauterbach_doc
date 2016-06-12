	PRESERVE8
	AREA |.text|, CODE, ALIGN=3
	CODE32
	EXTERN main
	EXTERN ||Image$$.bss$$ZI$$Base||
	EXTERN ||Image$$.bss$$ZI$$Limit||
	EXTERN ||Image$$.stack$$ZI$$Limit||
	GLOBAL __main
	ENTRY
__main
	; initialize stack pointer
	ldr	sp, _SP
	mov	fp, #0

	; clear .bss-section
	ldr	r1, BSS_S
	ldr	r2, BSS_E
	subs	r2, r2, r1
	beq	gomain
	mov 	r0, #0
bss_clear
	strb	r0, [r1]
	subs	r2, r2, #1
	add	r1, r1, #1
	bne	bss_clear
gomain
	bl	main
_end
	b	_end

BSS_S	DCD	||Image$$.bss$$ZI$$Base||
BSS_E	DCD	||Image$$.bss$$ZI$$Limit||
_SP	DCD	||Image$$.stack$$ZI$$Limit||

	END
