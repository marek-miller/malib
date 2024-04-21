default rel

%include "syscalls.inc"
%include "malib.inc"

global _start

SECTION .data

exit_code		db	EXIT_SUCESS
hello_x64		db	'Hello, x64 world!', 0xa, 0

SECTION .bss

SECTION .text
	extern ma_printstr

_start:
	mov	rdi, STDOUT
	lea	rsi, [hello_x64]
	call 	ma_printstr

_exit:
	mov	rax, SYS_EXIT
	lea	rdi, [exit_code]
	syscall

