global install_gdt
global idt_flush

install_gdt:
     CLI
     MOV EAX, [esp + 4]
     LGDT [EAX]
     MOV AX, 0x10
     MOV DS, AX
     MOV ES, AX
     MOV FS, AX
     MOV GS, AX
     MOV SS, AX
     JMP 0x08:.reload_CS

.reload_CS:
     RET

idt_flush:
     MOV eax, [esp+4]
     LIDT [eax]
     RET 
