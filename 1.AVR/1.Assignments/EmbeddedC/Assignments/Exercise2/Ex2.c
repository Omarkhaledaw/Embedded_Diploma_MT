#include <stdio.h>

#define GET_BIT(REG,BIT) (((REG)&(1<<BIT))>>BIT)
#define GET_SUM(a,size,sum) \
{ \
	for(int i = 0;i<size;i++){ \
	sum+=a[i]; \
	} \
}
int main(){
	int sum = 0;
	int array[5]={1,2,3,4,5};

	GET_SUM(array,5,sum);
	printf("Sum = %d",sum);

	return 0;
}
