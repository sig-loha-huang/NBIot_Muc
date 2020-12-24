/*******************************************************************************
 * COPYRIGHT@SIGBEAN
 *******************************************************************************
 * �ļ�����:  
 * ��������: ����Ҫ�������ļ��Ĺ��ܡ����ݼ���Ҫģ�飩    
 * ʹ��˵��: ������ʹ���ļ�����ʱ����Լ������
 * �ļ�����:                
 * ��д����: 
 * �޸���ʷ: 
 *  
 * �޸������޸���  BugID/CRID      �޸�����
 * -----------------------------------------------------------------------------
 * 
 ******************************************************************************/
/******************************* �����ļ����� *********************************/
#include <cortex_m4.h>
#include <stdio.h>
#include <rf_test.h>
/******************************* �ֲ��궨�� ***********************************/
#define    DD_LNA_PIN      16
#define    DD_LPEN_BPIN    13

/******************************* �ֲ����������Ͷ��� ***************************/

/******************************* �ֲ�����ԭ������ *****************************/
/******************************* ȫ�ֱ������� *********************************/
u8 g_PBit = 0;
/******************************* ����ʵ�� *************************************/
void Dd_Rf_IcWriteReg(u8 reg_id,u16 data)
{
    u32 regval = 0;

    /*wait spi idle*/
    while(REG(0x400E0010) == 1);

    /*write */ 
    regval = (data)|(reg_id<<16)|(0<<23)|(1<<24)|(4<<25);
    REG(0x400E0008) = regval;    

}
u16 Dd_Rf_IcReadReg(u8 reg_id)
{
    u32 regval = 0;

    /*wait spi idle*/
    while(REG(0x400E0010) == 1);

    /*read */ 
    regval = (0xffff)|(reg_id<<16)|(1<<23)|(1<<24)|(4<<25);
    
    REG(0x400E0008) = regval;  

    /*wait spi idle*/
    while(REG(0x400E0010) == 1);    

    return ((u16)REG(0x400E000C));
}
void Rf_ReadRegAll(void)
{
    u16 reg_val;
    int i;
    for(i=0;i<=22;i++)
    {
        reg_val = Dd_Rf_IcReadReg(i);
        printf("%x\n",reg_val);
    }   
}
void Dd_Rf_Close(void)
{
    Dd_Rf_IcWriteReg(0,0x8038);
}
void Dd_Mipi_Clk_High(void)
{
    REG(REG_GPIO_SWPORTA_DR) |= (0x1 << 1);
}

void Dd_Mipi_Clk_Low(void)
{
    REG(REG_GPIO_SWPORTA_DR) &= (~(0x1 << 1));
}

void Dd_Mipi_Data_High(void)
{
    REG(REG_GPIO_SWPORTA_DR) |= (0x1 << 0);
}

void Dd_Mipi_Data_Low(void)
{
    REG(REG_GPIO_SWPORTA_DR) &= (~(0x1 << 0));
}

void Dd_Mipi_SSCHead(void)
{
    int Count ;
    Dd_Mipi_Clk_Low();
    Dd_Mipi_Data_Low();
    for(Count = 0;Count<10;Count++);
    Dd_Mipi_Data_High();
    for(Count = 0;Count<10;Count++);
    Dd_Mipi_Data_Low();
    for(Count = 0;Count<10;Count++);
}

void Dd_Mipi_BusPark(void)
{
    /*Bus Park*/
    Dd_Mipi_Clk_High();
    Dd_Mipi_Data_Low();    
    Dd_Mipi_Clk_Low();
}    

void Dd_Mipi_Reg_Write(u8 SlaveAddr,u8 RegAddr,u8 u8Data)
{
    s8 index = 0;
    RegAddr = RegAddr & 0x1F;
    RegAddr = RegAddr | 0x40;
    g_PBit = 1;
    /* ssc */
    Dd_Mipi_SSCHead();

    /* slave addr */
    for(index = 3;index>=0;index--)
    {
        Dd_Mipi_Clk_High();
        if(SlaveAddr & (1 << index))
        {
            Dd_Mipi_Data_High();
            g_PBit++;
        }    
        else
        {
            Dd_Mipi_Data_Low();
        }    
        Dd_Mipi_Clk_Low();
    }    

    /*reg addr*/
    for(index = 7;index>=0;index--)
    {
        Dd_Mipi_Clk_High();
        if(RegAddr & (1 << index))
        {
            Dd_Mipi_Data_High();
            g_PBit++;
        }  
        else
            Dd_Mipi_Data_Low();
        Dd_Mipi_Clk_Low();
    }

    /*p_bit*/
    Dd_Mipi_Clk_High();
    if((g_PBit & 0x01) == 1)
        Dd_Mipi_Data_High();
    else
        Dd_Mipi_Data_Low();
    Dd_Mipi_Clk_Low();
    /*data*/
    g_PBit = 1;
    for(index = 7;index>=0;index--)
    {
        Dd_Mipi_Clk_High();
        if(u8Data & (1 << index))
        {
            Dd_Mipi_Data_High();
            g_PBit++;
        }  
        else
            Dd_Mipi_Data_Low();
        Dd_Mipi_Clk_Low();
    }

    /*p_bit*/
    Dd_Mipi_Clk_High();
    if((g_PBit & 0x01)== 1)
        Dd_Mipi_Data_High();
    else
        Dd_Mipi_Data_Low();
    Dd_Mipi_Clk_Low();

    /*bus park*/
    Dd_Mipi_BusPark();    
}

void Dd_Mipi_LowPowerMode(void)
{
    Dd_Mipi_Reg_Write(0x0C,0x1C,0x80);        
    Dd_Mipi_Reg_Write(0x0F,0x1C,0x80);        
}

void Dd_LNAAndLpen_Low(void)
{
    /*LNA config*/
    Dd_SetIOAFunction0(DD_LNA_PIN);
    /*LP_PIN*/
    Dd_SetIOBFunction0(DD_LPEN_BPIN);

    REG(REG_GPIO_SWPORTA_DDR) |=  (0x1 << DD_LNA_PIN); 
    REG(REG_GPIO_SWPORTA_DR) &= (~(0x1 << DD_LNA_PIN));

    REG(REG_GPIO_SWPORTB_DDR) |=  (0x1 << DD_LPEN_BPIN); 
    REG(REG_GPIO_SWPORTB_DR) &= (~(0x1 << DD_LPEN_BPIN));
}

void Dd_Rf_ForErrorInit(void)
{
    u32 regval = 0;
    u32 Count;
    /*read */ 
    regval = (0xffff)|(0x7f<<16)|(1<<23)|(1<<24)|(4<<25);
    
    for(Count = 0;Count< 16;Count++)
    {
        REG(RF_SPI_DATA) = regval;  
    }    
}

void Rf_ParaReg_Compar(void)
{
    u16 regdata[24] = {
        0x8038,0x6205,0xa80f,0xe656,0x7200,0xc10,0x192,0x820,0xc000,0x0,
        0xc820,0xf9,0x7c82,0x9040,0x4a24,0xe01a,0x5203,0xb54,0x0,0x30,
        0xb000,0x3f00,0x0};

    u16 reg_val;
    int i;


    /* enable rf  spi config default */
    #if RX_IQ_SWAP
    REG(RF_CTRL) = (1<<6)|(1<<7)|(RF_RX_PHI<<8)|(RF_TX_PHI<<13)|(1<<4)|(1<<2)|(1<<23)|(1<<22);
    #else
    REG(RF_CTRL) = (1<<6)|(1<<7)|(RF_RX_PHI<<8)|(RF_TX_PHI<<13)|(1<<2)|(1<<23)|(1<<22);
    #endif

    /*Rx disable, Tx Disable, Tx Clk enable*/
    REG(RF_TX_RX) = 0;

    /*tx init data*/
    REG(RF_TX_INIT) = 0x800800;  

    Dd_Rf_ForErrorInit();

    for(i=0;i<=20;i++)
    {
        Dd_Rf_IcWriteReg(i,regdata[i]);
    }    
     
    for(i=0;i<=20;i++)
    {
        reg_val = Dd_Rf_IcReadReg(i);

        if(reg_val != regdata[i])
        {
            DD_DEBUG_PRINTF("Error Config RF Reg %d:%04x\r\n",i,reg_val);
            return ;
        }    
    }   
        
    DD_DEBUG_PRINTF("RF Reg Config OK !!!\r\n");
}

/******************************* Դ�ļ����� ***********************************/

