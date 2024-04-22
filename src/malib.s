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
	push	rsi
	mov	rdi, rsi
	call	ma_strlen
	pop	rsi
	pop	rdi

	mov	rdx, rax
	push	rax
	mov	rax, SYS_WRITE
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
	mov	rcx, -1
	cld
	repne 	scasb
	add	rcx, 2
	sub	rax, rcx
	ret	

; Convert an unsigned hex integer to ASCII
;
; Parameters:
;	rdi	- memory address to write to
;	rsi	- hex integer
;	rdx	- number of bytes to write (more than 8
;		  will result in additional padding with '0')
;
; Returns:
;	rax 	- number of bytes written
ma_toa:
	or	rdx, rdx
	jz	.rt

	mov	rcx, rdx
	add	rdi, rdx
	dec	rdi
	push	rdx

	lea	rdx, [toa_charset]
	mov	rax, rsi
	std
.lp:
	mov	rsi, rax
	and	rsi, 0xf
	add	rsi, rdx
	movsb
	shr	rax, 4
	loop	.lp
	
	cld
	pop	rdx
.rt:
	mov	rax, rdx
	ret
