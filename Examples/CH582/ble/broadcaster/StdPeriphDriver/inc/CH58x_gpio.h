/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_gpio.h
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef __CH58x_GPIO_H__
#define __CH58x_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief	GPIO_pins_define
 */
#define GPIO_Pin_0      (0x00000001) /*!< Pin 0 selected */
#define GPIO_Pin_1      (0x00000002) /*!< Pin 1 selected */
#define GPIO_Pin_2      (0x00000004) /*!< Pin 2 selected */
#define GPIO_Pin_3      (0x00000008) /*!< Pin 3 selected */
#define GPIO_Pin_4      (0x00000010) /*!< Pin 4 selected */
#define GPIO_Pin_5      (0x00000020) /*!< Pin 5 selected */
#define GPIO_Pin_6      (0x00000040) /*!< Pin 6 selected */
#define GPIO_Pin_7      (0x00000080) /*!< Pin 7 selected */
#define GPIO_Pin_8      (0x00000100) /*!< Pin 8 selected */
#define GPIO_Pin_9      (0x00000200) /*!< Pin 9 selected */
#define GPIO_Pin_10     (0x00000400) /*!< Pin 10 selected */
#define GPIO_Pin_11     (0x00000800) /*!< Pin 11 selected */
#define GPIO_Pin_12     (0x00001000) /*!< Pin 12 selected */
#define GPIO_Pin_13     (0x00002000) /*!< Pin 13 selected */
#define GPIO_Pin_14     (0x00004000) /*!< Pin 14 selected */
#define GPIO_Pin_15     (0x00008000) /*!< Pin 15 selected */
#define GPIO_Pin_16     (0x00010000) /*!< Pin 16 selected */
#define GPIO_Pin_17     (0x00020000) /*!< Pin 17 selected */
#define GPIO_Pin_18     (0x00040000) /*!< Pin 18 selected */
#define GPIO_Pin_19     (0x00080000) /*!< Pin 19 selected */
#define GPIO_Pin_20     (0x00100000) /*!< Pin 20 selected */
#define GPIO_Pin_21     (0x00200000) /*!< Pin 21 selected */
#define GPIO_Pin_22     (0x00400000) /*!< Pin 22 selected */
#define GPIO_Pin_23     (0x00800000) /*!< Pin 23 selected */
#define GPIO_Pin_All    (0xFFFFFFFF) /*!< All pins selected */

/**
 * @brief  Configuration GPIO Mode
 */
typedef enum
{
    GPIO_ModeIN_Floating, //��������
    GPIO_ModeIN_PU,       //��������
    GPIO_ModeIN_PD,       //��������
    GPIO_ModeOut_PP_5mA,  //����������5mA
    GPIO_ModeOut_PP_20mA, //����������20mA

} GPIOModeTypeDef;

/**
 * @brief  Configuration GPIO IT Mode
 */
typedef enum
{
    GPIO_ITMode_LowLevel,  //�͵�ƽ����
    GPIO_ITMode_HighLevel, //�ߵ�ƽ����
    GPIO_ITMode_FallEdge,  //�½��ش���
    GPIO_ITMode_RiseEdge,  //�����ش���

} GPIOITModeTpDef;

/**
 * @brief   GPIOA�˿�����ģʽ����
 *
 * @param   pin     - PA0-PA15
 * @param   mode    - �����������
 */
void GPIOA_ModeCfg(uint32_t pin, GPIOModeTypeDef mode);

/**
 * @brief   GPIOB�˿�����ģʽ����
 *
 * @param   pin     - PB0-PB23
 * @param   mode    - �����������
 */
void GPIOB_ModeCfg(uint32_t pin, GPIOModeTypeDef mode);

/**
 * @brief   GPIOA�˿���������õ�
 *
 * @param   pin     - PA0-PA15
 */
#define GPIOA_ResetBits(pin)      (R32_PA_CLR |= pin)

/**
 * @brief   GPIOA�˿���������ø�
 *
 * @param   pin     - PA0-PA15
 */
#define GPIOA_SetBits(pin)        (R32_PA_OUT |= pin)

/**
 * @brief   GPIOB�˿���������õ�
 *
 * @param   pin     - PB0-PB23
 */
#define GPIOB_ResetBits(pin)      (R32_PB_CLR |= pin)

/**
 * @brief   GPIOB�˿���������ø�
 *
 * @param   pin     - PB0-PB23
 */
#define GPIOB_SetBits(pin)        (R32_PB_OUT |= pin)

/**
 * @brief   GPIOA�˿����������ƽ��ת
 *
 * @param   pin     - PA0-PA15
 */
#define GPIOA_InverseBits(pin)    (R32_PA_OUT ^= pin)

/**
 * @brief   GPIOB�˿����������ƽ��ת
 *
 * @param   pin     - PB0-PB23
 */
#define GPIOB_InverseBits(pin)    (R32_PB_OUT ^= pin)

/**
 * @brief   GPIOA�˿�32λ���ݷ��أ���16λ��Ч
 *
 * @return  GPIOA�˿�32λ����
 */
#define GPIOA_ReadPort()          (R32_PA_PIN)

/**
 * @brief   GPIOB�˿�32λ���ݷ��أ���24λ��Ч
 *
 * @return  GPIOB�˿�32λ����
 */
#define GPIOB_ReadPort()          (R32_PB_PIN)

/**
 * @brief   GPIOA�˿�����״̬��0-���ŵ͵�ƽ��(!0)-���Ÿߵ�ƽ
 *
 * @param   pin     - PA0-PA15
 *
 * @return  GPIOA�˿�����״̬
 */
#define GPIOA_ReadPortPin(pin)    (R32_PA_PIN & (pin))

/**
 * @brief   GPIOB�˿�����״̬��0-���ŵ͵�ƽ��(!0)-���Ÿߵ�ƽ
 *
 * @param   pin     - PB0-PB23
 *
 * @return  GPIOB�˿�����״̬
 */
#define GPIOB_ReadPortPin(pin)    (R32_PB_PIN & (pin))

/**
 * @brief   GPIOA�����ж�ģʽ����
 *
 * @param   pin     - PA0-PA15
 * @param   mode    - ��������
 */
void GPIOA_ITModeCfg(uint32_t pin, GPIOITModeTpDef mode);

/**
 * @brief   GPIOB�����ж�ģʽ����
 *
 * @param   pin     - PB0-PB23
 * @param   mode    - ��������
 */
void GPIOB_ITModeCfg(uint32_t pin, GPIOITModeTpDef mode);

/**
 * @brief   ��ȡGPIOA�˿��жϱ�־״̬
 *
 * @return  GPIOA�˿��жϱ�־״̬
 */
#define GPIOA_ReadITFlagPort()       (R16_PA_INT_IF)

/**
 * @brief   ��ȡGPIOB�˿��жϱ�־״̬
 *
 * @return  GPIOB�˿��жϱ�־״̬
 */
#define GPIOB_ReadITFlagPort()       ((R16_PB_INT_IF & (~((GPIO_Pin_22 | GPIO_Pin_23) >> 14))) | ((R16_PB_INT_IF << 14) & (GPIO_Pin_22 | GPIO_Pin_23)))

/**
 * @brief   ��ȡGPIOA�˿������жϱ�־״̬
 *
 * @param   pin     - PA0-PA15
 *
 * @return  GPIOA�˿������жϱ�־״̬
 */
#define GPIOA_ReadITFlagBit(pin)     (R16_PA_INT_IF & (pin))

/**
 * @brief   ��ȡGPIOB�˿������жϱ�־״̬
 *
 * @param   pin     - PB0-PB23
 *
 * @return  GPIOB�˿������жϱ�־״̬
 */
#define GPIOB_ReadITFlagBit(pin)     (R16_PB_INT_IF & ((pin) | (((pin) & (GPIO_Pin_22 | GPIO_Pin_23)) >> 14)))

/**
 * @brief   ���GPIOA�˿������жϱ�־״̬
 *
 * @param   pin     - PA0-PA15
 */
#define GPIOA_ClearITFlagBit(pin)    (R16_PA_INT_IF = pin)

/**
 * @brief   ���GPIOB�˿������жϱ�־״̬
 *
 * @param   pin     - PB0-PB23
 */
#define GPIOB_ClearITFlagBit(pin)    (R16_PB_INT_IF = ((pin) | (((pin) & (GPIO_Pin_22 | GPIO_Pin_23)) >> 14)))

/**
 * @brief   ���蹦������ӳ��
 *
 * @param   s       - �Ƿ�ʹ��ӳ��
 * @param   perph   - RB_PIN_SPI0   -  SPI0:  PA12/PA13/PA14/PA15 -> PB12/PB13/PB14/PB15
 *                    RB_PIN_UART1  -  UART1: PA8/PA9 ->  PB12/PB13
 *                    RB_PIN_UART0  -  UART0: PB4/PB7 ->  PA15/PA14
 *                    RB_PIN_TMR2   -  TMR2:  PA11 ->  PB11
 *                    RB_PIN_TMR1   -  TMR1:  PA10 ->  PB10
 *                    RB_PIN_TMR0   -  TMR0:  PA9 ->  PB23
 */
void GPIOPinRemap(FunctionalState s, uint16_t perph);

/**
 * @brief   ģ������GPIO���Ź��ܿ���
 *
 * @param   s       - �Ƿ�����ģ�����蹦��
 * @param   perph   - RB_PIN_ADC0_1_IE      -  ADC0-1ͨ��
 *                    RB_PIN_ADC2_3_IE      -  ADC2-3ͨ��
 *                    RB_PIN_ADC4_5_IE      -  ADC4-5ͨ��
 *                    RB_PIN_ADC6_7_IE      -  ADC6-7ͨ��
 *                    RB_PIN_ADC8_9_IE      -  ADC8-9ͨ��
 *                    RB_PIN_ADC10_11_IE    -  ADC10-11ͨ��
 *                    RB_PIN_ADC12_13_IE    -  ADC12-13ͨ��
 *                    RB_PIN_XT32K_IE       -  �ⲿ32K����
 *                    RB_PIN_USB_IE         -  USB�����ź�����
 *                    RB_PIN_ETH_IE         -  ��̫�������ź�����
 *                    RB_PIN_SEG0_3_IE      -  LCD������SEG0-3��������
 *                    RB_PIN_SEG4_7_IE      -  LCD������SEG4-7��������
 *                    RB_PIN_SEG8_11_IE     -  LCD������SEG8-11��������
 *                    RB_PIN_SEG12_15_IE    -  LCD������SEG12-15��������
 *                    RB_PIN_SEG16_19_IE    -  LCD������SEG16-19��������
 *                    RB_PIN_SEG20_23_IE    -  LCD������SEG20-23��������
 */
void GPIOAGPPCfg(FunctionalState s, uint16_t perph);

#ifdef __cplusplus
}
#endif

#endif // __CH58x_GPIO_H__
