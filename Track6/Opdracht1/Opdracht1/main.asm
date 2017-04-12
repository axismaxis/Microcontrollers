;
; Opdracht1.asm
;
; Author : cezan
;


; Replace with your application code
start:

	ldi xh, 0x05
	ldi xl, 0x40     ; setting the index x to r540
	ldi r20, 0x55	; the value to write to the regs
	ldi r21, 0x09	; number of loops will be decreased
write_loop:
	ST X+, r20		; wrinting the value reg to the selected index reg
	dec	r21			; Decreasing reg with numer of loops
	brne write_loop ; looping

end:
	rjmp end