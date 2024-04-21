default rel

%include "syscalls.inc"
%include "malib.inc"

global ma_print, ma_strlen, ma_toa

SECTION .data

toa_charset	db	'0123456789abcdef'

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
ma_print:
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
ma_strlen:
	xor	rax, rax
	dec	rax
.count:
	inc	rax
	cmp 	[rdi+rax], byte 0
	jne	.count
	ret	

; Convert an unsigned hex integer to ASCII
;
; Parameters:
;	rdi	- memory address to write to
;	rsi	- hex integer
;	rdx	- number of bytes to write
;	(more than 8 results in additional padding with '0')
;
; Returns:
;	rax 	- number of bytes written
ma_toa:
	push	rdx
	cmp	rdx, 0
	jne	.write
	pop	rax
	ret
.write:
	dec	rdx
	mov	rcx, rsi
	and	rcx, 0xf
	lea	rax, [toa_charset]
	add	rax, rcx
	mov	cl, [rax]
	mov	[rdi + rdx], cl
	shr	rsi, 4
	cmp	rdx, 0
	jne	.write

	pop	rax
	sub	rax, rdx
	ret