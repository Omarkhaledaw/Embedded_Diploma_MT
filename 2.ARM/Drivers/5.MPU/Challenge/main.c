#include "tm4c123gh6pm_registers.h"

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

/* Data memory barrier instruction */
#define DMB()                  __asm("DMB")

/* Data synchronization barrier instruction */
#define DSB()                  __asm("DSB")

/* Instruction synchronization barrier instruction */
#define ISB()                  __asm("ISB")

/*Global variables*/
volatile unsigned char count = 0;

/*ISR*/
void SysTick_Handler(){
  count++;
  if(count == 5){
    GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08;  //Red led on only
  }else if(count == 10){
    GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04;  //Blue led on only
  }else if(count == 15){
    GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02;  //Green led on only
    count = 0;
  }
}

/*Functions prototype*/
void led_init();
void systick_init();
void mpu_init();
void memoryMangementFault_init();

int main(){
  
  /*SETUP LOOP*/
  Enable_Exceptions();//Enable Exceptions
  Enable_Faults();//Enable Faults
  mpu_init();
  // Enable clock for PORTF and allow time for clock to start 
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= 0x00000020; //Convert 100000 to hexa also set the clock of PORTF
  delay = SYSCTL_REGCGC2_REG;
  
  led_init();
  systick_init();
  

  /*MAIN LOOP*/
  while(1){
    
    Wait_For_Interrupt(); //Go to low power mode while waiting for the next interrupt
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
  SYSTICK_RELOAD_REG = 15999999; //Set the RELOAD value in the reload register
  SYSTICK_CURRENT_REG = 0;      //Clearing the counter CURRENT register 
  SYSTICK_CTRL_REG |= 0x07;     //Set the ConTRol register in order to use the system clock and enable the timer again
  NVIC_SYSTEM_PRI3_REG = ((NVIC_SYSTEM_PRI3_REG & 0x1FFFFFFF)|(2<<29))
}
void memoryMangementFault_init(){
  NVIC_SYSTEM_PRI1_REG = ((NVIC_SYSTEM_PRI1_REG & 0xFFFFFF1F) | (3<<5));// Masking the priority register before asigning priority level 3 for memory mangement fault
  NVIC_SYSTEM_SYSHNDCTRL |= (1<<16);// Enabling the Memory mangement fault
}
void mpu_init(){
  
  memoryMangementFault_init();
  /*Check if there's a MPU before anything else*/
  if(MPU_TYPE_REG==0){
    return;
  }
  DMB(); //Ensures all memory accesses are finished before a fresh memory access is made
  MPU_CTRL_REG = 0; //Disable MPU before starting
  /*Region 0*/
  MPU_NUMBER_REG = 0;
  MPU_BASE_REG = 0x00000000;
  MPU_ATTR_REG = (0x11<<1) | (0x00000001) | (0x00020000) | (0x03<<24);
  /*Region 1*/
  MPU_BASE_REG = 0x20000000 | 0x00000010 | 1;
  MPU_ATTR_REG = (0x0E<<1) | (0x00000001) |(0x00020000) | (0x03<<24);
  /*Region 2*/
  MPU_BASE_REG = 0x40025000 | 0x00000010 | 2;
  MPU_ATTR_REG = (0x0B<<1) | (0x00000001) | (0x00020000) | (0x03<<24);
  /*Region 3*/
  MPU_BASE_REG = 0x400FE000 | 0x00000010 | 3;
  MPU_ATTR_REG = (0x0B<<1) | (0x00000001) | (0x00050000) | (0x03<<24);
  
  MPU_CTRL_REG = 0x00000001; //Enabling the mpu
  DSB(); //Ensures all memory accesses are finished before the next instruction is executed
  
  ISB(); //Ensures that all previous instructions are completed before the next instruction is executed. This also flushes the CPU pipeline
}