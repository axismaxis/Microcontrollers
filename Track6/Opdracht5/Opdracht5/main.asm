;
; Opdracht5.asm
;
; Created: 12-Apr-17 2:25:33 PM
; Author : cezan
;


; Replace with your application code
start:
    ;antwoord is r10 r11 r12 r13
	;getal 1 is r14 r15 r16 r17 
	;getal 2 is r18 r19 20 r21

	ldi r17, 0xa
	ldi r21, 0xa

	mov r13, r17 
	adc r13, r21
	mov r12, r16 
	adc r12, r20
	mov r11, r15 
	adc r11, r19
	mov r10, r14 
	adc r10, r18

end:
	rjmp end

