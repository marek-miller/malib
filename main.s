default rel

%define	STDIN		0
%define	STDOUT		1
%define	STDERR		2

%define	EXIT_SUCESS	0

; system calls
%define SYS_WRITE	1
%define	SYS_EXIT	60


SECTION .data

exit_code		db	0
hello_x64		db	`Hello, x64 world!\n`, 0


SECTION .bss


SECTION .text
	global _start
	extern print_str

_start:
	mov	rdi, STDOUT
	lea	rsi, [hello_x64]
	call 	print_str

_exit:
	mov	rax, SYS_EXIT
	lea	rdi, [exit_code]
	syscall

