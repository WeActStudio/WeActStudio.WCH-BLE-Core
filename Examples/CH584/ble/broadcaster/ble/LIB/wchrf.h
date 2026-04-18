/********************************** (C) COPYRIGHT ******************************
 * File Name         : wchrf.h
 * Author            : WCH
 * Version           : V1.40
 * Date              : 2024/9/27
 * Description       : head file(CH585/CH584)
 *
 * Copyright (c) 2023 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics. 
*******************************************************************************/



/******************************************************************************/
#ifndef __WCH_RF_H
#define __WCH_RF_H

#include "stdint.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include "CH58xBLE_LIB.h"

typedef uint32_t rfRole_States_t;
// Define function type that rfRole process callback
typedef void (*pfnRfRoleProcess)( rfRole_States_t status, uint8_t id );

#define  RFIP_MODE_BLE                0
#define  RFIP_MODE_RF_BASIC           1
#define  RFIP_MODE_RF_FAST            2

/* RF DMA structure definition */
typedef struct
{
    uint32_t Status;         /* Status */
#define   STA_DMA_ENABLE         0x80000000
#define   STA_LEN_MASK           0x00000FFF

    uint32_t BufferSize;     /* Buffer lengths */
    uint32_t BufferAddr;     /* address pointer */
    uint32_t NextDescAddr;   /* next descriptor address pointer */
} RF_DMADESCTypeDef;

/* rfRole config structure definition */
typedef struct
{
    int8_t TxPower;
    RF_DMADESCTypeDef *pTx;
    RF_DMADESCTypeDef *pRx;
    pfnRfRoleProcess rfProcessCB;
    uint32_t processMask;
#define    RF_STATE_RX             (1<<0)
#define    RF_STATE_RBU            (1<<1)
#define    RF_STATE_TIMEOUT        (1<<2)
#define    RF_STATE_RX_CRCERR      (1<<3)
#define    RF_STATE_TX_FINISH      (1<<4)
#define    RF_STATE_TX_IDLE        (1<<5)
#define    RF_STATE_RX_RETRY       (1<<6)
#define    RF_STATE_MAP_UPDATE     (1<<7) //!< map update enable
} rfRoleConfig_t;

/*********************************************************************
 * GLOBAL MACROS
 */
#define  RF_MAX_DATA_LEN              251

// defined for properties
// whitening off enable
#define  BB_WHITENING_OFF             (1<<0)
#define  PROP_WAIT_ACK                (1<<1)
#define  BB_WHITENING_CH              (1<<2)


/* package type */
#define  PKT_HEAD_LEN           4
#define  PKT_ACK_LEN           (PKT_HEAD_LEN-2)
#define  PKT_RESV_LEN           PKT_ACK_LEN

/* device id type */
#define  RF_ROLE_ID_INVALD       (0x07)
#define  RF_ROLE_ID_MASK         (0x07)
#define  RF_ROLE_BOUND_MAX       (0x07)
#define  RF_ROLE_BOUND_ID        RF_ROLE_ID_INVALD
#define  RF_ROLE_DISCARDED_EN    (1<<3)

#define  RF_BOUND_MUTI_MAX        2
#define  RF_BOUND_4K_MAX          7

/* bound status */
#define BOUND_STA_SUCCESS        0x00   //!< Success
#define BOUND_STA_FAILURE        0x01   //!< Failure
#define BOUND_STA_INVALIDPARM    0x02   //!< Invalid request field
#define BOUND_STA_TIMEOUT        0x17   //!< timeout

/* bound request */
#define  BOUND_REQ_TYPE          0x01  //!< 4k mode
#define  BOUND_FAST_REQ_TYPE     0x02  //!< 8k mode
#define  BOUND_MUTI_REQ_TYPE     0x04  //!< muti fast mode
#define  BOUND_LP_REQ_TYPE       0x10  //!< lower power mode

/* package type */
typedef struct
{
    uint8_t type;                 //!< bit0-2:device id
                                  //!< bit3-7:reserved
    uint8_t length;               //!< data length
    uint8_t seq;                  //!< reserved
    uint8_t resv;                 //!< reserved
} rfPackage_t;

/* rfRole parameter */
typedef struct
{
    uint32_t accessAddress;       //!< access address,32bit PHY address
    uint32_t crcInit;             //!< crc initial value
    uint32_t frequency;           //!< rf frequency (2400000kHz-2483500kHz)
    uint32_t properties;          //!< bit0: 0-whitening on 1-whitening off
                                  //!< bit1: 0-  1-wait ack
                                  //!< BIT4-5 00-1M  01-2M
    uint16_t rxMaxLen;            //!< The maximum length of data received
    uint16_t sendInterval;        //!< Resend interval N*0.5us
    uint16_t sendTime;            //!< Time to switch from Rx t0 Tx (N*0.5us)+24us
    uint8_t mapCheckCount;        //!< Set the threshold of continuous packet loss to determine the quality of the channel.(default 2)
} rfRoleParam_t;

/* rfip tx parameter */
typedef struct
{
    uint32_t accessAddress;       //!< access address,32bit PHY address
    uint32_t crcInit;             //!< crc initial value
    uint32_t frequency;           //!< rf frequency (2400000kHz-2483500kHz)
    uint32_t properties;          //!< bit0: 0-whitening on 1-whitening off
                                  //!< bit1: 0-  1-wait ack
                                  //!< bit2: 0-  1-set the channel index of Data whitening
                                  //!< BIT4-5 00-1M  01-2M
    uint32_t txDMA;               //!< Tx DMA address
    uint8_t  whiteChannel;        //!< white channel(properties bit2 = 1)
    uint8_t  sendTime;            //!< Time to switch from Rx t0 Tx (N*0.5us)+24us
    uint16_t sendCount;           //!< resend count
} rfipTx_t;

/* rfip rx  parameter */
typedef struct
{
    uint32_t accessAddress;       //!< access address,32bit PHY address
    uint32_t crcInit;             //!< crc initial value
    uint32_t frequency;           //!< rf frequency (2400000kHz-2483500kHz)
    uint32_t properties;          //!< bit0: 0-whitening on 1-whitening off
                                  //!< bit1: 0-  1-send ack
                                  //!< BIT4-5 00-1M  01-2M
    uint32_t rxDMA;               //!< Rx DMA address
    uint8_t  whiteChannel;        //!< white channel(properties bit2 = 1)
    uint16_t rxMaxLen;            //!< Maximum length of Rx data
    uint16_t timeOut;             //!< Rx wait timeout,0:No timeout others: N*0.5us
} rfipRx_t;

typedef struct
{
    bStatus_t status; //!< Status for the connection
    /* SUCCESS
     * BOUND_STA_FAILURE: If the device binding fails on the device side, the application layer needs to restart the binding
     * BOUND_STA_INVALIDPARM: When the host receives a mismatched connection request, devType indicates the bound request type of the peer side
     * BOUND_STA_TIMEOUT: When the connection times out, it automatically switches to the bind state */
    uint8_t role;     //!< the role of the binding
    uint8_t devId;    //!< The ID number of the binding
    uint8_t devType;  //!< The device type of the binding
    uint8_t periTime; //!< reserved
    uint8_t hop;      //!< Frequency hopping mode
    uint8_t PeerInfo[6]; //!< Information about the peer device
} staBound_t;

// Define function type that rfRole bound  process callback
typedef void (*pfnRfRoleBoundCB)( staBound_t * );

/* Definition of roles */
#define  RF_ROLE_RX_MOD0      0 //!< host
#define  RF_ROLE_TX_MOD0      1 //!< device

/* Definition of frequency hopping mode type */
#define  RF_HOP_OFF           0  //!< Fixed frequency
#define  RF_HOP_BLECS2_MODE   1  //!< Frequency Hopping Mode 1 (same as BLE-CS#2)
#define  RF_HOP_MANUF_MODE    2  //!< Frequency Hopping Mode 2 (Manufacturer-Defined)

/* DEVICE configuration information */
typedef struct
{
    uint8_t devType;  //!< the device type, 0:Not specified
    uint8_t deviceId; //!< the device ID, 7:the ID number is assigned by the host
    uint8_t calVal;  //!< Calibration values
    uint8_t speed;  //!< communication speed(kHz)
    uint16_t timeout;  //!< Connection communication timeout period (in about 1 ms)
    uint8_t OwnInfo[6]; //!< Local Information
    uint8_t PeerInfo[6]; //!< Peer information
    pfnRfRoleBoundCB rfBoundCB;
} rfBoundDevice_t;

/* HOST configuration information */
typedef struct
{
    uint8_t hop; //!< Frequency hopping mode
    int8_t rssi;  //!< reserved
    uint8_t periTime; //!< Fixed value 8
    uint8_t devType;   //!< reserved
    uint16_t timeout; //!< Connection communication timeout period (in about 1 ms)
    uint8_t OwnInfo[6]; //!< Local Information
    uint8_t PeerInfo[6];   //!< resv
    pfnRfRoleBoundCB rfBoundCB;
    uint32_t ChannelMap;  //!< indicating  Used and Unused data channels.Every channel is represented with a
                          //!< bit positioned as per the data channel index,The LSB represents data channel index 0
} rfBoundHost_t;

/* listing information */
typedef struct
{
    uint8_t deviceId;  //!< The ID number of the list 0-6:Connection   7:binding
    int8_t rssi;       //!< Minimum RSSI threshold for binding, 0 means unlimited (deviceId=7 valid)
    uint8_t devType;   //!< Specify the bound device type, 0 means unlimited (deviceId=7 valid)
    uint8_t peerInfo[6]; //!< Specify the peer information of the binding, 0 means unlimited (deviceId=7 valid)
} rfRoleList_t;

/* Connection or binding management lists */
typedef struct
{
    uint8_t number;  //!< Number of lists
    rfRoleList_t *pList; //!< listing information
} rfRoleSpeed_t;

/* The timing of communication for devices */
typedef struct __attribute__((packed))
{
    uint8_t sub1Number;
    uint8_t sub2Number;
    uint16_t subInterval[16]; //!< 0.5us
} rfDevsTimeing_t;

/* bound frequency lists */
typedef struct
{
    uint8_t number;  //!< Number of lists
    uint32_t *pFrequency; //!< listing information
} rfHostBoundFre_t;

/*******************************************************************************
 * PUBLIC FUNCTIONS
 */

/**
 * @brief   read rssi
 *
 * @param   None.
 *
 * @return  the value of rssi.
 */
int8_t RFIP_ReadRssi( void );

/**
 * @brief   read crc state
 *
 * @param   None.
 *
 * @return  the value of crc state.
 */
uint8_t RFIP_ReadCrc( uint8_t *pBuf );

/**
 * @brief   set output power level@ TxPower
 *
 * @param   None.
 *
 * @return  the value of crc state.
 */
void RFIP_SetTxPower( uint8_t val );

/**
 * @brief   rf calibration
 *
 * @param   None 
 *
 * @return  None
 */
void RFIP_Calibration( void );

/**
 * @brief   reinitialize the rfip register after sleep wake-up
 *
 * @param   None
 *
 * @return  None
 */
void RFIP_WakeUpRegInit( void );

/**
 * @brief   rf mode single channel mode.
 *
 * @param   ch - rf channel,f=2402+ch*2 MHz, ch=0,...,39
 *
 * @return  0 - success, 1- phy busy
 */
bStatus_t RFIP_SingleChannel( uint8_t ch );

/**
 * @brief   used to stop single channel mode.
 *
 * @param   None.
 *
 * @return  None.
 */
void RFIP_TestEnd( void );

/**
 * @brief   library-fast initial
 *
 * @param   pConf - rfRole config
 *
 * @return  0-success.
 */
bStatus_t RFRole_FastInit( rfRoleConfig_t *pConf );

/**
 * @brief   used to stop TX/RX
 *
 * @param   None
 *
 * @return  0-success.
 */
bStatus_t RFRole_Stop( void );

/**
 * @brief   used to power off rf
 *
 * @param   None
 *
 * @return  0-success.
 */
bStatus_t RFRole_Shut(void );

/**
 * @brief   used to set rf-role parameter
 *
 * @param   pParam- rfRole parameter
 *
 * @return  0-success.
 */
bStatus_t RFRole_SetParam( rfRoleParam_t *pParam );

/**
 * @brief   set Connection or binding management lists
 *
 * @param   pList_t - management lists(global variable)
 *
 * @return  0-success.
 */
bStatus_t RFBound_SetSpeedType( rfRoleSpeed_t *pList_t );

/**
 * @brief   the list of communication frequencies for binding purposes
 *
 * @param   pList_t - the list of binding frequencies lists(global)
 *
 * @return  0-success.
 *
 * note:    The host mode polls the configured frequency at a 1ms cycle.
 *          The device mode polls the configured frequency at an 8ms cycle.
 *
 */
bStatus_t RFBound_SetFrequencyList( rfHostBoundFre_t *pList_t );

/**
 * @brief   set speed of devices(muti fast mode)
 *
 * @param   pList -
 *
 * @return  0-success.
 */
bStatus_t RFRole_SetDevTimeing( rfDevsTimeing_t *pList );

/**
 * @brief  Start sending
 *
 * note:  If sending is currently in progress, wait until the previous data packets have been sent before sending.
 *
 * @param   pList -
 *
 * @return  0-success.
 */
void RFRole_StartLpTx( void );

/**
 * @brief   Stop binding, disconnect the connection, and clear the sending and receiving data status.
 *
 * @param   None
 *
 * @return  0-success.
 */
bStatus_t RFBound_Stop( void );

/**
 * @brief   start host mode(lower power)
 *
 * @param   pConfig - host configuration information
 *
 * @return  0-success.
 */
bStatus_t RFBound_StartLpHost( rfBoundHost_t *pConfig );

/**
 * @brief   start host mode(muti fast)
 *
 * @param   pConfig - host configuration information
 *
 * @return  0-success.
 */
bStatus_t RFBound_StartMutiHost( rfBoundHost_t *pConfig );

/**
 * @brief   start host mode(8k)
 *
 * @param   pConfig - host configuration information
 *
 * @return  0-success.
 */
bStatus_t RFBound_Start8kHost( rfBoundHost_t *pConfig );

/**
 * @brief   start host mode(4k)
 *
 * @param   pConfig - host configuration information
 *
 * @return  0-success.
 */
bStatus_t RFBound_StartHost( rfBoundHost_t *pConfig );

/**
 * @brief   start device mode(lower power)
 *
 * @param   None.
 *
 * @return  0-success.
 */
bStatus_t RFBound_StartLpDevice( rfBoundDevice_t *pConfig );

/**
 * @brief   start device mode(muti fast)
 *
 * @param   None.
 *
 * @return  0-success.
 */
bStatus_t RFBound_StartMutiDevice( rfBoundDevice_t *pConfig );

/**
 * @brief   start device mode(8k)
 *
 * @param   pConfig - device configuration information
 *
 * @return  0-success.
 */
bStatus_t RFBound_Start8kDevice( rfBoundDevice_t *pConfig );

/**
 * @brief   start device mode(4k)
 *
 * @param   pConfig - device configuration information
 *
 * @return  0-success.
 */
bStatus_t RFBound_StartDevice( rfBoundDevice_t *pConfig );

/**
 * @brief   clear data list
 *
 * @param   dev_id
 *
 * @return  0-success.
 */
bStatus_t RFRole_ClearTxData( uint8_t dev_id );

/**
 * @brief   switch rf mode,must idle status.
 *
 * @param   mode - 0:BLE   1:RF basic  2:RF fast
 *
 * @return  0-success.
 */
bStatus_t RFRole_SwitchMode( uint8_t mode );

/**
 * @brief   channel map detection and start map update
 *
 * note: only the host role can be called
 *       lower power mode and 8k mode support
 *
 * @param   rssi -
 * @param   id -
 *
 * @return  0-success.
 */
bStatus_t RFRole_MapCheck( int8_t rssi,uint8_t id );

/**
 * @brief   Set a lower power consumption mode.
 *
 * note: only the device role can be called(4k&8k)
  *
 * @param   level - 0:disable(Slightly improve the transmission efficiency.) others: lower power level
 *
 * @return  None.
 */
void RFRole_LowPower( uint8_t level );

/**
 * @brief   start phy update.
 *
 * note:  supported in version 1.3 and above.
 *        4k mode and 8k mode support
 *
 * @param   phy - 0:1M  1:2M
 *
 * @return  0-success.
 */
bStatus_t RFRole_PHYUpdate( uint8_t dev_id, uint8_t phy );

/**
 * @brief   get status.
 *
 * note:  supported in version 1.4 and above.
 *
 * @param   id -
 *
 * @return  0-idle others-busy.
 */
uint32_t RFRole_GetStatus( uint8_t id );

/**
 * @brief   library-basic initial
 *
 * @param   pConf - rfRole config
 *
 * @return  0-success.
 */
bStatus_t RFRole_BasicInit( rfRoleConfig_t *pConf );

/**
 * @brief   set tx delay time
 *
 * @param   us - delay n*us
 *
 * @return  0-success.
 */
bStatus_t RFIP_SetTxDelayTime( uint16_t us );

/**
 * @brief   tx start
 *
 * @param   None
 *
 * @return  0-success.
 */
bStatus_t RFIP_SetTxStart( void );

/**
 * @brief   set tx parameter
 *
 * @param   pParm - rfip tx parameter
 *
 * @return  0-success.
 */
bStatus_t RFIP_SetTxParm( rfipTx_t *pParm );

/**
 * @brief   set rx parameter and start rx
 *
 * @param   pParm - rfip rx parameter
 *
 * @return  0-success.
 */
bStatus_t RFIP_SetRx( rfipRx_t *pParm );

/*
 * END @ API
 */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif
