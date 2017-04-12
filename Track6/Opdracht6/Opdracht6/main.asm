;
; Opdracht6.asm
;
; Created: 12-Apr-17 4:07:13 PM
; Author : cezan
;


; Replace with your application code
start:
	ldi r21, 0x6 ; number of loops, will be decreased
	ldi r22, 0x01
inv_loop:

	loopie:
		shl r22, r23 ; bitshift the value of r22 1 to the left
		ldi r22, r23 ; setting r22 to r23 for the next opperation

		OUT PORTA, r23 ; setting the bitshifted value to portA 
		dec r21	; decrease the loop value reg 
		brne loopie ; loop

		ldi r21, 0x06 ; resetting the counter for the loop
		ldi r22, 0x01 ; resetting r22 for the next operation.
	rjmp inv_loop
