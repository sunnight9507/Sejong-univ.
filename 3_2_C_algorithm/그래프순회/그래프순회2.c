#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int edgesize;
	int visit;
}Node;

typedef struct Que{
	int *q;
	int last;
	int count;
}Que;

Node * newnode(){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->edgesize = 0;
	temp->visit = 0;
	return temp;
}

void insert(Node ***g,int a,int b){

	g[a][b]->edgesize = 1;
	g[b][a]->edgesize = 1;
	// a������ ����Ʈ���� b������ ���� ��� ����
	// b������ ����Ʈ���� a������ ���� ��� ����
}

void putnode(Node ***g,int n){
	int i,j;

	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++)
			free(g[i][j]);
		free(g[i]);
	} 
}

void enque(Que *que,int a,int n){
	que->last++;
	que->q[que->last] = a;
}

int deque(Que *que){
	int e;
	int i;

	e = que->q[0];
	for(i=0;i<que->last;i++)
		que->q[i] = que->q[i+1];
	que->last--;
	return e;
}

void BFSprint(Node ***g,int a,int n,Que *que){
	int i;
	int b;

	if(g[a][0]->visit == 0){
		printf("%d\n",a);
		g[a][0]->visit = 1;
	}


	for(i=1;i<=n;i++){
		if(g[a][i]->edgesize == 1){
			if(g[i][0]->visit == 0){
				enque(que,i,n);
				printf("%d\n",i);
				g[i][0]->visit = 1;
				g[a][i]->edgesize = 0;
				g[i][a]->edgesize = 0;
			}
		}
	}

	if(que->last == -1)
		return;

	b = deque(que);
	
	BFSprint(g,b,n,que);

	return;
}

int main(){
	int i,j;
	int n,m,s;
	int x,y;

	Que *que;

	Node ***k;

	scanf("%d %d %d",&n,&m,&s);

	k = (Node***)malloc(sizeof(Node**)*(n+1)); // index 0�� ����ü�� ���� & 1-n���� ����ü �迭 �Ҵ�
	que = (Que*)malloc(sizeof(que));
	que->q = (int*)calloc(sizeof(int),n);
	que->last = -1;

	for(i=0;i<=n;i++){
		k[i] = (Node**)malloc(sizeof(Node*)*(n+1));
		for(j=0;j<=n;j++)
			k[i][j] = (Node*)malloc(sizeof(Node));
	}	
	
	for(i=1;i<=n;i++){
		k[i][0]->visit = 0;
		for(j=1;j<=n;j++){
			k[i][j]->edgesize = 0;
		}
	}

	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		insert(k,x,y);
	}

	BFSprint(k,s,n,que);
	
	putnode(k,n); // �޸� ����
	
	free(k);
}
