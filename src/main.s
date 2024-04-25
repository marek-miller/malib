%include "malib_int.inc"
%include "malib.inc"
%include "syscalls.inc"

global _start

SECTION .data

hello_x64		db	'Hello, x64 World!', 0xa, 0

SECTION .bss

SECTION .text

_start:
	mov	rdi, STDOUT
	lea	rsi, [hello_x64]
	call 	ma_print

	call	ma_clock
	mov	r12, rax
	call	ma_clock
	mov	r13, rax
	call	ma_clock
	mov	r14, rax

_exit:
	mov	rax, SYS_EXIT
	mov	rdi, EXIT_SUCCESS
	syscall
