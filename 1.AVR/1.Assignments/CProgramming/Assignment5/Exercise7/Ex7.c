#include <stdio.h>

enum Fan_level{
	Level_1=1,Level_2,Level_3
};


int main(){
	enum Fan_level fan = Level_1;
	printf("Welcome to Exercise 7 program\n");
	printf("Level1 = %d\n",fan);

	if(fan == Level_1){
		fan = Level_2;
	}

	printf("Level2 = %d\n",fan);

	if(fan == Level_2){
		fan = Level_3;
	}

	printf("Level3 = %d\n",fan);

	return 0;
}
