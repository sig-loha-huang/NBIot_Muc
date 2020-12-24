/*******************************************************************************
 * COPYRIGHT@SIGBEAN
 *******************************************************************************
 * 文件名称:  
 * 功能描述: （简要描述本文件的功能、内容及主要模块）    
 * 使用说明: （描述使用文件功能时的制约条件）
 * 文件作者:                
 * 编写日期: 
 * 修改历史: 
 *  
 * 修改日期修改人  BugID/CRID      修改内容
 * -----------------------------------------------------------------------------
 * 
 ******************************************************************************/
/******************************* 包含文件声明 *********************************/
#include <stdio.h>
#include <cortex_m4.h>

/******************************* 局部宏定义 ***********************************/

/******************************* 局部常数和类型定义 ***************************/
unsigned char g_u8PllClkFlag = PLL_USE_PLLCLK;

/******************************* 局部函数原型声明 *****************************/

/******************************* 函数实现 *************************************/
/*******************************************************************************
* 函数名称: Dd_Clock_Init
* 函数功能: clock与pll相关配置
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Clock_Init(void)
{
#if 0
    int Count = 0;
    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,0);

    /*** enable pll ***/
    REG(REG_PLL_CTRL) &= (~(PLL_EN_PLL << 29));
 
    /********************* config pll ***************************************************
    
     VCO=CLKIN*DIV_LOOP/DIV_PRE = 19.2M*PLL_DIV_LOOP/PLL_DIV_PRE = 19.2*112/4 = 537.6M

     CLKOUT=VCO/DIV_OUT = 537.6M / PLL_DIV_OUT = 537.6M / 2 = 268.8M

    ************************************************************************************/
    REG(REG_PLL_CTRL) = (PLL_DIV_PRE) | (PLL_DIV_LOOP << 6) | (PLL_DIV_OUT<<14) |(PLL_SW_VCO_460_600M<<20)|
                        (PLL_SW_ICP<<23) | (PLL_SW_LP <<25) | (PLL_SW_LOCK <<26) | (PLL_SW_VREG <<27) ;
#if 0
    /********************* config pll for 38.4M config **********************************

     VCO=CLKIN*DIV_LOOP/DIV_PRE = 19.2M*PLL_DIV_LOOP/PLL_DIV_PRE = 19.2*64/4 = 307.2M

     CLKOUT=VCO/DIV_OUT = 307.2M / PLL_DIV_OUT = 307.2M / 4 = 76.8M

    ************************************************************************************/    
    REG(REG_PLL_CTRL) = (PLL_DIV_PRE) | (64 << 6) | (4 <<14) |(PLL_SW_VCO_220_360M<<20)|
                        (PLL_SW_ICP<<23) | (PLL_SW_LP <<25) | (PLL_SW_LOCK <<26) | (PLL_SW_VREG <<27) ;
#endif
    /*** enable pll ***/
    REG(REG_PLL_CTRL) |= (PLL_EN_PLL << 29);
    
    for(Count=0;Count<2000;Count++);

    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,1);
#endif
    WRITE_REG(REG_CLK_GATE,  0xffffffff);   
    WRITE_REG(REG_RSTN_SOFT, 0xffffffff);    
}

void Dd_Pll_Enable(void)
{   
    if(g_u8PllClkFlag == PLL_USE_PLLCLK)
        return ;

    u32 regval = 0;

    int Count = 0;
    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,0);

    /*** disable pll ***/
    REG(REG_PLL_CTRL) &= (~(PLL_EN_PLL << 29));
 
    /*** enable pll ***/
    REG(REG_PLL_CTRL) |= (PLL_EN_PLL << 29);
    
    for(Count=0;Count<800;Count++);

    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,1);

    regval = REG(REG_CLK_DIV);
    regval = (regval & 0xFFFFF00F) | 0x10;
    WRITE_REG(REG_CLK_DIV,regval);

    g_u8PllClkFlag = PLL_USE_PLLCLK;   
}

/*******************************************************************************
* 函数名称: Dd_Clock_Pll_268M
* 函数功能: 配置PLL的时钟为268M,cpu总线时钟为134M
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:   
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Clock_Pll_268M(void)
{
    int Count = 0;
    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,0);

    /*** enable pll ***/
    REG(REG_PLL_CTRL) &= (~(PLL_EN_PLL << 29));
 
    /********************* config pll ***************************************************
    
     VCO=CLKIN*DIV_LOOP/DIV_PRE = 19.2M*PLL_DIV_LOOP/PLL_DIV_PRE = 19.2*112/4 = 537.6M

     CLKOUT=VCO/DIV_OUT = 537.6M / PLL_DIV_OUT = 537.6M / 2 = 268.8M

    ************************************************************************************/
    REG(REG_PLL_CTRL) = (PLL_DIV_PRE) | (PLL_DIV_LOOP << 6) | (PLL_DIV_OUT<<14) |(PLL_SW_VCO_460_600M<<20)|
                        (PLL_SW_ICP<<23) | (PLL_SW_LP <<25) | (PLL_SW_LOCK <<26) | (PLL_SW_VREG <<27) ;

    /*** enable pll ***/
    REG(REG_PLL_CTRL) |= (PLL_EN_PLL << 29);
    
    for(Count=0;Count<2000;Count++);

    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,1);
}
/*******************************************************************************
* 函数名称: Dd_Clock_Pll_153M
* 函数功能: 配置PLL的时钟为153M,cpu总线时钟为76M
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:   
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Clock_Pll_153M(void)
{
    int Count = 0;
    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,0);

    /*** enable pll ***/
    REG(REG_PLL_CTRL) &= (~(PLL_EN_PLL << 29));
 
    /********************* config pll for 153.6M config **********************************

     VCO=CLKIN*DIV_LOOP/DIV_PRE = 19.2M*PLL_DIV_LOOP/PLL_DIV_PRE = 19.2*64/4 = 307.2M

     CLKOUT=VCO/DIV_OUT = 307.2M / PLL_DIV_OUT = 307.2M / 2 = 153.6M

    ************************************************************************************/    
    REG(REG_PLL_CTRL) = (PLL_DIV_PRE) | (64 << 6) | (PLL_DIV_OUT <<14) |(PLL_SW_VCO_220_360M<<20)|
                        (PLL_SW_ICP<<23) | (PLL_SW_LP <<25) | (PLL_SW_LOCK <<26) | (PLL_SW_VREG <<27) ;

    /*** enable pll ***/
    REG(REG_PLL_CTRL) |= (PLL_EN_PLL << 29);
    
    for(Count=0;Count<2000;Count++);

    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,1);
}

/*******************************************************************************
* 函数名称: Dd_Clock_Pll_76M
* 函数功能: 配置PLL的时钟为76M,cpu总线时钟为38M
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:   
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Clock_Pll_76M(void)
{
    int Count = 0;
    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,0);

    /*** enable pll ***/
    REG(REG_PLL_CTRL) &= (~(PLL_EN_PLL << 29));
 
    /********************* config pll for 38.4M config **********************************

     VCO=CLKIN*DIV_LOOP/DIV_PRE = 19.2M*PLL_DIV_LOOP/PLL_DIV_PRE = 19.2*64/4 = 307.2M

     CLKOUT=VCO/DIV_OUT = 307.2M / PLL_DIV_OUT = 307.2M / 4 = 76.8M

    ************************************************************************************/    
    REG(REG_PLL_CTRL) = (PLL_DIV_PRE) | (64 << 6) | (4 <<14) |(PLL_SW_VCO_220_360M<<20)|
                        (PLL_SW_ICP<<23) | (PLL_SW_LP <<25) | (PLL_SW_LOCK <<26) | (PLL_SW_VREG <<27) ;

    /*** enable pll ***/
    REG(REG_PLL_CTRL) |= (PLL_EN_PLL << 29);
    
    for(Count=0;Count<2000;Count++);

    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,1);
}
/*******************************************************************************
* 函数名称: Dd_Clock_Pll_268M_DIV_Test
* 函数功能: 配置PLL的时钟为268M,cpu总线时钟为134M,时钟分频为PllDiv
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:   
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Clock_Pll_268M_DIV_Test(u32 PllDiv)
{
    int Count = 0;
    u32 regval;
    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,0);

    /*** enable pll ***/
    REG(REG_PLL_CTRL) &= (~(PLL_EN_PLL << 29));
 
    /********************* config pll ***************************************************
    
     VCO=CLKIN*DIV_LOOP/DIV_PRE = 19.2M*PLL_DIV_LOOP/PLL_DIV_PRE = 19.2*112/4 = 537.6M

     CLKOUT=VCO/DIV_OUT = 537.6M / PLL_DIV_OUT = 537.6M / 2 = 268.8M

    ************************************************************************************/
    REG(REG_PLL_CTRL) = (PLL_DIV_PRE) | (PLL_DIV_LOOP << 6) | (PLL_DIV_OUT<<14) |(PLL_SW_VCO_460_600M<<20)|
                        (PLL_SW_ICP<<23) | (PLL_SW_LP <<25) | (PLL_SW_LOCK <<26) | (PLL_SW_VREG <<27) ;

    /*** enable pll ***/
    REG(REG_PLL_CTRL) |= (PLL_EN_PLL << 29);
    
    regval = REG(REG_CLK_DIV);
    regval &= (~0xf);
    //regval &= 0x0;
    WRITE_REG(REG_CLK_DIV,regval|PllDiv);
    
    for(Count=0;Count<2000;Count++);

    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,1);
}

/*******************************************************************************
* 函数名称: Dd_Clock_Use_ExtClosk
* 函数功能: 使用外部19.2M的时钟
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:   
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
NB_FAST_CODE void Dd_Clock_Use_ExtClock(void)
{
    u32 regval = 0;
    u32 clk;

    if(g_u8PllClkFlag == PLL_USE_EXTCLK)
        return ;
  
    clk = CLK_4P8M;
    regval = REG(REG_CLK_DIV);
    regval = (regval & 0xFFFFF00F) | 0x20;
    WRITE_REG(REG_CLK_DIV,regval);

    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,2);


    /*** enable pll ***/
    REG(REG_PLL_CTRL) &= (~(PLL_EN_PLL << 29));

    vPortUseExtClkSetupSysTick();

    g_u8PllClkFlag = PLL_USE_EXTCLK; 
}
/*******************************************************************************
* 函数名称: Dd_Clock_Use_ExtClock_DIV_Test
* 函数功能: 使用外部19.2M的时钟,时钟分频为PllDiv
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:   
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Clock_Use_ExtClock_DIV_Test(u32 PllDiv)
{
    u32 regval;
    regval = REG(REG_CLK_DIV);
    regval &= (~(0xff << 4));
    WRITE_REG(REG_CLK_DIV,regval|(PllDiv << 4));
    
    /*config use pll clock*/
    WRITE_REG(REG_CLK_GLO_SRC,2);

    /*** enable pll ***/
    REG(REG_PLL_CTRL) &= (~(PLL_EN_PLL << 29));
}
/*******************************************************************************
* 函数名称: clock_get_apb
* 函数功能: 获取当前的apb时钟
* 相关文档: 
* 函数参数:
* 参数名称:  
* 返回值:   返回当前的APB时钟
* 函数说明:
* 修改日期版本号修改人修改内容
* -----------------------------------------------------------------
* 
*******************************************************************************/
unsigned long clock_get_apb(void)
{
    return ARM_CLK;
}
/******************************* 源文件结束 ***********************************/

