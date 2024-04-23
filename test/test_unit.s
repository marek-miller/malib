%include "malib_int.inc"
%include "malib.inc"
%include "syscalls.inc"

global _start

SECTION .data

TEST_RT		db	EXIT_SUCCESS		; test return value

TEST_FAILMSG	db	"FAIL ", __?FILE?__, ":0x____", 0xa, 0
TEST_FAILOFF	equ	$-6			; placeholder for a tag

str01		db	0
str02		db	"This is a test", 0
str03		db	"This is also", 0, "a test", 0

toa_buf		db	"________________"
toa_int		dq	0x1234, 0x333, 0x1, 0x7777
toa_len		dq	4, 3, 8, 0
toa_exp		db	"1234____", "333_____", "00000001", "________"

SECTION .bss

SECTION .text

_start:
	call	test_strlen
	call	test_toa

_exit:
	mov	rax, SYS_EXIT
	mov	rdi, [TEST_RT]
	syscall

; Print debugging info and set global return value to EXIT_FAILURE.
_test_fail:
	mov	rsi, rdi
	mov	rdx, 4
	lea	rdi, [TEST_FAILOFF]
	call	ma_toa
	mov	rdi, STDERR
	lea	rsi, [TEST_FAILMSG]
	call	ma_print
        mov	[TEST_RT], byte EXIT_FAILURE
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
	case_strlen	str01, 0x00, __?LINE?__
	case_strlen	str02, 0x0e, __?LINE?__
	case_strlen	str03, 0x0c, __?LINE?__

	ret

test_toa:
	lea 	rdi, [toa_buf]

%macro case_toa 2
	; clear the buffer
	mov	rax,  '________'
	mov	qword [rdi], rax
	; call ma_toa
	push	rdi
	mov	rsi, qword [toa_int + 8*%1]
	mov	rdx, qword [toa_len + 8*%1]
	call	ma_toa
	pop	rdi
	; compare result
	mov	rax, [toa_exp + 8*%1]
	cmp	[rdi], rax
	jz	%%.rt
	push	rdi
	mov	rdi, %2
	call	_test_fail
	pop	rdi
%%.rt:
%endmacro

	case_toa	0, __?LINE?__
	case_toa	1, __?LINE?__
	case_toa	2, __?LINE?__
	case_toa	3, __?LINE?__

	ret
