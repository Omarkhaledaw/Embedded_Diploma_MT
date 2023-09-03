#include "tm4c123gh6pm_registers.h"

/*define*/
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762
/*
#define PF1  (*((volatile unsigned long *)(0x40025000+0x08)))
#define PF2  (*((volatile unsigned long *)(0x40025000+0x10)))
#define PF3  (*((volatile unsigned long *)(0x40025000+0x20)))
*/

/*Functions prototype*/
void Delay_MS(unsigned long long n);
void led_init();

int main(){
  
  /*SETUP LOOP*/
  // Enable clock for PORTF and allow time for clock to start 
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= 0x00000020;
  delay = SYSCTL_REGCGC2_REG;
  led_init();
  
  /*MAIN LOOP*/
  while(1){
    GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08;
    Delay_MS(1000);
    GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04;
    Delay_MS(1000);
    GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02;
    Delay_MS(1000);
    /*
        // Access each pin indvidually using the Bit Band feature
        PF1 = 0x02; // Turn on the Red LED 
        PF2 = 0x00; // Turn off the Blue LED 
        PF3 = 0x00; // Turn off the Green LED
        Delay_MS(1000);
        
        // Access each pin indvidually using the Bit Band feature 
        PF1 = 0x00; // Turn off the Red LED 
        PF2 = 0x04; // Turn on the Blue LED
        PF3 = 0x00; // Turn off the Green LED 
        Delay_MS(1000);
        
        // Access each pin indvidually using the Bit Band feature 
        PF1 = 0x00; // Turn off the Red LED 
        PF2 = 0x00; // Turn off the Blue LED 
        PF3 = 0x08; // Turn on the Green LED 
        Delay_MS(1000); 
    */
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