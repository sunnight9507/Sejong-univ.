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
	h->heap[p] = tmp; // ���� ��ġ �ٲٱ�
		
	tmp = h->heap[in+1];
	h->heap[in+1] = h->heap[p+1];
	h->heap[p+1] = tmp; // ����ġ �� �ٲٱ�

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
	int **g; // �׷���
	int *edge; // MST ������ �߰��Ǵ� ������ �����ϴ� �迭
	int a,b,c; // ����,����,����ġ �Է�
	Heap *h; // ����,����ġ ������ ��
	int edgemin = 1; // ó�� ���� ������ �׻� 1
	int totalweight = 0; // ����ġ ��
	int weight = 0;
	int n,m;
	int i,j;

	scanf("%d %d",&n,&m);

	g = (int**)malloc(sizeof(int*)*(n+1));

	for(i=1;i<=n;i++)
		g[i] = (int*)calloc(sizeof(int),(n+1));

	for(i=0;i<m;i++){
		scanf("%d %d %d",&a,&b,&c);
		insert(g,a,b,c);// �׷��� �迭�� ����
	}

	h = (Heap*)malloc(sizeof(Heap));
	h->heap = (int*)malloc(sizeof(int)*(n*(n+1))); // ������ �ִ� ����
	h->end = 2; // �ʱⰪ�� 2 (2���� �ֱ� ����)

	edge = (int*)malloc(sizeof(int)*n);

	edge[0] = edgemin; // 1���� ����

	for(i=0;i<n;i++){
		if(g[edgemin][0] == 0){  // edgemin�̶�� ������ edge�迭�� ����Ǿ� ���� �ʴ� ���
			totalweight += weight;
			g[edgemin][0] = 1;
			edge[i] = edgemin;
		}
		else{ // ����Ǿ� �ִ� ���
			i--;
		}

		if(i==n-1)
			break; 
 
		for(j=1;j<=n;j++){
			if((g[edgemin][j] != 0) && (g[j][0] == 0)){
				heap_insert(h,j,g[edgemin][j]); // ���� ���� (����,����ġ)
			}
		}
		edgemin = h->heap[2]; // ���� ���� �ִ� ���� ����
		weight = h->heap[3]; // ���� ���� �ִ� ����ġ �� ����
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
	// �޸� ����
}