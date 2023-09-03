#include "tm4c123gh6pm_registers.h"

/*Prototype*/
void switch_init();
void led_init();

int main()
{
  // Enable clock for PORTF and allow time for clock to start 
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= 0x00000020; //Convert 100000 to hexa also set the clock of PORTF
  delay = SYSCTL_REGCGC2_REG;
  
  //Initializing the switch(PF0) and led(PF1)
  switch_init();
  led_init();
  while(1){
    if(!(GPIO_PORTF_DATA_REG & (1<<0))){
      GPIO_PORTF_DATA_REG |= (1<<1); //LED ON
    }else{
      GPIO_PORTF_DATA_REG &= ~(1<<1); //LED OFF
    }
  }
}
/*Functions*/
void switch_init(){
  GPIO_PORTF_LOCK_REG = 0x4C4F434B;     //For unlocking the GPIO LOCK register
  GPIO_PORTF_CR_REG |= (1<<0);          //Set comit register for enabling the GPIOAFSEL,GPIOPUR,GPIOPDR and GPIODEN
  GPIO_PORTF_AMSEL_REG &= ~(1<<0);      //Clearing the Analouge Mode SELect register to disable Analog on PF0
  GPIO_PORTF_PCTL_REG &= 0xFFFFFFF0;    //Clearing PCMx register for allowing pin PF0 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<0);      //Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_PUR_REG |= (1<<0);         //Set the pin PF0 to enable the pull up resistor config
  GPIO_PORTF_DIR_REG &= ~(1<<0);        //Clearing the pin PF0 to make it INPUT
  GPIO_PORTF_DEN_REG |= (1<<0);         //Set the pin PF0 to enable it
}
void led_init(){
  GPIO_PORTF_AMSEL_REG &= ~(1<<1);      //Clearing the Analouge Mode SELect register to disable Analog on PF1
  GPIO_PORTF_PCTL_REG &= 0xFFFFFF0F;    //Clearing PCMx register for allowing pin PF1 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<1);      //Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_DIR_REG |= (1<<1);        //Set the pin PF1 to make it OUTPUT
  GPIO_PORTF_DEN_REG |= (1<<1);         //Set the pin PF1 to enable it
  GPIO_PORTF_DATA_REG &= ~(1<<1);       //Making sure that the led is off at first LOW (Positive Logic)
}