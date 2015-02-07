@******************************************************************
@ File: head.S
@ Function: init set stack of interrupt mode & supervisor mode
@******************************************************************

.extern main
.text
.global _start
_start:
@**************************************
@ interrupt vector table
@**************************************
    b Reset
@ 0x04: Undef
HandleUndef:
    b HandleUndef
@0x08: SWI
HandleSWI:
    b HandleSWI
@0x0c: PrefectchAbort
HandlePrefectchAbort:
    b HandlePrefectchAbort
@0x10: DataAbort
HandleDataAbort:
    b HandleDataAbort
@0x14: Reserve
HandleNotUsed:
    b HandleNotUsed
@0x18: IRQ
    b HandleIRQ
@0x1c: FIQ
HandleFIQ:
    b HandleFIQ

Reset:
    ldr sp,=4096
    bl disable_watch_dog
    
    msr cpsr_c,#0xd2 @ IRQ mode
    ldr sp,=3072

    msr cpsr_c,#0xd3 @ supervisor mode
    ldr sp,=4096

    bl led_init
    bl key_init
    bl irq_init
    msr cpsr_c,#0x5f

    ldr lr,=halt_loop
    ldr pc,=main
halt_loop:
    b halt_loop

HandleIRQ:
    sub lr,lr,#4
    stmdb sp!,{ r0-r12,lr }

    ldr lr,=int_return
    ldr pc,=EINT_handle
int_return:
    ldmia sp!,{ r0-r12,pc }^
