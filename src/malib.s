%include "malib_int.inc"
%define MALIB_API
global		ma_print
global		ma_strlen
global		ma_toa

%include "malib.inc"
%include "syscalls.inc"

SECTION .data

SECTION .bss

SECTION .text

ma_print:
	push	rdi			; calculate string length
	mov	rdi, rsi
	call	ma_strlen		; we know that rsi is preserved here
	pop	rdi

.l1:	mov	rdx, rax		; rax = string length
	push	rax
	mov	rax, SYS_WRITE
	syscall

.rt:	pop	rax
	ret


ma_strlen:
	xor	rax, rax
	mov	rcx, -1			; set the counter to max value
	repne 	scasb			; repeat until \0 character found
	add	rcx, 2			; rcx = -#steps-2

.rt:	sub	rax, rcx
	ret	


ma_toa:
	push	rdx
	or	rdx, rdx
	jz	.rt

	mov	 r8, '89abcdef'		; lookup table, little endian

	mov	rcx, rdx		; rotate rsi, each digit is 4 bits
	shl	 cl, 2
	ror	rsi, cl

.l1:	rol	rsi, 4
	mov	rcx, rsi
	and	 cl,  0x0f		; extract and clear digit, so it won't
	and	rsi, -0x10		;   reappear after full lap of rol's
	mov	rax, '01234567'
	cmp	 cl, 8			; if the digit is greater than 8,
	cmovge	rax, r8			;   we use 2nd half of the lookup table
	;and	 cl, 0xf7		;   and subtract 8
	sub	cl, 8
	shl	 cl, 3			; each ascii sign is 8 bits
	shr	rax, cl
	stosb
	dec	rdx
	jnz	.l1

.rt:	pop	rax
	ret
