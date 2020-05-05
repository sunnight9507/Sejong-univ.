#include <stdio.h>
#include <stdlib.h>

typedef struct Heap{
	int end;
	int *heap;
}Heap;

void insert(int **g,int a,int b,int c){
	g[a][b] = c;
	g[b][a] = c;
}

void upheap(Heap *h,int in){
	int tmp;
	int p = in/2-(in/2)%2;

	if(in == 2)
		return;

	if(h->heap[in+1] >= h->heap[p+1])
		return;

	tmp = h->heap[in];
	h->heap[in] = h->heap[p];
	h->heap[p] = tmp; // 정점 위치 바꾸기
		
	tmp = h->heap[in+1];
	h->heap[in+1] = h->heap[p+1];
	h->heap[p+1] = tmp; // 가중치 값 바꾸기

	upheap(h,p);
}

void downheap(Heap *h,int in){
	int l,r;
	int g;
	int tmp;

	l = in*2;
	r = in*2+2;

	if(l > h->end)
		return;

	g = l;

	if(r <= h->end){
		if(h->heap[r+1] < h->heap[g+1]){
			g = r;
		}
	}
	if(h->heap[in+1] <= h->heap[g+1])
		return;

	tmp = h->heap[in];
	h->heap[in] = h->heap[g];
	h->heap[g] = tmp;

	tmp = h->heap[in+1];
	h->heap[in+1] = h->heap[g+1];
	h->heap[g+1] = tmp;

	downheap(h,g);
}

void heap_insert(Heap *h,int i,int weight){
	h->heap[h->end] = i;
	h->heap[h->end+1] = weight;

	upheap(h,h->end);

	h->end += 2;
}

int main(){
	int **g; // 그래프
	int *edge; // MST 생성시 추가되는 정점을 저장하는 배열
	int a,b,c; // 정점,정점,가중치 입력
	Heap *h; // 정점,가중치 저장할 힙
	int edgemin = 1; // 처음 넣을 정점은 항상 1
	int totalweight = 0; // 가중치 합
	int weight = 0;
	int n,m;
	int i,j;

	scanf("%d %d",&n,&m);

	g = (int**)malloc(sizeof(int*)*(n+1));

	for(i=1;i<=n;i++)
		g[i] = (int*)calloc(sizeof(int),(n+1));

	for(i=0;i<m;i++){
		scanf("%d %d %d",&a,&b,&c);
		insert(g,a,b,c);// 그래프 배열에 삽입
	}

	h = (Heap*)malloc(sizeof(Heap));
	h->heap = (int*)malloc(sizeof(int)*(n*(n+1))); // 간선의 최대 개수
	h->end = 2; // 초기값은 2 (2개씩 넣기 때문)

	edge = (int*)malloc(sizeof(int)*n);

	edge[0] = edgemin; // 1부터 시작

	for(i=0;i<n;i++){
		if(g[edgemin][0] == 0){  // edgemin이라는 정점이 edge배열에 저장되어 있지 않는 경우
			totalweight += weight;
			g[edgemin][0] = 1;
			edge[i] = edgemin;
		}
		else{ // 저장되어 있는 경우
			i--;
		}

		if(i==n-1)
			break; 
 
		for(j=1;j<=n;j++){
			if((g[edgemin][j] != 0) && (g[j][0] == 0)){
				heap_insert(h,j,g[edgemin][j]); // 힙에 삽입 (정점,가중치)
			}
		}
		edgemin = h->heap[2]; // 가장 위에 있는 정점 제거
		weight = h->heap[3]; // 가장 위에 있는 가중치 값 제거
		h->heap[2] = h->heap[h->end-2];
		h->heap[3] = h->heap[h->end-1];
		h->end -= 2;
		downheap(h,2); // downheap 
	}

	for(i=0;i<n;i++)
		printf(" %d",edge[i]);

	printf("\n%d",totalweight);

	
	free(edge);
	free(h->heap);
	free(h);
	for(i=1;i<=n;i++)
		free(g[i]);
	free(g);
	// 메모리 해제
}