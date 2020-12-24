
#ifndef __SPI_FLASH_H__
#define __SPI_FLASH_H__
/*
 ------------------------------------------------------------------------
--
//  ------------------------------------------------------------------------
//
//                    (C) COPYRIGHT 2002 - 2016 SYNOPSYS, INC.
//                            ALL RIGHTS RESERVED
//
//  This software and the associated documentation are confidential and
//  proprietary to Synopsys, Inc.  Your use or disclosure of this
//  software is subject to the terms and conditions of a written
//  license agreement between you, or your company, and Synopsys, Inc.
//
// The entire notice above must be reproduced on all authorized copies.
//
//  ------------------------------------------------------------------------

// 
// Release version :  4.01a
// File Version     :        $Revision: #4 $ 
// Revision: $Id: //dwh/DW_ocb/DW_apb_ssi/amba_dev/sim/verilog_header_file/spi_flash.h.v#4 $ 
//
// Abstract: Memory map header file for the DW_apb_ssi peripheral
*/



#define SPI_FLASH_SSI_BASE  0x40060000

#define SPI_FLASH_Ctrlr0_Offset      0x00
#define SPI_FLASH_Ctrlr1_Offset      0x04
#define SPI_FLASH_Ssienr_Offset      0x08
#define SPI_FLASH_Mwcr_Offset        0x0C
#define SPI_FLASH_Ser_Offset         0x10
#define SPI_FLASH_Baudr_Offset       0x14
#define SPI_FLASH_Txftlr_Offset      0x18
#define SPI_FLASH_Rxftlr_Offset      0x1C
#define SPI_FLASH_Txflr_Offset       0x20
#define SPI_FLASH_Rxflr_Offset       0x24
#define SPI_FLASH_Sr_Offset          0x28
#define SPI_FLASH_Imr_Offset         0x2C
#define SPI_FLASH_Isr_Offset         0x30
#define SPI_FLASH_Risr_Offset        0x34
#define SPI_FLASH_Txoicr_Offset      0x38
#define SPI_FLASH_Rxoicr_Offset      0x3C
#define SPI_FLASH_Rxuicr_Offset      0x40
#define SPI_FLASH_Msticr_Offset      0x44
#define SPI_FLASH_Icr_Offset         0x48
#define SPI_FLASH_Dmacr_Offset       0x4C
#define SPI_FLASH_Dmatdlr_Offset     0x50
#define SPI_FLASH_Dmardlr_Offset     0x54
#define SPI_FLASH_Idr_Offset         0x58
#define SPI_FLASH_Version_Id_Offset  0x5C
#define SPI_FLASH_Dr_Low_Offset      0x60
#define SPI_FLASH_Dr_High_Offset     0x9C

#define SPI_FLASH_Ctrlr0     (SPI_FLASH_SSI_BASE + SPI_FLASH_Ctrlr0_Offset    )
#define SPI_FLASH_Ctrlr1     (SPI_FLASH_SSI_BASE + SPI_FLASH_Ctrlr1_Offset    )
#define SPI_FLASH_Ssienr     (SPI_FLASH_SSI_BASE + SPI_FLASH_Ssienr_Offset    )
#define SPI_FLASH_Mwcr       (SPI_FLASH_SSI_BASE + SPI_FLASH_Mwcr_Offset      )
#define SPI_FLASH_Ser        (SPI_FLASH_SSI_BASE + SPI_FLASH_Ser_Offset       )
#define SPI_FLASH_Baudr      (SPI_FLASH_SSI_BASE + SPI_FLASH_Baudr_Offset     )
#define SPI_FLASH_Txftlr     (SPI_FLASH_SSI_BASE + SPI_FLASH_Txftlr_Offset    )
#define SPI_FLASH_Rxftlr     (SPI_FLASH_SSI_BASE + SPI_FLASH_Rxftlr_Offset    )
#define SPI_FLASH_Txflr      (SPI_FLASH_SSI_BASE + SPI_FLASH_Txflr_Offset     )
#define SPI_FLASH_Rxflr      (SPI_FLASH_SSI_BASE + SPI_FLASH_Rxflr_Offset     )
#define SPI_FLASH_Sr         (SPI_FLASH_SSI_BASE + SPI_FLASH_Sr_Offset        )
#define SPI_FLASH_Imr        (SPI_FLASH_SSI_BASE + SPI_FLASH_Imr_Offset       )
#define SPI_FLASH_Isr        (SPI_FLASH_SSI_BASE + SPI_FLASH_Isr_Offset       )
#define SPI_FLASH_Risr       (SPI_FLASH_SSI_BASE + SPI_FLASH_Risr_Offset      )
#define SPI_FLASH_Txoicr     (SPI_FLASH_SSI_BASE + SPI_FLASH_Txoicr_Offset    )
#define SPI_FLASH_Rxoicr     (SPI_FLASH_SSI_BASE + SPI_FLASH_Rxoicr_Offset    )
#define SPI_FLASH_Rxuicr     (SPI_FLASH_SSI_BASE + SPI_FLASH_Rxuicr_Offset    )
#define SPI_FLASH_Msticr     (SPI_FLASH_SSI_BASE + SPI_FLASH_Msticr_Offset    )
#define SPI_FLASH_Icr        (SPI_FLASH_SSI_BASE + SPI_FLASH_Icr_Offset       )
#define SPI_FLASH_Dmacr      (SPI_FLASH_SSI_BASE + SPI_FLASH_Dmacr_Offset     )
#define SPI_FLASH_Dmatdlr    (SPI_FLASH_SSI_BASE + SPI_FLASH_Dmatdlr_Offset   )
#define SPI_FLASH_Dmardlr    (SPI_FLASH_SSI_BASE + SPI_FLASH_Dmardlr_Offset   )
#define SPI_FLASH_Idr        (SPI_FLASH_SSI_BASE + SPI_FLASH_Idr_Offset       )
#define SPI_FLASH_Version_Id (SPI_FLASH_SSI_BASE + SPI_FLASH_Version_Id_Offset)
#define SPI_FLASH_Dr_Low     (SPI_FLASH_SSI_BASE + SPI_FLASH_Dr_Low_Offset    )
#define SPI_FLASH_Dr_High    (SPI_FLASH_SSI_BASE + SPI_FLASH_Dr_High_Offset   )

#define SSIi_ssi_0_PING_1BIT_WR (SPI_FLASH_Ctrlr0  )


#define     DW_TX_FIFO_FULL_BIT     0x02   
#define     DW_RX_FIFO_EMPTY_BIT    0x08

#define     DD_SPI_8BIT_TX_MODE     0x107
#define     DD_SPI_8BIT_RX_MODE     0x207
#define     DD_SPI_8BIT_TXRX_MODE   0x007

#define     DD_SPI0_SCLK_PIN        0      //GPIOB 0
#define     DD_SPI0_STEN_PIN        1      //GPIOB 1
#define     DD_SPI0_MOSI_PIN        2      //GPIOB 2
#define     DD_SPI0_MISO_PIN        3      //GPIOB 3
#define     DD_FLASH_WP_PIN  5
#define     DD_FLASH_HOLD_PIN  4

#define  	DD_CMD_WREN                  0x06
#define  	DD_CMD_WRDI                  0x04
#define  	DD_CMD_RDSR                  0x05
#define  	DD_CMD_WRSR                  0x01
#define  	DD_CMD_WRSR2                 0x31               //QE Bit

#define  	DD_CMD_READ                  0x03
#define  	DD_CMD_WRITE                 0x02
#define  	DD_CMD_FASTREAD              0x0B               // SPI Flash only
#define  	DD_CMD_FASTREAD_DUAL_OUTPUT  0x3B               // SPI Flash only
#define  	DD_CMD_BLOCKERASE            0xD8               // SPI Flash only
#define  	DD_CMD_SECTORERASE           0x20               // SPI Flash only
#define  	DD_CMD_CHIPERASE             0xC7               // SPI Flash only
#define  	DD_CMD_POWERDOWN             0xB9               // SPI Flash only
#define  	DD_CMD_RELEASE_POWERDOWN     0xAB               // SPI Flash only
#define  	DD_CMD_UNIQUE_ID             0x4B               // SPI Flash only
#define  	DD_CMD_SIMPLE_ID             0x90               // SPI Flash only
#define  	DD_CMD_JEDEC_ID              0x9F               // SPI Flash only

extern void Dd_Spi_Flash_Init(void);
extern void Dd_Spi_Flash_Write(int addr,unsigned char *data, int len);
extern void  Dd_Spi_Flash_Read(int addr,unsigned char *data,int len);
extern void Dd_Spi_Flash_Wirte_Cmd(int cmd, int len);
extern int Dd_Spi_Flash_Read_Cmd(int cmd);
extern void Dd_Flash_WrEnable(void);
extern void Dd_Wait_Flash_ready(void);
extern void Dd_Spi_Flash_sector_erase(int sector_tmp,int size);
extern unsigned short Dd_Read_FlashId(void);
extern void Dd_boot_spi_init(void);

         
#endif

