ORG 0
	acall	CONFIGURE_LCD
	MOV R5, #0 ;;; saýý sayýsý
	MOV R2, #0 ;;;basamak sayýsý
	

KEYBOARD_LOOP: ;;;main loop
	acall KEYBOARD
	MOV B, #'#'
	MOV R6, #'A'
	MOV R7, #'B'
	
	CJNE A, B, SAVE ;;; if  not # then save
	acall SAVE_NUMBER
SECOND_LOOP:	
	MOV R2, #0 
	MOV A, #01H
	INC R5
	
	sjmp KEYBOARD_LOOP

	
	;now, A has the key pressed

MEMORY_READER: 
	PUSH 4
	MOV A, R5
	MOV R2, A
	MOV R0, #40H
	MOV R3, #40H
	MOV A, R4
		
	MOV @R0, A
	INC R0
	DJNZ R5, MEMORY_READER
	SJMP
	

SAVE_NUMBER:
	MOV R3, #0 ;;;TEMP
	MOV R6, #1
	MOV R7, #10

LOOP2: ;;; digitleri okuyup sayýyý oluþturup tekrar stacke yazýyor
	MOV B, R6
	POP 4
	MOV A, R4
	MUL AB

	ADD A, R3
	MOV R3, A
	CLR A
	
	MOV B, R7
	MOV A, R6
	MUL AB
	MOV R6, A

	DJNZ R2, LOOP2 
	PUSH 3
	SJUMP SECOND_LOOP



SAVE: 
	acall SEND_DATA
	MOV R1, A
	PUSH 1
	INC R2
	sjmp KEYBOARD_LOOP
	
	
	
	

CONFIGURE_LCD:	;THIS SUBROUTINE SENDS THE INITIALIZATION COMMANDS TO THE LCD
	mov a,#38H	;TWO LINES, 5X7 MATRIX
	acall SEND_COMMAND
	mov a,#0FH	;DISPLAY ON, CURSOR BLINKING
	acall SEND_COMMAND
	mov a,#06H	;INCREMENT CURSOR (SHIFT CURSOR TO RIGHT)
	acall SEND_COMMAND
	mov a,#01H	;CLEAR DISPLAY SCREEN
	acall SEND_COMMAND
	mov a,#80H	;FORCE CURSOR TO BEGINNING OF THE FIRST LINE
	acall SEND_COMMAND
	ret



SEND_COMMAND:
	mov p1,a		;THE COMMAND IS STORED IN A, SEND IT TO LCD
	clr p3.5		;RS=0 BEFORE SENDING COMMAND
	clr p3.6		;R/W=0 TO WRITE
	setb p3.7	;SEND A HIGH TO LOW SIGNAL TO ENABLE PIN
	acall DELAY
	clr p3.7
	ret


SEND_DATA:
	mov p1,a		;SEND THE DATA STORED IN A TO LCD
	setb p3.5	;RS=1 BEFORE SENDING DATA
	clr p3.6		;R/W=0 TO WRITE
	setb p3.7	;SEND A HIGH TO LOW SIGNAL TO ENABLE PIN
	acall DELAY
	clr p3.7
	ret


DELAY:
	push 0
	push 1
	mov r0,#50
DELAY_OUTER_LOOP:
	mov r1,#255
	djnz r1,$
	djnz r0,DELAY_OUTER_LOOP
	pop 1
	pop 0
	ret


KEYBOARD: ;takes the key pressed from the keyboard and puts it to A
	mov	P0, #0ffh	;makes P0 input
K1:
	mov	P2, #0	;ground all rows
	mov	A, P0
	anl	A, #00001111B
	cjne	A, #00001111B, K1
K2:
	acall	DELAY
	mov	A, P0
	anl	A, #00001111B
	cjne	A, #00001111B, KB_OVER
	sjmp	K2
KB_OVER:
	acall DELAY
	mov	A, P0
	anl	A, #00001111B
	cjne	A, #00001111B, KB_OVER1
	sjmp	K2
KB_OVER1:
	mov	P2, #11111110B
	mov	A, P0
	anl	A, #00001111B
	cjne	A, #00001111B, ROW_0
	mov	P2, #11111101B
	mov	A, P0
	anl	A, #00001111B
	cjne	A, #00001111B, ROW_1
	mov	P2, #11111011B
	mov	A, P0
	anl	A, #00001111B
	cjne	A, #00001111B, ROW_2
	mov	P2, #11110111B
	mov	A, P0
	anl	A, #00001111B
	cjne	A, #00001111B, ROW_3
	ljmp	K2
	
ROW_0:
	mov	DPTR, #KCODE0
	sjmp	KB_FIND
ROW_1:
	mov	DPTR, #KCODE1
	sjmp	KB_FIND
ROW_2:
	mov	DPTR, #KCODE2
	sjmp	KB_FIND
ROW_3:
	mov	DPTR, #KCODE3
KB_FIND:
	rrc	A
	jnc	KB_MATCH
	inc	DPTR
	sjmp	KB_FIND
KB_MATCH:
	clr	A
	movc	A, @A+DPTR; get ASCII code from the table 
	ret

;ASCII look-up table 
KCODE0:	DB	'1', '2', '3', 'A'
KCODE1:	DB	'4', '5', '6', 'B'
KCODE2:	DB	'7', '8', '9', 'C'
KCODE3:	DB	'*', '0', '#', 'D'

END


