@*********************************************************************
@   File : head.S
@   Description : Perform some hardware initialization
@   and then jump to main function.
@*********************************************************************

.text
.global _start
_start:
    bl disable_watch_dog
    bl sdram_init
    ldr sp,=4096
    bl nand_init
    
    ldr r0,=0x30000000
    mov r1,#4096
    mov r2,#2048
    bl nand_read

    ldr sp,=0x34000000
    ldr lr,=halt_loop
    ldr pc,=main

halt_loop:
    b halt_loop

disable_watch_dog:
    ldr r0,=0x53000000
    mov r1,#0x0
    str r1,[r0]
    mov pc,lr

sdram_init:
    mov r1,#0x48000000
    adrl r2,sdram_cfg_val
    add r3,r1,#52
1:
    ldr r4,[r2],#4
    str r4,[r1],#4
    cmp r1,r3
    bne 1b
    mov pc,lr

.align 4
sdram_cfg_val:
    .long 0x22011110    @BWSCON
    .long 0x00000700    @BANKCON0
    .long 0x00000700    @BANKCON1
    .long 0x00000700    @BANKCON2
    .long 0x00000700    @BANKCON3
    .long 0x00000700    @BANKCON4
    .long 0x00000700    @BANKCON5
    .long 0x00018005    @BANKCON6
    .long 0x00018005    @BANKCON7
    .long 0x008C07A3    @REFRESH
    .long 0x000000B1    @BANKSIZE
    .long 0x00000030    @MRSRB6
    .long 0x00000030    @MRSRB7
