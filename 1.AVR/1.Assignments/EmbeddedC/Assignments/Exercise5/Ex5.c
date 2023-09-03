#include <stdio.h>

int RisingEdgeCounter(int);

int main(){

	int count =0;
	count = RisingEdgeCounter(1);
	count = RisingEdgeCounter(1);
	count = RisingEdgeCounter(0);
	count = RisingEdgeCounter(1);
	count = RisingEdgeCounter(0);
	count = RisingEdgeCounter(1);
	count = RisingEdgeCounter(1);
	count = RisingEdgeCounter(1);
	count = RisingEdgeCounter(0);
	count = RisingEdgeCounter(0);
	count = RisingEdgeCounter(1);
	count = RisingEdgeCounter(0);
	printf("Count = %d\n",count);

	return 0;
}
int RisingEdgeCounter(int pinStatus){
	static int count = 0;
	static int previousStatus = 0;
	if(pinStatus == 1 && previousStatus == 0){
		count++;
	}
	previousStatus = pinStatus;
	return count;

}
