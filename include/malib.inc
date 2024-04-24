%ifndef MALIB_API
%define MALIB_API

; Print a null-terminated string to file destriptor.
;
; Parameters:
;	rdi	- file destriptor, e.g. STDOUT, STDERR
;	rsi	- string address
; Returns:
;	rax	- number of characters written
;
extern ma_print


; Calculate the length of a null-terminated string.
;
; Parameters:
; 	rdi	- address of the string
; Returns:
;	rax	- number of characters in the string
;
extern ma_strlen


; Convert an unsigned hex integer to ASCII.
;
; Parameters:
;	rdi	- memory address to write to
;	rsi	- hex integer
;	rdx	- number of bytes to write (more than 8
;		  will result in additional padding on the left with '0')
; Returns:
;	rax 	- number of bytes written
;
extern ma_toa


; Xorshift PRNG by G.Marsaglia.
;
; Marsaglia, G., Xorshift RNGs.
; Journal of Statistical Software, 8(14), 1–6 (2003).
; https://doi.org/10.18637/jss.v008.i14
;
; Parameters:
;	rdi	- pointer to state (nonzero qword)
; Returns:
;	rax	- pseudorandom 64 bit unsigned integer
; Notes:
;  The function updates the state (qword), address of which is preserved in rdi.
extern ma_xorshift64

%endif ; MALIB_API

%ifndef MALIB_CONSTS
%define MALIB_CONSTS

%define	EXIT_SUCCESS	0
%define	EXIT_FAILURE	255

%define	STDIN		0
%define	STDOUT		1
%define	STDERR		2

%endif ; MALIB_CONSTS
