default rel

%include "syscalls.inc"
%include "malib.inc"

global _start

SECTION .data

exit_code		db	EXIT_SUCCESS

SECTION .bss

SECTION .text

_start:

_exit:
	mov	rax, SYS_EXIT
	mov	rdi, [exit_code]
	syscall

