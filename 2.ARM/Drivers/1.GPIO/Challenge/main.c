#include "tm4c123gh6pm_registers.h"

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762

/*Functions prototype*/
void Delay_MS(unsigned long long n);
void switch1_init();
void switch2_init();
void leds_init();

int main(){
  
  /*SETUP LOOP*/
  // Enable clock for PORTF and allow time for clock to start 
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= 0x00000020;
  delay = SYSCTL_REGCGC2_REG;
  
  switch1_init();
  switch2_init();
  leds_init();
  
  /*MAIN LOOP*/
  while(1){
    if(!(GPIO_PORTF_DATA_REG & (1<<0))){
      
      Delay_MS(10);
      if(!(GPIO_PORTF_DATA_REG & (1<<0))){
        GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04; //BLUE
        Delay_MS(500);
        GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08; //GREEN
        Delay_MS(500);
     
      }
    }else if(!(GPIO_PORTF_DATA_REG & (1<<4))){
            
      Delay_MS(10);
      if(!(GPIO_PORTF_DATA_REG & (1<<4))){
      GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; //RED
      Delay_MS(500);
      GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04; //BLUE
      Delay_MS(500);
    }
  }
}
/*Functions*/
void Delay_MS(unsigned long long n){
  
  volatile unsigned long long count = 0;
  while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}
void switch1_init(){
  
  GPIO_PORTF_LOCK_REG = 0x4C4F434B;     //For unlocking the GPIO LOCK register
  GPIO_PORTF_CR_REG |= (1<<0);          //Set comit register for enabling the GPIOAFSEL,GPIOPUR,GPIOPDR and GPIODEN
  GPIO_PORTF_AMSEL_REG &= ~(1<<0);      //Clearing the Analouge Mode SELect register to disable Analog on PF0
  GPIO_PORTF_PCTL_REG &= 0xFFFFFFF0;    //Clearing PCMx register for allowing pin PF0 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<0);      //Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_PUR_REG |= (1<<0);         //Set the pin PF0 to enable the pull up resistor config
  GPIO_PORTF_DIR_REG &= ~(1<<0);        //Clearing the pin PF0 to make it INPUT
  GPIO_PORTF_DEN_REG |= (1<<0);         //Set the pin PF0 to enable it
}
void switch2_init(){

  GPIO_PORTF_AMSEL_REG &= ~(1<<4);      //Clearing the Analouge Mode SELect register to disable Analog on PF4
  GPIO_PORTF_PCTL_REG &= 0xFFF0FFFF;    //Clearing PCMx register for allowing pin PF4 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<4);      //Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_PUR_REG |= (1<<4);         //Set the pin PF4 to enable the pull up resistor config
  GPIO_PORTF_DIR_REG &= ~(1<<4);        //Clearing the pin PF4 to make it INPUT
  GPIO_PORTF_DEN_REG |= (1<<4);         //Set the pin PF4 to enable it
}
void leds_init(){
  
  GPIO_PORTF_AMSEL_REG &= 0xF1;         //Clearing the Analouge Mode SELect register to disable Analog on PF1,2,3
  GPIO_PORTF_PCTL_REG &= 0xFFFF000F;    //Clearing PCMx register for allowing pins PF1,2,3 available for GPIO
  GPIO_PORTF_AFSEL_REG &= 0xF1;         //Clearing Alternative Function SELect register to use the pins for GPIO
  GPIO_PORTF_DIR_REG |= 0x0E;           //Clearing the pins PF1,2,3 to make it OUTPUT
  GPIO_PORTF_DEN_REG |= 0x0E;           //Set the pins PF1,2,3 to enable it
  GPIO_PORTF_DATA_REG &= 0xF1;          //Making sure that the leds are off at first LOW (Positive Logic)
}