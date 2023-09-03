 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT Init */
#define PORT_INIT_SID                           (uint8)0x00

/* Service ID for Set PORT Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID              (uint8)0x01

/* Service ID for refresh PORT Direction  */
#define PORT_REFRESH_PORT_DIRECTION_SID         (uint8)0x02

/* Service ID for PORT GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID               (uint8)0x03

/* Service ID for Set PORT Mode */
#define PORT_SET_PIN_MODE_SID                   (uint8)0x04
   
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                        (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE           (uint8)0x0B

/* DET code to report API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG                     (uint8)0x0C

/* DET code to report API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE               (uint8)0x0D
#define PORT_E_MODE_UNCHANGEABLE                (uint8)0x0E
/* DET code to report API service called without module initialization */
#define PORT_E_UNINIT                           (uint8)0x0F

/* DET code to report APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER                    (uint8)0x10
   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Description: Data type for the symbolic name of a port pin */
typedef uint8   Port_PinType;

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistorType;

/* Description: Different port pin modes */
typedef uint8   Port_PinModeType;

/* Description: Different port pin level */
typedef enum
{
    PORT_PIN_LEVEL_LOW,PORT_PIN_LEVEL_HIGH
}Port_LevelType;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 *      5. the initial value --> Low or High
 *      6. the pin mode type --> ADC, CAN, DIO, DIO, DIO_GPT, DIO_WDG, FLEXRAY, ICU, LIN, MEM, PWM and SPI
 *      7. the pin direction changeable --> False or True
 *      8. the pin mode changeable --> False or True
 */
typedef struct 
{
    uint8 port_num; 
    Port_PinType pin_num; 
    Port_PinDirectionType direction;
    Port_InternalResistorType resistor;
    Port_LevelType initial_value;
    Port_PinModeType pin_mode;
    uint8 PORT_PIN_DIRECTION_CHANGEABLE;
    uint8 PORT_PIN_MODE_CHANGEABLE;
    
}Port_ConfigChannels;

/* Data Structure required for initializing the Port Driver */
typedef struct Port_ConfigType
{
	Port_ConfigChannels Channels[PORT_CONFIGURED_CHANNLES];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Description: Initializes the Port Driver module */
void Port_Init(const Port_ConfigType* ConfigPtr);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Description: Sets the port pin direction */
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
#endif

/* Description: Refreshes port direction */
void Port_RefreshPortDirection(void);

#if (PORT_VERSION_INFO_API == STD_ON)
/* Description: Returns the version information of this module */
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/* Description: Sets the port pin mode */
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
