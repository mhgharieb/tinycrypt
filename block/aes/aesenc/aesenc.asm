; Listing generated by Microsoft (R) Optimizing Compiler Version 19.10.25019.0 

	TITLE	C:\hub\aes\aesenc\aesenc.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_gf_mul2
PUBLIC	_sub_byte
PUBLIC	_aesenc
; Function compile flags: /Ogspy
; File c:\hub\aes\aesenc\aesenc.c
;	COMDAT _aesenc
_TEXT	SEGMENT
_v$ = -16						; size = 16
_state$ = 8						; size = 4
_key$ = 12						; size = 4
_last$ = 16						; size = 4
_aesenc	PROC						; COMDAT

; 95   : void aesenc (void *state, void *key, int last) {

	sub	esp, 16					; 00000010H
	push	ebx
	push	ebp

; 96   :     w128_t  *s, *k, v;
; 97   :     uint32_t i, w;
; 98   :     
; 99   :     s=(w128_t*)state;
; 100  :     k=(w128_t*)key;
; 101  : 
; 102  :     // sub bytes and shift rows
; 103  :     for (i=0; i<16; i++) {    

	mov	ebp, DWORD PTR _state$[esp+20]
	xor	ebx, ebx
	push	edi
	mov	edi, ebx
	push	esi
$LL4@aesenc:

; 104  :       v.b[((((i >> 2) + 4 - (i & 3) ) & 3) * 4) + (i & 3)] = sub_byte(s->b[i]);

	movzx	eax, BYTE PTR [edi+ebp]
	mov	esi, edi
	push	eax
	and	esi, 3
	call	_sub_byte
	pop	ecx
	mov	ecx, edi
	shr	ecx, 2
	sub	ecx, esi
	and	ecx, 3
	inc	edi
	lea	ecx, DWORD PTR [esi+ecx*4]
	mov	BYTE PTR _v$[esp+ecx+32], al
	cmp	edi, 16					; 00000010H
	jb	SHORT $LL4@aesenc

; 105  :     }
; 106  :     
; 107  :     // if not last round
; 108  :     if (!last) {

	cmp	DWORD PTR _last$[esp+28], ebx
	jne	SHORT $LN6@aesenc

; 109  :       // mix columns
; 110  :       for (i=0; i<4; i++) {

	mov	ebp, ebx
$LL7@aesenc:

; 111  :         w = v.w[i];

	mov	esi, DWORD PTR _v$[esp+ebp*4+32]

; 112  :         v.w[i] = ROTR32(w,  8) ^ 

	mov	edi, esi
	ror	edi, 8
	mov	eax, edi
	xor	eax, esi
	push	eax
	call	_gf_mul2
	pop	ecx
	mov	ecx, esi
	rol	esi, 8
	rol	ecx, 16					; 00000010H
	xor	eax, ecx
	xor	eax, esi
	xor	eax, edi
	mov	DWORD PTR _v$[esp+ebp*4+32], eax
	inc	ebp
	cmp	ebp, 4
	jb	SHORT $LL7@aesenc
	mov	ebp, DWORD PTR _state$[esp+28]
$LN6@aesenc:

; 113  :                  ROTR32(w, 16) ^ 
; 114  :                  ROTL32(w,  8) ^ 
; 115  :                  gf_mul2(ROTR32(w, 8) ^ w);
; 116  :       }
; 117  :     }
; 118  :     // add round key
; 119  :     for (i=0; i<4; i++) {

	mov	edx, DWORD PTR _key$[esp+28]
	lea	eax, DWORD PTR _v$[esp+32]
	sub	edx, eax
	sub	ebp, eax
	pop	esi
$LL10@aesenc:
	lea	eax, DWORD PTR [edx+ebx*4]

; 120  :       s->w[i] = v.w[i] ^ k->w[i];

	mov	ecx, DWORD PTR _v$[esp+eax+28]
	lea	eax, DWORD PTR [ebx*4]
	xor	ecx, DWORD PTR _v$[esp+ebx*4+28]
	add	eax, ebp
	inc	ebx
	mov	DWORD PTR _v$[esp+eax+28], ecx
	cmp	ebx, 4
	jb	SHORT $LL10@aesenc
	pop	edi
	pop	ebp
	pop	ebx

; 121  :     }
; 122  : }

	add	esp, 16					; 00000010H
	ret	0
_aesenc	ENDP
_TEXT	ENDS
; Function compile flags: /Ogspy
; File c:\hub\aes\aesenc\aesenc.c
;	COMDAT _sub_byte
_TEXT	SEGMENT
_x$ = 8							; size = 1
_y$1$ = 11						; size = 1
_sub_byte PROC						; COMDAT

; 70   : {

	push	ebp
	mov	ebp, esp
	push	ebx

; 71   :     uint8_t i, y=x, sb;

	mov	bl, BYTE PTR _x$[ebp]

; 72   : 
; 73   :     if (x) {

	test	bl, bl
	je	SHORT $LN6@sub_byte

; 74   :       // calculate logarithm gen 3
; 75   :       for (i=1, y=1; i != 0; i++) {

	mov	bh, 1
	mov	cl, bh
	mov	BYTE PTR _y$1$[ebp], cl
$LL4@sub_byte:

; 76   :         y ^= gf_mul2(y);

	movzx	eax, cl
	push	eax
	call	_gf_mul2
	pop	ecx
	mov	cl, BYTE PTR _y$1$[ebp]
	xor	cl, al
	mov	BYTE PTR _y$1$[ebp], cl

; 77   :         if (y == x) break;

	cmp	cl, bl
	je	SHORT $LN17@sub_byte

; 74   :       // calculate logarithm gen 3
; 75   :       for (i=1, y=1; i != 0; i++) {

	add	bh, 1
	jne	SHORT $LL4@sub_byte
$LN17@sub_byte:

; 78   :       }
; 79   :       x = ~i;

	not	bh

; 80   :       // calculate anti-logarithm gen 3
; 81   :       for (i=0, y=1; i<x; i++) {

	mov	bl, 1
	test	bh, bh
	je	SHORT $LN6@sub_byte

; 78   :       }
; 79   :       x = ~i;

	push	esi
	movzx	esi, bh
$LL7@sub_byte:

; 82   :         y ^= gf_mul2(y);

	movzx	eax, bl
	push	eax
	call	_gf_mul2
	xor	bl, al
	pop	ecx
	sub	esi, 1
	jne	SHORT $LL7@sub_byte
	pop	esi
$LN6@sub_byte:

; 83   :       }
; 84   :     }
; 85   : 
; 86   :     sb = y;

	push	4
	mov	al, bl
	pop	ecx
$LL10@sub_byte:

; 87   :     
; 88   :     for (i=0; i<4; i++) {
; 89   :       y   = ROTL8(y, 1);

	rol	bl, 1

; 90   :       sb ^= y;

	xor	al, bl
	sub	ecx, 1
	jne	SHORT $LL10@sub_byte

; 91   :     }
; 92   :     return sb ^ 0x63;

	xor	al, 99					; 00000063H
	pop	ebx

; 93   : }

	pop	ebp
	ret	0
_sub_byte ENDP
_TEXT	ENDS
; Function compile flags: /Ogspy
; File c:\hub\aes\aesenc\aesenc.c
;	COMDAT _gf_mul2
_TEXT	SEGMENT
_w$ = 8							; size = 4
_gf_mul2 PROC						; COMDAT

; 62   :     uint32_t t = w & 0x80808080;

	mov	ecx, DWORD PTR _w$[esp-4]
	and	ecx, -2139062144			; 80808080H

; 63   :     
; 64   :     return ( (w ^ t ) << 1) ^ ( ( t >> 7) * 0x0000001B);

	mov	eax, ecx
	shr	ecx, 7
	xor	eax, DWORD PTR _w$[esp-4]
	imul	ecx, ecx, 27
	add	eax, eax
	xor	eax, ecx

; 65   : }

	ret	0
_gf_mul2 ENDP
_TEXT	ENDS
END
