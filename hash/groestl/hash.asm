; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.40219.01 

	TITLE	C:\odzhan\tinycrypt\hash\groestl\hash.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_sbox
PUBLIC	_mul2
CONST	SEGMENT
_sbox	DB	063H
	DB	07cH
	DB	077H
	DB	07bH
	DB	0f2H
	DB	06bH
	DB	06fH
	DB	0c5H
	DB	030H
	DB	01H
	DB	067H
	DB	02bH
	DB	0feH
	DB	0d7H
	DB	0abH
	DB	076H
	DB	0caH
	DB	082H
	DB	0c9H
	DB	07dH
	DB	0faH
	DB	059H
	DB	047H
	DB	0f0H
	DB	0adH
	DB	0d4H
	DB	0a2H
	DB	0afH
	DB	09cH
	DB	0a4H
	DB	072H
	DB	0c0H
	DB	0b7H
	DB	0fdH
	DB	093H
	DB	026H
	DB	036H
	DB	03fH
	DB	0f7H
	DB	0ccH
	DB	034H
	DB	0a5H
	DB	0e5H
	DB	0f1H
	DB	071H
	DB	0d8H
	DB	031H
	DB	015H
	DB	04H
	DB	0c7H
	DB	023H
	DB	0c3H
	DB	018H
	DB	096H
	DB	05H
	DB	09aH
	DB	07H
	DB	012H
	DB	080H
	DB	0e2H
	DB	0ebH
	DB	027H
	DB	0b2H
	DB	075H
	DB	09H
	DB	083H
	DB	02cH
	DB	01aH
	DB	01bH
	DB	06eH
	DB	05aH
	DB	0a0H
	DB	052H
	DB	03bH
	DB	0d6H
	DB	0b3H
	DB	029H
	DB	0e3H
	DB	02fH
	DB	084H
	DB	053H
	DB	0d1H
	DB	00H
	DB	0edH
	DB	020H
	DB	0fcH
	DB	0b1H
	DB	05bH
	DB	06aH
	DB	0cbH
	DB	0beH
	DB	039H
	DB	04aH
	DB	04cH
	DB	058H
	DB	0cfH
	DB	0d0H
	DB	0efH
	DB	0aaH
	DB	0fbH
	DB	043H
	DB	04dH
	DB	033H
	DB	085H
	DB	045H
	DB	0f9H
	DB	02H
	DB	07fH
	DB	050H
	DB	03cH
	DB	09fH
	DB	0a8H
	DB	051H
	DB	0a3H
	DB	040H
	DB	08fH
	DB	092H
	DB	09dH
	DB	038H
	DB	0f5H
	DB	0bcH
	DB	0b6H
	DB	0daH
	DB	021H
	DB	010H
	DB	0ffH
	DB	0f3H
	DB	0d2H
	DB	0cdH
	DB	0cH
	DB	013H
	DB	0ecH
	DB	05fH
	DB	097H
	DB	044H
	DB	017H
	DB	0c4H
	DB	0a7H
	DB	07eH
	DB	03dH
	DB	064H
	DB	05dH
	DB	019H
	DB	073H
	DB	060H
	DB	081H
	DB	04fH
	DB	0dcH
	DB	022H
	DB	02aH
	DB	090H
	DB	088H
	DB	046H
	DB	0eeH
	DB	0b8H
	DB	014H
	DB	0deH
	DB	05eH
	DB	0bH
	DB	0dbH
	DB	0e0H
	DB	032H
	DB	03aH
	DB	0aH
	DB	049H
	DB	06H
	DB	024H
	DB	05cH
	DB	0c2H
	DB	0d3H
	DB	0acH
	DB	062H
	DB	091H
	DB	095H
	DB	0e4H
	DB	079H
	DB	0e7H
	DB	0c8H
	DB	037H
	DB	06dH
	DB	08dH
	DB	0d5H
	DB	04eH
	DB	0a9H
	DB	06cH
	DB	056H
	DB	0f4H
	DB	0eaH
	DB	065H
	DB	07aH
	DB	0aeH
	DB	08H
	DB	0baH
	DB	078H
	DB	025H
	DB	02eH
	DB	01cH
	DB	0a6H
	DB	0b4H
	DB	0c6H
	DB	0e8H
	DB	0ddH
	DB	074H
	DB	01fH
	DB	04bH
	DB	0bdH
	DB	08bH
	DB	08aH
	DB	070H
	DB	03eH
	DB	0b5H
	DB	066H
	DB	048H
	DB	03H
	DB	0f6H
	DB	0eH
	DB	061H
	DB	035H
	DB	057H
	DB	0b9H
	DB	086H
	DB	0c1H
	DB	01dH
	DB	09eH
	DB	0e1H
	DB	0f8H
	DB	098H
	DB	011H
	DB	069H
	DB	0d9H
	DB	08eH
	DB	094H
	DB	09bH
	DB	01eH
	DB	087H
	DB	0e9H
	DB	0ceH
	DB	055H
	DB	028H
	DB	0dfH
	DB	08cH
	DB	0a1H
	DB	089H
	DB	0dH
	DB	0bfH
	DB	0e6H
	DB	042H
	DB	068H
	DB	041H
	DB	099H
	DB	02dH
	DB	0fH
	DB	0b0H
	DB	054H
	DB	0bbH
	DB	016H
_mul2	DB	00H
	DB	02H
	DB	04H
	DB	06H
	DB	08H
	DB	0aH
	DB	0cH
	DB	0eH
	DB	010H
	DB	012H
	DB	014H
	DB	016H
	DB	018H
	DB	01aH
	DB	01cH
	DB	01eH
	DB	020H
	DB	022H
	DB	024H
	DB	026H
	DB	028H
	DB	02aH
	DB	02cH
	DB	02eH
	DB	030H
	DB	032H
	DB	034H
	DB	036H
	DB	038H
	DB	03aH
	DB	03cH
	DB	03eH
	DB	040H
	DB	042H
	DB	044H
	DB	046H
	DB	048H
	DB	04aH
	DB	04cH
	DB	04eH
	DB	050H
	DB	052H
	DB	054H
	DB	056H
	DB	058H
	DB	05aH
	DB	05cH
	DB	05eH
	DB	060H
	DB	062H
	DB	064H
	DB	066H
	DB	068H
	DB	06aH
	DB	06cH
	DB	06eH
	DB	070H
	DB	072H
	DB	074H
	DB	076H
	DB	078H
	DB	07aH
	DB	07cH
	DB	07eH
	DB	080H
	DB	082H
	DB	084H
	DB	086H
	DB	088H
	DB	08aH
	DB	08cH
	DB	08eH
	DB	090H
	DB	092H
	DB	094H
	DB	096H
	DB	098H
	DB	09aH
	DB	09cH
	DB	09eH
	DB	0a0H
	DB	0a2H
	DB	0a4H
	DB	0a6H
	DB	0a8H
	DB	0aaH
	DB	0acH
	DB	0aeH
	DB	0b0H
	DB	0b2H
	DB	0b4H
	DB	0b6H
	DB	0b8H
	DB	0baH
	DB	0bcH
	DB	0beH
	DB	0c0H
	DB	0c2H
	DB	0c4H
	DB	0c6H
	DB	0c8H
	DB	0caH
	DB	0ccH
	DB	0ceH
	DB	0d0H
	DB	0d2H
	DB	0d4H
	DB	0d6H
	DB	0d8H
	DB	0daH
	DB	0dcH
	DB	0deH
	DB	0e0H
	DB	0e2H
	DB	0e4H
	DB	0e6H
	DB	0e8H
	DB	0eaH
	DB	0ecH
	DB	0eeH
	DB	0f0H
	DB	0f2H
	DB	0f4H
	DB	0f6H
	DB	0f8H
	DB	0faH
	DB	0fcH
	DB	0feH
	DB	01bH
	DB	019H
	DB	01fH
	DB	01dH
	DB	013H
	DB	011H
	DB	017H
	DB	015H
	DB	0bH
	DB	09H
	DB	0fH
	DB	0dH
	DB	03H
	DB	01H
	DB	07H
	DB	05H
	DB	03bH
	DB	039H
	DB	03fH
	DB	03dH
	DB	033H
	DB	031H
	DB	037H
	DB	035H
	DB	02bH
	DB	029H
	DB	02fH
	DB	02dH
	DB	023H
	DB	021H
	DB	027H
	DB	025H
	DB	05bH
	DB	059H
	DB	05fH
	DB	05dH
	DB	053H
	DB	051H
	DB	057H
	DB	055H
	DB	04bH
	DB	049H
	DB	04fH
	DB	04dH
	DB	043H
	DB	041H
	DB	047H
	DB	045H
	DB	07bH
	DB	079H
	DB	07fH
	DB	07dH
	DB	073H
	DB	071H
	DB	077H
	DB	075H
	DB	06bH
	DB	069H
	DB	06fH
	DB	06dH
	DB	063H
	DB	061H
	DB	067H
	DB	065H
	DB	09bH
	DB	099H
	DB	09fH
	DB	09dH
	DB	093H
	DB	091H
	DB	097H
	DB	095H
	DB	08bH
	DB	089H
	DB	08fH
	DB	08dH
	DB	083H
	DB	081H
	DB	087H
	DB	085H
	DB	0bbH
	DB	0b9H
	DB	0bfH
	DB	0bdH
	DB	0b3H
	DB	0b1H
	DB	0b7H
	DB	0b5H
	DB	0abH
	DB	0a9H
	DB	0afH
	DB	0adH
	DB	0a3H
	DB	0a1H
	DB	0a7H
	DB	0a5H
	DB	0dbH
	DB	0d9H
	DB	0dfH
	DB	0ddH
	DB	0d3H
	DB	0d1H
	DB	0d7H
	DB	0d5H
	DB	0cbH
	DB	0c9H
	DB	0cfH
	DB	0cdH
	DB	0c3H
	DB	0c1H
	DB	0c7H
	DB	0c5H
	DB	0fbH
	DB	0f9H
	DB	0ffH
	DB	0fdH
	DB	0f3H
	DB	0f1H
	DB	0f7H
	DB	0f5H
	DB	0ebH
	DB	0e9H
	DB	0efH
	DB	0edH
	DB	0e3H
	DB	0e1H
	DB	0e7H
	DB	0e5H
CONST	ENDS
PUBLIC	_mix_bytes
; Function compile flags: /Ogspy
;	COMDAT _mix_bytes
_TEXT	SEGMENT
_x2$ = -15						; size = 1
_x1$ = -14						; size = 1
_x7$ = -13						; size = 1
_x6$ = -12						; size = 1
_x5$ = -11						; size = 1
_x4$ = -10						; size = 1
_x3$ = -9						; size = 1
_y0$ = -8						; size = 1
_t3$ = -7						; size = 1
_t1$ = -6						; size = 1
_t5$ = -5						; size = 1
_t4$ = -4						; size = 1
_t2$ = -3						; size = 1
_x0$ = -2						; size = 1
_t0$ = -1						; size = 1
_i0$ = 8						; size = 1
_y3$ = 11						; size = 1
_i1$ = 12						; size = 1
_y6$ = 15						; size = 1
_i2$ = 16						; size = 1
_y4$ = 19						; size = 1
_i3$ = 20						; size = 1
_i4$ = 24						; size = 1
_i5$ = 28						; size = 1
_y7$ = 31						; size = 1
_i6$ = 32						; size = 1
_y1$ = 35						; size = 1
_i7$ = 36						; size = 1
_y2$ = 39						; size = 1
_output$ = 40						; size = 4
_mix_bytes PROC						; COMDAT
; File c:\odzhan\tinycrypt\hash\groestl\hash.c
; Line 56
	push	ebp
	mov	ebp, esp
	sub	esp, 16					; 00000010H
; Line 61
	mov	cl, BYTE PTR _i0$[ebp]
; Line 63
	mov	dl, BYTE PTR _i3$[ebp]
	mov	al, cl
	xor	al, BYTE PTR _i1$[ebp]
; Line 68
	xor	cl, BYTE PTR _i7$[ebp]
	mov	BYTE PTR _t0$[ebp], al
	mov	al, BYTE PTR _i1$[ebp]
	xor	al, BYTE PTR _i2$[ebp]
	push	ebx
	mov	BYTE PTR _t1$[ebp], al
	mov	al, BYTE PTR _i2$[ebp]
	xor	al, dl
	mov	BYTE PTR _t2$[ebp], al
	mov	al, BYTE PTR _i4$[ebp]
	xor	dl, al
	xor	al, BYTE PTR _i5$[ebp]
	mov	BYTE PTR _t3$[ebp], dl
; Line 70
	xor	dl, BYTE PTR _t0$[ebp]
	mov	BYTE PTR _t4$[ebp], al
	mov	al, BYTE PTR _i5$[ebp]
	xor	al, BYTE PTR _i6$[ebp]
	mov	BYTE PTR _x0$[ebp], dl
; Line 71
	mov	dl, BYTE PTR _t4$[ebp]
	xor	dl, BYTE PTR _t1$[ebp]
	mov	BYTE PTR _t5$[ebp], al
	mov	al, BYTE PTR _i6$[ebp]
	xor	al, BYTE PTR _i7$[ebp]
	mov	BYTE PTR _x1$[ebp], dl
; Line 72
	mov	dl, BYTE PTR _t5$[ebp]
	xor	dl, BYTE PTR _t2$[ebp]
; Line 84
	mov	bl, cl
	mov	BYTE PTR _x2$[ebp], dl
	mov	dl, al
	xor	dl, BYTE PTR _t3$[ebp]
	xor	bl, BYTE PTR _t5$[ebp]
	mov	BYTE PTR _x3$[ebp], dl
	mov	dl, cl
	xor	dl, BYTE PTR _t4$[ebp]
	xor	bl, BYTE PTR _i3$[ebp]
	mov	BYTE PTR _x4$[ebp], dl
	mov	dl, BYTE PTR _t5$[ebp]
	xor	dl, BYTE PTR _t0$[ebp]
	mov	BYTE PTR _x5$[ebp], dl
	mov	dl, al
	xor	dl, BYTE PTR _t1$[ebp]
	mov	BYTE PTR _x6$[ebp], dl
	mov	dl, cl
	xor	dl, BYTE PTR _t2$[ebp]
; Line 86
	xor	cl, BYTE PTR _t1$[ebp]
	mov	BYTE PTR _x7$[ebp], dl
	mov	dl, BYTE PTR _t2$[ebp]
	xor	dl, BYTE PTR _t0$[ebp]
	xor	cl, BYTE PTR _i5$[ebp]
	xor	dl, BYTE PTR _i6$[ebp]
	mov	BYTE PTR _y7$[ebp], cl
	mov	BYTE PTR _y0$[ebp], dl
	mov	dl, BYTE PTR _t3$[ebp]
	xor	dl, BYTE PTR _t1$[ebp]
	xor	dl, BYTE PTR _i7$[ebp]
	mov	BYTE PTR _y1$[ebp], dl
	mov	dl, BYTE PTR _t4$[ebp]
	xor	dl, BYTE PTR _t2$[ebp]
	xor	dl, BYTE PTR _i0$[ebp]
	mov	BYTE PTR _y2$[ebp], dl
	mov	dl, BYTE PTR _t5$[ebp]
	xor	dl, BYTE PTR _t3$[ebp]
	xor	dl, BYTE PTR _i1$[ebp]
	mov	BYTE PTR _y3$[ebp], dl
	mov	dl, al
	xor	al, BYTE PTR _t0$[ebp]
	xor	dl, BYTE PTR _t4$[ebp]
	xor	al, BYTE PTR _i4$[ebp]
	xor	dl, BYTE PTR _i2$[ebp]
	mov	BYTE PTR _y6$[ebp], al
; Line 88
	mov	al, BYTE PTR _x3$[ebp]
	mov	BYTE PTR _y4$[ebp], dl
	test	al, al
	jns	SHORT $LN3@mix_bytes
	add	al, al
	xor	al, 27					; 0000001bH
	jmp	SHORT $LN4@mix_bytes
$LN3@mix_bytes:
	add	al, al
$LN4@mix_bytes:
; Line 89
	test	BYTE PTR _x0$[ebp], 128			; 00000080H
	je	SHORT $LN5@mix_bytes
	mov	dl, BYTE PTR _x0$[ebp]
	add	dl, dl
	xor	dl, 27					; 0000001bH
	mov	BYTE PTR _x0$[ebp], dl
	jmp	SHORT $LN6@mix_bytes
$LN5@mix_bytes:
	shl	BYTE PTR _x0$[ebp], 1
$LN6@mix_bytes:
; Line 91
	xor	cl, al
; Line 92
	jns	SHORT $LN7@mix_bytes
	add	cl, cl
	xor	cl, 27					; 0000001bH
	jmp	SHORT $LN11@mix_bytes
$LN7@mix_bytes:
	add	cl, cl
$LN11@mix_bytes:
; Line 93
	mov	al, BYTE PTR _y4$[ebp]
	mov	BYTE PTR _t0$[ebp], cl
	mov	cl, al
	xor	cl, BYTE PTR _x0$[ebp]
; Line 94
	jns	SHORT $LN9@mix_bytes
	add	cl, cl
	xor	cl, 27					; 0000001bH
	jmp	SHORT $LN10@mix_bytes
$LN9@mix_bytes:
	add	cl, cl
$LN10@mix_bytes:
; Line 96
	xor	al, BYTE PTR _t0$[ebp]
	mov	edx, DWORD PTR _output$[ebp]
	mov	BYTE PTR [edx], al
; Line 97
	mov	al, BYTE PTR _y1$[ebp]
	xor	al, cl
	mov	BYTE PTR [edx+5], al
; Line 99
	movzx	eax, BYTE PTR _x4$[ebp]
	movzx	eax, BYTE PTR _mul2[eax]
	movzx	ecx, BYTE PTR _y0$[ebp]
	xor	eax, ecx
	mov	al, BYTE PTR _mul2[eax]
	xor	al, bl
; Line 100
	movzx	ecx, BYTE PTR _y1$[ebp]
	mov	BYTE PTR [edx+1], al
	movzx	eax, BYTE PTR _x5$[ebp]
	movzx	eax, BYTE PTR _mul2[eax]
	xor	eax, ecx
	mov	al, BYTE PTR _mul2[eax]
	xor	al, BYTE PTR _y6$[ebp]
; Line 101
	movzx	ecx, BYTE PTR _y2$[ebp]
	mov	BYTE PTR [edx+2], al
	movzx	eax, BYTE PTR _x6$[ebp]
	movzx	eax, BYTE PTR _mul2[eax]
	xor	eax, ecx
	mov	al, BYTE PTR _mul2[eax]
	xor	al, BYTE PTR _y7$[ebp]
; Line 102
	movzx	ecx, BYTE PTR _y3$[ebp]
	mov	BYTE PTR [edx+3], al
	movzx	eax, BYTE PTR _x7$[ebp]
	movzx	eax, BYTE PTR _mul2[eax]
	xor	eax, ecx
	mov	al, BYTE PTR _mul2[eax]
	xor	al, BYTE PTR _y0$[ebp]
; Line 103
	movzx	ecx, bl
	mov	BYTE PTR [edx+4], al
	movzx	eax, BYTE PTR _x1$[ebp]
	movzx	eax, BYTE PTR _mul2[eax]
	xor	eax, ecx
	mov	al, BYTE PTR _mul2[eax]
	xor	al, BYTE PTR _y2$[ebp]
; Line 104
	movzx	ecx, BYTE PTR _y6$[ebp]
	mov	BYTE PTR [edx+6], al
	movzx	eax, BYTE PTR _x2$[ebp]
	movzx	eax, BYTE PTR _mul2[eax]
	xor	eax, ecx
	mov	al, BYTE PTR _mul2[eax]
	xor	al, BYTE PTR _y3$[ebp]
	pop	ebx
	mov	BYTE PTR [edx+7], al
; Line 105
	leave
	ret	0
_mix_bytes ENDP
_TEXT	ENDS
PUBLIC	_perm_P
; Function compile flags: /Ogspy
;	COMDAT _perm_P
_TEXT	SEGMENT
_state$ = -64						; size = 64
_input$ = 8						; size = 4
_round$ = 11						; size = 1
_output$ = 12						; size = 4
_perm_P	PROC						; COMDAT
; Line 107
	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
; Line 109
	mov	esi, DWORD PTR _input$[ebp]
	push	edi
	lea	edi, DWORD PTR _state$[ebp]
; Line 111
	mov	BYTE PTR _round$[ebp], 0
$LL9@perm_P:
; Line 121
	movzx	eax, BYTE PTR [esi+63]
	movzx	eax, BYTE PTR _sbox[eax]
	push	edi
	push	eax
	movzx	eax, BYTE PTR [esi+54]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+45]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+36]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+27]
	movzx	eax, BYTE PTR _sbox[eax]
	movzx	ebx, BYTE PTR _round$[ebp]
	push	eax
	movzx	eax, BYTE PTR [esi+18]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+9]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi]
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
; Line 131
	lea	eax, DWORD PTR [edi+8]
	push	eax
	movzx	eax, BYTE PTR [esi+7]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+62]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+53]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+44]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+35]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+26]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+17]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+8]
	xor	eax, 16					; 00000010H
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
	add	esp, 72					; 00000048H
; Line 141
	lea	eax, DWORD PTR [edi+16]
	push	eax
	movzx	eax, BYTE PTR [esi+15]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+6]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+61]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+52]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+43]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+34]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+25]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+16]
	xor	eax, 32					; 00000020H
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
; Line 151
	lea	eax, DWORD PTR [edi+24]
	push	eax
	movzx	eax, BYTE PTR [esi+23]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+14]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+5]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+60]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+51]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+42]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+33]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+24]
	xor	eax, 48					; 00000030H
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
	add	esp, 72					; 00000048H
; Line 161
	lea	eax, DWORD PTR [edi+32]
	push	eax
	movzx	eax, BYTE PTR [esi+31]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+22]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+13]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+4]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+59]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+50]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+41]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+32]
	xor	eax, 64					; 00000040H
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
; Line 171
	lea	eax, DWORD PTR [edi+40]
	push	eax
	movzx	eax, BYTE PTR [esi+39]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+30]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+21]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+12]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+3]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+58]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+49]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+40]
	xor	eax, 80					; 00000050H
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
	add	esp, 72					; 00000048H
; Line 181
	lea	eax, DWORD PTR [edi+48]
	push	eax
	movzx	eax, BYTE PTR [esi+47]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+38]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+29]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+20]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+11]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+2]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+57]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+48]
	xor	eax, 96					; 00000060H
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
; Line 191
	lea	eax, DWORD PTR [edi+56]
	push	eax
	movzx	eax, BYTE PTR [esi+55]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+46]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+37]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+28]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+19]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+10]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+1]
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	movzx	eax, BYTE PTR [esi+56]
	xor	eax, 112				; 00000070H
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
	add	esp, 72					; 00000048H
; Line 193
	cmp	BYTE PTR _round$[ebp], 0
	jne	SHORT $LN1@perm_P
; Line 194
	mov	esi, DWORD PTR _output$[ebp]
$LN1@perm_P:
; Line 111
	inc	BYTE PTR _round$[ebp]
	cmp	BYTE PTR _round$[ebp], 10		; 0000000aH
; Line 196
	mov	eax, esi
; Line 197
	mov	esi, edi
; Line 198
	mov	edi, eax
	jb	$LL9@perm_P
	pop	edi
	pop	esi
	pop	ebx
; Line 200
	leave
	ret	0
_perm_P	ENDP
_TEXT	ENDS
PUBLIC	_perm_Q
; Function compile flags: /Ogspy
;	COMDAT _perm_Q
_TEXT	SEGMENT
_state$ = -64						; size = 64
_input$ = 8						; size = 4
_round$ = 11						; size = 1
_output$ = 12						; size = 4
_perm_Q	PROC						; COMDAT
; Line 202
	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
; Line 204
	mov	esi, DWORD PTR _input$[ebp]
	push	edi
	lea	edi, DWORD PTR _state$[ebp]
; Line 206
	mov	BYTE PTR _round$[ebp], 0
$LL9@perm_Q:
; Line 215
	movzx	eax, BYTE PTR [esi+55]
	movzx	ebx, BYTE PTR _round$[ebp]
	xor	eax, 159				; 0000009fH
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	edi
	push	eax
	mov	al, BYTE PTR [esi+38]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+21]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+4]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+59]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+42]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+25]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+8]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
; Line 225
	lea	eax, DWORD PTR [edi+8]
	push	eax
	movzx	eax, BYTE PTR [esi+63]
	xor	eax, 143				; 0000008fH
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+46]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+29]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+12]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+3]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+50]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+33]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+16]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
	add	esp, 72					; 00000048H
; Line 235
	lea	eax, DWORD PTR [edi+16]
	push	eax
	mov	al, BYTE PTR [esi+7]
	not	al
	movzx	eax, al
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+54]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+37]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+20]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+11]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+58]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+41]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+24]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
; Line 245
	lea	eax, DWORD PTR [edi+24]
	push	eax
	movzx	eax, BYTE PTR [esi+15]
	xor	eax, 239				; 000000efH
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+62]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+45]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+28]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+19]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+2]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+49]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+32]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
	add	esp, 72					; 00000048H
; Line 255
	lea	eax, DWORD PTR [edi+32]
	push	eax
	movzx	eax, BYTE PTR [esi+23]
	xor	eax, 223				; 000000dfH
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+6]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+53]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+36]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+27]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+10]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+57]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+40]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
; Line 265
	lea	eax, DWORD PTR [edi+40]
	push	eax
	movzx	eax, BYTE PTR [esi+31]
	xor	eax, 207				; 000000cfH
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+14]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+61]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+44]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+35]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+18]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+1]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+48]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
	add	esp, 72					; 00000048H
; Line 275
	lea	eax, DWORD PTR [edi+48]
	push	eax
	movzx	eax, BYTE PTR [esi+39]
	xor	eax, 191				; 000000bfH
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+22]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+5]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+52]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+43]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+26]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+9]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+56]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
; Line 285
	lea	eax, DWORD PTR [edi+56]
	push	eax
	movzx	eax, BYTE PTR [esi+47]
	xor	eax, 175				; 000000afH
	xor	eax, ebx
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+30]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+13]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+60]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+51]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+34]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi+17]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	mov	al, BYTE PTR [esi]
	not	al
	movzx	eax, al
	movzx	eax, BYTE PTR _sbox[eax]
	push	eax
	call	_mix_bytes
	add	esp, 72					; 00000048H
; Line 287
	cmp	BYTE PTR _round$[ebp], 0
	jne	SHORT $LN1@perm_Q
; Line 288
	mov	esi, DWORD PTR _output$[ebp]
$LN1@perm_Q:
; Line 206
	inc	BYTE PTR _round$[ebp]
	cmp	BYTE PTR _round$[ebp], 10		; 0000000aH
; Line 290
	mov	eax, esi
; Line 291
	mov	esi, edi
; Line 292
	mov	edi, eax
	jb	$LL9@perm_Q
	pop	edi
	pop	esi
	pop	ebx
; Line 294
	leave
	ret	0
_perm_Q	ENDP
_TEXT	ENDS
PUBLIC	_crypto_hash
; Function compile flags: /Ogspy
;	COMDAT _crypto_hash
_TEXT	SEGMENT
_pad_block$ = -492					; size = 256
_q_state$ = -236					; size = 64
_x_state$ = -172					; size = 64
_p_state$ = -108					; size = 64
_buf$ = -44						; size = 64
_h_state$ = 20						; size = 64
tv517 = 84						; size = 4
tv90 = 88						; size = 4
tv512 = 92						; size = 4
_message_left_len$ = 96					; size = 4
_remaining$ = 103					; size = 1
_out$ = 112						; size = 4
_in$ = 116						; size = 4
_inlen$ = 120						; size = 8
_crypto_hash PROC					; COMDAT
; Line 296
	push	ebp
	lea	ebp, DWORD PTR [esp-104]
	sub	esp, 596				; 00000254H
; Line 298
	mov	ecx, DWORD PTR _inlen$[ebp]
	lea	edx, DWORD PTR [ecx+8]
	shr	edx, 6
	inc	edx
	shl	edx, 6
; Line 299
	mov	al, dl
	sub	al, cl
; Line 311
	cmp	DWORD PTR _inlen$[ebp+4], 0
	mov	BYTE PTR _remaining$[ebp], 0
	mov	DWORD PTR _message_left_len$[ebp], ecx
	ja	SHORT $LN28@crypto_has
	cmp	ecx, 65536				; 00010000H
	jb	SHORT $LN17@crypto_has
$LN28@crypto_has:
; Line 312
	or	eax, -1
	jmp	$LN18@crypto_has
$LN17@crypto_has:
	push	ebx
	push	esi
	push	edi
; Line 316
	movzx	esi, al
	xor	al, al
; Line 323
	push	64					; 00000040H
	lea	edi, DWORD PTR _pad_block$[ebp]
	mov	ecx, esi
	rep stosb
	pop	ebx
	shr	edx, 6
	lea	edi, DWORD PTR _h_state$[ebp]
	mov	ecx, ebx
	mov	BYTE PTR _pad_block$[ebp], 128		; 00000080H
	rep stosb
	mov	BYTE PTR _pad_block$[ebp+esi-1], dl
; Line 325
	mov	BYTE PTR _h_state$[ebp+62], 1
; Line 329
	test	dl, dl
	je	$LN14@crypto_has
	mov	esi, DWORD PTR _in$[ebp]
	mov	eax, ebx
	movzx	ecx, dl
	sub	eax, esi
	mov	DWORD PTR tv512[ebp], esi
	mov	DWORD PTR tv517[ebp], eax
	mov	DWORD PTR tv90[ebp], ecx
	jmp	SHORT $LN16@crypto_has
$LL29@crypto_has:
; Line 316
	mov	esi, DWORD PTR tv512[ebp]
	mov	eax, DWORD PTR tv517[ebp]
$LN16@crypto_has:
; Line 330
	add	eax, esi
	cmp	eax, DWORD PTR _inlen$[ebp]
	jae	SHORT $LN13@crypto_has
; Line 332
	sub	DWORD PTR _message_left_len$[ebp], ebx
	jmp	SHORT $LN30@crypto_has
$LN13@crypto_has:
; Line 333
	mov	edx, DWORD PTR _message_left_len$[ebp]
	test	edx, edx
	je	SHORT $LN11@crypto_has
; Line 334
	mov	al, bl
	sub	al, dl
; Line 337
	and	DWORD PTR _message_left_len$[ebp], 0
	lea	edi, DWORD PTR _buf$[ebp]
	mov	ecx, edx
	rep movsb
	mov	BYTE PTR _remaining$[ebp], al
	movzx	ecx, al
	lea	esi, DWORD PTR _pad_block$[ebp]
	lea	edi, DWORD PTR _buf$[ebp+edx]
; Line 338
	jmp	SHORT $LN31@crypto_has
$LN11@crypto_has:
; Line 339
	movzx	esi, BYTE PTR _remaining$[ebp]
	lea	esi, DWORD PTR _pad_block$[ebp+esi]
$LN30@crypto_has:
	mov	ecx, ebx
	lea	edi, DWORD PTR _buf$[ebp]
$LN31@crypto_has:
	rep movsb
; Line 342
	xor	eax, eax
	mov	esi, ebx
$LL9@crypto_has:
; Line 343
	mov	cl, BYTE PTR _buf$[ebp+eax]
	xor	cl, BYTE PTR _h_state$[ebp+eax]
	inc	eax
	dec	esi
	mov	BYTE PTR _x_state$[ebp+eax-1], cl
	jne	SHORT $LL9@crypto_has
; Line 345
	lea	eax, DWORD PTR _p_state$[ebp]
	push	eax
	lea	eax, DWORD PTR _x_state$[ebp]
	push	eax
	call	_perm_P
; Line 346
	lea	eax, DWORD PTR _q_state$[ebp]
	push	eax
	lea	eax, DWORD PTR _buf$[ebp]
	push	eax
	call	_perm_Q
	add	esp, 16					; 00000010H
; Line 348
	xor	eax, eax
	mov	esi, ebx
$LL6@crypto_has:
; Line 349
	mov	cl, BYTE PTR _q_state$[ebp+eax]
	xor	cl, BYTE PTR _p_state$[ebp+eax]
	xor	BYTE PTR _h_state$[ebp+eax], cl
	inc	eax
	dec	esi
	jne	SHORT $LL6@crypto_has
; Line 329
	add	DWORD PTR tv512[ebp], ebx
	dec	DWORD PTR tv90[ebp]
	jne	$LL29@crypto_has
$LN14@crypto_has:
; Line 352
	lea	eax, DWORD PTR _p_state$[ebp]
	push	eax
	lea	eax, DWORD PTR _h_state$[ebp]
	push	eax
	call	_perm_P
; Line 353
	mov	esi, DWORD PTR _out$[ebp]
	pop	ecx
	pop	ecx
	lea	eax, DWORD PTR _p_state$[ebp+32]
	push	32					; 00000020H
	sub	esi, eax
	xor	ecx, ecx
	pop	edi
$LL3@crypto_has:
; Line 354
	mov	dl, BYTE PTR _h_state$[ebp+ecx+32]
	lea	eax, DWORD PTR _p_state$[ebp+ecx+32]
	xor	dl, BYTE PTR [eax]
	inc	ecx
	dec	edi
	mov	BYTE PTR [eax+esi], dl
	jne	SHORT $LL3@crypto_has
; Line 356
	pop	edi
	pop	esi
	xor	eax, eax
	pop	ebx
$LN18@crypto_has:
; Line 357
	add	ebp, 104				; 00000068H
	leave
	ret	0
_crypto_hash ENDP
_TEXT	ENDS
END
