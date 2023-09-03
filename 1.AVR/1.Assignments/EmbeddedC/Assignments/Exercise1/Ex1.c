#include <stdio.h>

#define GET_BIT(REG,BIT) (((REG)&(1<<BIT))>>BIT)

int main(){
	unsigned char var1 = 0x0F;
	printf("The value of bit number 0 is %d\n",GET_BIT(var1,0));

	printf("The value of bit number 4 is %d",GET_BIT(var1,4));

	return 0;
}
