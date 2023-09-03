#include "tm4c123gh6pm_registers.h"

/*Defines*/
/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm("CPSIE I")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm("CPSID I")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm("CPSIE F")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm("CPSID F") 

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm("WFI")

/*Function prototype*/
void led_init();
void switch_init();

/*ISR*/
void FallingEdgeTrigger(){
  GPIO_PORTF_DATA_REG |= (1<<2);        //Turning led blue on
  GPIO_PORTF_ICR_REG |=(1<<4);  //clearing the interrupt flag
}
int main(){
  /*SETUP LOOP*/
  
  //Enable clock for PORTF and allow time for clock to start 
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= 0x00000020;
  delay = SYSCTL_REGCGC2_REG;
  
  led_init();
  switch_init();
  

  Enable_Exceptions();//Enable Exceptions
  Enable_Faults();//Enable Faults
  
  /*MAIN LOOP*/
  While(1){
    Wait_For_Interrupt();//Go to low power mode while waiting for the next interrupt
  }
}

/*Functions*/
void led_init(){
  
  GPIO_PORTF_AMSEL_REG &= ~(1<<2);      //Clearing the Analouge Mode SELect register to disable Analog on PF2
  GPIO_PORTF_PCTL_REG &= 0xFFFFF0FF;    //Clearing PCMx register for allowing pin PF2 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<2);      //Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_DIR_REG |= (1<<2);         //Clearing the pin PF2 to make it OUTPUT
  GPIO_PORTF_DEN_REG |= (1<<2);         //Set the pin PF2 to enable it
  GPIO_PORTF_DATA_REG &= ~(1<<2);       //Making sure that the led is off at first LOW (Positive Logic)
}
void switch_init(){
  
  GPIO_PORTF_AMSEL_REG &= ~(1<<4);//Clearing the Analouge Mode SELect register to disable Analog on PF4
  GPIO_PORTF_PCTL_REG &= 0xFFF0FFFF;//Clearing PCMx register for allowing pin PF4 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<4);//Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_PUR_REG |= (1<<4);//Clearing the pin PF4 to make it INPUT
  GPIO_PORTF_DIR_REG &= ~(1<<4);//Set the pin PF4 to enable the pull up resistor config
  GPIO_PORTF_DEN_REG |= (1<<4);//Set the pin PF4 to enable it
  
  GPIO_PORTF_IS_REG &= ~(1<<4);//Clearing Interrupt Sense bit for portf to detect edges
  GPIO_PORTF_IBE_REG &= ~(1<<4);//Clearing Interrupt Both Edges bit for portf to detect a specific edge
  GPIO_PORTF_IEV_REG &= ~(1<<4);//Clearing Interrupt EVent bit for portf to detect falling edge
  GPIO_PORTF_IM_REG |= (1<<4);//Set the Interrupt Mask bit for portf to allow interrupts
  
  NVIC_PRI7_REG = ((NVIC_PRI7_REG & 0xFF1FFFF)|(2<<21));//Set the priority in the NVIC System Handler priority register
  NVIC_EN0_REG |= 0x40000000;//Enabling the NVIC interrupts for portf
  
}