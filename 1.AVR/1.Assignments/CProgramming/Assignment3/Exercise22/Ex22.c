#include <stdio.h>

int removeDuplicates(int arr_old[], int n_old, int arr_new[], int*n_new);

int main(){

	int a[10] = {1,2,3,3,3,4,4,5,5,5};
	int b[10];
	int size = 0;
	int ret;
	ret = removeDuplicates(a,10,b,&size);
	for(int i=0;i<size;i++)
	{
		printf("%d,",b[i]);
	}
	printf("\n%d",ret);


	return 0;
}
int removeDuplicates(int arr_old[], int n_old, int arr_new[], int*n_new){
	if(n_old == 0){
		return 0;
	}else{
		/*
		int i =0;
		int dupp =0;
		*n_new = 0;
		arr_new[*n_new] = arr_old[i];
		(*n_new)++;
		for(i = 1;i<n_old-1;i++){
			for(int j = 0;j<i;j++){
				if(arr_new[j] == arr_old[i]){
					dupp = 1;
				}
			}
			if(dupp == 0){
				arr_new[*n_new] = arr_old[i];
				(*n_new)++;
				dupp = 0;
			}
		}
		*/
		int i =0;
		*n_new = 0;
		for(i = 0;i<n_old-1;i++){
			if(arr_old[i] != arr_old[i+1]){
				arr_new[*n_new] = arr_old[i];
				(*n_new)++;
			}
		}
		arr_new[*n_new] = arr_old[i];
		(*n_new)++;
		return 1;
	}
}
