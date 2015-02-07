SECTIONS {
    . = 0x00000000;
        .text : {
            head.o
            init.o
            uart.o
            interrupt.o
            led.o
            main.o
        }
}
