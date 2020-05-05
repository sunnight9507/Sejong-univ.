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
			if(f[i][j] == e1 || f[i][j] == e2) // e1,e2라는 정점이 있으면 a++
				a++;
		}

		if(a==2) // 한 집합 안에 e1,e2가 있는 경우이므로 return 0 => 간선을 선택할 수 없다.
			return 0;
		else if(a==1){ // 집합안에 e1,e2 중 하나만 있는 경우
			if(in1 != 0){
				in2 = i;
			}
			else 
				in1 = i;
		}
	}

	// a==2(한 집합안에 e1,e2가 같이 있을 경우)가 아니면 무조건 e1,e2는 서로 다른 집합에 있다 그러므로 합병해줘야 한다.

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
	// index가 앞에 있는 집합에 index가 뒤에 있는 집합을 넣어줌 & 뒤에 있는 집합은 0으로 바꿔줌
	return 1; // 간선을 선택했다는 의미
}

int main(){
	int n,m;
	int a,b,c;
	int i;
	Heap *h;
	int **f; // 집합
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
		f[i] = (int*)calloc(sizeof(int),n); // 집합을 저장할 배열

	h = (Heap*)malloc(sizeof(Heap));
	h->heap = (int*)malloc(sizeof(int)*(m+1)*3); // 힙을 만들 공간 할당
	h->end = m*3; 

	for(i=1;i<=m;i++){
		scanf("%d %d %d",&a,&b,&c);
		h->heap[i*3] = a;
		h->heap[i*3+1] = b;
		h->heap[i*3+2] = c; // 입력받을 때마다 힙에 저장
	}

	buildHeap(h); // 상향식 힙 생성

	for(i=0;i<n;i++)
		f[i][0] = i+1;  // 집합 배열 초기화

	while(1){
		if(edgen == n-1) // 간선 개수가 n-1개 선택되었을 때 나가기
			break;

		e1 = h->heap[3];
		e2 = h->heap[4];
		weight = h->heap[5]; 

		h->heap[3] = h->heap[h->end];
		h->heap[4] = h->heap[h->end+1];
		h->heap[5] = h->heap[h->end+2]; // 가장 위에 있는 정점 두개 & 가중치 값 제거

		h->end -= 3;

		downheap(h,3); // 힙 정렬

		possible = merge(f,e1,e2,weight,n); // e1이라는 정점과 e2라는 정점이 있는 집합을 합병(possible = 1) or 같은 집합일 경우 패스(possible = 0)

		if(possible == 1){
			printf(" %d",weight); // MST 간선 무게 출력
			totalweight += weight;
			edgen++; // 선택된 간선 개수
		} // 집합을 합병했을 때만 무게 출력 후 전체 무게에 더해줌
	}

	printf("\n%d",totalweight); // MST 총무게 출력

	free(h->heap);
	free(h);
	for(i=0;i<n;i++)
		free(f[i]);
	free(f); // 메모리 해제
}