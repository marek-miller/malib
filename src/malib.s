default rel

global ma_printstr, ma_strlen

%define	STDIN		0
%define	STDOUT		1
%define	STDERR		2

%define	EXIT_SUCESS	0

; system calls
%define SYS_WRITE	1
%define	SYS_EXIT	60

SECTION .data

SECTION .bss

SECTION .text

; Print a null-terminated string to file destriptor.
;
; Parameters:
;	rdi	- file destriptor, e.g. 
;			1 - STDOUT
;			2 - STDERR 
;	rsi	- string address
;
; Returns:
;	rax	- number of characters written
;
ma_printstr:
	push	rdi
	mov	rdi, rsi
	call	ma_strlen
	pop	rdi

	push	rax
	mov	rax, SYS_WRITE	
	mov	rdx, [rsp]	
	syscall

	pop	rax
	ret

; Calculate the length of a null-terminated string.
; 
; Parameters:
; 	rdi	- address of the string
;
; Returns:
;	rax	- number of characters in the string
;
ma_strlen:
	xor	rax, rax
	not	rax
.count:
	inc	rax
	cmp 	[rdi+rax], byte 0
	jne	.count
	ret	
