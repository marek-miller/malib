%include "malib_int.inc"
%define MALIB_API
global		ma_clock
global		ma_print
global		ma_strlen
global		ma_toa
global		ma_xorshift64

%include "malib.inc"
%include "syscalls.inc"

SECTION .data

SECTION .bss

SECTION .text

ma_clock:
	sub	rsp, 16

	mov	rax, SYS_CLOCK_GETTIME
	mov	rdi, 3			; CLOCK_THREAD_CPUTIME_ID
	lea	rsi, -16[rsp]		; struct timespec *tp
	syscall

	mov	rax, -16[rsp]		; seconds
	mov	rcx, 1000000000
	mul	rcx
	add	rax, -8[rsp]		; nanos

.rt:	add	rsp, 16
	ret

ma_print:
	push	rdi			; calculate string length
	mov	rdi, rsi
	call	ma_strlen		; we know that rsi is preserved here
	pop	rdi

	mov	rdx, rax		; rax = string length
	push	rax
	mov	rax, SYS_WRITE
	syscall

.rt:	pop	rax
	ret


ma_strlen:
	xor	rax, rax
	mov	rcx, -1			; set the counter to max value,
	repne 	scasb			;  repeat until \0 character found
	add	rcx, 2			; rcx = -#steps-2

.rt:	sub	rax, rcx
	ret


ma_toa:
	push	rdx
	or	rdx, rdx
	jz	.rt

	mov	 r8, '01234567'		; lookup table
	mov	 r9, '89abcdef'

	xor	rax, rax		; check if rdx is greater than 16
	mov	al, '0'			; for larger values we print zeros
.l0:	cmp	rdx, 16
	jbe	.l1
	stosb
	dec	rdx
	jmp	.l0

.l1:	mov	rcx, rdx		; rotate rsi, each digit is 4 bits
	shl	 cl, 2
	ror	rsi, cl

.l2:	rol	rsi, 4
	mov	rcx, rsi
	and	 cl, 0x0f		; extract digit, we don'n need it to
	mov	rax, r8			;  clear it from rsi since rdx < 16
	cmp	 cl, 8			; if the digit is greater than 8,
	cmovge	rax, r9			;  we use 2nd half of the lookup table
	and	 cl, 0xf7		;  and subtract 8
	shl	 cl, 3			; each ascii sign is 8 bits
	shr	rax, cl
	stosb
	dec	rdx
	jnz	.l2

.rt:	pop	rax
	ret


ma_xorshift64:
	mov	rax, [rdi]
	mov	rdx, rax
	shl	rax, 13
	xor	rax, rdx
	mov	rdx, rax
	shr	rax, 7
	xor	rax, rdx
	mov	rdx, rax
	shl	rax, 17
	xor	rax, rdx
.rt:	mov	[rdi], rax
	ret
