#include <stdio.h>

struct distance{
	int foot;
	int inch;

}dis1,dis2,sum;

int main(){

	printf("Welcome to Exercise 2 program, please enter the first and second distance\n1st distance\nFeet: ");
	fflush(stdout);
	scanf("%d",&dis1.foot);
	printf("Inch: ");
	fflush(stdout);
	scanf("%d",&dis1.inch);

	printf("Great, now enter the second distance\nFoot: ");
	fflush(stdout);
	scanf("%d",&dis2.foot);
	printf("Inch: ");
	fflush(stdout);
	scanf("%d",&dis2.inch);

	sum.foot = dis1.foot+dis2.foot;
	sum.inch = dis1.inch+dis2.inch;
	while(sum.inch>12){
		sum.foot++;
		sum.inch-=12;
	}
	printf("Calculating...\nTotal foot = %d\nTotal inches = %d",sum.foot,sum.inch);

	return 0;
}
