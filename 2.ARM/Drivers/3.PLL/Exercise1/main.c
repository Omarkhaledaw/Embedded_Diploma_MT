#include "tm4c123gh6pm_registers.h"

/*Functions prototype*/
void led_init();
void pll_init();
void systick_init();

int main(){
  
  /*SETUP LOOP*/
  // Enable clock for PORTF and allow time for clock to start 
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= 0x00000020;
  delay = SYSCTL_REGCGC2_REG;
  
  led_init();
  pll_init();
  systick_init();
  
  /*LOOP*/
  while(1){
    GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08;  //Red led on only
    while(!(SYSTICK_CTRL_REG & (1<<16)));                       //This counter bit in the control register will be cleared when it reaches the reload value
    GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04;  //Blue led on only
    while(!(SYSTICK_CTRL_REG & (1<<16)));                       //This counter bit in the control register will be cleared when it reaches the reload value
    GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02;  //Green led on only
    while(!(SYSTICK_CTRL_REG & (1<<16)));                       //This counter bit in the control register will be cleared when it reaches the reload value
  }
}
/*Functions*/
void led_init(){

  GPIO_PORTF_AMSEL_REG &= 0xF1;         //Clearing the Analouge Mode SELect register to disable Analog on PF1,2,3
  GPIO_PORTF_PCTL_REG &= 0xFFFF000F;    //Clearing PCMx register for allowing pins PF1,2,3 available for GPIO
  GPIO_PORTF_AFSEL_REG &= 0xF1;         //Clearing Alternative Function SELect register to use the pins for GPIO
  GPIO_PORTF_DIR_REG |= 0x0E;           //Clearing the pins PF1,2,3 to make it OUTPUT
  GPIO_PORTF_DEN_REG |= 0x0E;           //Set the pins PF1,2,3 to enable it
  GPIO_PORTF_DATA_REG &= 0xF1;          //Making sure that the leds are off at first LOW (Positive Logic)
}
void systick_init(){

  SYSTICK_CTRL_REG = 0;         //Clearing the ALL of the ConTRoL register to turn of the systick timer at initialization 
  SYSTICK_RELOAD_REG = 79999999; //Set the RELOAD value in the reload register
  SYSTICK_CURRENT_REG = 0;      //Clearing the counter CURRENT register 
  SYSTICK_CTRL_REG &= 0x05;     //Set the ConTRol register in order to use the system clock and enable the timer again
}
void pll_init(){

  SYSCTL_RCC2_REG |= 0x80000000;//Enable the RCC2 register over the RCC register
  SYSCTL_RCC2_REG |= 0x00000800;//Set the bypass bit
  
  SYSCTL_RCC_REG &= ~0x000007C0;//Clearing the XTAL bits before use
  SYSCTL_RCC_REG |= 0x00000540;//Specifing the value of crystal attached to the main oscillator

  SYSCTL_RCC2_REG &= ~0x00000070;//Clearing the OSCSRC2 bits before use
  SYSCTL_RCC2_REG |= 0x00000000;//Selecting the input source for oscillation which in this case the main oscillator
  
  SYSCTL_RCC2_REG &= ~0x00002000;//Clearing the PWRDN2 bit to activate the PLL
  
  SYSCTL_RCC2_REG |= 0x40000000;//Set the DIV400 to enable the SYSDIV2LIB for the SYSDIV2
  SYSCTL_RCC2_REG = ((SYSCTL_RCC2_REG & ~0x1FC00000)|(4<<22));//Clear the SYSDIV2 before adding the divider value to it
  
  while(!(SYSCTL_RIS_REG & 0x00000040));//Wait until the PLL reaches T_READY
  
  SYSCTL_RCC2_REG &= ~0x00000800;//Clear the bypass bit
}