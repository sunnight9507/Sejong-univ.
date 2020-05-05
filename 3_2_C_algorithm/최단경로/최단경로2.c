#include <stdio.h>
#include <stdlib.h>

#define M 10000

typedef struct Heap{
	int *heap;
	int end;
}Heap;

int popheap(Heap *H){
	int e;
	int i;

	e = H->heap[0];

	for(i=0;i<H->end-1;i++){
		H->heap[i] = H->heap[i+1];
	}

	H->end--;
	H->heap[H->end] = 0;

	return e;
}

void putheap(Heap *H,int i){

	H->heap[H->end] = i;
	H->end++;

}

void findedge(int **G,Heap *H,int n,int s){
	int i;
	int e;

	e = popheap(H);

	for(i=1;i<=n;i++){
		if(G[e][i] != 0 && i != s){
			if((G[0][e] + G[e][i]) < G[0][i]){
				G[0][i] = G[0][e] + G[e][i];
				putheap(H,i);
				G[i][0] = 1;
			}
			else{
				if(G[i][0] == 0){
					putheap(H,i);
					G[i][0] = 1;
				}
			}
		}
	}
}

int main(){
	int n,m,s;
	int a,b,c;
	int **G;
	Heap *H; // heap
	int i;

	scanf("%d %d %d",&n,&m,&s);

	G = (int**)malloc(sizeof(int*)*(n+1));
	for(i=0;i<=n;i++)
		G[i] = (int*)calloc(sizeof(int),(n+1));

	for(i=1;i<=n;i++)
		G[0][i] = M;

	for(i=0;i<m;i++){
		scanf("%d %d %d",&a,&b,&c);
		G[a][b] = c;
	}

	H = (Heap*)malloc(sizeof(Heap));
	H->heap = (int*)calloc(sizeof(int),n);

	H->heap[0] = s;
	H->end = 1;
	G[0][s] = 0;

	while(1){
		if(H->heap[0] == 0)
			break;

		findedge(G,H,n,s);

	}

	for(i=1;i<=n;i++){
		if(G[0][i]!=M && i!=s)
			printf("%d %d\n",i,G[0][i]);
	}
		
}