/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup wifiiot
 * @{
 *
 * @brief Provides dedicated device operation interfaces on the Wi-Fi module,
 * including ADC, AT, flash, GPIO, I2C, I2S, partition, PWM, SDIO, UART, and watchdog.
 *
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file wifiiot_sdio.h
 *
 * @brief Declares the SDIO interface functions.
 *
 * These functions are used for SDIO initialization and data transmission. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef WIFIIOT_SDIO_H
#define WIFIIOT_SDIO_H

/**
 * @brief Indicates the number of extended registers on an SDIO device.
 */
#define WIFI_IOT_SDIO_EXTENDREG_COUNT  64

/**
 * @brief Provides extended SDIO attributes.
 */
typedef struct {
    /** Interrupt status */
    unsigned int                   intStat;
    /** Message status */
    unsigned int                   msgStat;
    /** Number of sent bytes */
    unsigned int                   xferCount;
    /** Flow control information */
    unsigned int                   creditInfo;
    /** Whether flow control information is valid */
    unsigned char                  creditIsvalid;
    /** Common register */
    unsigned char                  commReg[WIFI_IOT_SDIO_EXTENDREG_COUNT];
    /** Whether a common register is valid */
    unsigned char                  commregIsvalid;
    /** Number of valid common registers */
    unsigned int                  validCommregCnt;
}WifiIotSdioExtendFunc;

/**
 * @brief Defines attributes of an SDIO ADMA table.
 */
typedef struct {
    /** Data sending parameter */
    unsigned short param;
    /** Data length */
    unsigned short len;
    /** Data address */
    unsigned int address;
}WifiIotSdioAdmatable;

/**
 * @brief SDIO interrupt callback structure.
 */
typedef struct {
    /** Callback invoked when the host starts a read operation */
    int (*RdstartCallback)(unsigned int len, unsigned char *admaTable);
    /** Callback invoked when the host finishes a read operation */
    int (*RdoverCallback)(void);
    /** Callback invoked when a data read failure occurs on the host */
    void (*RderrCallback)(void);
    /** Callback invoked when the host starts a write operation */
    int (*WrstartCallback)(unsigned int len, unsigned char *admaTable);
    /** Callback invoked when the host finishes a write operation */
    int (*WroverCallback)(void);
    /** Callback invoked when a message is received from the host */
    void (*ProcessmsgCallback)(unsigned int msg);
    /** Callback invoked when a soft reset interrupt message is received from the host */
    void (*SoftRstCallback)(void);
} WifiIotSdioIntcallback;

/**
 * @brief Indicates the callback invoked upon a message event on the host.
 */
typedef void (*NotifyHostMessageEvent)(void);

/**
 * @brief Initializes the SDIO device.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioInit(void);

/**
 * @brief Reinitializes the SDIO device.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioReinit(void);


/**
 * @brief Resets the SDIO device.
 *
 * @since 1.0
 * @version 1.0
 */
void SdioSoftReset(void);

/**
 * @brief Registers an interrupt callback for the SDIO device.
 *
 * @param callbackFunc Indicates the pointer to the interrupt callback to register.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioRegisterCallback(const WifiIotSdioIntcallback *callbackFunc);

/**
 * @brief Completes data sending on the SDIO device.
 *
 * After data sending is complete, the SDIO device sets a complete flag for the ADMA ID <b>admaIndex</b>
 * to indicate that the ADMA data between channel 0 and the complete flag is set.
 *
 * @param admaTable Indicates the pointer to the start address of the ADMA table.
 * Each ADMA table occupies 8 bytes.
 * @param admaIndex Indicates the ADMA ID, ranging from 0 to 130.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioCompleteSend(unsigned char *admaTable, unsigned int admaIndex);

/**
 * @brief Sets the ADMA table that requires data padding.
 *
 * @param padlen Indicates the length of the data to pad.
 * @param admatable Indicates the pointer to the start address of the ADMA table.
 * Each ADMA table occupies 8 bytes.
 * @param admaIndex Indicates the ADMA ID, ranging from 0 to 130.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioSetPadAdmatab(unsigned int padlen, unsigned char *admatable, unsigned int admaIndex);

/**
 * @brief Sets the extended SDIO attributes.
 *
 * @param extFunc Indicates the pointer to the extended attributes.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioWriteExtinfo(WifiIotSdioExtendFunc *extFunc);

/**
 * @brief Starts to send data.
 *
 * Data with the length specified by <b>xferBytes</b> is ready for transmission.
 *
 * @param xferBytes Indicates the length of the data to send.
 * @since 1.0
 * @version 1.0
 */
void SdioSendData(unsigned int xferBytes);

/**
 * @brief Sets an SDIO ADMA.
 *
 * This function places a specified length of data into the ADMA with a specified ADMA ID <b>admaIndex</b>.
 *
 * @param admatable Indicates the pointer to the start address of the ADMA table.
 * Each ADMA table occupies 8 bytes.
 * @param admaIndex Indicates the ADMA ID, ranging from 0 to 130.
 * @param dataAddr Indicates the pointer to the address where data is to send.
 * @param dataLen Indicates the length of the data to send.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioSetAdmatable(unsigned char *admatable, unsigned int admaIndex,
                              const unsigned int *dataAddr, unsigned int dataLen);

/**
 * @brief Sends a suspended SDIO message.
 *
 * @return Returns <b>1</b> if no message is suspended or the suspended message is successfully sent;
 * returns <b>0</b> if the SDIO device is not working or is sending messages.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioSchedMsg(void);

/**
 * @brief Adds a message to a message queue and sends the message.
 *
 * @param msg Indicates the ID of the message to add to the message queue and send,
 * ranging from 0 to 31.
 * @return Returns <b>1</b> if the operation is successful;
 * returns <b>0</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioSendSyncMsg(unsigned int msg);

/**
 * @brief Sends a specified message.
 *
 * @param msg Indicates the ID of the message to send, ranging from 0 to 31.
 * @return Returns <b>1</b> if the operation is successful;
 * returns <b>0</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioSendMsgAck(unsigned int msg);

/**
 * @brief Clears a specified suspended message in the message queue,
 * adds a new message to it, and sends the new message.
 *
 * @param sendMsg Indicates the ID of the message to send, ranging from 0 to 31.
 * @param clearMsg Indicates the ID of the message to clear, ranging from 0 to 31.
 * @return Returns <b>1</b> if the operation is successful; returns <b>0</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioProcessMsg(unsigned int sendMsg, unsigned int clearMsg);

/**
 * @brief Checks whether a specified message is suspended.
 *
 * @param msg Indicates the ID of the message to check, ranging from 0 to 31.
 * @return Returns <b>1</b> if the message is suspended; returns <b>0</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioIsPendingMsg(unsigned int msg);

/**
 * @brief Checks whether a specified message is being sent.
 *
 * @param msg Indicates the ID of the message to check, ranging from 0 to 31.
 * @return Returns <b>1</b> if the message is being sent; returns <b>0</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SdioIsSendingMsg(unsigned int msg);

/**
 * @brief Obtains the extended configuration.
 *
 * @return Returns the pointer to the address of the extended configuration.
 * @since 1.0
 * @version 1.0
 */
WifiIotSdioExtendFunc *SdioGetExtendInfo(void);

/**
 * @brief Registers the callback that will be invoked when the host sends a message or data.
 *
 * @param msgEventCallback Indicates the callback to be invoked when a message or data is sent.
 * @since 1.0
 * @version 1.0
 */
void SdioRegisterNotifyMessageCallback(NotifyHostMessageEvent msgEventCallback);

/**
 * @brief Sets whether the SDIO device is powered off in deep sleep mode.
 *
 * @param powerDown Specifies whether to power off the SDIO device.
 * The value <b>1</b> means to power it off, and <b>0</b> means not to power it off.
 * @since 1.0
 * @version 1.0
 */
void SdioSetPowerdownWhenDeepSleep(unsigned char powerDown);

#endif
/** @} */
