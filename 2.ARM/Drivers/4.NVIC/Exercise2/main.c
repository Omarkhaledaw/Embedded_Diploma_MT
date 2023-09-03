#include "tm4c123gh6pm_registers.h"

/*Defines*/
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762

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
void Delay_MS(unsigned long long n);

/*Global variables*/
volatile unsigned char flag = 0;

/*ISR*/
void FallingEdgeTrigger(){
  flag = 1;
  GPIO_PORTF_ICR_REG |=(1<<0);  //clearing the interrupt flag
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
    if(flag == 0){
      GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02;
      Delay_MS(1000);
      GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04;
      Delay_MS(1000);
      GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08;
      Delay_MS(1000);
    }else if(flag == 1){
    
      GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x0E; 
      Delay_MS(5000);
      flag = 0;
    }
  }
}

/*Functions*/
void Delay_MS(unsigned long long n){
  
  volatile unsigned long long count = 0;
  while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}
void led_init(){

  GPIO_PORTF_AMSEL_REG &= 0xF1;         //Clearing the Analouge Mode SELect register to disable Analog on PF1,2,3
  GPIO_PORTF_PCTL_REG &= 0xFFFF000F;    //Clearing PCMx register for allowing pins PF1,2,3 available for GPIO
  GPIO_PORTF_AFSEL_REG &= 0xF1;         //Clearing Alternative Function SELect register to use the pins for GPIO
  GPIO_PORTF_DIR_REG |= 0x0E;           //Clearing the pins PF1,2,3 to make it OUTPUT
  GPIO_PORTF_DEN_REG |= 0x0E;           //Set the pins PF1,2,3 to enable it
  GPIO_PORTF_DATA_REG &= 0xF1;          //Making sure that the leds are off at first LOW (Positive Logic)
}
void switch_init(){
  
  GPIO_PORTF_LOCK_REG   = 0x4C4F434B;                           //For unlocking the GPIO LOCK register
  GPIO_PORTF_CR_REG    |= (1<<0);                               //Set comit register for enabling the GPIOAFSEL,GPIOPUR,GPIOPDR and GPIODEN
  GPIO_PORTF_AMSEL_REG &= ~(1<<0);                              //Clearing the Analouge Mode SELect register to disable Analog on PF4
  GPIO_PORTF_PCTL_REG &= 0xFFFFFFF0;                            //Clearing PCMx register for allowing pin PF4 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<0);                              //Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_PUR_REG |= (1<<0);                                 //Clearing the pin PF4 to make it INPUT
  GPIO_PORTF_DIR_REG &= ~(1<<0);                                //Set the pin PF4 to enable the pull up resistor config
  GPIO_PORTF_DEN_REG |= (1<<0);                                 //Set the pin PF4 to enable it
  
  GPIO_PORTF_IS_REG &= ~(1<<0);                                 //Clearing Interrupt Sense bit for portf to detect edges
  GPIO_PORTF_IBE_REG &= ~(1<<0);                                //Clearing Interrupt Both Edges bit for portf to detect a specific edge
  GPIO_PORTF_IEV_REG &= ~(1<<0);                                //Clearing Interrupt EVent bit for portf to detect falling edge
  GPIO_PORTF_IM_REG |= (1<<0);                                  //Set the Interrupt Mask bit for portf to allow interrupts
  
  NVIC_PRI7_REG = ((NVIC_PRI7_REG & 0xFF1FFFF)|(2<<21));        //Set the priority in the NVIC System Handler priority register
  NVIC_EN0_REG |= 0x40000000;                                   //Enabling the NVIC interrupts for portf
  
}