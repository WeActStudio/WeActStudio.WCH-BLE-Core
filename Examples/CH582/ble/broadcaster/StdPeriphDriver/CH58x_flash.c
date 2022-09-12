/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH58x_flash.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include "CH58x_common.h"

/* RESET_EN */
#define RESET_Enable           0x00000008
#define RESET_Disable          0xFFFFFFF7

/* LOCKUP_RST_EN */
#define UART_NO_KEY_Enable     0x00000100
#define UART_NO_KEY_Disable    0xFFFFFEFF

/* BOOT_PIN */
#define BOOT_PIN_PB22          0x00000200
#define BOOT_PIN_PB11          0xFFFFFDFF

/* FLASH_WRProt */
#define FLASH_WRProt           0xFFF003FF

/*********************************************************************
 * @fn      FLASH_ROM_READ
 *
 * @brief   Read Flash
 *
 * @param   StartAddr   - read address
 * @param   Buffer      - read buffer
 * @param   len         - read len
 *
 * @return  none
 */
void FLASH_ROM_READ(uint32_t StartAddr, void *Buffer, uint32_t len)
{
    uint32_t  i, Length = (len + 3) >> 2;
    uint32_t *pCode = (uint32_t *)StartAddr;
    uint32_t *pBuf = (uint32_t *)Buffer;

    for(i = 0; i < Length; i++)
    {
        *pBuf++ = *pCode++;
    }
}

/*********************************************************************
 * @fn      UserOptionByteConfig
 *
 * @brief   Configure User Option Byte.���ڵ����û���������Ч��������Ч,��ÿ����¼��ֻ���޸�һ��
 *          (ʹ�øú���������ʹ�ùٷ��ṩ��.S�ļ���ͬʱ���øú����������ϵ�����ߵ��Խӿ�Ĭ�Ϲر�)
 *
 * @param   RESET_EN        - �ⲿ��λ����ʹ��
 * @param   BOOT_PIN        - ENABLE-ʹ��Ĭ��boot��-PB22,DISABLE-ʹ��boot��-PB11
 * @param   UART_NO_KEY_EN  - �����ⰴ������ʹ��
 * @param   FLASHProt_Size  - д������С(��λ4K)
 *
 * @return  0-Success, 1-Err
 */
uint8_t UserOptionByteConfig(FunctionalState RESET_EN, FunctionalState BOOT_PIN, FunctionalState UART_NO_KEY_EN,
                           uint32_t FLASHProt_Size)
{
    uint32_t s, t;

    FLASH_ROM_READ(0x14, &s, 4);

    if(s == 0xF5F9BDA9)
    {
        s = 0;
        FLASH_EEPROM_CMD(CMD_GET_ROM_INFO, 0x7EFFC, &s, 4);
        s &= 0xFF;

        if(RESET_EN == ENABLE)
            s |= RESET_Enable;
        else
            s &= RESET_Disable;

        /* bit[7:0]-bit[31-24] */
        s |= ((~(s << 24)) & 0xFF000000); //��8λ ������Ϣȡ����

        if(BOOT_PIN == ENABLE)
            s |= BOOT_PIN_PB22;
        if(UART_NO_KEY_EN == ENABLE)
            s |= UART_NO_KEY_Enable;

        /* bit[23-10] */
        s &= 0xFF0003FF;
        s |= ((FLASHProt_Size << 10) | (5 << 20)) & 0x00FFFC00;

        /*Write user option byte*/
        FLASH_ROM_WRITE(0x14, &s, 4);

        /* Verify user option byte */
        FLASH_ROM_READ(0x14, &t, 4);

        if(s == t)
            return 0;
        else
            return 1;
    }

    return 1;
}

/*********************************************************************
 * @fn      UserOptionByteClose_SWD
 *
 * @brief   �����ߵ��Խӿڣ���������ֵ���ֲ���.���ڵ����û���������Ч��������Ч,��ÿ����¼��ֻ���޸�һ��
 *          (ʹ�øú���������ʹ�ùٷ��ṩ��.S�ļ���ͬʱ���øú����������ϵ�����ߵ��Խӿ�Ĭ�Ϲر�)
 *
 * @return  0-Success, 1-Err
 */
uint8_t UserOptionByteClose_SWD(void)
{
    uint32_t s, t;

    FLASH_ROM_READ(0x14, &s, 4);

    if(s == 0xF5F9BDA9)
    {
        FLASH_EEPROM_CMD(CMD_GET_ROM_INFO, 0x7EFFC, &s, 4);

        s &= ~((1 << 4) | (1 << 7)); //���õ��Թ��ܣ� ����SPI��дFLASH

        /* bit[7:0]-bit[31-24] */
        s &= 0x00FFFFFF;
        s |= ((~(s << 24)) & 0xFF000000); //��8λ ������Ϣȡ����

        /*Write user option byte*/
        FLASH_ROM_WRITE(0x14, &s, 4);

        /* Verify user option byte */
        FLASH_ROM_READ(0x14, &t, 4);

        if(s == t)
            return 0;
        else
            return 1;
    }

    return 1;
}

/*********************************************************************
 * @fn      UserOptionByte_Active
 *
 * @brief   �û���������Ч������ִ�к��Զ���λ
 *
 * @return  0-Success, 1-Err
 */
void UserOptionByte_Active(void)
{
    FLASH_ROM_SW_RESET();
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R16_INT32K_TUNE = 0xFFFF;
    R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
    R8_SAFE_ACCESS_SIG = 0;
    while(1);
}
