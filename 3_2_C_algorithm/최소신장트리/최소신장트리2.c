#include <stdio.h>
#include <stdlib.h>

typedef struct Heap{
	int end;
	int *heap;
}Heap;

void downheap(Heap *h,int in){
	int l,r;
	int g;
	int tmp;

	l = in*2;
	r = in*2+3;

	if(l > h->end)
		return;

	g = l;

	if(r <= h->end){
		if(h->heap[r+2] < h->heap[g+2]){
			g = r;
		}
	}
	if(h->heap[in+2] <= h->heap[g+2])
		return;

	tmp = h->heap[in];
	h->heap[in] = h->heap[g];
	h->heap[g] = tmp;

	tmp = h->heap[in+1];
	h->heap[in+1] = h->heap[g+1];
	h->heap[g+1] = tmp;

	tmp = h->heap[in+2];
	h->heap[in+2] = h->heap[g+2];
	h->heap[g+2] = tmp;

	downheap(h,g);
}

void buildHeap(Heap *h){
	int i;

	int medium = ((h->end/3)/2)*3;

	for(i=medium;i>=3;i-=3)
		downheap(h,i);
}

int merge(int **f,int e1,int e2,int weight,int n){
	int i,j;
	int in1=0,in2=0;
	int a;

	for(i=0;i<n;i++){
		a=0;
		for(j=0;;j++){
			if(f[i][j] == 0)
				break;
			if(f[i][j] == e1 || f[i][j] == e2) // e1,e2��� ������ ������ a++
				a++;
		}

		if(a==2) // �� ���� �ȿ� e1,e2�� �ִ� ����̹Ƿ� return 0 => ������ ������ �� ����.
			return 0;
		else if(a==1){ // ���վȿ� e1,e2 �� �ϳ��� �ִ� ���
			if(in1 != 0){
				in2 = i;
			}
			else 
				in1 = i;
		}
	}

	// a==2(�� ���վȿ� e1,e2�� ���� ���� ���)�� �ƴϸ� ������ e1,e2�� ���� �ٸ� ���տ� �ִ� �׷��Ƿ� �պ������ �Ѵ�.

	for(i=0;;i++){
		if(f[in1][i] == 0)
			break;
	}  
	j=i;
	for(i=0;;i++){
		if(f[in2][i] == 0)
			break;
		f[in1][j+i] = f[in2][i];
		f[in2][i] = 0;
	}
	// index�� �տ� �ִ� ���տ� index�� �ڿ� �ִ� ������ �־��� & �ڿ� �ִ� ������ 0���� �ٲ���
	return 1; // ������ �����ߴٴ� �ǹ�
}

int main(){
	int n,m;
	int a,b,c;
	int i;
	Heap *h;
	int **f; // ����
	int totalweight = 0;
	int weight = 0;
	int edge = 0;
	int e1,e2;
	int possible = 0;
	int edgen = 0;
	int k;

	scanf("%d %d",&n,&m);

	f = (int**)malloc(sizeof(int*)*n);
	for(i=0;i<n;i++)
		f[i] = (int*)calloc(sizeof(int),n); // ������ ������ �迭

	h = (Heap*)malloc(sizeof(Heap));
	h->heap = (int*)malloc(sizeof(int)*(m+1)*3); // ���� ���� ���� �Ҵ�
	h->end = m*3; 

	for(i=1;i<=m;i++){
		scanf("%d %d %d",&a,&b,&c);
		h->heap[i*3] = a;
		h->heap[i*3+1] = b;
		h->heap[i*3+2] = c; // �Է¹��� ������ ���� ����
	}

	buildHeap(h); // ����� �� ����

	for(i=0;i<n;i++)
		f[i][0] = i+1;  // ���� �迭 �ʱ�ȭ

	while(1){
		if(edgen == n-1) // ���� ������ n-1�� ���õǾ��� �� ������
			break;

		e1 = h->heap[3];
		e2 = h->heap[4];
		weight = h->heap[5]; 

		h->heap[3] = h->heap[h->end];
		h->heap[4] = h->heap[h->end+1];
		h->heap[5] = h->heap[h->end+2]; // ���� ���� �ִ� ���� �ΰ� & ����ġ �� ����

		h->end -= 3;

		downheap(h,3); // �� ����

		possible = merge(f,e1,e2,weight,n); // e1�̶�� ������ e2��� ������ �ִ� ������ �պ�(possible = 1) or ���� ������ ��� �н�(possible = 0)

		if(possible == 1){
			printf(" %d",weight); // MST ���� ���� ���
			totalweight += weight;
			edgen++; // ���õ� ���� ����
		} // ������ �պ����� ���� ���� ��� �� ��ü ���Կ� ������
	}

	printf("\n%d",totalweight); // MST �ѹ��� ���

	free(h->heap);
	free(h);
	for(i=0;i<n;i++)
		free(f[i]);
	free(f); // �޸� ����
}