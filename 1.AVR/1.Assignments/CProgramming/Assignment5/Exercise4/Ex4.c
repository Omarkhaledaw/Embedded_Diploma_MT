#include <stdio.h>

struct Time{
	int hour;
	int minute;
	int second;
}start,end,diff;

void timeDifference(struct Time,struct Time);


int main(){

	printf("Welcome to Exercise 4 program\nplease enter the start time separated by space h/m/s: ");
	fflush(stdout);
	scanf("%d %d %d",&start.hour,&start.minute,&start.second);
	printf("Great, now enter the end time h/m/s: ");
	fflush(stdout);
	scanf("%d %d %d",&end.hour,&end.minute,&end.second);
	timeDifference(start,end);
	printf("Calculating...\n%d hours\n%d minutes\n%d seconds",diff.hour,diff.minute,diff.second);
	return 0;
}
void timeDifference(struct Time num1,struct Time num2){
	diff.hour = start.hour - end.hour;
	diff.minute = start.minute - end.minute;
	diff.second = start.second - end.second;
}
