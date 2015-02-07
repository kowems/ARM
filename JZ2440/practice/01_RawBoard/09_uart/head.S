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
    bl uart_init
    
    msr cpsr_c,#0xd2
    ldr sp,=3072

    msr cpsr_c,#0xd3
    ldr sp,=4096
    
    msr cpsr_c,#0x53

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
    
