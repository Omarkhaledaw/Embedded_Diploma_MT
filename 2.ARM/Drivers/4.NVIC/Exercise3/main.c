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

/*Functions prototype*/
void led_init();
void systick_init();

/*ISR*/
void SysTick_Handler(){
  GPIO_PORTF_DATA_REG ^= (1<<1); //Toggle instead of on an off
}

int main(){
  
  /*SETUP LOOP*/
  // Enable clock for PORTF and allow time for clock to start 
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= 0x00000020; //Convert 100000 to hexa also set the clock of PORTF
  delay = SYSCTL_REGCGC2_REG;
  
  led_init();
  systick_init();
  
  Enable_Exceptions();//Enable Exceptions
  Enable_Faults();//Enable Faults
  /*MAIN LOOP*/
  while(1){
    Wait_For_Interrupt(); //Go to low power mode while waiting for the next interrupt
  }
}
/*Functions*/
void led_init(){
  GPIO_PORTF_AMSEL_REG &= ~(1<<1);      //Clearing the Analouge Mode SELect register to disable Analog on PF1
  GPIO_PORTF_PCTL_REG &= 0xFFFFFF0F;    //Clearing PCMx register for allowing pin PF1 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<1);      //Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_DIR_REG |= (1<<1);        //Set the pin PF1 to make it OUTPUT
  GPIO_PORTF_DEN_REG |= (1<<1);         //Set the pin PF1 to enable it
  GPIO_PORTF_DATA_REG &= ~(1<<1);       //Making sure that the led is off at first LOW (Positive Logic)
}
void systick_init(){

  SYSTICK_CTRL_REG = 0;         //Clearing the ALL of the ConTRoL register to turn of the systick timer at initialization 
  SYSTICK_RELOAD_REG = 7999999; //Set the RELOAD value in the reload register
  SYSTICK_CURRENT_REG = 0;      //Clearing the counter CURRENT register 
  SYSTICK_CTRL_REG |= 0x07;     //Set the ConTRol register in order to use the system clock and enable the timer again
  NVIC_SYSTEM_PRI3_REG = ((NVIC_SYSTEM_PRI3_REG & 0x1FFFFFFF)|(2<<29))
}