/******************************* 包含文件声明 *********************************/
#include <stdio.h>
#include <cortex_m4.h>
#include <core_cm3.h>
#include <string.h>

/******************************* 局部宏定义 ***********************************/

/******************************* 局部常数和类型定义 ***************************/
typedef void (* IRQ_HANDLER) (void);

struct autosave_regs {
	long uregs[8];
};
#define ARM_XPSR	uregs[7]
#define ARM_PC		uregs[6]
#define ARM_LR		uregs[5]
#define ARM_R12		uregs[4]
#define ARM_R3		uregs[3]
#define ARM_R2		uregs[2]
#define ARM_R1		uregs[1]
#define ARM_R0		uregs[0]


/******************************* 局部函数原型声明 *****************************/


/******************************* 函数实现 *************************************/
void Dd_DoReset(void)
{
    while(1);
      
    REG(REG_RSTN_SYS_SOFT) = 0x000;
}


void dump_regs(struct autosave_regs *regs)
{
	printf("pc : %08lx    lr : %08lx    xPSR : %08lx\n",
	       regs->ARM_PC, regs->ARM_LR, regs->ARM_XPSR);
	printf("r12 : %08lx   r3 : %08lx    r2 : %08lx\n"
		"r1 : %08lx    r0 : %08lx\n",
		regs->ARM_R12, regs->ARM_R3, regs->ARM_R2,
		regs->ARM_R1, regs->ARM_R0);
    printf("reg : %08x \n",*(unsigned int *)0xE000ED2C);
    
}

void bad_mode(void)
{
	printf("MCU Resetting CPU ...\n");
	Dd_DoReset();
}

void do_hard_fault(struct autosave_regs *autosave_regs)
{
	printf("MCU Hard fault\n");
	dump_regs(autosave_regs);
	bad_mode();
}

void do_mm_fault(struct autosave_regs *autosave_regs)
{
	printf("Memory management fault\n");
	dump_regs(autosave_regs);
	bad_mode();
}

void do_bus_fault(struct autosave_regs *autosave_regs)
{
	printf("Bus fault\n");
	dump_regs(autosave_regs);
	bad_mode();
}

void do_usage_fault(struct autosave_regs *autosave_regs)
{
	printf("Usage fault\n");
	dump_regs(autosave_regs);
	bad_mode();
}

void do_invalid_entry(struct autosave_regs *autosave_regs)
{
	printf("Exception\n");
	dump_regs(autosave_regs);
	bad_mode();
}


