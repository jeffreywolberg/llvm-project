	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 0
	.globl	_foo                            ; -- Begin function foo
	.p2align	2
_foo:                                   ; @foo
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x1
	mov	x20, x0
	add	x8, x1, #4
	str	x8, [sp]
Lloh0:
	adrp	x0, l_.str@PAGE
Lloh1:
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	mov	w8, #25960
	movk	w8, #27756, lsl #16
	str	w8, [x19, #4]
	mov	w8, #111
	strh	w8, [x19, #8]
	ldr	w8, [x19]
	add	w0, w8, w20
	.cfi_def_cfa wsp, 48
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	.cfi_def_cfa_offset 0
	.cfi_restore w30
	.cfi_restore w29
	.cfi_restore w19
	.cfi_restore w20
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #96
	.cfi_def_cfa_offset 96
	stp	x20, x19, [sp, #64]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #80]             ; 16-byte Folded Spill
	add	x29, sp, #80
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_remember_state
Lloh2:
	adrp	x8, ___stack_chk_guard@GOTPAGE
Lloh3:
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
Lloh4:
	ldr	x8, [x8]
	stur	x8, [x29, #-24]
	mov	x8, #10
	movk	x8, #25977, lsl #32
	movk	x8, #8563, lsl #48
	str	x8, [sp, #16]
	add	x8, sp, #16
	add	x19, x8, #4
	strb	wzr, [sp, #24]
	str	x19, [sp]
Lloh5:
	adrp	x0, l_.str@PAGE
Lloh6:
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	mov	w8, #25960
	movk	w8, #27756, lsl #16
	str	w8, [sp, #20]
	mov	w8, #111
	strh	w8, [sp, #24]
	ldr	w8, [sp, #16]
	add	w20, w8, #15
	str	x19, [sp]
Lloh7:
	adrp	x0, l_.str.4@PAGE
Lloh8:
	add	x0, x0, l_.str.4@PAGEOFF
	bl	_printf
	str	x20, [sp]
Lloh9:
	adrp	x0, l_.str.5@PAGE
Lloh10:
	add	x0, x0, l_.str.5@PAGEOFF
	bl	_printf
	ldur	x8, [x29, #-24]
Lloh11:
	adrp	x9, ___stack_chk_guard@GOTPAGE
Lloh12:
	ldr	x9, [x9, ___stack_chk_guard@GOTPAGEOFF]
Lloh13:
	ldr	x9, [x9]
	cmp	x9, x8
	b.ne	LBB1_2
; %bb.1:
	mov	w0, #0
	.cfi_def_cfa wsp, 96
	ldp	x29, x30, [sp, #80]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #96
	.cfi_def_cfa_offset 0
	.cfi_restore w30
	.cfi_restore w29
	.cfi_restore w19
	.cfi_restore w20
	ret
LBB1_2:
	.cfi_restore_state
	bl	___stack_chk_fail
	.loh AdrpLdrGotLdr	Lloh11, Lloh12, Lloh13
	.loh AdrpAdd	Lloh9, Lloh10
	.loh AdrpAdd	Lloh7, Lloh8
	.loh AdrpAdd	Lloh5, Lloh6
	.loh AdrpLdrGotLdr	Lloh2, Lloh3, Lloh4
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Orig: %s\n"

l_.str.1:                               ; @.str.1
	.asciz	"hello"

l_.str.2:                               ; @.str.2
	.asciz	"yes!"

l_.str.4:                               ; @.str.4
	.asciz	"After: %s\n"

l_.str.5:                               ; @.str.5
	.asciz	"%d\n"

.subsections_via_symbols
