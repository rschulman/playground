%macro ISR_NOERRORCODE 1
	[GLOBAL isr%1]
	isr%1:
		CLI
		push byte 0
		push byte %1
		JMP isr_common_stub
%endmacro

%macro ISR_ERRORCODE 1
	[GLOBAL isr%1]
	isr%1:
		CLI
		PUSH byte %1
		JMP isr_common_stub
%endmacro

ISR_NOERRORCODE 0
ISR_NOERRORCODE 1
ISR_NOERRORCODE 2
ISR_NOERRORCODE 3
ISR_NOERRORCODE 4
ISR_NOERRORCODE 5
ISR_NOERRORCODE 6
ISR_NOERRORCODE 7
ISR_ERRORCODE 8
ISR_NOERRORCODE 9
ISR_ERRORCODE 10
ISR_ERRORCODE 11
ISR_ERRORCODE 12
ISR_ERRORCODE 13
ISR_ERRORCODE 14
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_NOERRORCODE 17
ISR_NOERRORCODE 18
ISR_NOERRORCODE 19
ISR_NOERRORCODE 20
ISR_NOERRORCODE 21
ISR_NOERRORCODE 22
ISR_NOERRORCODE 23
ISR_NOERRORCODE 23
ISR_NOERRORCODE 24
ISR_NOERRORCODE 25
ISR_NOERRORCODE 26
ISR_NOERRORCODE 27
ISR_NOERRORCODE 28
ISR_NOERRORCODE 29
ISR_NOERRORCODE 30
ISR_NOERRORCODE 31

[EXTERN interrupt_handler]

isr_common_stub:
	PUSHA 		;push all the registers onto the stack to be retrieved later
	
	MOV ax, ds
	PUSH eax	; Push the data descriptor onto the stack

	MOV ax, 0x10	; This is the kernel data descriptor
	MOV ds, ax
	MOV es, ax
	MOV fs, ax
	MOV es, ax
	MOV gs, ax

	CALL interrupt_handler

	POP eax		; Get back the data descriptor
	MOV ds, ax
	MOV es, ax
	MOV fs, ax
	MOV es, ax
	MOV gs, ax

	POPA
	ADD esp, 8	; Cleans up the error code and ISR number that we pushed
	STI		; Restart interrupts
	IRET
	
	
