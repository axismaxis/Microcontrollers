;
; Opdracht3.asm
;
; Created: 12-Apr-17 1:00:13 PM
; Author : cezan
;


; Replace with your application code
start:
    ldi xh, 0x06
	ldi xl, 0x60    ; setting the index x to r0a60
	ldi yh, 0x08
	ldi yl, 0xB0
	ldi r21, 0xa	; number of loops, will be decreased

loopie:
	ld r10, x+ ; load value from index reg to register r10
	st x+, r10
	dec r21		; decrease the loop value reg 
	brne loopie ; loop


end:
	rjmp end