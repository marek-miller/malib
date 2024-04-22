%define MALIB_API
global ma_print, ma_strlen, ma_toa

%include "malib.inc"
%include "malib_int.inc"
%include "syscalls.inc"

SECTION .data

toa_chset	db	'0123456789abcdef'

SECTION .bss

SECTION .text

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

ma_strlen:
	xor	rax, rax
	mov	rcx, -1			; set the counter to max value
	cld
	repne 	scasb			; repeat until \0 character found
	add	rcx, 2			; rcx = -#steps-2
	 				; (last iteration decremented it too)
	sub	rax, rcx
	ret	

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
