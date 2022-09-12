/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH58x_usb2dev.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include "CH58x_common.h"

uint8_t *pU2EP0_RAM_Addr;
uint8_t *pU2EP1_RAM_Addr;
uint8_t *pU2EP2_RAM_Addr;
uint8_t *pU2EP3_RAM_Addr;

/*********************************************************************
 * @fn      USB2_DeviceInit
 *
 * @brief   USB2�豸���ܳ�ʼ����4���˵㣬8��ͨ����
 *
 * @param   none
 *
 * @return  none
 */
void USB2_DeviceInit(void)
{
    R8_USB2_CTRL = 0x00; // ���趨ģʽ,ȡ�� RB_UC_CLR_ALL

    R8_U2EP4_1_MOD = RB_UEP4_RX_EN | RB_UEP4_TX_EN | RB_UEP1_RX_EN | RB_UEP1_TX_EN; // �˵�4 OUT+IN,�˵�1 OUT+IN
    R8_U2EP2_3_MOD = RB_UEP2_RX_EN | RB_UEP2_TX_EN | RB_UEP3_RX_EN | RB_UEP3_TX_EN; // �˵�2 OUT+IN,�˵�3 OUT+IN

    R16_U2EP0_DMA = (uint16_t)(uint32_t)pU2EP0_RAM_Addr;
    R16_U2EP1_DMA = (uint16_t)(uint32_t)pU2EP1_RAM_Addr;
    R16_U2EP2_DMA = (uint16_t)(uint32_t)pU2EP2_RAM_Addr;
    R16_U2EP3_DMA = (uint16_t)(uint32_t)pU2EP3_RAM_Addr;

    R8_U2EP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
    R8_U2EP1_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK | RB_UEP_AUTO_TOG;
    R8_U2EP2_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK | RB_UEP_AUTO_TOG;
    R8_U2EP3_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK | RB_UEP_AUTO_TOG;
    R8_U2EP4_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;

    R8_USB2_DEV_AD = 0x00;
    R8_USB2_CTRL = RB_UC_DEV_PU_EN | RB_UC_INT_BUSY | RB_UC_DMA_EN; // ����USB�豸��DMA�����ж��ڼ��жϱ�־δ���ǰ�Զ�����NAK
    R16_PIN_ANALOG_IE |= RB_PIN_USB2_IE | RB_PIN_USB2_DP_PU;        // ��ֹUSB�˿ڸ��ռ���������
    R8_USB2_INT_FG = 0xFF;                                          // ���жϱ�־
    R8_U2DEV_CTRL = RB_UD_PD_DIS | RB_UD_PORT_EN;                   // ����USB�˿�
    R8_USB2_INT_EN = RB_UIE_SUSPEND | RB_UIE_BUS_RST | RB_UIE_TRANSFER;
}

/*********************************************************************
 * @fn      U2DevEP1_IN_Deal
 *
 * @brief   U2�˵�1�����ϴ�
 *
 * @param   l   - �ϴ����ݳ���(<64B)
 *
 * @return  none
 */
void U2DevEP1_IN_Deal(uint8_t l)
{
    R8_U2EP1_T_LEN = l;
    R8_U2EP1_CTRL = (R8_U2EP1_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_ACK;
}

/*********************************************************************
 * @fn      U2DevEP2_IN_Deal
 *
 * @brief   U2�˵�2�����ϴ�
 *
 * @param   l   - �ϴ����ݳ���(<64B)
 *
 * @return  none
 */
void U2DevEP2_IN_Deal(uint8_t l)
{
    R8_U2EP2_T_LEN = l;
    R8_U2EP2_CTRL = (R8_U2EP2_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_ACK;
}

/*********************************************************************
 * @fn      U2DevEP3_IN_Deal
 *
 * @brief   U2�˵�3�����ϴ�
 *
 * @param   l   - �ϴ����ݳ���(<64B)
 *
 * @return  none
 */
void U2DevEP3_IN_Deal(uint8_t l)
{
    R8_U2EP3_T_LEN = l;
    R8_U2EP3_CTRL = (R8_U2EP3_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_ACK;
}

/*********************************************************************
 * @fn      U2DevEP4_IN_Deal
 *
 * @brief   U2�˵�4�����ϴ�
 *
 * @param   l   - �ϴ����ݳ���(<64B)
 *
 * @return  none
 */
void U2DevEP4_IN_Deal(uint8_t l)
{
    R8_U2EP4_T_LEN = l;
    R8_U2EP4_CTRL = (R8_U2EP4_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_ACK;
}
