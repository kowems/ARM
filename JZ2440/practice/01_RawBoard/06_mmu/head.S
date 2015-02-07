@****************************************************
@ File:head.S
@ function:initialize hardware & copy program to sdram and then jump to sdram to continu
@****************************************************
.equ SDRAM_REGISTER_BASE,0x48000000
.equ SDRAM_BASE_ADDR,0x30000000

.text
.global _start
_start:
    bl disable_watch_dog
    bl setup_sdram
    bl copy_steppingstone_to_sdram   @ assembler function
    ldr sp,=4096
@    bl copy_2th_to_sdram   @ c function
    bl create_page_table
    bl mmu_init
    ldr sp,=0xB4000000
    ldr pc,=main
halt_loop:
    b halt_loop

disable_watch_dog:
    ldr r0,=0x53000000
    mov r1,#0x0
    str r1,[r0]
    mov pc,lr

copy_steppingstone_to_sdram:
    mov r1,#2048
    ldr r2,=0x30004000
    mov r3,#4*1024    @ a mistake here : 2*1024. if set this value,cpu will be confusion,so that coping all thing at all.
1:
    ldr r4,[r1],#4
    str r4,[r2],#4
    cmp r1,r3    @ compare address
    bne 1b
    mov pc,lr

setup_sdram:
    mov r1,#SDRAM_REGISTER_BASE
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
    .long 0x22011110 @BWSCON
    .long 0x00000700 @BANKCON0
    .long 0x00000700 @BANKCON1
    .long 0x00000700 @BANKCON2
    .long 0x00000700 @BANKCON3
    .long 0x00000700 @BANKCON4
    .long 0x00000700 @BANKCON5
    .long 0x00018005 @BANKCON6
    .long 0x00018005 @BANKCON7
    .long 0x008C07A3 @REFRESH
    .long 0x000000B1 @BANKSIZE
    .long 0x00000030 @MRSRB6
    .long 0x00000030 @MRSRB7
