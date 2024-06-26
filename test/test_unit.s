%include "malib_int.inc"
%include "malib.inc"
%include "syscalls.inc"

global _start

SECTION .data

TEST_RT		db	EXIT_SUCCESS	; test return value
TEST_FAILMSG	db	"FAIL ", __?FILE?__, ":0x____", 0xa, 0
TEST_FAILOFF	equ	$-6		; placeholder for a tag

str01		db	0
str02		db	"This is a test", 0
str03		db	"This is also", 0, "a test", 0

align 8
toa_buf		db	"________________", "__"
align 8
toa_int		dq	0x333, 0x1, 0x7777, 0xababe, 0x1a2bc9, 0x1234
toa_len		dq	3, 9, 0, 5, 6, 18
toa_exp		db	"333_____________", "000000001_______", \
			"________________", "ababe___________", \
			"1a2bc9__________", "0000000000000012"

SECTION .bss

SECTION .text

_start:
	call	test_clock
	call	test_strlen
	call	test_toa
	call	test_xorshift64

_exit:
	mov	rax, SYS_EXIT
	mov	rdi, [TEST_RT]
	syscall

; Print debugging info and set global return value to EXIT_FAILURE.
;
; Parameters:
;	rdi	- tag to print
; Returns
;	rax	- EXIT_FAILURE
_test_fail:
	mov	rsi, rdi
	mov	rdx, 4
	lea	rdi, [TEST_FAILOFF]
	call	ma_toa
	mov	rdi, STDERR
	lea	rsi, [TEST_FAILMSG]
	call	ma_print
        mov	rax, EXIT_FAILURE
        mov	[TEST_RT], al
	ret

test_clock:
%define STEPS 64
	push	r12
	push	rbp
	mov	rbp, rsp
	sub	rsp, 8*STEPS

	; populate an array with STEPS calls to ma_clock
	mov	r12, rsp
.l1:	call	ma_clock
	mov	[r12], rax
	add	r12, 8
	cmp	r12, rbp
	jne	.l1

	; check if results increose monotonously
	mov	rcx, STEPS
.l2:	dec	rcx
	jz	.rt
	lea	rdi, 8[rsp]
	lea	rsi, [rsp]
	cmpsq
	jb	.l2
.fail:	lea	rdi, [rcx + 0x0700]
	call	_test_fail

.rt:	mov	rsp, rbp
	pop	rbp
	pop	r12
	ret


test_strlen:
%macro case_strlen 3
	lea	rdi, [%1]
	call	ma_strlen
	cmp	rax, %2
	je	%%.rt
	mov	rdi, %3
	call	_test_fail
%%.rt:
%endmacro

	case_strlen	str01, 0x00, 0x0000
	case_strlen	str02, 0x0e, 0x0001
	case_strlen	str03, 0x0c, 0x0002

	ret


test_toa:
	lea 	rdi, [toa_buf]

%macro case_toa 2
	mov	rax,  '________'	; clear the buffer
	mov	[rdi], rax
	mov	8[rdi], rax

	push	rdi			; call ma_toa
	mov	rsi, 8*%1[toa_int]
	mov	rdx, 8*%1[toa_len]
	call	ma_toa
	pop	rdi

	; compare result (16 digits)
	mov	rax, 16*%1[toa_exp]
	cmp	[rdi], rax
	jne	%%.fail
	mov	rax, (16*%1 + 8)[toa_exp]
	cmp	8[rdi], rax
	jne	%%.fail
	jmp	%%.rt
%%.fail:
	push	rdi
	mov	rdi, %2
	call	_test_fail
	pop	rdi
%%.rt:
%endmacro

	case_toa	0, 0x0100
	case_toa	1, 0x0101
	case_toa	2, 0x0102
	case_toa	3, 0x0103
	case_toa	4, 0x0104
	case_toa	5, 0x0105

	ret


test_xorshift64:
	push	r12
	push	r13
	push	rbp
	mov	rbp, rsp
	sub	rsp, 0x08

	mov	qword -8[rbp], 1111	; seed

	lea	r13, -8[rbp]
	mov	r12, 64
.l1:	mov	rdi, r13
	call	ma_xorshift64
	dec	r12
	jnz	.l1

	mov	rdx, 0xc20dae4994e35988	; check the last number generated
	cmp	rax, rdx		; (cmp takes only 32bit immidiates)
	je	.rt
	mov	rdi, 0x0200		; tag
	call	_test_fail

.rt:	mov	rsp, rbp
	pop	rbp
	pop	r13
	pop	r12
	ret
