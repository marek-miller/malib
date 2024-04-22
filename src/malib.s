default rel

%include "malib.inc"
%include "syscalls.inc"

global ma_print, ma_strlen, ma_toa

SECTION .data

toa_chset	db	'0123456789abcdef'

SECTION .bss

SECTION .text

; Print a null-terminated string to file destriptor.
;
; Parameters:
;	rdi	- file destriptor, e.g. MA_STDOUT
;	rsi	- string address
; Returns:
;	rax	- number of characters written
;
ma_print:
	push	rdi			; calculate string length
	push	rsi			; ma_srlnen need not preserve rdi/rsi
	mov	rdi, rsi
	call	ma_strlen
	pop	rsi
	pop	rdi

	mov	rdx, rax		; rax = string length
	push	rax
	mov	rax, SYS_WRITE
	syscall
	pop	rax
	ret

; Calculate the length of a null-terminated string.
; 
; Parameters:
; 	rdi	- address of the string
; Returns:
;	rax	- number of characters in the string
;
ma_strlen:
	xor	rax, rax
	mov	rcx, -1			; set the counter to max value
	cld
	repne 	scasb			; repeat until \0 character found
	add	rcx, 2			; rcx = -#steps-2
	 				; (last iteration decremented in too)
	sub	rax, rcx
	ret	

; Convert an unsigned hex integer to ASCII
;
; Parameters:
;	rdi	- memory address to write to
;	rsi	- hex integer
;	rdx	- number of bytes to write (more than 8
;		  will result in additional padding with '0')
; Returns:
;	rax 	- number of bytes written
;
ma_toa:
	push	rdx			; if num_bytes is zero, return
	or	rdx, rdx
	jz	.rt

	mov	rcx, rdx		; rearrange function params:
	add	rdi, rdx		; rcx - num_bytes
	dec	rdi			; rdi - end of buffer
	lea	rdx, [toa_chset]	; rdx - charset lookup table
	mov	rax, rsi		; rax - hex integer to convert
	std				; loop in reverse order, clear DF later
.lp:
	mov	rsi, rax		; get the least signifcant digit
	and	rsi, 0xf		;
	add	rsi, rdx		; look its symbol up in the charset
	movsb				;
	shr	rax, 4			; get next digit
	loop	.lp
	cld
.rt:
	pop	rax
	ret
