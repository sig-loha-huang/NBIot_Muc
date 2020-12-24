/******************************* 包含文件声明 *********************************/
#include <cortex_m4.h>
#include <spi_flash.h>
/******************************* 局部宏定义 ***********************************/

/******************************* 局部常数和类型定义 ***************************/
#define CONFIG_SF_DEFAULT_SPEED		1000000

/******************************* 局部函数原型声明 *****************************/

/******************************* 函数实现 *************************************/
void Dd_Spi_Flash_Init(void)
{  
    int clk_div;

    clk_div = ARM_CLK/CONFIG_SF_DEFAULT_SPEED;

    /*初始化SPI所用的管脚复用*/
    REG(REG_B_IO_FUNC_HSEL0_CLR) = (0x1 << DD_SPI0_SCLK_PIN);
    REG(REG_B_IO_FUNC_LSEL0_SET) = (0x1 << DD_SPI0_SCLK_PIN);

    REG(REG_B_IO_FUNC_HSEL0_CLR) = (0x1 << DD_SPI0_STEN_PIN);
    REG(REG_B_IO_FUNC_LSEL0_SET) = (0x1 << DD_SPI0_STEN_PIN);

    REG(REG_B_IO_FUNC_HSEL0_CLR) = (0x1 << DD_SPI0_MOSI_PIN);
    REG(REG_B_IO_FUNC_LSEL0_SET) = (0x1 << DD_SPI0_MOSI_PIN);

    REG(REG_B_IO_FUNC_HSEL0_CLR) = (0x1 << DD_SPI0_MISO_PIN);
    REG(REG_B_IO_FUNC_LSEL0_SET) = (0x1 << DD_SPI0_MISO_PIN);


    /*wp pin,hold pin config for normal read */
 //   REG(REG_B_IO_FUNC_HSEL0_CLR) |= (0x1 << DD_FLASH_WP_PIN) | (0x1 << DD_FLASH_HOLD_PIN);
//    REG(REG_B_IO_FUNC_LSEL0_CLR) |= (0x1 << DD_FLASH_WP_PIN) | (0x1 << DD_FLASH_HOLD_PIN);


    /*Disable SPI_CFG*/
    WRITE_REG(SPI_FLASH_Ssienr, 0x0);

    /*SCPH, 0; DFS, 8 bit*/
    WRITE_REG(SPI_FLASH_Ctrlr0, DD_SPI_8BIT_TX_MODE);   

    WRITE_REG(SPI_FLASH_Txftlr, 0x8); 
    WRITE_REG(SPI_FLASH_Rxftlr, 0x8);

    /* 1 byte receive */
    WRITE_REG(SPI_FLASH_Ctrlr1, 0x0);    

    /* 20 divider of PCLK for ssclk = 40M/20 */
    WRITE_REG(SPI_FLASH_Baudr,  clk_div);
    
    /* slave enable for cs_0 */
    WRITE_REG(SPI_FLASH_Ser,    0x1);

    /* disable interrupt, use polling mode */
    WRITE_REG(SPI_FLASH_Imr,    0x0);     
}
void Dd_boot_spi_init(void)
{
    REG(REG_B_IO_FUNC_HSEL0_SET) = (0x1 << DD_SPI0_SCLK_PIN);
    REG(REG_B_IO_FUNC_LSEL0_CLR) = (0x1 << DD_SPI0_SCLK_PIN);

    REG(REG_B_IO_FUNC_HSEL0_SET) = (0x1 << DD_SPI0_STEN_PIN);
    REG(REG_B_IO_FUNC_LSEL0_CLR) = (0x1 << DD_SPI0_STEN_PIN);

    REG(REG_B_IO_FUNC_HSEL0_SET) = (0x1 << DD_SPI0_MOSI_PIN);
    REG(REG_B_IO_FUNC_LSEL0_CLR) = (0x1 << DD_SPI0_MOSI_PIN);

    REG(REG_B_IO_FUNC_HSEL0_SET) = (0x1 << DD_SPI0_MISO_PIN);
    REG(REG_B_IO_FUNC_LSEL0_CLR) = (0x1 << DD_SPI0_MISO_PIN);
} 
void Dd_Spi_Flash_Cs_Enable(void)
{

}    
void Dd_Spi_Flash_Cs_Disable(void)
{
}    

void Dd_Spi_Flash_Wirte_Cmd(int cmd, int len)
{  
    int u32Index;
    
    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TX_MODE);

    /* Enable SPI CFG */      
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);

    WRITE_REG(SPI_FLASH_Dr_Low, (cmd&0xFF));
    
    /* wait spi transfer start */
    u32Index = 0;
    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
    {
    	u32Index++;
    	if(u32Index > 10) break;
    } /*wait SPI busy*/

    /* wait SPI idle */
    while(READ_REG(SPI_FLASH_Sr) &0x1); 
  
    /* Disable SPI_CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x0); 

}

void Dd_Spi_Flash_Wirte_Cmd_QEbit(void)
{  
    int u32Index;
    
    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TX_MODE);

    /* Enable SPI CFG */      
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);

    WRITE_REG(SPI_FLASH_Dr_Low, (DD_CMD_WRSR&0xFF));
    WRITE_REG(SPI_FLASH_Dr_Low, 0x00);
    WRITE_REG(SPI_FLASH_Dr_Low, 0x02);
    
    /* wait spi transfer start */
    u32Index = 0;
    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
    {
    	u32Index++;
    	if(u32Index > 10) break;
    } /*wait SPI busy*/

    /* wait SPI idle */
    while(READ_REG(SPI_FLASH_Sr) &0x1); 
  
    /* Disable SPI_CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x0); 

}
void Dd_Wait_Flash_ReadQeBit(void)
{
    int rd_value;

    rd_value = Dd_Spi_Flash_Read_Cmd(0x35);

    Dd_Uart2_Printf("Read QE Bit %x\r\n",rd_value);
    
    while((rd_value &0x02) != 0x02) 
    {
	    rd_value = Dd_Spi_Flash_Read_Cmd(0x35);
    }
}




int Dd_Spi_Flash_Read_Cmd(int cmd)
{  
    int rdata;
    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TXRX_MODE);

    /* Enable SPI CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);
    
    WRITE_REG(SPI_FLASH_Dr_Low, (cmd&0xFF));
    WRITE_REG(SPI_FLASH_Dr_Low, 0x00);

    /* wait spi transfer start */
    rdata = 0;
    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
    {
    	rdata++;
    	if(rdata > 10) break;
    } /*wait SPI busy*/

    /* wait SPI idle */
    while(READ_REG(SPI_FLASH_Sr) &0x1); 
    
    rdata = READ_REG(SPI_FLASH_Dr_Low); 
    
    rdata = READ_REG(SPI_FLASH_Dr_Low);
    
    /* Disable SPI_CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x0); 

    return rdata;
}

int Dd_Spi_Flash_Read_StatueReg(int cmd)
{  
    int rdata;
    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TXRX_MODE);

    /* Enable SPI CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);
    
    WRITE_REG(SPI_FLASH_Dr_Low, (cmd&0xFF));
    WRITE_REG(SPI_FLASH_Dr_Low, 0x00);

    /* wait spi transfer start */
    rdata = 0;
    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
    {
    	rdata++;
    	if(rdata > 10) break;
    } /*wait SPI busy*/

    /* wait SPI idle */
    while(READ_REG(SPI_FLASH_Sr) &0x1); 
    
    rdata = READ_REG(SPI_FLASH_Dr_Low); 
    
    rdata = READ_REG(SPI_FLASH_Dr_Low);
    
    /* Disable SPI_CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x0); 

    Dd_Uart2_Printf("SReg:%02x\r\n",rdata);

    return rdata;
}

void Dd_Flash_WrEnable(void)
{
	unsigned int status = 0;
	do 
    {
        Dd_Spi_Flash_Wirte_Cmd(DD_CMD_WREN,1);
        
        status = Dd_Spi_Flash_Read_Cmd(DD_CMD_RDSR);
                
        if((status&0xfc) &&(status &0x2))
    	{
    		Dd_Spi_Flash_Wirte_Cmd(0x01, 2);
    		status = 0;
    	} 
        
	}while(status != 0x2);
}

void Dd_Wait_Flash_ready(void)
{
    int rd_value;

    rd_value = Dd_Spi_Flash_Read_Cmd(DD_CMD_RDSR);
    
    while(rd_value &0x01) 
    {
	    rd_value = Dd_Spi_Flash_Read_Cmd(DD_CMD_RDSR);
    }
}

unsigned short Dd_Read_FlashId(void)
{
    short u16Temp = 0;
    short u16index,u16rdata;
    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TXRX_MODE);


    /* Enable SPI CFG */      
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);
    
    WRITE_REG(SPI_FLASH_Dr_Low, DD_CMD_SIMPLE_ID);
    WRITE_REG(SPI_FLASH_Dr_Low, 00);
    WRITE_REG(SPI_FLASH_Dr_Low, 00);
    WRITE_REG(SPI_FLASH_Dr_Low, 00);
    
    u16index = 0; 
    while(u16index < 2)
    {
    	WRITE_REG(SPI_FLASH_Dr_Low, 0x00);
    	u16index++;
    }
    
    /* wait spi transfer start */
    u16index = 0;
    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
    { 
    	u16index++;
    	if(u16index > 10)
        {
            break;
        }    
    } /* wait SPI busy */  
    
   	/* wait SPI idle */	
    while(READ_REG(SPI_FLASH_Sr) &0x1); 
    
    u16index = 0;

    while(u16index < 2+4)
    {    
    	u16rdata = READ_REG(SPI_FLASH_Dr_Low);        
    	u16Temp  = ((u16Temp <<8) | (u16rdata & 0xFF));
    	u16index ++;
    }
    /* Disable SPI_CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x0); 

    return u16Temp;
}
unsigned short Dd_Read_JEDEC_Id(void)
{
    short u16FlashId[6];

    short u16Temp = 0;
    short u16index;
    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TXRX_MODE);


    /* Enable SPI CFG */      
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);
    
    WRITE_REG(SPI_FLASH_Dr_Low, DD_CMD_JEDEC_ID);
    WRITE_REG(SPI_FLASH_Dr_Low, 0);
    WRITE_REG(SPI_FLASH_Dr_Low, 0);
    WRITE_REG(SPI_FLASH_Dr_Low, 0);

    /* wait spi transfer start */
    u16index = 0;
    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
    { 
    	u16index++;
    	if(u16index > 10)
        {
            break;
        }    
    } /* wait SPI busy */  
    
   	/* wait SPI idle */	
    while(READ_REG(SPI_FLASH_Sr) &0x1); 

    u16index = 0;
    /*while Rx fifo is not empty Read Data */
    while((READ_REG(SPI_FLASH_Sr) &DW_RX_FIFO_EMPTY_BIT) == DW_RX_FIFO_EMPTY_BIT)
    {
    	u16FlashId[u16index++] = READ_REG(SPI_FLASH_Dr_Low);
    }
    /* Disable SPI_CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x0); 
    Dd_Uart2_Printf("%x %x %x %x \n",u16FlashId[0],u16FlashId[1],u16FlashId[2],
                                      u16FlashId[3]);
    return u16Temp;
}

/*** 擦除扇区的命令 每次擦除的大小为4KB ***/
void Dd_Spi_Flash_sector_erase(int sector_tmp,int size)
{
    char u8Index;
    while(size >4096)
    {    
        Dd_Flash_WrEnable();    

        WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TX_MODE);

        /* Enable SPI CFG */              
        WRITE_REG(SPI_FLASH_Ssienr, 0x1);

        /*Write Cmd and Addr*/
        WRITE_REG(SPI_FLASH_Dr_Low, DD_CMD_SECTORERASE);
        WRITE_REG(SPI_FLASH_Dr_Low, ((sector_tmp&0xFF0000)>>16));
        WRITE_REG(SPI_FLASH_Dr_Low, ((sector_tmp&0xFF00)>>8 ));
        WRITE_REG(SPI_FLASH_Dr_Low, (sector_tmp&0xFF));

        
        /*wait spi transfer start*/
        u8Index = 0;
        while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
        {
        	u8Index++;
        	if(u8Index > 10) break;
        } /*wait SPI busy*/

        /* wait SPI idle */	  
        while(READ_REG(SPI_FLASH_Sr) &0x1); 
        
        /* Disable SPI_CFG */
        WRITE_REG(SPI_FLASH_Ssienr, 0x0);

        Dd_Wait_Flash_ready();
        size = size-4096;
        sector_tmp = sector_tmp + 4096;
    }    
    Dd_Flash_WrEnable();    

    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TX_MODE);

    /* Enable SPI CFG */              
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);

    /*Write Cmd and Addr*/
    WRITE_REG(SPI_FLASH_Dr_Low, DD_CMD_SECTORERASE);
    WRITE_REG(SPI_FLASH_Dr_Low, ((sector_tmp&0xFF0000)>>16));
    WRITE_REG(SPI_FLASH_Dr_Low, ((sector_tmp&0xFF00)>>8 ));
    WRITE_REG(SPI_FLASH_Dr_Low, (sector_tmp&0xFF));

    
    /*wait spi transfer start*/
    u8Index = 0;
    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
    {
    	u8Index++;
    	if(u8Index > 10) break;
    } /*wait SPI busy*/

    /* wait SPI idle */	  
    while(READ_REG(SPI_FLASH_Sr) &0x1); 
    
    /* Disable SPI_CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x0);

    Dd_Wait_Flash_ready();
    
}

void Dd_Spi_Flash_Write(int addr, unsigned char *data, int len)
{
    int u32Index;

    while(len >= 256)
    {
        Dd_Flash_WrEnable();
        
        WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TX_MODE);

        /* Enable SPI CFG */              
        WRITE_REG(SPI_FLASH_Ssienr, 0x1);

        /*Write Cmd and Addr*/
        WRITE_REG(SPI_FLASH_Dr_Low, DD_CMD_WRITE);
        WRITE_REG(SPI_FLASH_Dr_Low, ((addr&0xFF0000)>>16));
        WRITE_REG(SPI_FLASH_Dr_Low, ((addr&0xFF00  )>>8 ));
        WRITE_REG(SPI_FLASH_Dr_Low, ( addr&0xFF)         );

        /*Write Data*/
        for(u32Index = 0;u32Index < 256; u32Index++)
        {   
            /*if fifo is full*/
            while((READ_REG(SPI_FLASH_Sr) & DW_TX_FIFO_FULL_BIT) == 0);
            
            WRITE_REG(SPI_FLASH_Dr_Low, data[u32Index]);
        }

        /*wait spi transfer start*/
        u32Index = 0;
        while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
        {
        	u32Index++;
        	if(u32Index > 10) break;
        } /*wait SPI busy*/

        /* wait SPI idle */	  
        while(READ_REG(SPI_FLASH_Sr) &0x1); 
        
        /* Disable SPI_CFG */
        WRITE_REG(SPI_FLASH_Ssienr, 0x0); 
        Dd_Wait_Flash_ready();

    	len -= 256;
    	data += 256;
    	addr += 256;
    }
    Dd_Flash_WrEnable();
    
    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TX_MODE);

    /* Enable SPI CFG */              
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);

    /*Write Cmd and Addr*/
    WRITE_REG(SPI_FLASH_Dr_Low, DD_CMD_WRITE);
    WRITE_REG(SPI_FLASH_Dr_Low, ((addr&0xFF0000)>>16));
    WRITE_REG(SPI_FLASH_Dr_Low, ((addr&0xFF00  )>>8 ));
    WRITE_REG(SPI_FLASH_Dr_Low, ( addr&0xFF)         );

    /*Write Data*/
    for(u32Index = 0;u32Index < len ; u32Index++)
    {   
        /*if fifo is full*/
        while((READ_REG(SPI_FLASH_Sr) & DW_TX_FIFO_FULL_BIT) == 0);
        
        WRITE_REG(SPI_FLASH_Dr_Low, data[u32Index]);
    }

    /*wait spi transfer start*/
    u32Index = 0;
    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
    {
    	u32Index++;
    	if(u32Index > 10) break;
    } /*wait SPI busy*/

    /* wait SPI idle */	  
    while(READ_REG(SPI_FLASH_Sr) &0x1); 
    
    /* Disable SPI_CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x0); 
    Dd_Wait_Flash_ready();
}


void  Dd_Spi_Flash_Read(int addr,unsigned char *data,int len)
{
    int u32WriteIndex = 0;  
    int u32ReadIndex = 0;

    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TXRX_MODE);

    /* Enable SPI CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);

    /* Read Cmd and Addr */
    WRITE_REG(SPI_FLASH_Dr_Low, DD_CMD_READ);
    WRITE_REG(SPI_FLASH_Dr_Low, ((addr&0xFF0000)>>16));
    WRITE_REG(SPI_FLASH_Dr_Low, ((addr&0xFF00  )>>8 ));
    WRITE_REG(SPI_FLASH_Dr_Low, ( addr&0xFF));
    
    for(u32WriteIndex = 0;u32WriteIndex < len ; u32WriteIndex++)
    {
        
    	WRITE_REG(SPI_FLASH_Dr_Low, 0x00);
        while((READ_REG(SPI_FLASH_Sr) &DW_TX_FIFO_FULL_BIT) == 0);
        /*while Rx fifo is not empty*/
        if((READ_REG(SPI_FLASH_Sr) & DW_RX_FIFO_EMPTY_BIT) == DW_RX_FIFO_EMPTY_BIT)
        {
            if(u32ReadIndex<4)
        	{
        	    READ_REG(SPI_FLASH_Dr_Low);
            }
            else
            {
            	data[u32ReadIndex-4] = READ_REG(SPI_FLASH_Dr_Low);
            }    
        	u32ReadIndex++;
        }
    }

 //   u32WriteIndex = 0;
    /* wait spi transfer start */
    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0)
    {
 //   	u32WriteIndex++;
 //   	if(u32WriteIndex > 10) break;
    }
    
   	/* wait SPI idle */	
    while(READ_REG(SPI_FLASH_Sr) &0x1); 

    /*while Rx fifo is not empty Read Data */
    while((READ_REG(SPI_FLASH_Sr) &DW_RX_FIFO_EMPTY_BIT) == DW_RX_FIFO_EMPTY_BIT)
    {
        if(u32ReadIndex<4)
    	{
    	    READ_REG(SPI_FLASH_Dr_Low);
        }
        else
        {
        	data[u32ReadIndex-4] = READ_REG(SPI_FLASH_Dr_Low);
		    u32ReadIndex++;
        }    
    }
    /* Disable SPI_CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x0); 

}

void  Dd_Spi_Flash_Read_byte(int addr,unsigned char *data,int len)
{
    int u32WriteIndex = 0;
    int u32ReadIndex = 0;

    WRITE_REG(SPI_FLASH_Ctrlr0,DD_SPI_8BIT_TXRX_MODE);

    /* Enable SPI CFG */
    WRITE_REG(SPI_FLASH_Ssienr, 0x1);

    /* Read Cmd and Addr */
    WRITE_REG(SPI_FLASH_Dr_Low, DD_CMD_READ);
    WRITE_REG(SPI_FLASH_Dr_Low, ((addr&0xFF0000)>>16));
    WRITE_REG(SPI_FLASH_Dr_Low, ((addr&0xFF00  )>>8 ));
    WRITE_REG(SPI_FLASH_Dr_Low, ( addr&0xFF));

    while(u32WriteIndex < len)
    {
        while((READ_REG(SPI_FLASH_Sr) &DW_TX_FIFO_FULL_BIT) == DW_TX_FIFO_FULL_BIT)
        {
            if(u32WriteIndex >= len)
                break;

            WRITE_REG(SPI_FLASH_Dr_Low, 0x00);
            u32WriteIndex++;
        }

        while((READ_REG(SPI_FLASH_Sr) &DW_RX_FIFO_EMPTY_BIT) == DW_RX_FIFO_EMPTY_BIT)
        {
            	data[u32ReadIndex] = READ_REG(SPI_FLASH_Dr_Low);
    		    u32ReadIndex++;
        }
    }
//    while((READ_REG(SPI_FLASH_Sr) &0x1) == 0x0);

    while(READ_REG(SPI_FLASH_Sr) &0x1);

    while((READ_REG(SPI_FLASH_Sr) &DW_RX_FIFO_EMPTY_BIT) == DW_RX_FIFO_EMPTY_BIT)
    {
        	data[u32ReadIndex] = READ_REG(SPI_FLASH_Dr_Low);
		    u32ReadIndex++;
    }

    WRITE_REG(SPI_FLASH_Ssienr, 0x0);
}

