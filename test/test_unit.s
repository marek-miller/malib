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

%macro case_strlen 2
	push 	rax
	mov	rdi, %1
	call	ma_strlen

	mov	rdx, %2
	cmp	rax, rdx
	je	%%end
	mov	qword [rsp], test_fail
%%end:	pop	rax
%endmacro

	case_strlen str01, str01_len
	case_strlen str02, str02_len

	ret

