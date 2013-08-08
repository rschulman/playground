global isr_wrapper
extern fault

isr_wrapper:
	pushad
	call fault
	popad
	iret
