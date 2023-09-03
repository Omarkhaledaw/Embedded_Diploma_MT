#include "oadc.h" /*including the ADC header file*/
#include "odcm.h" /*including the DC Motor header file*/
#include "ogpio.h" /*including the GPIO header file*/
#include "olcd.h" /*including the LCD header file*/
#include "olm35.h" /*including the LM35 sensor header file*/
#include "opwm.h" /*including the PWM header file*/

int main(){
	/*Initializing the variable used for storing temperature value*/
	uint8 temp =0;
	/*Configuring ADC to work with internal V reference (2.56) and prescaler of 8*/
	ADC_ConfigType Configuration={INERNAL_vref,F_CPU_CLOCK_8};
	ADC_initial(&Configuration);
	/*Configuring LCD*/
	LCD_initial();
	/*Configuring DC Motor*/
	DcMotor_Init();
	/*Displaying FAN and Temperature strings that doesn't change*/
	LCD_stringRowColumn(0,2,"FAN is    ");
	LCD_stringRowColumn(1,2,"Temp =     C");

	while(1){
		/*Storing temperature value in temp using LM35_getTemp function*/
		temp = LM35_getTemp(2);
		/*Displaying the temperature variable*/
		LCD_move(1,9);
		LCD_integer2String(temp);
		/*If statement for the Fan state and speed*/
		if(temp < 30){
			/*Displaying OFF state when temperature less than 30 c*/
			LCD_stringRowColumn(0,9,"OFF");
			DcMotor_Rotate(Stop,0);

		}else {
			/*Displaying ON state when temperature greater than 30 c*/
			LCD_stringRowColumn(0,9,"ON ");

			if (temp < 60 && temp >= 30 ){
				/*Rotating fan with 25% in case 30 <= temperature < 60*/
				DcMotor_Rotate(Clockwise,25);
			}else if (temp < 90 && temp >= 60){
				/*Rotating fan with 50% in case 60 <= temperature < 90*/
				DcMotor_Rotate(Clockwise,50);
			}else if (temp < 120 && temp >=90){
				/*Rotating fan with 75% in case 90 <= temperature < 120*/
				DcMotor_Rotate(Clockwise,75);
			}else{
				/*Rotating fan with 100% in case 120 <= temperature */
				DcMotor_Rotate(Clockwise,100);
			}
		}

	}
}
