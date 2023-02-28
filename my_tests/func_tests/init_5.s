	.arch armv8-a
	.file	"init_5.c"
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"Hello this is a test"
	.align	3
.LC1:
	.string	"w"
	.align	3
.LC2:
	.string	"tmp_file"
	.align	3
.LC3:
	.string	"init_5.c"
	.align	3
.LC4:
	.string	"n == strlen(buf)"
	.align	3
.LC5:
	.string	"Wrote to tmp_file"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	mov	x29, sp
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	str	x0, [sp, 56]
	ldr	x0, [sp, 56]
	bl	strlen
	add	x0, x0, 1
	bl	malloc
	str	x0, [sp, 48]
	ldr	x1, [sp, 56]
	ldr	x0, [sp, 48]
	bl	strcpy
	adrp	x0, .LC1
	add	x1, x0, :lo12:.LC1
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	fopen
	str	x0, [sp, 40]
	ldr	x0, [sp, 40]
	bl	fileno
	str	w0, [sp, 36]
	ldr	x0, [sp, 48]
	bl	strlen
	mov	x2, x0
	ldr	x1, [sp, 48]
	ldr	w0, [sp, 36]
	bl	write
	str	x0, [sp, 24]
	ldr	x0, [sp, 48]
	bl	strlen
	mov	x1, x0
	ldr	x0, [sp, 24]
	cmp	x0, x1
	beq	.L2
	adrp	x0, __PRETTY_FUNCTION__.0
	add	x3, x0, :lo12:__PRETTY_FUNCTION__.0
	mov	w2, 14
	adrp	x0, .LC3
	add	x1, x0, :lo12:.LC3
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	__assert_fail
.L2:
	ldr	x0, [sp, 40]
	bl	fclose
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	puts
	mov	w0, 0
	ldp	x29, x30, [sp], 64
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.align	3
	.type	__PRETTY_FUNCTION__.0, %object
	.size	__PRETTY_FUNCTION__.0, 5
__PRETTY_FUNCTION__.0:
	.string	"main"
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
