#include <stdio.h>
#include <stdlib.h>

int main(){
	int i,j,N,max,maxin;
	int *a;

	scanf("%d",&N);
	a = (int*)malloc(sizeof(int)*N);

	for(i=0;i<N;i++){
		scanf("%d",a+i);
	}

	for(i=0;i<N;i++){
		max = *(a);
		maxin = 0;
		for(j=0;j<N-i;j++){
			if(max<*(a+j)){
				max = *(a+j);
				maxin = j;
			}
		}
		*(a+maxin) = *(a+j-1);
		*(a+j-1) = max;
	}

	for(i=0;i<N;i++){
		printf(" %d",*(a+i));
	}

	free(a);
}
