#include "tm4c123gh6pm_registers.h"

/*DEFINE*/
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762

/*Function Prototype*/
void switch_init();
void led_init();
void Delay_MS(unsigned long long n);


int main(){
  
  /*SETUP MODE*/
  unsigned char flag = 0;
  // Enable clock for PORTF and allow time for clock to start 
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= 0x00000020;
  delay = SYSCTL_REGCGC2_REG;
  
  /*LOOP MODE*/
  /*The basic idea is that every time the switch is pressed the LED either ON or OFF so in order to do that we*/
  while(1){
    
    if(!(GPIO_PORTF_DATA_REG & (1<<4))){
      
      Delay_MS(10); //Using delay to prevent debounce
      if(!(GPIO_PORTF_DATA_REG & (1<<4))){
        
        if(flag == 0){
          
          GPIO_PORTF_DATA_REG |= (1<<2); //LED ON
          flag = 1;
        }
      }
    }else{
      
      flag = 0;
    }
  }
}

/*Functions*/
void Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}
void switch_init(){
  GPIO_PORTF_AMSEL_REG &= ~(1<<4);      //Clearing the Analouge Mode SELect register to disable Analog on PF4
  GPIO_PORTF_PCTL_REG &= 0xFFF0FFFF;    //Clearing PCMx register for allowing pin PF4 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<4);      //Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_DIR_REG &= ~(1<<4);        //Clearing the pin PF4 to make it INPUT
  GPIO_PORTF_PUR_REG |= (1<<4);         //Set the pin PF4 to enable the pull up resistor config
  GPIO_PORTF_DEN_REG |= (1<<4);         //Set the pin PF4 to enable it
}
void led_init(){
  GPIO_PORTF_AMSEL_REG &= ~(1<<2);      //Clearing the Analouge Mode SELect register to disable Analog on PF2
  GPIO_PORTF_PCTL_REG &= 0xFFFFF0FF;    //Clearing PCMx register for allowing pin PF2 available for GPIO
  GPIO_PORTF_AFSEL_REG &= ~(1<<2);      //Clearing Alternative Function SELect register to use the pin for GPIO
  GPIO_PORTF_DIR_REG |= (1<<2);         //Clearing the pin PF2 to make it OUTPUT
  GPIO_PORTF_DEN_REG |= (1<<2);         //Set the pin PF2 to enable it
  GPIO_PORTF_DATA_REG &= ~(1<<2);       //Making sure that the led is off at first LOW (Positive Logic)
}