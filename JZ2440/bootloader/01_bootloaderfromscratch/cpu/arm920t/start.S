/*
 * boot - Startup code for ARM 2440
 *
 * Copyright (c) 2015 Eric Ju <Eric.X.Ju@gmail.com>
 * 
 * This program is free software;you can registribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;Either version 2 of
 * the License,or (at your option) any later version.
 *
 */

/*                  History
 *
 *   01/14/2015 Eric: initialization creation
 *
 */

#define S3C2440_MPLL_400MHz ((0x5c << 12) | (0x01 << 4) | (0x01 << 0))

.text
.global _start
_start: 
    b reset

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

/* switch cpu to supervisor mode */
reset:
    mrs r0,cpsr
    bic r0,r0,#0x1f /* clear low 5 bit */
    orr r0,r0,#0xd3 /* logic OR */
    msr cpsr,r0
/* disable watch dog */
    ldr r0, =0x53000000
    mov r1,#0
    str r1,[r0]
/* setup clock */
    ldr r0,=0x4c000014
    mov r1,#0x05    /* FCLK:HCLK:PCLK=1:4:8,HDIVN=1,PDIVN=1 */
    str r1,[r0]
    // set cpu bus mode as asynchronous
    mrc p15,0,r1,c1,c0,0
    orr r1,r1,#0xc0000000
    mcr p15,0,r1,c1,c0,0
    // set frequency division (MDIV,PDIV,SDIV)
    ldr r0,=0x4c000004
    ldr r1,=S3C2440_MPLL_400MHz
    str r1,[r0]

/* initialize SDRAM */
    ldr r0,=0x48000000
    adr r1,sdram_config
    add r3,r0,#(13*4)
0:
    ldr r2,[r1],#4
    str r2,[r0],#4
    cmp r0,r3
    bne 0b

/* setup stack */
    bl setup_stack   // prepare for calling c function
/* setup interrupt */
    #bl irq_init
    #msr cpsr,#0x53
/* initialize nand */
    bl nand_init

/* relocate */
    mov r0,#0;
    ldr r1,=_start
    ldr r2,=__bss_start
    sub r2,r2,r1
    bl copy_code_to_sdram

/* clear bss */
    ldr r0,=__bss_start
    ldr r1,=__bss_end
    mov r2,#0x00000000

clear_bss:
    str r2,[r0],#4
    cmp r0,r1
    ble clear_bss

/* run main */
    ldr lr,=halt
    ldr pc,=start_boot
halt:
    b halt

setup_stack:
    ldr sp,=0x34000000
    mov pc,lr

HandleIRQ:
    sub lr,lr,#4
    stmdb sp!,{r0-r12,lr}

    ldr lr,=irq_ret
    ldr pc,=Interrupt_handler
irq_ret:
    ldmia sp!,{r0-r12,pc}^

/* for debug */
led_on:
    ldr r0,=0x56000050
    mov r1,#0x00000100
    str r1,[r0]
    ldr r0,=0x56000054
    mov r1,#0x00000000
    str r1,[r0]
    mov pc,lr

sdram_config:
    .long 0x22011110    //BWSCON
    .long 0x00000700    //BANKCON0
    .long 0x00000700    //BANKCON1
    .long 0x00000700    //BANKCON2
    .long 0x00000700    //BANKCON3
    .long 0x00000700    //BANKCON4
    .long 0x00000700    //BANKCON5
    .long 0x00018005    //BANKCON6
    .long 0x00018005    //BANKCON7
    .long 0x008C04F4    //REFRESH
    .long 0x000000B1    //BANKSIZE
    .long 0x00000030    //MRSRB6
    .long 0x00000030    //MRSRB7
