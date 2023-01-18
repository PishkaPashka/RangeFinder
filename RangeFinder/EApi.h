/*
 *<Header>
 *+=========================================================================
 *I  Project Name: EApi for Embedded Application
 *+=========================================================================
 *I  Copyright: Copyright (c) 2014, AXIOMTEK
 *I  Author: Mark Lu,	mark.lu@axiomtek.com
 *+-------------------------------------------------------------------------
 *I
 *I  File Name            : EApi.h
 *I  File Location        : include
 *I  Last committed       : 1.0.0.1
 *I  Last changed by      : Mark Lu
 *I  Last changed date    : 2014.01.07
 *I  ID                   : 100236
 *I
 *+=========================================================================
 *</Header>
 */

#ifndef _EAPI_H_        
#define _EAPI_H_

#ifdef __cplusplus

#define EApi _declspec(dllexport)

extern "C"
{
/***********************************************************************/

#ifndef __IN
#  define __IN 
/* __IN
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Immediate value | Input value that must be specified and is essential 
 *                 | to function operation.
 *                 | 
 * Pointer         | Valid pointer to initialized buffer/variable.
 *                 | 
 */
#endif
#ifndef __INOPT
#  define __INOPT
/* __INOPT
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Pointer         | Valid pointer to initialized buffer/variable, or
 *                 | NULL Pointer.
 *                 | Note: refer to function specification for specifics.
 */
#endif
#ifndef __OUT
#  define __OUT
/* __OUT
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Pointer         | Valid pointer to destination buffer/variable
 */
#endif
#ifndef __OUTOPT
#  define __OUTOPT

/* __OUTOPT
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Pointer         | Valid pointer to destination buffer/variable, or
 *                 | NULL Pointer. 
 *                 | Note: refer to function specification for specifics.
 */
#endif
#ifndef __INOUT
#  define __INOUT
/* __INOUT
 * Arg Type        | Characteristics
 * ----------------+-----------------------------------------------------
 * Pointer         | Valid pointer to initialized buffer/variable
 *                 | Contents of buffer/variable updated before return.
 */
#endif
#ifndef EAPI_CALLTYPE
#  define EAPI_CALLTYPE
#endif
#ifndef EAPI_UINT32_C
#  define EAPI_UINT8_C(x)  ((uint8_t)(x))
#  define EAPI_UINT16_C(x) ((uint16_t)(x))
#  define EAPI_UINT32_C(x) ((uint32_t)(x))
#endif
/************************************************************************
 * All version numbers 
 * +=========+===============================+
 * | Bits    | Descriptions                  |
 * +=========+===============================+
 * | 24 - 31 | Version Number                |
 * +---------+-------------------------------+
 * | 16 - 23 | Revision Number               |
 * +---------+-------------------------------+
 * | 0  - 15 | Build Number                  |
 * +=========+===============================+
 */
#define EAPI_VER_MASK_VER     EAPI_UINT32_C(0xFF000000)
#define EAPI_VER_MASK_REV     EAPI_UINT32_C(0x00FF0000)
#define EAPI_VER_MASK_BUILD   EAPI_UINT32_C(0x0000FFFF)
#define EAPI_VER_GET_VER(x)   EAPI_UINT8_C (((x)>>24)&UINT8_MAX )
#define EAPI_VER_GET_REV(x)   EAPI_UINT8_C (((x)>>16)&UINT8_MAX )
#define EAPI_VER_GET_BUILD(x) EAPI_UINT16_C(((x)>> 0)&UINT16_MAX)
#define EAPI_VER_CREATE(Version,Revision,Build) (\
                      EAPI_UINT32_C(\
                        (((Version )&UINT8_MAX )<<24)|\
                        (((Revision)&UINT8_MAX )<<16)|\
                        (((Build   )&UINT16_MAX)<< 0) \
                      )\
                    )

/* Embedded API Standard Revision */
#define EAPI_VER      1
#define EAPI_REVISION 0
#define EAPI_VERSION EAPI_VER_CREATE(EAPI_VER, EAPI_REVISION, 3)


/************************************************************************
 */


/* Embedded Application System Interface */

/*
 *  EApi Types
 */
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

typedef uint32_t EApiStatus_t;
typedef uint32_t EApiId_t;

/*
 *
 *
 *  S T A T U S   C O D E S
 *
 *
 */
/* Description
 *   The EAPI library is not yet or unsuccessfully initialized. 
 *   EApiLibInitialize needs to be called prior to the first access of any 
 *   other EAPI function.
 * Actions
 *   Call EApiLibInitialize..
 */
#define EAPI_STATUS_NOT_INITIALIZED   EAPI_UINT32_C(0xFFFFFFFF)

/* Description
 *   Library is initialized.
 * Actions
 *   none.
 */
#define EAPI_STATUS_INITIALIZED       EAPI_UINT32_C(0xFFFFFFFE)

/* Description
 *   Memory Allocation Error.
 * Actions
 *   Free memory and try again..
 */
#define EAPI_STATUS_ALLOC_ERROR       EAPI_UINT32_C(0xFFFFFFFD)

/* Description 
 *   Time out in driver. This is Normally caused by hardware/software 
 *   semaphore timeout. 
 * Actions
 *   Retry.
 */
#define EAPI_STATUS_DRIVER_TIMEOUT    EAPI_UINT32_C(0xFFFFFFFC)

/* Description
 *   Library is not released.
 * Actions
 *   none.
 */
#define EAPI_AX_STATUS_NOT_RELEASED       EAPI_UINT32_C(0xFFFFFFFB)

/* Description
 *   Library of AXView is loaded failed.
 * Actions
 *   none.
 */
#define EAPI_AX_STATUS_DLLA_LOAD_FAILED       EAPI_UINT32_C(0xFFFFFFFA)

/* Description
 *   Library of AXWIO is loaded failed.
 * Actions
 *   none.
 */
#define EAPI_AX_STATUS_DLLB_LOAD_FAILED       EAPI_UINT32_C(0xFFFFFFF9)

/* Description
 *   Error code from core of AXView.
 * Actions
 *   none.
 */
// =================================================
#define EAPI_AX_STATUS_ERR_NONE					EAPI_UINT32_C(0xFFFE0000)		//AX__ERR_NONE			0x0000	// no error
#define EAPI_AX_STATUS_ERR_BUSY					EAPI_UINT32_C(0xFFFE0001)		//AX_ERR_BUSY			0x0001	// mutex busy
#define EAPI_AX_STATUS_ERR_CMD					EAPI_UINT32_C(0xFFFE0002)		//AX_ERR_CMD			0x0002	// cmd exec error
// =================================================
#define EAPI_AX_STATUS_ERR_OPEN_CREATE			EAPI_UINT32_C(0xFFFE0100)		//AX_ERR_OPEN_CREATE	0x0100	// open axview fail
#define EAPI_AX_STATUS_ERR_OPEN_REGD			EAPI_UINT32_C(0xFFFE0101)		//AX_ERR_OPEN_REG		0x0101	// cant read reg
#define EAPI_AX_STATUS_ERR_OPEN_SEARCH			EAPI_UINT32_C(0xFFFE0102)		//AX_ERR_OPEN_SEARCH	0x0102	// search failure
#define EAPI_AX_STATUS_ERR_OPEN_OPENED			EAPI_UINT32_C(0xFFFE0103)		//AX_ERR_OPEN_OPENED	0x0103	// already opened
#define EAPI_AX_STATUS_ERR_OPEN_CLOSED			EAPI_UINT32_C(0xFFFE0104)		//AX_ERR_OPEN_CLOSED	0x0104	// already closed
// =================================================
#define EAPI_AX_STATUS_ERR_RSP					EAPI_UINT32_C(0xFFFE0200)		//AX_ERR_RSP			0x0200	// cmd error base
#define EAPI_AX_STATUS_ERR_RSP_CMD				EAPI_UINT32_C(0xFFFE0201)		//AX_ERR_RSP_CMD		0x0201	// cmd exec error		(AXVIEW_ERR01)
#define EAPI_AX_STATUS_ERR_RSP_PARA				EAPI_UINT32_C(0xFFFE0202)		//AX_ERR_RSP_PARA		0x0202	// cmd para error		(AXVIEW_ERR02)
#define EAPI_AX_STATUS_ERR_RSP_HWM				EAPI_UINT32_C(0xFFFE020A)		//AX_ERR_RSP_HWM		0x020A	// hwm function error	(AXVIEW_ERR10)
#define EAPI_AX_STATUS_ERR_RSP_MCU				EAPI_UINT32_C(0xFFFE0214)		//AX_ERR_RSP_MCU		0x0214	// mcu function error	(AXVIEW_ERR20)
#define EAPI_AX_STATUS_ERR_RSP_SUPPORT			EAPI_UINT32_C(0xFFFE0263)		//AX_ERR_RSP_SUPPORT	0x0263	// cmd none support		(AXVIEW_ERR99)
// =================================================

/* Description 
 *  One or more of the EAPI function call parameters are out of the 
 *  defined range.
 *
 *  Possible Reasons include be
 *  NULL Pointer
 *  Invalid Offset
 *  Invalid Length
 *  Undefined Value
 *  
 *   Storage Write
 *    Incorrectly Aligned Offset
 *    Invalid Write Length
 * Actions
 *   Verify Function Parameters.
 */
#define EAPI_STATUS_INVALID_PARAMETER EAPI_UINT32_C(0xFFFFFEFF)

/* Description
 *   The Block Alignment is incorrect.
 * Actions
 *   Use pInputs and pOutputs to correctly select input and outputs. 
 */
#define EAPI_STATUS_INVALID_BLOCK_ALIGNMENT EAPI_UINT32_C(0xFFFFFEFE)

/* Description
 *   This means that the Block length is too long.
 * Actions
 *   Use Alignment Capabilities information to correctly align write access.
 */
#define EAPI_STATUS_INVALID_BLOCK_LENGTH    EAPI_UINT32_C(0xFFFFFEFD)

/* Description
 *   The current Direction Argument attempts to set GPIOs to a unsupported 
 *   directions. I.E. Setting GPI to Output.
 * Actions
 *   Use pInputs and pOutputs to correctly select input and outputs. 
 */
#define EAPI_STATUS_INVALID_DIRECTION       EAPI_UINT32_C(0xFFFFFEFC)

/* Description
 *   The Bitmask Selects bits/GPIOs which are not supported for the current ID.
 * Actions
 *   Use pInputs and pOutputs to probe supported bits..
 */
#define EAPI_STATUS_INVALID_BITMASK         EAPI_UINT32_C(0xFFFFFEFB)

/* Description
 *   Watchdog timer already started.
 * Actions
 *   Call EApiWDogStop, before retrying.
 */
#define EAPI_STATUS_RUNNING                 EAPI_UINT32_C(0xFFFFFEFA)

/* Description
 *   This function or ID is not supported at the actual hardware environment.
 * Actions
 *   none.
 */
#define EAPI_STATUS_UNSUPPORTED       EAPI_UINT32_C(0xFFFFFCFF)

/* Description
 *   I2C Device Error
 *   No Acknowledge For Device Address, 7Bit Address Only
 *   10Bit Address may cause Write error if 2 10Bit addressed devices 
 *   present on the bus.
 * Actions
 *   none.
 */
#define EAPI_STATUS_NOT_FOUND         EAPI_UINT32_C(0xFFFFFBFF)

/* Description
 *   I2C Time-out
 *   Device Clock stretching time-out, Clock pulled low by device 
 *   for too long
 * Actions
 *   none.
 */
#define EAPI_STATUS_TIMEOUT           EAPI_UINT32_C(0xFFFFFBFE)

/* Description
 *   EApi  I2C functions specific. The addressed I2C bus is busy or there 
 *   is a bus collision.
 *   The I2C bus is in use. Either CLK or DAT are low.
 *   Arbitration loss or bus Collision, data remains low when writing a 1
 * Actions
 *   Retry.
 */
#define EAPI_STATUS_BUSY_COLLISION    EAPI_UINT32_C(0xFFFFFBFD)

/* Description
 *   I2C Read Error
 *    Not Possible to detect.
 *   Storage Read Error
 *    ....
 * Actions
 *   Retry.
 */
#define EAPI_STATUS_READ_ERROR        EAPI_UINT32_C(0xFFFFFAFf)

/* Description
 *   I2C Write Error
 *     No Acknowledge received after writing any Byte after the First Address 
 *     Byte.
 *     Can be caused by 
 *     unsupported Device Command/Index
 *     Ext Command/Index used on Standard Command/Index Device
 *     10Bit Address Device Not Present
 *   Storage Write Error
 *    ...
 * Actions
 *   Retry.
 */
#define EAPI_STATUS_WRITE_ERROR       EAPI_UINT32_C(0xFFFFFAFE)


/* Description
 *   The amount of available data exceeds the buffer size.
 *   Storage buffer overflow was prevented. Read count was larger then 
 *   the defined buffer length.
 *   Read Count > Buffer Length
 * Actions
 *   Either increase the buffer size or reduce the block length.
 */
#define EAPI_STATUS_MORE_DATA         EAPI_UINT32_C(0xFFFFF9FF)

/* Description
 *   Generic error message. No further error details are available.
 * Actions
 *   none.
 */
#define EAPI_STATUS_ERROR             EAPI_UINT32_C(0xFFFFF0FF)

/* Description
 *   The operation was successful.
 * Actions
 *   none.
 */
#define EAPI_STATUS_SUCCESS           EAPI_UINT32_C(0)
#define EAPI_TEST_SUCCESS(x)        (!(x))

/* Library */
/* 
 * EApiLibInitialize
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Already initialized            | EAPI_STATUS_INITIALIZED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiLibInitialize(void);	/* Should be called before 
                             * calling any other API 
                             * function is called
                             */
/* 
 * EApiLibUnInitialize
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t
EAPI_CALLTYPE 
EApiLibUnInitialize(void);	/* Should be called before 
							 * program exit 
							 */ 

/* 
 *
 * Plug and Play Identifiers
 *
 *
 *
 */
/* 
 * The following MACROS are for Creating OEM IDs
 * OEM ID macros should be named
 * EAPI_[PNPID]_ID_[TYPE]_[NAME] 
 * E.G.
 * EAPI_PMG_ID_BOARD_CUSTOMERID
 */
#define EAPI_BYTE_SWAP_W(a) EAPI_UINT16_C((((a)<<8)&0xFF00)|(((a)>>8)&0x00FF))

#define EAPI_CREATE_PNPID(a, b, c) EAPI_BYTE_SWAP_W(((( a -'A'+1)&0x1F)<<10)|((( b -'A'+1)&0x1F)<< 5)|((( c -'A'+1)&0x1F)<< 0))

#define EAPI_CREATE_CUST_ID(a, b, c, Id) EAPI_UINT32_C((0xF<<28)|(EAPI_CREATE_PNPID(a, b, c)<<12)|(Id&0xFFF))

#define EAPI_PNPID_PICMG EAPI_CREATE_PNPID('P', 'M', 'G')  /* PICMG Should register this. */

#define EAPI_PNPID_PICMG EAPI_CREATE_PNPID('S', 'R', 'M')  /* SRAM Should register this. *//***************************************************** adding by Mark --- 20140120*/
#define EAPI_PNPID_PICMG EAPI_CREATE_PNPID('F', 'L', 'H')  /* FLASH Should register this. *//***************************************************** adding by Mark --- 20140120*/
#define EAPI_PNPID_PICMG EAPI_CREATE_PNPID('E', 'E', 'P')  /* EEPROM Should register this. *//***************************************************** adding by Mark --- 20140120*/

/*
 *
 *      B O A R D   I N F O M A T I O N   S T R I N G S 
 *
 */
/* IDS */
#define EAPI_ID_BOARD_MANUFACTURER_STR				EAPI_UINT32_C(0) /* Board Manufacturer Name String */
#define EAPI_ID_BOARD_NAME_STR						EAPI_UINT32_C(1) /* Board Name String */
#define EAPI_ID_BOARD_REVISION_STR					EAPI_UINT32_C(2) /* Board REVISION String */
#define EAPI_ID_BOARD_SERIAL_STR					EAPI_UINT32_C(3) /* Board Serial Number String */
#define EAPI_ID_BOARD_BIOS_REVISION_STR				EAPI_UINT32_C(4) /* Board Bios Revision String */
#define EAPI_ID_BOARD_HW_REVISION_STR				EAPI_UINT32_C(5) /* Board Hardware Revision String */
#define EAPI_ID_BOARD_PLATFORM_TYPE_STR				EAPI_UINT32_C(6) /* Platform ID (ETX, COM Express, etc...) */
#define EAPI_ID_BOARD_PRODUCTIONDATE_STR			EAPI_UINT32_C(7)

#define EAPI_ID_MCU_NAME_STR						EAPI_UINT32_C(8)
#define EAPI_ID_MCU_MANUFACTURER_STR				EAPI_UINT32_C(9)
#define EAPI_ID_MCU_PRODUCTIONDATE_STR				EAPI_UINT32_C(10)
#define EAPI_ID_MCU_FW_REVISION_STR					EAPI_UINT32_C(11)

#define EAPI_ID_BOARD_SENSOR_COUNTER_TEMP			EAPI_UINT32_C(12)
#define EAPI_ID_BOARD_SENSOR_TEMP					EAPI_UINT32_C(13)
#define EAPI_ID_BOARD_SENSOR_COUNTER_VOLTAGE		EAPI_UINT32_C(14)
#define EAPI_ID_BOARD_SENSOR_VOLTAGE				EAPI_UINT32_C(15)
#define EAPI_ID_BOARD_SENSOR_COUNTER_FAN			EAPI_UINT32_C(16)
#define EAPI_ID_BOARD_SENSOR_FAN					EAPI_UINT32_C(17)
#define EAPI_ID_BOARD_SENSOR_COUNTER_PWM			EAPI_UINT32_C(18)
#define EAPI_ID_BOARD_SENSOR_GET_PWM				EAPI_UINT32_C(19)
#define EAPI_ID_BOARD_SENSOR_SET_PWM				EAPI_UINT32_C(20)
#define EAPI_ID_BOARD_NAME_SET_PWM					EAPI_UINT32_C(21)

#define EAPI_ID_BOARD_UUID_STR						EAPI_UINT32_C(24)

#define EAPI_ID_STORAGE_SRAM						EAPI_UINT32_C(25)

#define EAPI_ID_BOARD_SENSOR_COUNTER_POWER			EAPI_UINT32_C(29)
#define EAPI_ID_BOARD_SENSOR_POWER					EAPI_UINT32_C(30)

#define EAPI_ID_BOARD_SENSOR_COUNTER_DIO_INTERNAL	EAPI_UINT32_C(31)
#define EAPI_ID_BOARD_SENSOR_GET_DIO_INTERNAL		EAPI_UINT32_C(32)
#define EAPI_ID_BOARD_SENSOR_SET_DIO_INTERNAL		EAPI_UINT32_C(32)
#define EAPI_ID_BOARD_NAME_SET_DIO_INTERNAL			EAPI_UINT32_C(34)

#define EAPI_ID_BOARD_SENSOR_COUNTER_DIO_EXTERNAL	EAPI_UINT32_C(35)
#define EAPI_ID_BOARD_SENSOR_GET_DIO_EXTERNAL		EAPI_UINT32_C(36)
#define EAPI_ID_BOARD_SENSOR_SET_DIO_EXTERNAL		EAPI_UINT32_C(36)
#define EAPI_ID_BOARD_NAME_SET_DIO_EXTERNAL			EAPI_UINT32_C(38)

#define EAPI_ID_BOARD_SENSOR_COUNTER_WDT_INTERNAL	EAPI_UINT32_C(39)
#define EAPI_ID_BOARD_SENSOR_GET_WDT_INTERNAL		EAPI_UINT32_C(40)
#define EAPI_ID_BOARD_SENSOR_SET_WDT_INTERNAL		EAPI_UINT32_C(40)
#define EAPI_ID_BOARD_SENSOR_RELOAD_WDT_INTERNAL	EAPI_UINT32_C(41)
#define EAPI_ID_BOARD_NAME_SET_WDT_INTERNAL			EAPI_UINT32_C(42)

#define EAPI_ID_BOARD_SENSOR_COUNTER_WDT_EXTERNAL	EAPI_UINT32_C(43)
#define EAPI_ID_BOARD_SENSOR_GET_WDT_EXTERNAL		EAPI_UINT32_C(44)
#define EAPI_ID_BOARD_SENSOR_SET_WDT_EXTERNAL		EAPI_UINT32_C(44)
#define EAPI_ID_BOARD_SENSOR_RELOAD_WDT_EXTERNAL	EAPI_UINT32_C(45)
#define EAPI_ID_BOARD_NAME_SET_WDT_EXTERNAL			EAPI_UINT32_C(46)

#define EAPI_ID_BOARD_DISCOUNTUARTAMOUNT			EAPI_UINT32_C(50)

#define EAPI_ID_BOARD_SMARTBATTERYSUPPORT			EAPI_UINT32_C(60)
#define EAPI_ID_BOARD_PoESUPPORT					EAPI_UINT32_C(61)
#define EAPI_ID_BOARD_AIOSUPPORT					EAPI_UINT32_C(62)
#define EAPI_ID_BOARD_I2CSUPPORT					EAPI_UINT32_C(63)

#define EAPI_ID_EC_ACCONNECTION						EAPI_UINT32_C(90)
#define EAPI_ID_EC_POWERSOURCE						EAPI_UINT32_C(91)
#define EAPI_ID_EC_BATTERYCOUNT						EAPI_UINT32_C(92)

#define EAPI_ID_EC_BATTERYNAME						EAPI_UINT32_C(100)
#define EAPI_ID_EC_BATTERYCONNECTION				EAPI_UINT32_C(101)
#define EAPI_ID_EC_BATTERYREMAININGCAPACITY			EAPI_UINT32_C(102)
#define EAPI_ID_EC_BATTERYONCHARGING				EAPI_UINT32_C(103)
#define EAPI_ID_EC_BATTERYDESIGNVOLTAGE				EAPI_UINT32_C(104)
#define EAPI_ID_EC_BATTERYDESIGNCAPACITY			EAPI_UINT32_C(105)
#define EAPI_ID_EC_BATTERYDESIGNENERGY				EAPI_UINT32_C(106)
#define EAPI_ID_EC_BATTERYVOLTAGE					EAPI_UINT32_C(107)
#define EAPI_ID_EC_BATTERYCURRENT					EAPI_UINT32_C(108)
#define EAPI_ID_EC_BATTERYCHARGINGVOLTAGE			EAPI_UINT32_C(109)
#define EAPI_ID_EC_BATTERYCHARGINGCURRENT			EAPI_UINT32_C(110)
#define EAPI_ID_EC_BATTERYTEMPERATURE				EAPI_UINT32_C(111)
#define EAPI_ID_EC_BATTERYREMAININGTIME				EAPI_UINT32_C(112)
#define EAPI_ID_EC_BATTERYCYCLECOUNT				EAPI_UINT32_C(113)
#define EAPI_ID_EC_BATTERYFULLCHARGINGCAPACITY		EAPI_UINT32_C(114)
#define EAPI_ID_EC_BATTERYCALIBRATO					EAPI_UINT32_C(115)
#define EAPI_ID_EC_BATTERYOVERCHARGED				EAPI_UINT32_C(116)
#define EAPI_ID_EC_BATTERYOVERTEMPERATURE			EAPI_UINT32_C(117)

/* 
 * EApiBoardGetStringA
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pBufLen==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * pBufLen!=NULL&&*pBufLen&&pBuffer==NULL | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * strlen(Id)+1>*pBufLen                  | EAPI_STATUS_MORE_DATA
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t
EAPI_CALLTYPE
EApiBoardGetStringA(
    __IN      EApiId_t  Id      , /* Name Id */
    __OUT     char     *pBuffer , /* Destination pBuffer */
    __INOUT   uint32_t *pBufLen   /* pBuffer Length */
    );


/*
 *
 *      B O A R D   I N F O M A T I O N   V A L U E S
 *
 */
/* IDS */
#define EAPI_ID_GET_EAPI_SPEC_VERSION         EAPI_UINT32_C(0) /* EAPI Specification 
                                                                * Revision I.E. The 
                                                                * EAPI Spec Version 
                                                                * Bits 31-24, Revision 
                                                                * 23-16, 15-0 always 0
                                                                * Used to implement 
                                                                * this interface
                                                                */

#define EAPI_ID_BOARD_BOOT_COUNTER_VAL        EAPI_UINT32_C(1) /* Units = Boots */
#define EAPI_ID_BOARD_RUNNING_TIME_METER_VAL  EAPI_UINT32_C(2) /* Units = Minutes */
#define EAPI_ID_BOARD_PNPID_VAL               EAPI_UINT32_C(3) /* Encoded PNP ID 
//                                                                * Format 
//                                                                * (Compressed ASCII)
//                                                                */
#define EAPI_ID_BOARD_PLATFORM_REV_VAL        EAPI_UINT32_C(4) /* Platform Revision 
//                                                                * I.E. The PICMG Spec 
//                                                                * Version Bits 31-24,
//                                                                * Revision 23-16, 
//                                                                * 15-0 always 0
//                                                                */
//
#define EAPI_ID_BOARD_DRIVER_VERSION_VAL  EAPI_UINT32_C(0x10000) /* Vendor Specific 
//                                                                  * (Optional) 
//                                                                  */
#define EAPI_ID_BOARD_LIB_VERSION_VAL     EAPI_UINT32_C(0x10001) /* Vendor Specific
                                                                  * (Optional) 
                                                                  */

#define EAPI_ID_HWMON_CPU_TEMP            EAPI_UINT32_C(0x20000) /* 0.1 */ 
#define EAPI_ID_HWMON_CHIPSET_TEMP        EAPI_UINT32_C(0x20001) /* 0.1 */ 
#define EAPI_ID_HWMON_SYSTEM_TEMP         EAPI_UINT32_C(0x20002) /* 0.1 */ 

#define EAPI_KELVINS_OFFSET 2731
#define EAPI_ENCODE_CELCIUS(Celsius) EAPI_UINT32_C((((Celsius)*10))+EAPI_KELVINS_OFFSET)
#define EAPI_DECODE_CELCIUS(Celsius) ((Celsius)- EAPI_KELVINS_OFFSET)/10

#define EAPI_ID_HWMON_VOLTAGE_VCORE       EAPI_UINT32_C(0x21004) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_2V5         EAPI_UINT32_C(0x21008) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_3V3         EAPI_UINT32_C(0x2100C) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_VBAT        EAPI_UINT32_C(0x21010) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_5V          EAPI_UINT32_C(0x21014) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_5VSB        EAPI_UINT32_C(0x21018) /* millivolts */
#define EAPI_ID_HWMON_VOLTAGE_12V         EAPI_UINT32_C(0x2101C) /* millivolts */

#define EAPI_ID_HWMON_FAN_CPU             EAPI_UINT32_C(0x22000) /* RPM */
#define EAPI_ID_HWMON_FAN_SYSTEM          EAPI_UINT32_C(0x22001) /* RPM */
#define EAPI_ID_HWMON_FAN_CHIPSET		  EAPI_UINT32_C(0x22002) /* RPM */

/* 
 * EApiBoardGetValue
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pValue==NULL                           | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiBoardGetValue(
    __IN  EApiId_t  Id      , /* Value Id */
    __OUT uint32_t *pValue    /* Return Value */
    );



/*
 *
 *      B A C K L I G H T
 *
 */
/* IDS */
#define EAPI_ID_BACKLIGHT_1           EAPI_UINT32_C(0)
#define EAPI_ID_BACKLIGHT_2           EAPI_UINT32_C(1)
#define EAPI_ID_BACKLIGHT_3           EAPI_UINT32_C(2)

/* Backlight Values */
#define EAPI_BACKLIGHT_SET_ON         EAPI_UINT32_C(0)
#define EAPI_BACKLIGHT_SET_OFF        EAPI_UINT32_C(0xFFFFFFFF)
#define EAPI_BACKLIGHT_SET_DIMEST     EAPI_UINT32_C(0)
#define EAPI_BACKLIGHT_SET_BRIGHTEST  EAPI_UINT32_C(255)
/* 
 * EApiVgaGetBacklightEnable
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pEnable==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t
EAPI_CALLTYPE
EApiVgaGetBacklightEnable( 
    __IN  EApiId_t  Id      , /* Backlight Id */
    __OUT uint32_t *pEnable   /* Backlight Enable */
    );
/* 
 * EApiVgaSetBacklightEnable
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * Enable!=EAPI_BACKLIGHT_SET_ON&&
 * Enable!=EAPI_BACKLIGHT_SET_OFF         | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t
EAPI_CALLTYPE
EApiVgaSetBacklightEnable(
    __IN  EApiId_t  Id      , /* Backlight Id */
    __IN  uint32_t  Enable    /* Backlight Enable */
    );
/* 
 * EApiVgaGetBacklightBrightness
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pBright==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t
EAPI_CALLTYPE
EApiVgaGetBacklightBrightness( 
    __IN  EApiId_t  Id      , /* Backlight Id */
    __OUT uint32_t *pBright   /* Backlight Brightness */
    );
/* 
 * EApiVgaSetBacklightBrightness
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * Bright>EAPI_BACKLIGHT_SET_BRIGHTEST    | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE
EApiVgaSetBacklightBrightness(
    __IN  EApiId_t  Id      , /* Backlight Id */
    __IN  uint32_t  Bright    /* Backlight Brightness */
    );


/*
 *
 *      S T O R A G E
 *
 */
/* IDs */
#define EAPI_ID_STORAGE_STD              EAPI_UINT32_C(0)
/* Dummy Example */
#define EAPI_PMG_ID_STORAGE_SAMPLE       EAPI_CREATE_CUST_ID('P', 'M', 'G', 0)
/* 
 * EApiStorageCap
 * 
 * Condition                                    | Return Values 
 * ---------------------------------------------+------------------------------
 * Library Uninitialized                        | EAPI_STATUS_NOT_INITIALIZED
 * ((pStorageSize==NULL)&&(pBlockLength==NULL)) | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                               | EAPI_STATUS_UNSUPPORTED
 * Common Error                                 | Common Error Code
 * Else                                         | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiStorageCap(
    __IN  EApiId_t  Id            , /* Storage Area Id */
    __OUT uint32_t  *pStorageSize , /* Total */
    __OUT uint32_t  *pBlockLength   /* Write Block Length
                                     * & Alignment 
                                     */
    );
/* 
 * EApiStorageAreaRead
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pBuffer==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * ByteCnt==0                             | EAPI_STATUS_INVALID_PARAMETER
 * BufLen==0                              | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Offset+ByteCnt>pStorageSize            | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Read Error                             | EAPI_STATUS_READ_ERROR
 * ByteCnt>BufLen                         | EAPI_STATUS_MORE_DATA
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiStorageAreaRead(
    __IN  EApiId_t  Id      , /* Storage Area Id */
    __IN  uint32_t  Offset  , /* Byte Offset */
    __OUT     void *pBuffer , /* Pointer to Data pBuffer */
    __IN  uint32_t  BufLen  , /* Data pBuffer Size in 
                               * bytes 
                               */
    __IN  uint32_t  ByteCnt   /* Number of bytes to read */
    );
/* 
 * EApiStorageAreaWrite
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pBuffer==NULL                          | EAPI_STATUS_INVALID_PARAMETER
 * ByteCnt==0                             | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Offset%pBlockLength                    | EAPI_STATUS_INVALID_BLOCK_ALIGNMENT
 * ByteCnt%pBlockLength                   | EAPI_STATUS_INVALID_BLOCK_ALIGNMENT
 * Offset+ByteCnt>pStorageSize            | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Write Error                            | EAPI_STATUS_WRITE_ERROR
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiStorageAreaWrite(
    __IN  EApiId_t  Id      , /* Storage Area Id */
    __IN  uint32_t  Offset  , /* Byte Offset */
    __IN      void *pBuffer , /* Pointer to Data pBuffer */
    __IN  uint32_t  ByteCnt   /* Number of bytes to write */
    );


/*
 *
 *      I 2 C / S M B u s
 *
 */
/* IDs */
#define EAPI_ID_I2C_EXTERNAL       EAPI_UINT32_C(0) /* Baseboard I2C Interface
                                                     * required 
                                                     */
#define EAPI_ID_I2C_LVDS_1         EAPI_UINT32_C(1) /* LVDS/EDP 1 Interface 
                                                     * (optional)
                                                     */
#define EAPI_ID_I2C_LVDS_2         EAPI_UINT32_C(2) /* LVDS/EDP 2 Interface 
                                                     * (optional)
                                                     */

/*
 * I2C Address Format 
 *
 *  L = Set to 0   
 *  H = Set to 1   
 *  X = Don't Care(Direction Bit)
 *  0-F Address Bit 
 *
 *  Bits 31-16 are Reserved and should be set to 0
 *
 *  Bit Offset      | F E D C B A 9 8 7 6 5 4 3 2 1 0
 *  ----------------+--------------------------------
 *  7  Bit Address  | L L L L L L L L 6 5 4 3 2 1 0 X
 *  10 Bit Address  | H H H H L 9 8 X 7 6 5 4 3 2 1 0
 *
 *  Examples where Don't Care bits set to 0
 *             Encoded Encoded
 *  Address     7Bit    10Bit
 *    0x01      0x02   0xF001
 *    0x58      0xA0   0xF058
 *    0x59      0xA2   0xF059
 *    0x77      0xEE   0xF077
 *    0x3FF            0xF6FF
 *
 */
#define EAPI_I2C_ENC_7BIT_ADDR(x)  EAPI_UINT8_C(((x)&0x07F)<<1)
#define EAPI_I2C_DEC_7BIT_ADDR(x)  EAPI_UINT8_C(((x)>>1)&0x07F)
/* 
 * EApiI2CGetBusCap
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * pMaxBlkLen==NULL                       | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                             | EAPI_STATUS_UNSUPPORTED
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE
EApiI2CGetBusCap(
    __IN  EApiId_t  Id         , /* I2C Bus Id */
    __OUT uint32_t *pMaxBlkLen   /* Max Block Length 
                                  * Supported on this
                                  * interface 
                                  */
    );

/* 
 * EApiI2CWriteRead
 * 
 * Condition                                | Return Values 
 * -----------------------------------------+------------------------------
 * Library Uninitialized                    | EAPI_STATUS_NOT_INITIALIZED
 * (WriteBCnt>1)&&(pWBuffer==NULL)          | EAPI_STATUS_INVALID_PARAMETER
 * (ReadBCnt>1)&&(pRBuffer==NULL)           | EAPI_STATUS_INVALID_PARAMETER
 * (ReadBCnt>1)&&(RBufLen==0)               | EAPI_STATUS_INVALID_PARAMETER
 * ((WriteBCnt==0)&&(ReadBCnt==0))          | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                               | EAPI_STATUS_UNSUPPORTED
 * WriteBCnt>(pMaxBlkLen+1)                 | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * ReadBCnt>(pMaxBlkLen+1)                  | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Bus Busy  SDA/SDC low                    | EAPI_STATUS_BUSY_COLLISION
 * Arbitration Error/Collision Error        | EAPI_STATUS_BUSY_COLLISION
 *   On Write 1 write cycle                 |
 *   SDA Remains low                        |
 * Timeout due to clock stretching          | EAPI_STATUS_TIMEOUT
 * start<Addr Byte><W>Nak                   | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte><R>Nak                   | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte><W>Ack<Data Byte 1>Nak   | EAPI_STATUS_WRITE_ERROR
 * ReadBCnt>(RBufLen+1)                     | EAPI_STATUS_MORE_DATA
 * Common Error                             | Common Error Code
 * Else                                     | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiI2CWriteReadRaw(
    __IN     EApiId_t  Id       , /* I2C Bus Id */
    __IN     uint8_t   Addr     , /* Encoded 7Bit I2C
                                   * Device Address 
                                   */
    __INOPT  void     *pWBuffer , /* Write Data pBuffer */
    __IN     uint32_t  WriteBCnt, /* Number of Bytes to 
                                   * write plus 1
                                   */
    __OUTOPT void     *pRBuffer , /* Read Data pBuffer */
    __IN     uint32_t  RBufLen  , /* Data pBuffer Length */
    __IN     uint32_t  ReadBCnt   /* Number of Bytes to 
                                   * Read plus 1
                                   */
    );

#define EApiI2CWriteRaw(Id, Addr, pBuffer, ByteCnt) EApiI2CWriteReadRaw(Id, Addr, pBuffer, ByteCnt, NULL, 0, 0)
#define EApiI2CReadRaw(Id, Addr, pBuffer, BufLen, ByteCnt) EApiI2CWriteReadRaw(Id, Addr, NULL, 0, pBuffer, BufLen, ByteCnt)


#define EAPI_I2C_ENC_10BIT_ADDR(x) EAPI_UINT32_C(((x)&0xFF)|(((x)&0x0300)<<1)|0xF000)
#define EAPI_I2C_DEC_10BIT_ADDR(x) EAPI_UINT32_C(((x)&0xFF)|(((x)>>1)&0x300))
#define EAPI_I2C_IS_10BIT_ADDR(x)  (((x)&0xF800)==0xF000)
#define EAPI_I2C_IS_7BIT_ADDR(x)   (!EAPI_I2C_IS_10BIT_ADDR(x))

/*
 * I2C Transfer Types
 * Bits 31 & 30 Selects Command Type
 *
 * Transfer Type 1: 
 * Address Format : 7Bit
 * Command Type   : None
 * Data Direction : Write
 * Start<Addr Byte><W>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 2: 
 * Address Format : 7Bit
 * Command Type   : None
 * Data Direction : Read 
 * Start<Addr Byte><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 3: 
 * Address Format : 7Bit
 * Command Type   : Standard
 * Data Direction : Write
 * Start<Addr Byte><W>Ack<CMD Byte>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 4: 
 * Address Format : 7Bit
 * Command Type   : Standard
 * Data Direction : Read
 * Start<Addr Byte><W>Ack<CMD Byte>Ack 
 * Start<Addr Byte><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 5: 
 * Address Format : 7Bit
 * Command Type   : Extended
 * Data Direction : Write
 * Start<Addr Byte><W>Ack<CMD Byte MSB>Ack<CMD Byte LSB>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 6: 
 * Address Format : 7Bit
 * Command Type   : Extended
 * Data Direction : Read
 * Start<Addr Byte><W>Ack<CMD Byte MSB>Ack<CMD Byte LSB>Ack 
 * Start<Addr Byte><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 7: 
 * Address Format : 10Bit
 * Command Type   : None
 * Data Direction : Write
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 8: 
 * Address Format : 10Bit
 * Command Type   : None
 * Data Direction : Read
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack 
 * Start<Addr Byte MSB><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 9: 
 * Address Format : 10Bit
 * Command Type   : Standard
 * Data Direction : Write
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<CMD Byte>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 10: 
 * Address Format : 10Bit
 * Command Type   : Standard
 * Data Direction : Read
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<CMD Byte>Ack 
 * Start<Addr Byte MSB><R>Ack<Data Byte 1>Nak Stop
 *
 * Transfer Type 11: 
 * Address Format : 10Bit
 * Command Type   : Extended
 * Data Direction : Write
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<CMD Byte MSB>Ack<CMD Byte LSB>Ack<Data Byte 1>Ack Stop
 *
 * Transfer Type 12: 
 * Address Format : 10Bit
 * Command Type   : Extended
 * Data Direction : Read
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack<CMD Byte MSB>Ack<CMD Byte LSB>Ack
 * Start<Addr Byte MSB><R>Ack<Data Byte 1>Nak Stop
 *
 */
#define EAPI_I2C_STD_CMD          EAPI_UINT32_C(0<<30)
#define EAPI_I2C_EXT_CMD          EAPI_UINT32_C(2<<30)
#define EAPI_I2C_NO_CMD           EAPI_UINT32_C(1<<30)    
#define EAPI_I2C_CMD_TYPE_MASK    EAPI_UINT32_C(3<<30)    

#define EAPI_I2C_ENC_STD_CMD(x)  EAPI_UINT32_C(((x)&0xFF)|EAPI_I2C_STD_CMD)
#define EAPI_I2C_ENC_EXT_CMD(x)  EAPI_UINT32_C(((x)&0xFFFF)|EAPI_I2C_EXT_CMD)
#define EAPI_I2C_IS_EXT_CMD(x)   (EAPI_UINT32_C((x)&(EAPI_I2C_CMD_TYPE_MASK))==EAPI_I2C_EXT_CMD)
#define EAPI_I2C_IS_STD_CMD(x)   (EAPI_UINT32_C((x)&(EAPI_I2C_CMD_TYPE_MASK))==EAPI_I2C_STD_CMD)
#define EAPI_I2C_IS_NO_CMD(x)    (EAPI_UINT32_C((x)&(EAPI_I2C_CMD_TYPE_MASK))==EAPI_I2C_NO_CMD)
/* 
 * EApiI2CReadTransfer
 * Addr Byte 1 Below Designates Addr MSB in a 10bit address transfer and 
 * the complete address in an 7bit address transfer.
 * 
 * Condition                                | Return Values 
 * -----------------------------------------+------------------------------
 * Library Uninitialized                    | EAPI_STATUS_NOT_INITIALIZED
 * pBuffer==NULL                            | EAPI_STATUS_INVALID_PARAMETER
 * BufLen==0                                | EAPI_STATUS_INVALID_PARAMETER
 * ByteCnt==0                               | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                               | EAPI_STATUS_UNSUPPORTED
 * ByteCnt>pMaxBlkLen                       | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Bus Busy  SDA/SDC low                    | EAPI_STATUS_BUSY_COLLISION
 * Arbitration Error/Collision Error        | EAPI_STATUS_BUSY_COLLISION
 *   On Write 1 write cycle                 |
 *   SDA Remains low                        |
 * Time-out due to clock stretching         | EAPI_STATUS_TIMEOUT
 * start<Addr Byte 1><W>Nak                 | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><R>Nak                 | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><W>Ack<Addr Byte 2>Nak | EAPI_STATUS_WRITE_ERROR or
 *                                          | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><W>Ack<CMD Byte 1>Nak  | EAPI_STATUS_WRITE_ERROR
 * start<Addr Byte 1><W>Ack<Data Byte 1>Nak | EAPI_STATUS_WRITE_ERROR
 * ByteCnt>BufLen                           | EAPI_STATUS_MORE_DATA
 * Common Error                             | Common Error Code
 * Else                                     | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiI2CReadTransfer(
    __IN  EApiId_t  Id      , /* I2C Bus Id */
    __IN  uint32_t  Addr    , /* Encoded 7/10Bit I2C
                               * Device Address
                               */
    __IN  uint32_t  Cmd     , /* I2C Command/Offset */
    __OUT     void *pBuffer , /* Transfer Data pBuffer */
    __IN  uint32_t  BufLen  , /* Data pBuffer Length */
    __IN  uint32_t  ByteCnt   /* Byte Count to read */
    );
/* 
 * EApiI2CWriteTransfer
 * Addr Byte 1 Below Designates Addr MSB in a 10bit address transfer and 
 * the complete address in an 7bit address transfer.
 * 
 * Condition                                | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                    | EAPI_STATUS_NOT_INITIALIZED
 * pBuffer==NULL                            | EAPI_STATUS_INVALID_PARAMETER
 * ByteCnt==0                               | EAPI_STATUS_INVALID_PARAMETER
 * unknown Id                               | EAPI_STATUS_UNSUPPORTED
 * ByteCnt+(overhead)>pMaxBlkLen            | EAPI_STATUS_INVALID_BLOCK_LENGTH
 * Bus Busy  SDA/SDC low                    | EAPI_STATUS_BUSY_COLLISION
 * Arbitration Error/Collision Error        | EAPI_STATUS_BUSY_COLLISION
 *   On Write 1 write cycle                 |
 *   SDA Remains low                        |
 * Time-out due to clock stretching         | EAPI_STATUS_TIMEOUT
 * start<Addr Byte 1><W>Nak                 | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><R>Nak                 | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><W>Ack<Addr Byte 2>Nak | EAPI_STATUS_WRITE_ERROR or
 *                                          | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte 1><W>Ack<CMD Byte 1>Nak  | EAPI_STATUS_WRITE_ERROR
 * start<Addr Byte 1><W>Ack<Data Byte 1>Nak | EAPI_STATUS_WRITE_ERROR
 * Common Error                             | Common Error Code
 * Else                                     | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE
EApiI2CWriteTransfer(
    __IN  EApiId_t  Id      , /* I2C Bus Id */
    __IN  uint32_t  Addr    , /* Encoded 7/10Bit I2C 
                               * Device Address 
                               */
    __IN  uint32_t  Cmd     , /* I2C Command/Offset */
    __IN      void *pBuffer , /* Transfer Data pBuffer */
    __IN  uint32_t  ByteCnt   /* Byte Count to write */
    );

/*
 * I2C Probe Types
 *
 * Probe Type 1: 
 * Address Format : 7Bit
 * Start<Addr Byte><W>Ack Stop
 *
 * Probe Type 2: 
 * Address Format : 10Bit
 * Start<Addr Byte MSB><W>Ack<Addr Byte LSB>Ack Stop
 *
 */

/* 
 * EApiI2CProbeDevice
 * 
 * Condition                                    | Return Values 
 * ---------------------------------------------+------------------------------
 * Library Uninitialized                        | EAPI_STATUS_NOT_INITIALIZED
 * Bus Busy  SDA/SDC low                        | EAPI_STATUS_BUSY_COLLISION
 * Arbitration Error/Collision Error            | EAPI_STATUS_BUSY_COLLISION
 *   On Write 1 write cycle                     |
 *   SDA Remains low                            |
 * Time-out due to clock stretching             | EAPI_STATUS_TIMEOUT
 *                                              |
 * 7Bit Address                                 |
 * start<Addr Byte><W>Nak                       | EAPI_STATUS_NOT_FOUND
 *                                              |
 * 10Bit Address                                |
 * start<Addr Byte MSB><W>Nak                   | EAPI_STATUS_NOT_FOUND
 * start<Addr Byte MSB><W>Ack<Addr Byte LSB>Nak | EAPI_STATUS_NOT_FOUND
 *                                              |
 * Common Error                                 | Common Error Code
 * Else                                         | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE
EApiI2CProbeDevice(
    __IN  EApiId_t  Id   , /* I2C Bus Id */
    __IN  uint32_t  Addr   /* Encoded 7/10Bit 
                            * I2C Device Address 
                            */
    );

/*
 *
 *      W A T C H D O G
 *
 */

/*
 *
 *
 * |<- Delay ->|<- Event Timeout ->|<- Trigger ->|
 * A-----------B-------------------C-------------D
 *			   ^				   |
 *             |				   | Reset Timer
 *			   |				   |
 *			   <-------------------E
 *
 *
 * Stage A
 *  Watchdog is started.
 *
 * Stage B
 *  Initial Event Period.
 *
 * Stage C
 *  Reset Period is exhausted.
 *  If didn't reset timer, WatchDog will be trigger to reboot system.
 *
 * Stage D
 *  System is reboot.
 *
 * Stage E
 *  Reset Watchdog's timer.
 *
 */

/* Description
 *   WatchDog Timer is NULL.
 * Actions
 *   none.
 */
#define EAPI_WDT_Timer_NULL            EAPI_UINT32_C(0x30000)

/* Description
 *   WatchDog Timer is over.
 * Actions
 *   none.
 */
#define EAPI_WDT_Timer_OVER            EAPI_UINT32_C(0x30001)

/* Description
 *   WatchDog Timer Mode is NULL.
 * Actions
 *   none.
 */
#define EAPI_WDT_Timer_Mode_NULL            EAPI_UINT32_C(0x30002)

/* Description
 *   WatchDog Timer Mode is not support.
 * Actions
 *   none.
 */
#define EAPI_WDT_Timer_Mode_UNKONW            EAPI_UINT32_C(0x30003)

#define EAPI_WDT_ID(WDT_NUM)    EAPI_UINT32_C(WDT_NUM)
#define EAPI_ID_WDT_AXeAPI		EAPI_WDT_ID(1)
#define EAPI_ID_WDT_AXuAPI		EAPI_WDT_ID(2)

/* 
 * EApiWDogGetCap
 * 
 * Condition                              | Return Values 
 * ---------------------------------------+------------------------------
 * Library Uninitialized                  | EAPI_STATUS_NOT_INITIALIZED
 * Unsupported                            | EAPI_STATUS_UNSUPPORTED
 * pMaxDelay==NULL&&                      |
 * pMaxResetTimeout==NULL&&               |
 * pMaxEventTimeout==NULL                 | EAPI_STATUS_INVALID_PARAMETER
 * Common Error                           | Common Error Code
 * Else                                   | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE
EApiWDogGetCap(
	__OUTOPT uint32_t *pEventFrom,		/* Event Timer From, 1 is eAPI, 2 is uAPI */
    __OUTOPT uint32_t *pEventTimer,		/* Event Timer in milliseconds
										 * 0 == Unsupported
										 */
    __OUTOPT uint32_t *pEventTimerMode  /* Event Timer Mode, 2 is Minute, 1 is Second */
    );
/* 
 * EApiWDogStart
 * 
 * Condition                        | Return Values 
 * ---------------------------------+------------------------------
 * Library Uninitialized            | EAPI_STATUS_NOT_INITIALIZED
 * Unsupported                      | EAPI_STATUS_UNSUPPORTED
 * Delay>pMaxDelay                  | EAPI_STATUS_INVALID_PARAMETER
 * EventTimeout>pMaxEventTimeout    | EAPI_STATUS_INVALID_PARAMETER
 * ResetTimeout>pMaxResetTimeout    | EAPI_STATUS_INVALID_PARAMETER
 * Already Running                  | EAPI_STATUS_RUNNING
 * Common Error                     | Common Error Code
 * Else                             | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiWDogStart(
    __IN uint32_t Delay       , /* Delay in milliseconds */
    __IN uint32_t EventTimeout, /* Event Timeout in milliseconds */
    __IN uint32_t ResetTimeout  /* Reset Timeout in milliseconds */
    );
/* 
 * EApiWDogStop
 * 
 * Condition                        | Return Values 
 * ---------------------------------+------------------------------
 * Library Uninitialized            | EAPI_STATUS_NOT_INITIALIZED
 * Unsupported                      | EAPI_STATUS_UNSUPPORTED
 * Common Error                     | Common Error Code
 * Else                             | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiWDogStop(void);
/* 
 * EApiWDogTrigger
 * 
 * Condition                        | Return Values 
 * ---------------------------------+------------------------------
 * Library Uninitialized            | EAPI_STATUS_NOT_INITIALIZED
 * Unsupported                      | EAPI_STATUS_UNSUPPORTED
 * Common Error                     | Common Error Code
 * Else                             | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiWDogTrigger(void);

/*
 *
 *      G P I O
 *
 */
/*
 *
 * +-----------------------------------------------+
 * |              Physical GPIO                    |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     +-----------------------------------------------+
 *    |     |     |     |     |     |     |     |                                               |
 *    |     |     |     |     |     |     +-----|-----------------------------------------+     |
 *    |     |     |     |     |     |     |     |                                         |     |
 *    |     |     |     |     |     +-----|-----|-----------------------------------+     |     |
 *    |     |     |     |     |     |     |     |                                   |     |     |
 *    |     |     |     |     +-----|-----|-----|-----------------------------+     |     |     |
 *    |     |     |     |     |     |     |     |                             |     |     |     |
 *    |     |     |     +-----|-----|-----|-----|-----------------------+     |     |     |     |
 *    |     |     |     |     |     |     |     |                       |     |     |     |     |
 *    |     |     +-----|-----|-----|-----|-----|-----------------+     |     |     |     |     |
 *    |     |     |     |     |     |     |     |                 |     |     |     |     |     |
 *    |     +-----|-----|-----|-----|-----|-----|-----------+     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     |           |     |     |     |     |     |     |
 *    +-----|-----|-----|-----|-----|-----|-----|-----+     |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |     |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |     |     |  |            EAPI_ID_GPIO_BITMASK00             |
 *    |     |     |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |     |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |     |  |            EAPI_ID_GPIO_GPIO07                |
 *    |     |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |     |
 *    |     |     |     |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |  |            EAPI_ID_GPIO_GPIO06                |
 *    |     |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |     |
 *    |     |     |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |  |            EAPI_ID_GPIO_GPIO05                |
 *    |     |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |     |
 *    |     |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |  |            EAPI_ID_GPIO_GPIO04                |
 *    |     |     |     |  +-----------------------------------------------+
 *    |     |     |     |
 *    |     |     |     |     0     0     0     0     0     0     0
 *    |     |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |     |  +-----------------------------------------------+
 *    |     |     |  |            EAPI_ID_GPIO_GPIO03                |
 *    |     |     |  +-----------------------------------------------+
 *    |     |     |
 *    |     |     |     0     0     0     0     0     0     0
 *    |     |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |     |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |     |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |     |  +-----------------------------------------------+
 *    |     |  |            EAPI_ID_GPIO_GPIO02                |
 *    |     |  +-----------------------------------------------+
 *    |     |
 *    |     |     0     0     0     0     0     0     0
 *    |  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    |  | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 *    |  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 *    |  +-----------------------------------------------+
 *    |  |            EAPI_ID_GPIO_GPIO01                |
 *    |  +-----------------------------------------------+
 *    |
 *    |     0     0     0     0     0     0     0
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | Bit | Bit | Bit | Bit | Bit | Bit | Bit | Bit |
 * |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
 * +-----------------------------------------------+
 * |            EAPI_ID_GPIO_GPIO00                |
 * +-----------------------------------------------+
 */
/* IDs */
/*
 * Individual ID Per GPIO Mapping
 */
#define EAPI_GPIO_GPIO_ID(GPIO_NUM)    EAPI_UINT32_C(GPIO_NUM)
#define EAPI_GPIO_GPIO_BITMASK  EAPI_UINT32_C(1)


//#define EAPI_ID_GPIO_GPIO00     EAPI_GPIO_GPIO_ID(0) /* (Optional) */
//#define EAPI_ID_GPIO_GPIO01     EAPI_GPIO_GPIO_ID(1) /* (Optional) */
//#define EAPI_ID_GPIO_GPIO02     EAPI_GPIO_GPIO_ID(2) /* (Optional) */
//#define EAPI_ID_GPIO_GPIO03     EAPI_GPIO_GPIO_ID(3) /* (Optional) */
//#define EAPI_ID_GPIO_GPIO04     EAPI_GPIO_GPIO_ID(4) /* (Optional) */
//#define EAPI_ID_GPIO_GPIO05     EAPI_GPIO_GPIO_ID(5) /* (Optional) */
//#define EAPI_ID_GPIO_GPIO06     EAPI_GPIO_GPIO_ID(6) /* (Optional) */
//#define EAPI_ID_GPIO_GPIO07     EAPI_GPIO_GPIO_ID(7) /* (Optional) */

#define EAPI_ID_GPIO_AXeAPI		EAPI_GPIO_GPIO_ID(1)
#define EAPI_ID_GPIO_AXuAPI		EAPI_GPIO_GPIO_ID(2)

#define EAPI_ID_GPIO_AXInput	EAPI_GPIO_GPIO_ID(1)
#define EAPI_ID_GPIO_AXOutput	EAPI_GPIO_GPIO_ID(0)

#define AX_OUTPUT 0
#define AX_INPUT 1

/*
 * Multiple GPIOs Per ID Mapping
 */
#define EAPI_GPIO_BANK_ID(GPIO_NUM)     EAPI_UINT32_C(0x10000|((GPIO_NUM)>>5))
#define EAPI_GPIO_BANK_MASK(GPIO_NUM) EAPI_UINT32_C((1<<((GPIO_NUM)&0x1F))
#define EAPI_GPIO_BANK_TEST_STATE(GPIO_NUM, TState, TValue) \
                        (((TValue>>((GPIO_NUM)&0x1F))&1)==(TState))

#define EAPI_ID_GPIO_BANK00    EAPI_GPIO_BANK_ID( 0) /* GPIOs  0 - 31 
                                                      * (optional)
                                                      */
#define EAPI_ID_GPIO_BANK01    EAPI_GPIO_BANK_ID(32) /* GPIOs 32 - 63 
                                                      * (optional)
                                                      */
#define EAPI_ID_GPIO_BANK02    EAPI_GPIO_BANK_ID(64) /* GPIOs 64 - 95
                                                      * (optional)
                                                      */


/* Bit mask Bit States */
#define EAPI_GPIO_BITMASK_SELECT   1
#define EAPI_GPIO_BITMASK_NOSELECT 0

/* Levels */
#define EAPI_GPIO_LOW     0
#define EAPI_GPIO_HIGH    1

/* Directions */
#define EAPI_GPIO_INPUT   1
#define EAPI_GPIO_OUTPUT  0

/* 
 * EApiGPIOGetDirectionCaps
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * ((pOutputs==NULL)&&(pInputs==NULL))| EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t
EAPI_CALLTYPE 
EApiGPIOGetDirectionCaps(
    __IN     EApiId_t Id        , /* GPIO Id */
    __OUT uint32_t *pInputs  , /* Supported GPIO Input
                                   * Bit Mask 
                                   */
    __OUT uint32_t *pOutputs   /* Supported GPIO Output
                                   * Bit Mask 
                                   */
    );
/* 
 * EApiGPIOGetDirection
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * Bitmask==0                         | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * (Bitmask&~(pInputs|pOutputs))      | EAPI_STATUS_INVALID_BITMASK
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiGPIOGetDirection(
    __IN  EApiId_t Id          , /* GPIO Id */
    __IN  uint32_t Bitmask     , /* Bit mask of Affected
                                  * Bits 
                                  */
    __OUT uint32_t *pDirection   /* Current Direction */
    );
/* 
 * EApiGPIOSetDirection
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * Bitmask==0                         | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * (Bitmask&~(pInputs|pOutputs))      | EAPI_STATUS_INVALID_BITMASK
 * (Bitmask&pDirection)&~pInputs      | EAPI_STATUS_INVALID_DIRECTION
 * (Bitmask&~pDirection)&~pOutputs    | EAPI_STATUS_INVALID_DIRECTION
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t 
EAPI_CALLTYPE 
EApiGPIOSetDirection(
    __IN  EApiId_t Id          , /* GPIO Id */
    __IN  uint32_t Bitmask     , /* Bit mask of Affected 
                                  * Bits 
                                  */
    __IN  uint32_t Direction     /* Direction */
    );
/* 
 * EApiGPIOGetLevel
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * Bitmask==0                         | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * (Bitmask&~(pInputs|pOutputs))      | EAPI_STATUS_INVALID_BITMASK
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t
EAPI_CALLTYPE 
EApiGPIOGetLevel(
    __IN  EApiId_t Id          , /* GPIO Id */
    __IN  uint32_t Bitmask     , /* Bit mask of Affected
                                  * Bits 
                                  */
    __OUT uint32_t *pLevel       /* Current Level */
    );
/* 
 * EApiGPIOSetLevel
 * 
 * Condition                          | Return Values 
 * -----------------------------------+------------------------------
 * Library Uninitialized              | EAPI_STATUS_NOT_INITIALIZED
 * Bitmask==0                         | EAPI_STATUS_INVALID_PARAMETER
 * Unsupported Id                     | EAPI_STATUS_UNSUPPORTED
 * Common Error                       | Common Error Code
 * Else                               | EAPI_STATUS_SUCCESS
 */
EApi
EApiStatus_t
EAPI_CALLTYPE 
EApiGPIOSetLevel(
    __IN  EApiId_t Id          , /* GPIO Id */
    __IN  uint32_t Bitmask     , /* Bit mask of Affected 
                                  * Bits 
                                  */
    __IN  uint32_t Level         /* Level */  
    );


/*
 *
 *      S E T R E C O V E R Y
 *
 */
EApi
EApiStatus_t
EAPI_CALLTYPE
EApiSetRecovery(void);

//#include "EApiCOM0.h"    /* COMExpress Platform Specific ID Mappings   */
//#include "EApiTCA.h"     /* TCA Platform Specific ID Mappings          */
//#include "EApiETX.h"     /* ETX Platform Specific ID Mappings          */
//#include "EApiQ7.h"      /* Q Seven Platform Specific ID Mappings      */
//#include "EApiMOPS.h"    /* MOPS Platform Specific ID Mappings         */
//#include "EApiPISA.h"    /* PISA Platform Specific ID Mappings         */
//#include "EApiEPIC.h"    /* EPIC Platform Specific ID Mappings         */
/****************************************************************************/
/*********************************************************************	AXView API	*********************************************************************/
EApi EApiStatus_t EAPI_CALLTYPE AXLibInitialize(void);
EApi EApiStatus_t EAPI_CALLTYPE AXLibUnInitialize(void);
EApi EApiStatus_t EAPI_CALLTYPE AXBoardGetStringA(
    __IN      EApiId_t  Id      , /* Name Id */
    __OUT     char     *pBuffer , /* Destination pBuffer */
    __INOUT   uint32_t *pBufLen   /* pBuffer Length */
    );
EApi EApiStatus_t EAPI_CALLTYPE AXBoardGetValue(
    __IN	EApiId_t  Id,		/* Value Id */
	__OUT	char     *pBuffer,	/* Destination pBuffer */
    __INOUT	uint32_t *pBufLen,	/* pBuffer Length */
    __INOUT	uint32_t *pIndex,	/* Index */
	__INOUT	uint32_t *pValue    /* Value */
    );
EApi EApiStatus_t EAPI_CALLTYPE AXBoardSetValue(
    __IN	EApiId_t  Id,		/* Value Id */
	__IN	char	 *pBuffer,	/* Destination pBuffer */
    __IN	uint32_t *pBufLen,	/* pBuffer Length */
    __IN	uint32_t *pIndex,	/* Index */
	__IN	uint32_t *pValue    /* Value */
    );
EApi EApiStatus_t EAPI_CALLTYPE AXWDogStart(
    __IN  uint32_t *pEventFrom,		/* Event Timer From, MB or MCU */
    __IN  uint32_t *pEventTimer,	/* Event Timer Counter */
    __IN  uint32_t *pEventTimerMode	/* Event Timer Mode, 2 is Minute, 1 is Second */
    );
EApi EApiStatus_t EAPI_CALLTYPE AXWDogStop(
    __IN uint32_t *pEventFrom		/* Event Timer From, MB or MCU */
	);
EApi EApiStatus_t EAPI_CALLTYPE AXWDogReset(
    __IN uint32_t *pEventFrom		/* Event Timer From, MB or MCU */
	);
EApi EApiStatus_t EAPI_CALLTYPE AXStorageCap(
    __IN  EApiId_t  Id            , /* Storage Area Id */
    __OUT uint32_t  *pStorageSize   /* Total */
    );
EApi EApiStatus_t EAPI_CALLTYPE AXStorageAreaRead(
    __IN	EApiId_t  Id, 		/* Storage Area Id */
    __IN	uint32_t  pOffset, 	/* Byte Offset */
    __OUT	char *pBuffer, 		/* Pointer to Data pBuffer */
    __IN	uint32_t  pBufLen, 	/* Data pBuffer Size in bytes */
    __IN	uint32_t  pByteCnt	/* Number of bytes to read */
    );
EApi EApiStatus_t EAPI_CALLTYPE AXStorageAreaWrite(
    __IN	EApiId_t  Id, 		/* Storage Area Id */
    __IN	uint32_t  pOffset, 	/* Byte Offset */
    __IN	char *pBuffer, 		/* Pointer to Data pBuffer */
    __IN	uint32_t  pBufLen, 	/* Data pBuffer Size in bytes */
    __IN	uint32_t  pByteCnt	/* Number of bytes to read */
    );
EApi EApiStatus_t EAPI_CALLTYPE AXRunRecovery(void);
EApi EApiStatus_t EAPI_CALLTYPE AXBoardGetACPIData(
	__OUT	char	 *pBuffer,		/* Destination pBuffer */
	__IN	uint32_t pOffset,		/* Byte Offset */
	__IN	uint32_t pBufLen		/* Data pBuffer Size in bytes */
    );
EApi EApiStatus_t EAPI_CALLTYPE AXThreshold(
	__IN	EApiId_t  Id, 		/* Index */
    __IN uint32_t *pThreshold	/* Value of Threshold */
	);
EApi EApiStatus_t EAPI_CALLTYPE AXLocker(
	__IN	EApiId_t  Id, 		/* Index */
    __OUT	uint32_t *pLocker	/* Value of Threshold */
	);
}
#endif

#ifdef __cplusplus

#endif

#endif /* _EAPI_H_ */