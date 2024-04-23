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
	push	rsi			; ma_srlnen need not preserve rdi/rsi
	mov	rdi, rsi
	call	ma_strlen
	pop	rsi
	pop	rdi

	mov	rdx, rax		; rax = string length
	push	rax
	mov	rax, SYS_WRITE
	syscall

.rt:	pop	rax
	ret

ma_strlen:
	xor	rax, rax
	mov	rcx, -1			; set the counter to max value
	cld
	repne 	scasb			; repeat until \0 character found
	add	rcx, 2			; rcx = -#steps-2

.rt:	sub	rax, rcx
	ret	

ma_toa:
	push	rdx
	or	rdx, rdx
	jz	.rt
	add	rdi, rdx
	dec	rdi			; rdi - end of buffer

	std
.lp:	mov	rax, '01234567'		; little endian
	mov	rcx, rsi
	and	cl, 0x0f
	cmp	cl, 8
	jl	.l1
	mov	rax, '89abcdef'
	sub	cl, 8
.l1:	shl	cl, 3
	shr	rax, cl
	stosb
	shr	rsi, 4			; get next digit
	dec	rdx
	jnz	.lp
	cld

.rt:	pop	rax
	ret
