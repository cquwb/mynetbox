	.file	"a.cpp"
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	120
	.text
	.globl	_Z1fv
	.type	_Z1fv, @function
_Z1fv:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z1fv, .-_Z1fv
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
