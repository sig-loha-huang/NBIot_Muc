/******************************* �����ļ����� *********************************/
#include <cortex_m4.h>
#include <stdio.h>
#include <vos.h>
/******************************* �ֲ��궨�� ***********************************/
#define CONFIG_SF_DEFAULT_SPEED		       1000000

#define SPI_FLASH_READ_ADDR                0x08000000
#define SPI_FLASH_WRITE_ADDR               0x08000000
#define SPI_FLASH_ERASE_SEC_ADDR           0x0F000000    
#define SPI_FLASH_ERASE_B32_ADDR           0x0E000000    
#define SPI_FLASH_ERASE_B64_ADDR           0x0C000000    
#define SPI_FLASH_WRITE_EN_ADDR            0x0d100000
#define SPI_FLASH_ERASE_CHIP_ADDR          0x0d300000 

#define SPI_FLASH_ERASE_TIMEING            600

#define     DD_FLASH_WP_PIN  5
#define     DD_FLASH_HOLD_PIN  4

#define     DD_SUCCESS  1
#define     DD_FAIL     0
/******************************* �ֲ����������Ͷ��� ***************************/

/******************************* �ֲ�����ԭ������ *****************************/

/******************************* ����ʵ�� *************************************/
/****************************IC ģ�����flash *********************************/
/*******************************************************************************
* ��������: Dd_flash_Ic_Init
* ��������: IC��дflash��ʼ������
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��: ����flash timing��д�ȴ�ʱ��
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_flash_Ic_Init(void)
{
    /*flash timeing*/
    REG(REG_FLASH_TIMING_CFG) = (REG(REG_FLASH_TIMING_CFG) & 0xFFFF0000)|(2<<8) | (ARM_CLK/1000000 + 1);
    
    REG(REG_FLASH_WAIT_CFG1) = (REG(REG_FLASH_WAIT_CFG1) & 0xFFFFFC00) | SPI_FLASH_ERASE_TIMEING;

	REG(REG_FLASH_WAIT_CFG1) = (REG(REG_FLASH_WAIT_CFG1) & 0xFFC3FFFF) |(15<<18);

    /*write waiting time 100us*/
    REG(REG_FLASH_WAIT_CFG2) = (REG(REG_FLASH_WAIT_CFG2) & 0xFFFFFC00) | 200;

    Dd_Fast_read_config();
}
/*******************************************************************************
* ��������: Dd_flash_Ic_write
* ��������: ICдflash
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��: 
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
int Dd_flash_Ic_write(int addr, unsigned char *data, int len)
{       
    int i;
    int remainder; 
    unsigned int lastdata = 0;
    unsigned int curdata;
    unsigned int * u32data;

    if(addr<0x100000)
    {
        DD_DEBUG_PRINTF("Flash Write Error %x\r\n",addr);
        return (-1);
    }    
    if((addr % 4) != 0)
    {
        DD_DEBUG_PRINTF("Flash Addr Error %x\r\n",addr);
        return (-1);
    }  

    addr = (addr + SPI_FLASH_WRITE_ADDR); 
    
    u32data = (unsigned int *)data;

    /*write data*/
    for(i = 0;i< (len/4);i++)
    {
        curdata = u32data[i];
        REG(SPI_FLASH_WRITE_EN_ADDR) = 0x01;
        *(unsigned int *)(addr+i*4) = curdata;

		vTaskDelay(10 / 1);		
        Feed_dog();                
    }

    remainder = len % 4;

    if(remainder == 0)
    {
	    return DD_SUCCESS;
    }    
    else if(remainder == 1)
    {
       lastdata = data[len - 1] | 0xFFFFFF00;
    }
    else if(remainder == 2)
    {
       lastdata = ((data[len - 1]<<8) | data[len - 2]) | 0xFFFF0000;
    }   
    else if(remainder == 3)
    {
       lastdata = (((data[len - 1]<<16) | (data[len - 2]<<8)) | data[len - 3]) | 0xFF000000;
    }   

    REG(SPI_FLASH_WRITE_EN_ADDR) = 0x01;
    
    *(unsigned int *)(addr+i*4) = lastdata;
        
	return DD_SUCCESS;
}
/*******************************************************************************
* ��������: Dd_flash_Ic_normal_read
* ��������: IC��ͨ��flash
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��: 
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
int Dd_flash_Ic_normal_read(int addr,unsigned char *data,int len,unsigned long *numberOfBytesRead)
{
    int i;
    addr = (addr + SPI_FLASH_READ_ADDR);

    /*wp pin,hold pin config for normal read */
  //  REG(REG_B_IO_FUNC_HSEL0_CLR) |= (0x1 << DD_FLASH_WP_PIN) | (0x1 << DD_FLASH_HOLD_PIN);
  //  REG(REG_B_IO_FUNC_LSEL0_CLR) |= (0x1 << DD_FLASH_WP_PIN) | (0x1 << DD_FLASH_HOLD_PIN);

    /*normal read cmd*/
    REG(REG_FLASH_CMD2) =  0x003;
    
    /*write data*/
    for(i = 0;i< len;i++)
    {
        data[i] = *(unsigned char *)(addr+i);    
    }
    
    *numberOfBytesRead = len;
    
	return DD_SUCCESS;
   
}
/*******************************************************************************
* ��������: Dd_flash_Ic_erase
* ��������: IC����flash����(����������)
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��: 
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
int Dd_flash_Ic_erase(int sector_tmp,int size)
{
    int i;
    int count = 0 ;


    if(sector_tmp<0x100000)
    {
        DD_DEBUG_PRINTF("Flash erase Error %x\r\n",sector_tmp);
        return (-1);
    }    
    sector_tmp = (sector_tmp + SPI_FLASH_ERASE_SEC_ADDR);

    /*config erase block waiting time*/
    //REG(REG_FLASH_WAIT_CFG1) = (REG(REG_FLASH_WAIT_CFG1) & 0xFFFFFC00) | SPI_FLASH_ERASE_TIMEING;

    /*erase*/
    count = size / 4096;

    if(size %4096 != 0)
    {
        count++;
    }    

    for(i = 0;i<count;i++)
    {
        /*wirte enable cmd*/
        REG(SPI_FLASH_WRITE_EN_ADDR) = 0x01;
        REG(sector_tmp+(i*4096)) = 0xFF;
        Feed_dog();        
    }
        
	return DD_SUCCESS;

    
}
/*******************************************************************************
* ��������: Dd_flash_Ic_read
* ��������: IC���ٶ�flash����(����4�߶�flash)
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��: 
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
void Dd_Fast_read_config(void)
{
    /*wp pin,hold pin config for normal read */
    REG(REG_B_IO_FUNC_HSEL0_SET) |= (0x1 << DD_FLASH_WP_PIN) | (0x1 << DD_FLASH_HOLD_PIN);
    REG(REG_B_IO_FUNC_LSEL0_CLR) |= (0x1 << DD_FLASH_WP_PIN) | (0x1 << DD_FLASH_HOLD_PIN);

    /*wirte enable cmd*/
    REG(SPI_FLASH_WRITE_EN_ADDR) = 0x01;
    WRITE_REG(0x0d400000,0x02);

    /*normal read cmd*/
    REG(REG_FLASH_CMD2) =  0x1EB;
}

int Dd_flash_Ic_read(int addr,unsigned char *data,int len,unsigned long *numberOfBytesRead)
{
    int i;
    addr = (addr + SPI_FLASH_READ_ADDR);
#if 0
    /*wp pin,hold pin config for normal read */
    REG(REG_B_IO_FUNC_HSEL0_SET) |= (0x1 << DD_FLASH_WP_PIN) | (0x1 << DD_FLASH_HOLD_PIN);
    REG(REG_B_IO_FUNC_LSEL0_CLR) |= (0x1 << DD_FLASH_WP_PIN) | (0x1 << DD_FLASH_HOLD_PIN);

    /*wirte enable cmd*/
    REG(SPI_FLASH_WRITE_EN_ADDR) = 0x01;
    WRITE_REG(0x0d400000,0x02);

    /*normal read cmd*/
    REG(REG_FLASH_CMD2) =  0x1EB;
#endif    
    /*write data*/
    for(i = 0;i< len;i++)
    {
        data[i] = *(unsigned char *)(addr+i);    
    }
    
    *numberOfBytesRead = len;
    
	return DD_SUCCESS;
   
}    
/*******************************************************************************
* ��������: Dd_flash_Ic_erase_block
* ��������: IC�������flash����
* ����ĵ�: 
* ��������:
* ��������:  
* ����ֵ:
* ����˵��: 
* �޸����ڰ汾���޸����޸�����
* -----------------------------------------------------------------
* 
*******************************************************************************/
int Dd_flash_Ic_erase_block(int BlockAddr,int size)
{
    int i;
    int count ;
    
    BlockAddr = (BlockAddr + SPI_FLASH_ERASE_B64_ADDR);

    /*config erase block waiting time*/
    REG(REG_FLASH_WAIT_CFG1) = (REG(REG_FLASH_WAIT_CFG1) & 0xFFFFFC00) | 200;


    /*erase cmd 64K*/
    count = size / 0x10000;//(64*1024);

    if(size %0x10000 != 0)
    {
        count++;
    }    

    for(i = 0;i<count;i++)
    {
        /*wirte enable cmd*/
        REG(SPI_FLASH_WRITE_EN_ADDR) = 0x01;
        REG(BlockAddr+(i*0x10000)) = 0xFF;
    }
        
	return DD_SUCCESS;
    
}



/******************************* Դ�ļ����� ***********************************/

