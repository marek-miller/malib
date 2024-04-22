default rel

%include "malib.inc"
%include "syscalls.inc"

global _start

test_fail		equ	EXIT_FAILURE

SECTION .data

str01		db	0
str01_len 	equ	0
str02		db	"This is a test", 0
str02_len	equ	$-str02 -1

SECTION .bss

str03_len	equ	1024*1024
str03		resb	str03_len+1

SECTION .text
	extern ma_strlen, ma_printstr

_start:
	mov	rax, EXIT_SUCCESS
	call	test_strlen

_exit:
	push	rax
	mov	rax, SYS_EXIT
	pop	rdi
	syscall

test_strlen:
	; initiate str03
	lea	rdi, [str03]
	xor	rcx, rcx
.set_str:
	mov	[rdi + rcx], byte 'A'
	inc	rcx
	cmp	rcx, str03_len
	jne	.set_str
	mov	[rdi + rcx], byte 0

	; check if ma_strlen returns correct length
%macro case_strlen 2
	push 	rax
	lea	rdi, [%1]
	call	ma_strlen

	mov	rdx, %2
	cmp	rax, rdx
	je	%%.rt
	mov	qword [rsp], test_fail
%%.rt:	pop	rax
%endmacro

	case_strlen str01, str01_len
	case_strlen str02, str02_len
	case_strlen str03, str03_len

	ret

