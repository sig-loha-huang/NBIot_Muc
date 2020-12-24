#include <bsp_reg.h>

  .syntax unified
	.cpu cortex-m4
	.thumb

.global	g_pfnVectors
.global	Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word	_sidata
/* start address for the .data section. defined in linker script */
.word	_sdata
/* end address for the .data section. defined in linker script */
.word	_edata
/* start address for the .bss section. defined in linker script */
.word	_sbss
/* end address for the .bss section. defined in linker script */
.word	_ebss

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section	.text.Reset_Handler
	.weak	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:
    /*open cache*/
	ldr 	r1, =REG_CACHE_CTRL
	mov 	r2, #0x0F
	str 	r2, [r1] 

	ldr 	r1, =REG_CACHE_RGN2  /*config 0x08120000 ~ 0x08180000 为cache区*/
	ldr 	r2, =0x017F0120
	str 	r2, [r1]

//	ldr 	r1, =REG_MCU_BOOT_MODE
//	mov 	r2, #02
//	str 	r2, [r1]
    mov     r0, #0    
    msr     primask, r0  //关闭异常和中断
     
relocate:
    /* relocate data to RAM */
    ldr    r0, =_sidata
    ldr    r1, =_sdata		    /* dest address */
	cmp    r0, r1
	beq    Jmp_clearbss

	ldr	r2, =_sdata
	ldr	r3, =_edata
    subs    r2, r3, r2                   /* r2 <- size of armboot */
    adds    r2, r0, r2                   /* r2 <- source end address */
    
copy_code_loop:
    ldmia  r0!, {r3-r10}                /* copy from source address [r0] */
    stmia  r1!, {r3-r10}                /* copy to   target address [r1] */
    cmp    r0, r2                       /* until source end address [r2] */
    ble    copy_code_loop

Jmp_clearbss:    
	ldr	r2, =_sbss
	b	LoopFillZerobss

/* Zero fill the bss segment. */
FillZerobss:
	movs	r3, #0
	str	r3, [r2], #4

LoopFillZerobss:
	ldr	r3, = _ebss
	cmp	r2, r3
	bcc	FillZerobss
	
    bl	main
	bx	lr
.size	Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt. This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None
 * @retval None
*/
    .section	.text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
	b	Infinite_Loop
	.size	Default_Handler, .-Default_Handler
/******************************************************************************
* 
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
 	.section	.isr_vector,"a",%progbits
	.type	g_pfnVectors, %object
	.size	g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
	.word	_estack
	.word	Reset_Handler
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	MemManage_Handler
	.word	BusFault_Handler
	.word	UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
    .word   vPortSVCHandler
    .word   DebugMon_Handler
    .word   0
    .word   xPortPendSVHandler
    .word   xPortSysTickHandler//SysTick_Handler  //xPortSysTickHandler
    
	.word	Dd_Wdt_IntISR                               /*  IRQ_WDT0         0 */
	.word	0                                           /*  IRQ_WDT1         1 */
	.word	0                                           /*  IRQ_GPIOA        2 */
	.word	0                                           /*  IRQ_GPIOB        3 */
	.word	0                                           /*  IRQ_TIMER0       4 */
	.word	0                                           /*  IRQ_TIMER1       5 */
	.word	0                                           /*  IRQ_RESV         6 */
	.word	0                                           /*  IRQ_I2C          7 */
	.word	0                                           /*  IRQ_UART0        8 */
	.word	0                                           /*  IRQ_UART1        9 */
	.word	Dd_Uart2_isr                                /*  IRQ_UART2        10*/
	.word	0                                           /*  IRQ_UART3        11*/
	.word	0                                           /*  IRQ_SPI0         12*/
	.word	0                                           /*  IRQ_SPI1         13*/
	.word	0                                           /*  IRQ_SPI2         14*/
	.word	0                                           /*  IRQ_SCI          15*/
	.word	0                                           /*  IRQ_DAA        	 16*/
	.word	0                                           /*  IRQ_CIPHER       17*/
	.word	Dd_Adc_Isr                                  /*  IRQ_ADC          18*/
	.word	0                                           /*  IRQ_SHA          19*/
	.word	0                                           /*  IRQ_CPM0         20*/
	.word	Dd_McuRecNbInt_Isr                          /*  IRQ_CPM1         21*/
	.word	Dd_CPM2_Isr                                 /*  IRQ_CPM2         22*/
	.word	0                                           /*  IRQ_SDMA         23*/
	.word	0                                           /*  IRQ_DMAC0_CH0    24*/
	.word	0                                           /*  IRQ_DMAC0_CH1    25*/
	.word	0                                           /*  IRQ_DMAC0_CH2    26*/
	.word	0                                           /*  IRQ_DMAC0_CH3    27*/
	.word	0                                           /*  IRQ_DMAC1_CH0    28*/
	.word	0                                           /*  IRQ_DMAC1_CH1	 29*/
    .word	0                                           /*  IRQ_DMAC1_CH2    30*/
	.word	0                                           /*  IRQ_DMAC1_CH3    31*/

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

//  .weak	NMI_Handler
//	.thumb_set NMI_Handler,Default_Handler
    .type NMI_Handler, %function
    NMI_Handler:
    	mov	r0, sp	@ pass auto-saved registers as argument
    	b	do_invalid_entry
    .type HardFault_Handler, %function
    HardFault_Handler:
    	mov	r0, sp	@ pass auto-saved registers as argument
    	b	do_hard_fault

    .type MemManage_Handler, %function
    MemManage_Handler:
    	mov	r0, sp	@ pass auto-saved registers as argument
    	b	do_mm_fault

    .type BusFault_Handler, %function
    BusFault_Handler:
    	mov	r0, sp	@ pass auto-saved registers as argument
    	b	do_bus_fault

    .type UsageFault_Handler, %function
    UsageFault_Handler:
    	mov	r0, sp	@ pass auto-saved registers as argument
    	b	do_usage_fault

    .type DebugMon_Handler, %function
    DebugMon_Handler:
    	mov	r0, sp	@ pass auto-saved registers as argument
    	b	do_invalid_entry
    
	.weak	xPortSysTickHandler//xPortSysTickHandler//SysTick_Handler
	.thumb_set xPortSysTickHandler,Default_Handler

	.weak	Dd_Wdt_IntISR
	.thumb_set Dd_Wdt_IntISR,Default_Handler

	.weak	Dd_Wdt_IntISR
	.thumb_set Dd_Wdt_IntISR,Default_Handler

	.weak	Dd_Timer1_isr
	.thumb_set Dd_Timer1_isr,Default_Handler

	.weak	Dd_Gpio_Isr
	.thumb_set Dd_Gpio_Isr,Default_Handler

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

