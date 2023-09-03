#include "oultrasonic.h"
#include "ogpio.h"
#include "oicu.h"
#include <avr/io.h>
#include <util/delay.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static uint8 g_edgeCount = 0;
static uint16 g_hightime = 0;

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/*
 * Description: function responsible for initialization of ultrasonic
 * 1-initialize ICU
 * 2-Setup the ICU call back function.
 * 3-Setup the direction for the trigger pin as output pin through the GPIO driver
 */
void Ultrasonic_init(){
	/*Initializing the trigger pin as output*/
	GPIO_setupPin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,PIN_OUTPUT);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOW);
	/*  initialize the ICU */
	ICU_Config Configuration = {F_CPU_8,RISING};
	ICU_initial(&Configuration);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
}
/*
 * Description : function responsible for Send the Trigger pulse to the ultrasonic
 */
void Ultrasonic_Trigger(){

	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,HIGH);
	_delay_ms(10);/*Making sure that Trigger signal is long enough to enable the echo pin */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOW);
}
/*
 * Function description: function responsible for reading distance using ultrasonic
 *  1- send the trigger pulse by using Ultrasonic_Trigger function.so ultrasonic start to produce echo pulse
 *	2- Start the measurements by the ICU from this moment.
 *
 *	Return: The measured distance in Centimeter
 */
uint16 Ultrasonic_readDistance(){
	uint16 timerValue = 0;
	uint16 distance = 0;

	Ultrasonic_Trigger();
	/*
		 * sound speed in air:
		 * 						 = 340 m/s = 340*100 cm/s = 34000 cm/s
		 * total distance:
		 * 						 = speed * time
		 * distance:
		 * 						 = total distance /2 = 34000 * time/2
		 *
		 * Total distance is divided by 2 because signal travels from HC-SR04 to object and returns to the module HC-SR-04.
		 *
		 * We have selected an internal 8MHz oscillator frequency for ATmega16, with Prescaler F_CPU/8 for timer frequency.
		 * Then time to execute 1 instruction is 1 us.So, the timer gets incremented after 1 us time elapse
		 * distance:
		 *					= 17000 x (TIMER value) x 1 x 10^-6 cm
		 *					= 0.017 x (TIMER value) cm
		 *					= (TIMER value) / 58.8 cm or (TIMER value) * 0.017 cm
	*/
	timerValue = ICU_getInputCaptureValue();
	distance =(float32)((SPEED_OF_SOUND*timerValue)/(2.0));

	return distance;
}
/*
 * Function description:
 * This is the call back function called by the ICU driver,
 * we initialize the call back in Ultrasonic_init()
 * the function used to calculate the high time (pulse time) generated by the ultrasonic sensor
 * */
void Ultrasonic_edgeProcessing(){
	g_edgeCount++;
	if(g_edgeCount == 1){

		ICU_clearTimerValue();/*Clear the timer counter register to start measurements from the first detected rising edge*/
		ICU_setEdgeDetection(FALLING);/* Detect falling edge */
	}else if(g_edgeCount == 2){
		g_edgeCount = 0;
		g_hightime = ICU_getInputCaptureValue();/* Store the High time value */
		ICU_clearTimerValue();/* Clearing Timer value */
		ICU_setEdgeDetection(RISING);/* Detect rising edge */
	}

}