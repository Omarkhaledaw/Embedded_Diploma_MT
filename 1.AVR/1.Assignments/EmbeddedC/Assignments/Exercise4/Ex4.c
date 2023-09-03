#include <stdio.h>

int FallingEdgeCounter(int);

int main(){

	int count =0;
	count = FallingEdgeCounter(1);
	count = FallingEdgeCounter(1);
	count = FallingEdgeCounter(0);
	count = FallingEdgeCounter(1);
	count = FallingEdgeCounter(0);
	count = FallingEdgeCounter(1);
	count = FallingEdgeCounter(1);
	count = FallingEdgeCounter(1);
	count = FallingEdgeCounter(0);
	count = FallingEdgeCounter(0);
	count = FallingEdgeCounter(1);
	count = FallingEdgeCounter(0);
	printf("Count = %d\n",count);

	return 0;
}
int FallingEdgeCounter(int pinStatus){
	static int count = 0;
	static int previousStatus = 0;
	if(pinStatus == 0 && previousStatus == 1){
		count++;
	}
	previousStatus = pinStatus;
	return count;

}
