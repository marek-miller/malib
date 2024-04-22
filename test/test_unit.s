%include "malib_int.inc"
%include "malib.inc"
%include "syscalls.inc"

global _start

SECTION .data

TEST_RT		db	EXIT_SUCCESS		; test return value
TEST_FAILMSG	db	"FAIL ", __FILE__, ":0x____", 0xa, 0
TEST_FAILOFF	equ	$-6			; placeholder for line number

str01		db	0
str01_len 	equ	0
str02		db	"This is a test", 0
str02_len	equ	$-str02 -1

SECTION .bss

str03_len	equ	1024*1024
str03		resb	str03_len+1

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
        mov	[rdi], dword EXIT_FAILURE
	ret

test_strlen:
	; check if ma_strlen returns correct length
%macro case_strlen 2
	lea	rdi, [%1]
	call	ma_strlen
	mov	rdx, %2
	cmp	rax, rdx
	je	%%.rt
	mov	rdi, __LINE__
	call	_test_fail
%%.rt:
%endmacro

	case_strlen str01, str01_len
	case_strlen str02, str02_len

	; initiate str03
        	lea	rdi, [str03]
        	xor	rcx, rcx
        .set_str:
        	mov	[rdi + rcx], byte 'A'
        	inc	rcx
        	cmp	rcx, str03_len
        	jne	.set_str
        	mov	[rdi + rcx], byte 0

	case_strlen str03, str03_len

	ret

