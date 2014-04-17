global install_gdt
global idt_flush

gdtr DW 0
     DD 0

install_gdt:
     MOV EAX, [esp + 4]
     MOV [gdtr + 2], EAX
     MOV AX, [esp + 8]
     MOV [gdtr], AX
     LGDT [gdtr]
     RET

idt_flush:
     MOV eax, [esp+4]
     LIDT [eax]
     RET 
