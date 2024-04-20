global _start

%define	STDIN		0
%define	STDOUT		1
%define	STDERR		2

%define	EXIT_SUCESS	0

; system calls
%define SYS_WRITE	1
%define	SYS_EXIT	60


SECTION .data

exit_code		db	EXIT_SUCESS
hello_x64		db	`Hello, x64 world!\n`, 0


SECTION .bss


SECTION .text

_start:
	mov	rdi, STDOUT
	lea	rsi, [hello_x64]
	call 	print_str

_exit:
	mov	rax, SYS_EXIT
	mov	rdi, exit_code
	syscall

;  Print a null-terminated string to file destriptor.
;
; Parameters:
;	rdi	- file destriptor, e.g. 
;			1 - STDOUT
;			2 - STDERR 
;
; Returns:
;	rax	- number of characters written
;
print_str:
	call	str_len
	push	rax
.syscall:
	mov	rax, SYS_WRITE	
	mov	rdx, [rsp]	
	syscall

	pop	rax
	ret

;  Calculate the length of a null-terminated string.
; 
; Parameters:
; 	rsi	- address of the string
;
; Returns:
;	rax	- number of characters in the string
;
str_len:
	xor	rax, rax
.loop:
	cmp 	[rsi+rax], byte 0
	je	.end_loop
	inc	rax
	jmp	.loop
.end_loop:
	ret	
