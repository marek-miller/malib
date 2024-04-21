default rel

%include "syscalls.inc"
%include "malib.inc"

global _start

SECTION .data

hello_x64		db	'Hello, x__ World!', 0xa, 0

SECTION .bss

SECTION .text
	extern ma_print, ma_toa

_start:
	mov	rdi, hello_x64 + 0x8	; offset to write to
	mov	rsi, 0x64		; number to covert
	mov	rdx, 0x2		; write 2 bytes
	call	ma_toa

	mov	rdi, STDOUT
	lea	rsi, [hello_x64]
	call 	ma_print

_exit:
	mov	rax, SYS_EXIT
	mov	rdi, EXIT_SUCCESS
	syscall

