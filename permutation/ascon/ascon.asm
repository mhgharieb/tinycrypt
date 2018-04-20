; Listing generated by Microsoft (R) Optimizing Compiler Version 19.10.25019.0 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	ascon_permute
;	COMDAT pdata
pdata	SEGMENT
$pdata$ascon_permute DD imagerel $LN11
	DD	imagerel $LN11+317
	DD	imagerel $unwind$ascon_permute
pdata	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$ascon_permute DD 0a1701H
	DD	067417H
	DD	056417H
	DD	045417H
	DD	033417H
	DD	0e015f017H
xdata	ENDS
; Function compile flags: /Ogspy
; File c:\hub\tinycrypt\permutation\ascon\ascon.c
;	COMDAT ascon_permute
_TEXT	SEGMENT
state$ = 24
rnds$ = 32
ascon_permute PROC					; COMDAT

; 9    : void ascon_permute(void *state, int rnds) {

$LN11:
	mov	rax, rsp
	mov	QWORD PTR [rax+8], rbx
	mov	QWORD PTR [rax+16], rbp
	mov	QWORD PTR [rax+24], rsi
	mov	QWORD PTR [rax+32], rdi
	push	r14
	push	r15

; 10   :     int      i;
; 11   :     uint64_t x0, x1, x2, x3, x4;
; 12   :     uint64_t t0, t1, t2, t3, t4;
; 13   :     
; 14   :     uint64_t *x=(uint64_t*)state;
; 15   :     
; 16   :     // load 320-bit state
; 17   :     x0 = x[0]; x1 = x[1];

	mov	rbx, QWORD PTR [rcx]

; 18   :     x2 = x[2]; x3 = x[3];
; 19   :     x4 = x[4];
; 20   : 
; 21   :     for (i=0; i<rnds; i++) {

	xor	r10d, r10d
	mov	rsi, QWORD PTR [rcx+8]
	mov	r9, rcx
	mov	r11, QWORD PTR [rcx+16]
	mov	rbp, QWORD PTR [rcx+24]
	mov	rdi, QWORD PTR [rcx+32]
	test	edx, edx
	jle	$LN3@ascon_perm

; 10   :     int      i;
; 11   :     uint64_t x0, x1, x2, x3, x4;
; 12   :     uint64_t t0, t1, t2, t3, t4;
; 13   :     
; 14   :     uint64_t *x=(uint64_t*)state;
; 15   :     
; 16   :     // load 320-bit state
; 17   :     x0 = x[0]; x1 = x[1];

	mov	r14d, r10d
	mov	r15d, edx
$LL4@ascon_perm:

; 22   :       // addition of round constant
; 23   :       x2 ^= ((0xfull - i) << 4) | i;
; 24   : 
; 25   :       // substitution layer
; 26   :       x0 ^= x4;    x4 ^= x3;    x2 ^= x1;

	xor	rbx, rdi
	mov	eax, 240				; 000000f0H
	sub	rax, r14
	xor	rdi, rbp
	or	rax, r10

; 27   :       t0  = x0;    t1  = x1;    t2  = x2;    t3  =  x3;    t4  = x4;
; 28   :       t0  = ~t0;   t1  = ~t1;   t2  = ~t2;   t3  = ~t3;    t4  = ~t4;

	mov	r8, rbx
	xor	r11, rax
	mov	rdx, rdi
	xor	r11, rsi
	mov	rax, rsi
	not	rax
	mov	rcx, r11

; 29   :       t0 &= x1;    t1 &= x2;    t2 &= x3;    t3 &=  x4;    t4 &= x0;

	and	rax, r11
	not	rcx
	and	rcx, rbp
	not	rdx
	and	rdx, rbx
	not	r8

; 30   :       x0 ^= t1;    x1 ^= t2;    x2 ^= t3;    x3 ^=  t4;    x4 ^= t0;

	xor	rbx, rax
	and	r8, rsi

; 31   :       x1 ^= x0;    x0 ^= x4;    x3 ^= x2;    x2  = ~x2;

	xor	rsi, rcx
	mov	rax, rbp
	not	rax
	xor	rsi, rbx
	and	rax, rdi
	xor	rbp, rdx
	xor	r11, rax
	xor	rdi, r8
	xor	rbp, r11
	xor	rbx, rdi
	not	r11

; 32   : 
; 33   :       // linear diffusion layer
; 34   :       x0 ^= ROTR(x0, 19) ^ ROTR(x0, 28);

	mov	rcx, rbx
	ror	rcx, 28
	mov	rax, rbx
	ror	rax, 19
	inc	r10
	xor	rcx, rax
	add	r14, 16
	xor	rbx, rcx

; 35   :       x1 ^= ROTR(x1, 61) ^ ROTR(x1, 39);

	mov	rax, rsi
	rol	rax, 3
	mov	rcx, rsi
	rol	rcx, 25
	xor	rcx, rax

; 36   :       x2 ^= ROTR(x2,  1) ^ ROTR(x2,  6);

	mov	rax, r11
	xor	rsi, rcx
	ror	rax, 1
	mov	rcx, r11
	ror	rcx, 6
	xor	rcx, rax

; 37   :       x3 ^= ROTR(x3, 10) ^ ROTR(x3, 17);

	mov	rax, rbp
	xor	r11, rcx
	ror	rax, 10
	mov	rcx, rbp
	ror	rcx, 17
	xor	rcx, rax

; 38   :       x4 ^= ROTR(x4,  7) ^ ROTR(x4, 41);

	mov	rax, rdi
	xor	rbp, rcx
	ror	rax, 7
	mov	rcx, rdi
	rol	rcx, 23
	xor	rcx, rax
	xor	rdi, rcx
	sub	r15, 1
	jne	$LL4@ascon_perm
$LN3@ascon_perm:

; 39   : 
; 40   :     }
; 41   :     // save 320-bit state
; 42   :     x[0] = x0; x[1] = x1;

	mov	QWORD PTR [r9], rbx

; 43   :     x[2] = x2; x[3] = x3;
; 44   :     x[4] = x4;
; 45   : }

	mov	rbx, QWORD PTR [rsp+24]
	mov	QWORD PTR [r9+8], rsi
	mov	rsi, QWORD PTR [rsp+40]
	mov	QWORD PTR [r9+24], rbp
	mov	rbp, QWORD PTR [rsp+32]
	mov	QWORD PTR [r9+32], rdi
	mov	rdi, QWORD PTR [rsp+48]
	mov	QWORD PTR [r9+16], r11
	pop	r15
	pop	r14
	ret	0
ascon_permute ENDP
_TEXT	ENDS
END
