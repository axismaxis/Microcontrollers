;
; Opdracht2.asm
;
; Created: 11-Apr-17 12:31:06 PM
; Author : cezan
;


; Replace with your application code
start:
    ldi xh, 0x0a
	ldi xl, 0x60     ; setting the index x to r0a60
	ldi r21, 0xa	; number of loops, will be decreased

loopie:
	ld r10, x+ ; load value from index reg to register r10
	com r10  ; complement from the r10
	dec r21		; decrease the loop value reg 
	brne loopie ; loop


end:
	rjmp end