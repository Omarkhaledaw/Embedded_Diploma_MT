 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Omar Khaled
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"
#include "tm4c123gh6pm_registers.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
  || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
  || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigChannels * PortChannels = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else
#endif
        {
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
                volatile uint32 * Port_Ptr = NULL_PTR;                                  /* point to the required Port Registers base address */
                volatile uint32 delay = 0;                                              /* delay variable used later for enabling the clock */
                volatile uint8 Pins_Count = 0;                                          /* counting variable for navigating through the pins of each port */
                PortChannels = ConfigPtr->Channels;                                     /* initializing the global pointer to point on the port configuration channels */        

                
                for(Pins_Count = 0;Pins_Count<PORT_CONFIGURED_CHANNLES;Pins_Count++)
                {
                  /*Setting the Portptr to point to the port base address*/
                  switch(PortChannels[Pins_Count].port_num)
                  {
                    case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;     /* PORTA Base Address */
                             break;
                    case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;     /* PORTB Base Address */
                             break;
                    case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;     /* PORTC Base Address */
                             break;
                    case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;     /* PORTD Base Address */
                             break;
                    case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;     /* PORTE Base Address */
                             break;
                    case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;     /* PORTF Base Address */
                             break;
                  }
                  /* Enable clock for PORT and allow time for clock to start*/
                  SET_BIT(SYSCTL_REGCGC2_REG, PortChannels[Pins_Count].port_num);
                  delay = SYSCTL_REGCGC2_REG;
                  
                  /*Special Pins configurations that requires enabling the commit register which also require inserting the magic number in the lock register*/
                  if( ((PortChannels[Pins_Count].port_num == PORT_PORTD_ID) && (PortChannels[Pins_Count].pin_num == PORT_PIN7_ID)) || ((PortChannels[Pins_Count].port_num == PORT_PORTF_ID) && (PortChannels[Pins_Count].pin_num == PORT_PIN0_ID)) ) /* PD7 or PF0 */
                  {
                      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                                     /* Unlock the GPIOCR register */   
                      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , PortChannels[Pins_Count].pin_num);    /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                  }
                  else if( (PortChannels[Pins_Count].port_num == PORT_PORTC_ID) && (PortChannels[Pins_Count].pin_num <= PORT_PIN3_ID) )         /* PC0 to PC3 */
                  {
                      /* Do Nothing ...  this is the JTAG pins */
                  }
                  else
                  {
                      /* Do Nothing ... No need to unlock the commit register for this pin */
                  }
                  if(PortChannels[Pins_Count].direction == PORT_PIN_OUT)
                  {
                      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
                      if(PortChannels[Pins_Count].initial_value == STD_HIGH)
                      {
                          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , PortChannels[Pins_Count].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                      }
                      else
                      {
                          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                      }
                  }else if(PortChannels[Pins_Count].direction == PORT_PIN_IN)
                  {
                      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
                      if(PortChannels[Pins_Count].resistor == PULL_UP)
                      {
                          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , PortChannels[Pins_Count].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                      }
                      else if(PortChannels[Pins_Count].resistor == PULL_DOWN)
                      {
                          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                      }
                      else
                      {
                          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortChannels[Pins_Count].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                      }
                  }else
                  {
                      /* Do Nothing */
                  
                  }
                  switch(PortChannels[Pins_Count].pin_mode)
                  {
                      case PORT_PIN_MODE_ADC:
                      {
                          if(PortChannels[Pins_Count].direction == PORT_PIN_IN && \
                            ((PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)))
                          {
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                          }else
                          {
                              /* Do Nothing */
                          }  
                          break;
                      }
                      case PORT_PIN_MODE_CAN:
                      {
                        if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                        
                        }else if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */

                        }else
                        {
                              /* Do Nothing */ 
                        }
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        break;
                      }
                      case PORT_PIN_MODE_DIO:
                      {
                        if(PortChannels[Pins_Count].pin_num <= PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID) /* PC0 to PC3 */
                        {
                              /* Do Nothing ...  this is the JTAG pins */
                        }else
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PortChannels[Pins_Count].pin_num * 4));     /* Clear the PMCx bits for this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */  
                        }
                        
                        break;
                      }
                      case PORT_PIN_MODE_DIO_GPT:
                      {
                        if(!(PortChannels[Pins_Count].port_num == PORT_PORTA_ID) || !(PortChannels[Pins_Count].port_num == PORT_PORTE_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000007 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                        }else
                        {
                              /* Do Nothing */ 
                        }
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        break;
                      }
                      case PORT_PIN_MODE_DIO_WDG:
                      {
                      
                              /* Do Nothing */
                        break;
                      }
                      case PORT_PIN_MODE_FLEXRAY:
                      {
                      
                              /* Do Nothing */
                        break;
                      }
                      case PORT_PIN_MODE_ICU:
                      {
                        if((PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                        }else{
                          
                              /* Do Nothing */
                        }
                        break;
                      }
                      case PORT_PIN_MODE_LIN:
                      {
                      
                              /* Do Nothing */
                        break;
                      }
                      case PORT_PIN_MODE_MEM:
                      {
                      
                              /* Do Nothing */
                        break;
                      }
                      case PORT_PIN_MODE_PWM:
                      {
                        if((PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                              
                        }else if((PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                        }else
                        {
                              /* Do Nothing */
                        }
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        break;
                      }
                      case PORT_PIN_MODE_SPI:
                      {
                        if((PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000002 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                        
                        }else if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                        }else{
                      
                              /* Do Nothing */
                        }
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        break;
                      }
                      case PORT_PIN_MODE_ANALOG_CMP:
                      {
                        if((PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID))
                        {
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                          
                        }else if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000009 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                          
                        }else
                        {
                              /* Do Nothing */
                        }
                        break;
                      }
                      case PORT_PIN_MODE_QEI:
                      {
                        if((PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000006 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                        }else
                        {                
                              /* Do Nothing */
                        }
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        break;
                      }
                      case PORT_PIN_MODE_UART:
                      {
                        if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                        
                        }else
                        {
                              /* Do Nothing */
                        }
                        break;
                      }
                      case PORT_PIN_MODE_USB:
                      {
                        if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID))
                        {
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                  
                        }else if((PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                        {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                              
                        }else
                        {                 
                              /* Do Nothing */
                        }
                        break;
                      }
                      default: break;
                  }
                  /*End of Switch cases*/
                }
                
                Port_Status = PORT_INITIALIZED;                                         /* changing the status of the port to initialized */
        }

}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
                volatile uint32 * Port_Ptr = NULL_PTR;                                  /* point to the required Port Registers base address */
                volatile uint8 Pins_Count = 0;                                          /* counting variable for navigating through the pins of each port */
                boolean error = FALSE;
                
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(Port_Status != PORT_INITIALIZED)
    {
            /* Report to DET  */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                            PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
            error = TRUE;
    }
    else
    {
            /* No Action Required */
    }
    if (PORT_CONFIGURED_CHANNLES <= Pin)
    {

            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                            PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
            error = TRUE;
    }
    else
    {
            /* No Action Required */
    }
    if (STD_OFF == PortChannels[Pins_Count].PORT_PIN_DIRECTION_CHANGEABLE )
    {

            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                            PORT_SET_PIN_MODE_SID, PORT_E_DIRECTION_UNCHANGEABLE);
            error = TRUE;
    }
    else
    {
            /* No Action Required */
    }
#endif
    if(error == FALSE)
    {
      Pins_Count = Pin;
      switch(PortChannels[Pins_Count].port_num)
      {
        case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;     /* PORTA Base Address */
                 break;
        case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;     /* PORTB Base Address */
                 break;
        case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;     /* PORTC Base Address */
                 break;
        case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;     /* PORTD Base Address */
                 break;
        case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;     /* PORTE Base Address */
                 break;
        case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;     /* PORTF Base Address */
                 break;
        default: break;
      }
      if(PortChannels[Pins_Count].direction == PORT_PIN_OUT)
      {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
      
      }else if(PortChannels[Pins_Count].direction == PORT_PIN_IN)
      {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
      
      }else
      {
          /* Do Nothing */
      
      }
      
    }else
    {
            /* No Action Required */
    }

}
#endif
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
                volatile uint32 * Port_Ptr = NULL_PTR;                                  /* point to the required Port Registers base address */
                volatile uint8 Pins_Count = 0;                                          /* counting variable for navigating through the pins of each port */
                boolean error = FALSE;
                
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(Port_Status != PORT_INITIALIZED)
    {
            /* Report to DET  */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                            PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
            error = TRUE;
    }
    else
    {
            /* No Action Required */
    }
#endif
    if(error == FALSE)
    {
      for(Pins_Count = 0;Pins_Count<PORT_CONFIGURED_CHANNLES;Pins_Count++)
      {
        /* Exclude the port pins from refreshing that are configured as pin direction changeable during runtime. */
        if(STD_OFF == PortChannels[Pins_Count].PORT_PIN_DIRECTION_CHANGEABLE)
        {
          switch(PortChannels[Pins_Count].port_num)
          {
            case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;     /* PORTA Base Address */
                     break;
            case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;     /* PORTB Base Address */
                     break;
            case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;     /* PORTC Base Address */
                     break;
            case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;     /* PORTD Base Address */
                     break;
            case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;     /* PORTE Base Address */
                     break;
            case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;     /* PORTF Base Address */
                     break;
            default: break;
          }
          if(BIT_IS_CLEAR(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num))
          {
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
          
          }else if(BIT_IS_SET(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num))
          {
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
          
          }else
          {
              /* Do Nothing */
          
          }
        }else
        {
            /* Do Nothing */
        
        }
    }
    }else
    {
            /* Do Nothing */
    }
}

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* Check if input pointer is not Null pointer */
      if(NULL_PTR == versioninfo)
      {
              /* Report to DET  */
              Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                              PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
      }
      else
#endif /* (PORT_VERSION_INFO_API == STD_ON) */
      {
              /* Copy the vendor Id */
              versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
              /* Copy the module Id */
              versioninfo->moduleID = (uint16)PORT_MODULE_ID;
              /* Copy Software Major Version */
              versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
              /* Copy Software Minor Version */
              versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
              /* Copy Software Patch Version */
              versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
      }

}
#endif
/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number
*                  Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
{
                volatile uint32 * Port_Ptr = NULL_PTR;                                  /* point to the required Port Registers base address */
                volatile uint8 Pins_Count = 0;                                          /* counting variable for navigating through the pins of each port */
                boolean error = FALSE;
  
#if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* Check if input pointer is not Null pointer */
      if(Port_Status != PORT_INITIALIZED)
      {
              /* Report to DET  */
              Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                              PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
              error = TRUE;
      }
      else
      {
              /* Do Nothing */
      }
      if (PORT_CONFIGURED_CHANNLES <= Pin)
      {

              Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                              PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
              error = TRUE;
      }
      else
      {
              /* Do Nothing */
      }
      if (PORT_PIN_MODES <= Mode)
      {

              Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                              PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
              error = TRUE;
      }
      else
      {
              /* Do Nothing */
      }
      if (STD_OFF == PortChannels[Pins_Count].PORT_PIN_MODE_CHANGEABLE )
      {

              Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                              PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
              error = TRUE;
      }
      else
      {
              /* Do Nothing */
      }
#endif
      if(error == FALSE)
      {
                 Pins_Count = Pin;
                /*Setting the Portptr to point to the port base address*/
                switch(PortChannels[Pins_Count].port_num)
                {
                  case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;     /* PORTA Base Address */
                           break;
                  case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;     /* PORTB Base Address */
                           break;
                  case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;     /* PORTC Base Address */
                           break;
                  case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;     /* PORTD Base Address */
                           break;
                  case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;     /* PORTE Base Address */
                           break;
                  case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;     /* PORTF Base Address */
                           break;
                }
                /* Enable clock for PORT and allow time for clock to start*/
                volatile unsigned long delay = 0;
                SET_BIT(SYSCTL_REGCGC2_REG, PortChannels[Pins_Count].port_num);
                delay = SYSCTL_REGCGC2_REG;
                
                /*Special Pins configurations that requires enabling the commit register which also require inserting the magic number in the lock register*/
                if( ((PortChannels[Pins_Count].port_num == PORT_PORTD_ID) && (PortChannels[Pins_Count].pin_num == PORT_PIN7_ID)) || ((PortChannels[Pins_Count].port_num == PORT_PORTF_ID) && (PortChannels[Pins_Count].pin_num == PORT_PIN0_ID)) ) /* PD7 or PF0 */
                {
                    *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                                     /* Unlock the GPIOCR register */   
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , PortChannels[Pins_Count].pin_num);    /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                }
                else if( (PortChannels[Pins_Count].port_num == PORT_PORTC_ID) && (PortChannels[Pins_Count].pin_num <= PORT_PIN3_ID) )         /* PC0 to PC3 */
                {
                    /* Do Nothing ...  this is the JTAG pins */
                }
                else
                {
                    /* Do Nothing ... No need to unlock the commit register for this pin */
                }
                if(PortChannels[Pins_Count].direction == PORT_PIN_OUT)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
      
                    if(PortChannels[Pins_Count].initial_value == STD_HIGH)
                    {
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , PortChannels[Pins_Count].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    }
                    else
                    {
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                    }
                }else if(PortChannels[Pins_Count].direction == PORT_PIN_IN)
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
      
                    if(PortChannels[Pins_Count].resistor == PULL_UP)
                    {
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , PortChannels[Pins_Count].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                    }
                    else if(PortChannels[Pins_Count].resistor == PULL_DOWN)
                    {
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                    }
                    else
                    {
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortChannels[Pins_Count].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                    }
                }else
                {
                    /* Do Nothing */
                
                }
                switch(PortChannels[Pins_Count].pin_mode)
                {
                    case PORT_PIN_MODE_ADC:
                    {
                        if(PortChannels[Pins_Count].direction == PORT_PIN_IN && \
                          ((PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)))
                        {
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                        }else
                        {
                            /* Do Nothing */
                        }  
                        break;
                    }
                    case PORT_PIN_MODE_CAN:
                    {
                      if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                      
                      }else if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */

                      }else
                      {
                            /* Do Nothing */ 
                      }
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                      break;
                    }
                    case PORT_PIN_MODE_DIO:
                    {
                      if(PortChannels[Pins_Count].pin_num <= PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID) /* PC0 to PC3 */
                      {
                            /* Do Nothing ...  this is the JTAG pins */
                      }else
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PortChannels[Pins_Count].pin_num * 4));     /* Clear the PMCx bits for this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */  
                      }
                      
                      break;
                    }
                    case PORT_PIN_MODE_DIO_GPT:
                    {
                      if(!(PortChannels[Pins_Count].port_num == PORT_PORTA_ID) || !(PortChannels[Pins_Count].port_num == PORT_PORTE_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000007 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                      }else
                      {
                            /* Do Nothing */ 
                      }
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                      break;
                    }
                    case PORT_PIN_MODE_DIO_WDG:
                    {
                    
                            /* Do Nothing */
                      break;
                    }
                    case PORT_PIN_MODE_FLEXRAY:
                    {
                    
                            /* Do Nothing */
                      break;
                    }
                    case PORT_PIN_MODE_ICU:
                    {
                      if((PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000003 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                      }else{
                        
                            /* Do Nothing */
                      }
                      break;
                    }
                    case PORT_PIN_MODE_LIN:
                    {
                    
                            /* Do Nothing */
                      break;
                    }
                    case PORT_PIN_MODE_MEM:
                    {
                    
                            /* Do Nothing */
                      break;
                    }
                    case PORT_PIN_MODE_PWM:
                    {
                      if((PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                            
                      }else if((PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                      }else
                      {
                            /* Do Nothing */
                      }
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                      break;
                    }
                    case PORT_PIN_MODE_SPI:
                    {
                      if((PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000002 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                      
                      }else if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                      }else{
                    
                            /* Do Nothing */
                      }
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                      break;
                    }
                    case PORT_PIN_MODE_ANALOG_CMP:
                    {
                      if((PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID))
                      {
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                        
                      }else if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000009 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        
                      }else
                      {
                            /* Do Nothing */
                      }
                      break;
                    }
                    case PORT_PIN_MODE_QEI:
                    {
                      if((PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000006 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                      }else
                      {                
                            /* Do Nothing */
                      }
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                      break;
                    }
                    case PORT_PIN_MODE_UART:
                    {
                      if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTA_ID)\
                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTE_ID)\
                                                      ||(PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID)\
                                                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000001 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                      
                      }else
                      {
                            /* Do Nothing */
                      }
                      break;
                    }
                    case PORT_PIN_MODE_USB:
                    {
                      if((PortChannels[Pins_Count].pin_num == PORT_PIN0_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                        ||(PortChannels[Pins_Count].pin_num == PORT_PIN1_ID && PortChannels[Pins_Count].port_num == PORT_PORTB_ID)\
                          ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                            ||(PortChannels[Pins_Count].pin_num == PORT_PIN5_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID))
                      {
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                
                      }else if((PortChannels[Pins_Count].pin_num == PORT_PIN6_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                              ||(PortChannels[Pins_Count].pin_num == PORT_PIN7_ID && PortChannels[Pins_Count].port_num == PORT_PORTC_ID)\
                                ||(PortChannels[Pins_Count].pin_num == PORT_PIN2_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                  ||(PortChannels[Pins_Count].pin_num == PORT_PIN3_ID && PortChannels[Pins_Count].port_num == PORT_PORTD_ID)\
                                    ||(PortChannels[Pins_Count].pin_num == PORT_PIN4_ID && PortChannels[Pins_Count].port_num == PORT_PORTF_ID))
                      {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[Pins_Count].pin_num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[Pins_Count].pin_num);              /* Enable Alternative function for this pin by settomg the corresponding bit in GPIOAFSEL register */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000008 << (PortChannels[Pins_Count].pin_num * 4));     /* Set the PMCx bits for this pin */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[Pins_Count].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                            
                      }else
                      {                 
                            /* Do Nothing */
                      }
                      break;
                    }
                    default: break;
                }
                /*End of Switch cases*/ 
        
      }else
      {
              /* Do Nothing */
      }

}
#endif