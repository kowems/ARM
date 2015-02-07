@*************************************************************************************
@
@ File: head.S
@ Function: boot 2440 CPU
@
@*************************************************************************************

.extern main
.text
.global _start
_start:
    b Reset

HandleUndef:
    b HandleUndef

HandleSWI:
    b HandleSWI

HandlePrefetchAbort:
    b HandlePrefetchAbort

HandleDataAbort:
    b HandleDataAbort

HandleNotUsed:
    b HandleNotUsed

    b HandleIRQ

HandleFIQ:
    b HandleFIQ

Reset:
    ldr sp,=4096
    bl disable_watch_dog
    bl clock_init
    bl mem_setup
    bl nand_init

@ copy binary from nand
    ldr r0,=0x30000000
    mov r1,#4096
    mov r2,#16*1024
    bl nand_read

    bl clean_bss
    
    msr cpsr_c,#0xd2
    ldr sp,=0x31000000

    msr cpsr_c,#0xdf
    ldr sp,=0x34000000
    
    ldr lr,=openIRQ
    ldr pc,=irq_init
openIRQ:
    msr cpsr_c,#0x5f

    ldr lr,=halt_loop
    ldr pc,=main
halt_loop:
    b halt_loop

HandleIRQ:
    sub lr,lr,#4
    stmdb sp!,{ r0-r12,lr }

    ldr lr,=int_return
    ldr pc,=Interrupt_handler
int_return:
    ldmia sp!,{ r0-r12,pc }^
