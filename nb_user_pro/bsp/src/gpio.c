/*******************************************************************************
* COPYRIGHT@SIGBEN
*******************************************************************************
* �ļ�����:  gpio.c
* ��������: 
* ʹ��˵��:
* �ļ�����:                
* ��д����: 
* �޸���ʷ: 
* �޸������޸���  BugID/CRID      �޸�����
* -----------------------------------------------------------------------------
* 
******************************************************************************/

/******************************* �����ļ����� *********************************/
#include <stdio.h>
#include <cortex_m4.h>
/******************************* �ֲ��궨�� ***********************************/

/******************************* ȫ�ֱ�������/��ʼ�� **************************/

/******************************* �ֲ����������Ͷ��� ***************************/

/******************************* �ֲ�����ԭ������ *****************************/

/******************************* ����ʵ�� *************************************/

/********************** gpio B �������� ***************************************/
/****** ����IO����Ϊ����0 gpio����*********************************************/
void Dd_SetIOAFunction0(u32 PinBit)
{
    REG(REG_IO_FUNC_HSEL0_CLR) |= (1<<PinBit);
    REG(REG_IO_FUNC_LSEL0_CLR) |= (1<<PinBit);
}

/****** ����IO����Ϊ����1 ****************************************************/
void Dd_SetIOAFunction1(u32 PinBit)
{
    REG(REG_IO_FUNC_HSEL0_CLR) |= (1<<PinBit);
    REG(REG_IO_FUNC_LSEL0_SET) |= (1<<PinBit);
}

/****** ����IO����Ϊ����2 ****************************************************/
void Dd_SetIOAFunction2(u32 PinBit)
{
    REG(REG_IO_FUNC_HSEL0_SET) |= (1<<PinBit);
    REG(REG_IO_FUNC_LSEL0_CLR) |= (1<<PinBit);
}

/****** ����IO����Ϊ����3 ****************************************************/
void Dd_SetIOAFunction3(u32 PinBit)
{
    REG(REG_IO_FUNC_HSEL0_SET) |= (1<<PinBit);
    REG(REG_IO_FUNC_LSEL0_SET) |= (1<<PinBit);
}

/****** ����IO����Ϊ����0 gpio����*********************************************/
void Dd_SetIOBFunction0(u32 PinBit)
{
    REG(REG_B_IO_FUNC_HSEL0_CLR) |= (1<<PinBit);
    REG(REG_B_IO_FUNC_LSEL0_CLR) |= (1<<PinBit);
}

/****** ����IO����Ϊ����1 ****************************************************/
void Dd_SetIOBFunction1(u32 PinBit)
{
    REG(REG_B_IO_FUNC_HSEL0_CLR) |= (1<<PinBit);
    REG(REG_B_IO_FUNC_LSEL0_SET) |= (1<<PinBit);
}

/****** ����IO����Ϊ����2 ****************************************************/
void Dd_SetIOBFunction2(u32 PinBit)
{
    REG(REG_B_IO_FUNC_HSEL0_SET) |= (1<<PinBit);
    REG(REG_B_IO_FUNC_LSEL0_CLR) |= (1<<PinBit);
}

/****** ����IO����Ϊ����3 ****************************************************/
void Dd_SetIOBFunction3(u32 PinBit)
{
    REG(REG_B_IO_FUNC_HSEL0_SET) |= (1<<PinBit);
    REG(REG_B_IO_FUNC_LSEL0_SET) |= (1<<PinBit);
}



/********************* ����gpio�������ģʽ************************************/
void Dd_GpioB_SetDir(u32 u32PinBit,u32 u32DirFlag)
{
    if(GPIO_DIR_INPUT == u32DirFlag)
    {
        REG(REG_GPIO_SWPORTB_DDR) &=  (~(0x1 << u32PinBit)); 
    }   
    else if(GPIO_DIR_OUTPUT == u32DirFlag)
    {
        REG(REG_GPIO_SWPORTB_DDR) |=  (0x1 << u32PinBit); 
    }    
}
void Dd_GpioB_SetOut(u32 u32PinBit,u32 u32OutFlag)
{
    if(GPIO_OUTPUT_LOW == u32OutFlag)
    {
        REG(REG_GPIO_SWPORTB_DR) &= (~(0x1 << u32PinBit));
    }   
    else if(GPIO_OUTPUT_HIGH == u32OutFlag)
    {
        REG(REG_GPIO_SWPORTB_DR) |= (0x1 << u32PinBit);
    }  
}

void Dd_GpioA_SetDir(u32 u32PinBit,u32 u32DirFlag)
{
    if(GPIO_DIR_INPUT == u32DirFlag)
    {
        REG(REG_GPIO_SWPORTA_DDR) &=  (~(0x1 << u32PinBit)); 
    }   
    else if(GPIO_DIR_OUTPUT == u32DirFlag)
    {
        REG(REG_GPIO_SWPORTA_DDR) |=  (0x1 << u32PinBit); 
    }    
}
void Dd_GpioA_SetOut(u32 u32PinBit,u32 u32OutFlag)
{
    if(GPIO_OUTPUT_LOW == u32OutFlag)
    {
        REG(REG_GPIO_SWPORTA_DR) &= (~(0x1 << u32PinBit));
    }   
    else if(GPIO_OUTPUT_HIGH == u32OutFlag)
    {
        REG(REG_GPIO_SWPORTA_DR) |= (0x1 << u32PinBit);
    }  
}


/********************* ��ȡ����gpio���� **************************************/
u32 Dd_GpioA_ReadData(void)
{
    unsigned int Value;
    Value = REG(REG_GPIO_SWPORTA_EXT_PORTA);
    return Value;
}
u32 Dd_GpioB_ReadData(void)
{
    unsigned int Value;
    Value = REG(REG_GPIO_SWPORTB_EXT_PORTA);
    return Value;
}

u8 Dd_GpioA_ReadPinBit(u32 u32PinBit)
{
    u32 tmp;
    tmp = REG(REG_GPIO_SWPORTA_EXT_PORTA);
    if(((tmp>>u32PinBit) & 0x1) == 1)
        return 1;
    else
        return 0;
}
u8 Dd_GpioB_ReadPinBit(u32 u32PinBit)
{
    u32 tmp;
    tmp = REG(REG_GPIO_SWPORTB_EXT_PORTA);
    if(((tmp>>u32PinBit) & 0x1) == 1)
        return 1;
    else
        return 0;
}
/********************* ����gpio�ж� *******************************************/
void Dd_GpioB_SetInterFun(u8 IntTpye,u8 IntPolarity,u32 u32PinBit)
{
    if(IntTpye == GPIO_INT_TYPE_LEVEL)
    {
        /*�жϴ�����ʽ ���óɵ�ƽ������ʽ*/
        REG(REG_GPIO_SWPORTB_INTTYPE_LEVEL) &= (~(0x1 << u32PinBit)); 
    }
    else if(IntTpye == GPIO_INT_TYPE_EDGE)
    {
        /*�жϴ�����ʽ ���óɱ��ش�����ʽ*/
        REG(REG_GPIO_SWPORTB_INTTYPE_LEVEL) |= (0x1 << u32PinBit); 

        /*˫�ش���*/
        if(IntPolarity == GPIO_INT_POLA_BOTH)
        {
            REG(REG_GPIO_SWPORTB_INT_BOTHEDGE) |= (0x1 << GPIO_PIN_02);
            REG(REG_GPIO_SWPORTB_INTEN) |= (0x1 << u32PinBit);
            return ;
        }   
    }
    /*�ߵ�ƽ���� �����ش���*/
    if(GPIO_INT_POLA_HIGH == IntPolarity)
    {
        REG(REG_GPIO_SWPORTB_INT_POLARITY) |= (0x1 << u32PinBit);
    }
    /*�͵�ƽ���� �½��ش���*/
    else if(GPIO_INT_POLA_LOW == IntPolarity)
    {
        REG(REG_GPIO_SWPORTB_INT_POLARITY) &= (~(0x1 << u32PinBit));
    }    
    /*ʹ���ж�*/
    REG(REG_GPIO_SWPORTB_INTEN) |= (0x1 << u32PinBit);
}

/******************** gpio �ж� *******************************************/
void Dd_GpioB_Isr(void)
{
    unsigned int State;
    
    /*��ȡ�ж�״̬*/
    State = REG(REG_GPIO_SWPORTB_INTSTATUS);

    /*gpioB pin0*/
    if((State & (1<<0)) != 0)
    {
        /*����ж�*/
        REG(REG_GPIO_SWPORTB_PORTA_EOI) = 1;    
    }    
    else if((State & (1<<1)) != 0)
    {
        /*����ж�*/
        REG(REG_GPIO_SWPORTB_PORTA_EOI) = (1<<1);    
    }    
    else if((State & (1<<2)) != 0)
    {
        /*����ж�*/
        REG(REG_GPIO_SWPORTB_PORTA_EOI) = (1<<2);   
    }
    else if((State & (1<<3)) != 0)
    {
        /*����ж�*/
        REG(REG_GPIO_SWPORTB_PORTA_EOI) = (1<<3);   
    }
    /**add other user code***/
}   

void Dd_GpioA_Isr(void)
{
    unsigned int State;
    
    /*��ȡ�ж�״̬*/
    State = REG(REG_GPIO_SWPORTA_INTSTATUS);

    /*gpioB pin0*/
    if((State & (1<<0)) != 0)
    {
        /*����ж�*/
        REG(REG_GPIO_SWPORTA_PORTA_EOI) = 1;    
    }    
    else if((State & (1<<1)) != 0)
    {
        /*����ж�*/
        REG(REG_GPIO_SWPORTA_PORTA_EOI) = (1<<1);    
    }    
    else if((State & (1<<2)) != 0)
    {
        /*����ж�*/
        REG(REG_GPIO_SWPORTA_PORTA_EOI) = (1<<2);   
    }
    else if((State & (1<<3)) != 0)
    {
        /*����ж�*/
        REG(REG_GPIO_SWPORTA_PORTA_EOI) = (1<<3);   
    }
    /**add other user code***/
}   

/***************    gpio ���ܲ���     **************************************/
void Dd_Gpio_Led_Init(void)
{
    Dd_SetIOAFunction0(GPIO_LED_RED_PIN);
    Dd_SetIOAFunction0(GPIO_LED_GREEN_PIN);

    Dd_GpioA_SetDir(GPIO_LED_RED_PIN,GPIO_DIR_OUTPUT);
    Dd_GpioA_SetDir(GPIO_LED_GREEN_PIN,GPIO_DIR_OUTPUT);
}

void Dd_Gpio_Led_RedOn(void)
{
    Dd_GpioA_SetOut(GPIO_LED_RED_PIN,GPIO_OUTPUT_HIGH);
}    

void Dd_Gpio_Led_RedOff(void)
{
    Dd_GpioA_SetOut(GPIO_LED_RED_PIN,GPIO_OUTPUT_LOW);
}    

void Dd_Gpio_Led_GreenOn(void)
{
    Dd_GpioA_SetOut(GPIO_LED_GREEN_PIN,GPIO_OUTPUT_HIGH);
}    

void Dd_Gpio_Led_GreenOff(void)
{
    Dd_GpioA_SetOut(GPIO_LED_GREEN_PIN,GPIO_OUTPUT_LOW);
}  

/******************************* Դ�ļ����� ***********************************/

