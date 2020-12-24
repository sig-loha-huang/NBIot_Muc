#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cortex_m4.h>

extern void clear_share_memory(void);

void start_Nb(void)
{
    /*config nb boot mode->flash mode*/
    REG(REG_BOOT_MODE) = 0x03;   
    
    /*´ò¿ªÊ±ÖÓ*/
    REG(REG_CLK_GATE)= REG(REG_CLK_GATE) | 1;   
    /*reset release nb*/
    REG(REG_RSTN_SOFT) = REG(REG_RSTN_SOFT) | 1;    
}

void stop_Nb(void)
{    
    /*stop nb*/
    REG(REG_RSTN_SOFT) = REG(REG_RSTN_SOFT) & 0xFFFFFFFE;
    REG(REG_CLK_GATE) =REG(REG_CLK_GATE) & 0xFFFFFFFE;
}


unsigned char init_NbModule(void)
{    
    stop_Nb();
    //clear_share_memory();
	start_Nb();
}    


