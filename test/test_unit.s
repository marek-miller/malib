%include "malib_int.inc"
%include "malib.inc"
%include "syscalls.inc"

global _start

SECTION .data

TEST_RT		db	EXIT_SUCCESS		; test return value
TEST_FAILMSG	db	"FAIL ", __?FILE?__, ":0x____", 0xa, 0
TEST_FAILOFF	equ	$-6			; placeholder for line number

str01		db	0
str02		db	"This is a test", 0

SECTION .bss

SECTION .text

_start:
	call	test_strlen

_exit:
	mov	rax, SYS_EXIT
	lea	rsi, [TEST_RT]
	mov	rdi, [rsi]
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
	lea	rdi, [TEST_RT]
        mov	[rdi], byte EXIT_FAILURE
	ret

test_strlen:
	; check if ma_strlen returns correct length
%macro case_strlen 2
	lea	rdi, [%1]
	call	ma_strlen
	cmp	rax, %2
	je	%%.rt
	mov	rdi, %2
	call	_test_fail
%%.rt:
%endmacro

	case_strlen str01, 0x0000
	case_strlen str02, 0x000e

	ret

