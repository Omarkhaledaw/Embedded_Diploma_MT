#include <stdio.h>


int main(){
	char ch = 0;
	for(int i = 0;i<120;i++){
		if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
			printf("%c",ch);
		}
		ch+=1;
	}
	return 0;
}
