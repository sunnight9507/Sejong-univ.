#include <stdio.h>
#include <stdlib.h>

int main(){
	int i,j,N,k;
	int *a;

	scanf("%d",&N);
	a = (int*)malloc(sizeof(int)*N);

	for(i=0;i<N;i++){
		scanf("%d",a+i);
	}

	for(i=1;i<N;i++){
		k = *(a+i);
		for(j=i-1;j>=0;j--){
			if(k<*(a+j)){
				*(a+j+1) = *(a+j);
				if(j==0){
					*(a+j) = k;
				}
			}else{
				*(a+j+1) = k;
				break;
			}
		}
	}

	for(k=0;k<N;k++){
		printf(" %d",*(a+k));
	}

	free(a);
}
