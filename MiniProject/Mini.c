#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0

void systemState(int,int,int,int,int,int);

int main(){

	char input;
	char input2;
	char trafficData;
	int state = TRUE;
	int state2 = TRUE;
	int engine=OFF;
	int ac=OFF;
	int vehicleSpeed;
	int roomTemp=35;
	int engineTempC=OFF;
	int engineTemp=100;

	while(state != FALSE){
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n\n");
		fflush(stdout);
		scanf(" %c",&input);

		if(input=='a'){
			engine =ON;
			while(state2 != FALSE){
				printf("a. Turn off engine\n");
				printf("b. Set the traffic light color\n");
				printf("c. Set the room temperature\n");
				printf("d. Set the engine temperature\n");
				fflush(stdout);
				scanf(" %c",&input2);

				if(input2=='a' || input2=='A'){
					printf("Turning off the engine\n");
					engine=OFF;
					ac=OFF;
					vehicleSpeed=0;
					roomTemp=35;
					engineTempC=OFF;
					engineTemp=100;
					state2=FALSE;

				}
				else if(input2=='b' || input2=='B'){
					printf("Please enter the required color: ");
					fflush(stdout);
					scanf(" %c",&trafficData);
					if(trafficData=='g' || trafficData=='G'){
						vehicleSpeed=100;
						systemState(engine,ac,vehicleSpeed,roomTemp,engineTempC,engineTemp);
					}else if(trafficData=='o' || trafficData=='O'){
						vehicleSpeed=30;
						systemState(engine,ac,vehicleSpeed,roomTemp,engineTempC,engineTemp);
					}else if(trafficData=='r' || trafficData=='R'){
						vehicleSpeed=0;
						systemState(engine,ac,vehicleSpeed,roomTemp,engineTempC,engineTemp);
					}
				}else if(input2=='c' || input2=='C'){
					printf("Please enter the required temperature: ");
					fflush(stdout);
					scanf(" %d",&roomTemp);
					if(roomTemp<=10){
						ac=ON;
						roomTemp=20;
					}else if (roomTemp>30){
						ac=ON;
						roomTemp=20;
					}else{
						ac=OFF;
					}
					systemState(engine,ac,vehicleSpeed,roomTemp,engineTempC,engineTemp);
				}else if(input2=='d' || input2=='D'){
					printf("Please enter the required engine temperature: ");
					fflush(stdout);
					scanf(" %d",&engineTemp);
					if(engineTemp<100){
						engineTempC=ON;
						engineTemp=125;
					}else if(engineTemp>150){
						engineTempC=ON;
						engineTemp=125;
					}else{
						engineTempC=OFF;
					}
					systemState(engine,ac,vehicleSpeed,roomTemp,engineTempC,engineTemp);
				}
			}

		}
		if(input=='b'){
			printf("Turning off the vehicle engine\n\n");

		}
		if(input=='c'){
			printf("Quitting the system, have a nice day.");
			state=FALSE;
		}
		if(vehicleSpeed==30){
			ac=ON;
			roomTemp=(roomTemp*(5/4))+1;
			engineTempC=ON;
			engineTemp=(engineTemp*(5/4))+1;
		}

	}
	return 0;
}
void systemState(int engine,int ac,int vspeed,int rTemp,int eTempC,int eTemp){
	printf("Engine is %d\n",engine);
	printf("AC is %d\n",ac);
	printf("Vehicle speed is %d\n",vspeed);
	printf("Room Temperature is %d\n",rTemp);
	printf("Engine temperature controller is %d\n",eTempC);
	printf("Engine temperature is %d\n\n",eTemp);
}
