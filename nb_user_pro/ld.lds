
ENTRY(Reset_Handler)


MEMORY
{    
    RAM (xrw)    : ORIGIN = 0x00000400, LENGTH = 63K
    FLASH (xr)    : ORIGIN = 0x08120000, LENGTH = 128K
}

/* higher address of the user mode stack */
_estack = 0x00010000;

/* Sections Definitions */

SECTIONS
{    
    .text :
    {
	    . = ALIGN(4);
        KEEP(*(.isr_vector))            /* Startup code */
        ./bsp/boot.o (.text*);

        *(EXCLUDE_FILE(./bsp/src/clock.o ./bsp/src/rf_test.o *lib_a*.o *printf.o *vsnprintf.o *memset.o *memcpy.o ./bsp/src/load_nb.o ./bsp/src/ota_hal.o ./vos/src/*.o ./bsp/src/adc.o ./bsp/src/gpio.o ./bsp/src/board.o ./bsp/src/compat/compat.o ./bsp/src/timer.o ./bsp/src/flash.o ./bsp/src/uart_cmd.o ./bsp/src/circbuf.o ./bsp/src/core_cm3.o ./bsp/src/sys_cmd.o ./bsp/src/rtc.o ./bsp/src/mcu2nb.o ./bsp/src/uart.o ./nb_main.o ./freertos/portable/LH3200/*.o ./freertos/*.o).text*);
        *(EXCLUDE_FILE(./bsp/src/clock.o ./bsp/src/rf_test.o *lib_a*.o *printf.o *vsnprintf.o *memset.o *memcpy.o ./bsp/src/load_nb.o ./bsp/src/ota_hal.o ./vos/src/*.o ./bsp/src/adc.o ./bsp/src/gpio.o ./bsp/src/board.o ./bsp/src/compat/compat.o ./bsp/src/timer.o ./bsp/src/flash.o ./bsp/src/uart_cmd.o ./bsp/src/circbuf.o ./bsp/src/core_cm3.o ./bsp/src/sys_cmd.o ./bsp/src/rtc.o ./bsp/src/mcu2nb.o ./bsp/src/uart.o ./nb_main.o ./freertos/portable/LH3200/*.o ./freertos/*.o).rodata) ;                /* read-only data (constants) */
        *(EXCLUDE_FILE(./bsp/src/clock.o ./bsp/src/rf_test.o *lib_a*.o *printf.o *vsnprintf.o *memset.o *memcpy.o ./bsp/src/load_nb.o ./bsp/src/ota_hal.o ./vos/src/*.o ./bsp/src/adc.o ./bsp/src/gpio.o ./bsp/src/board.o ./bsp/src/compat/compat.o ./bsp/src/timer.o ./bsp/src/flash.o ./bsp/src/uart_cmd.o ./bsp/src/circbuf.o ./bsp/src/core_cm3.o ./bsp/src/sys_cmd.o ./bsp/src/rtc.o ./bsp/src/mcu2nb.o ./bsp/src/uart.o ./nb_main.o ./freertos/portable/LH3200/*.o ./freertos/*.o).rodata*);                  

        *(.glue_7);
        *(.glue_7t);
    	*(.got*);
    	*(.igot*);
    	*(.rel*);    	
	    . = ALIGN(4);
   	 _etext = .;
    } >FLASH

    .ARM.exidx :
    {
        _sexidx = .;    
        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)
       	_eexid = . ;
    } > FLASH

    /* used by the startup to initialize data */
    _sidata = LOADADDR(.data);

    .data  :
    {
	    . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _sdata = . ;

        ./freertos/portable/LH3200/*.o(.text .text* .rodata .rodata* .constdata .constdata*); 
        ./freertos/*.o(.text .text* .rodata .rodata* .constdata .constdata*); 
        ./nb_main.o(.text .text* .rodata .rodata* .constdata .constdata*); 
        ./bsp/src/uart.o(.text .text* .rodata .rodata* .constdata .constdata*); 
        ./bsp/src/mcu2nb.o(.text .text* .rodata .rodata* .constdata .constdata*); 
        ./bsp/src/rtc.o(.text .text* .rodata .rodata* .constdata .constdata*); 
        ./bsp/src/sys_cmd.o(.text .text* .rodata .rodata* .constdata .constdata*); 
        ./bsp/src/circbuf.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/core_cm3.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/uart_cmd.o(.text .text* .rodata .rodata* .constdata .constdata*); 
        ./bsp/src/timer.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/board.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/adc.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/gpio.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/flash.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/compat/compat.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./vos/src/*.o(.text .text* .rodata .rodata* .constdata .constdata*);
        *lib_a*.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/ota_hal.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/load_nb.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/rf_test.o(.text .text* .rodata .rodata* .constdata .constdata*);
        ./bsp/src/clock.o(.text .text* .rodata .rodata* .constdata .constdata*); 
        *(.fastcode);
        *(.fastcode.*);

        *(.rodata) ;                /* read-only data (constants) */
        *(.rodata*);

        *(.data);
        *(.data.*)

	    . = ALIGN(4);
	    /* This is used by the startup in order to initialize the .data secion */
   	 _edata = . ;
    } >RAM AT> FLASH 

    .bss :
    {
	    . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;

        *(.bss);
        *(.bss.*);
	    *(COMMON);
	    . = ALIGN(4);
	    /* This is used by the startup in order to initialize the .bss secion */
   	 _ebss = . ;
    } >RAM
    _end = .;
    
  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
