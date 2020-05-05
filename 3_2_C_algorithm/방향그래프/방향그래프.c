#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int in;
	int name;
}Node;

Node G[100][100];
int *Q;
int topSort[100]={0};
int n,m;

void enque(int a){
	int i=1;
	while(Q[i] != -1){
		i++;
	}
	Q[i] = a;
}

int deque(){
	int e;
	int i=1;
	e = Q[1];
	while(1){
		Q[i] = Q[i+1];
		if(Q[i] == -1)
			break;
		i++;
	}
	return e;
}

void input(int x,int y){
	int i=1;
	int j;

	while(1){
		if(G[x][i].name == -1)
			break;
		i++;
	}
	for(j=i-1;j>=1;j--)
		G[x][j+1].name = G[x][j].name;

	G[x][1].name = y;
	G[y][0].in++;
}

int corect(char *ch,char x){
	int i=0;
	int a;

	for(i=0;i<n;i++){
		if(ch[i] == x)
			a=i;
	}
	return a;
}

void buildGraph(char *ch){
	int i=0;
	int j;
	char a,b;
	int x,y;

	for(i=0;i<n;i++){
		G[i][0].in = 0;
		G[i][0].name = i;
		for(j=1;j<=n;j++)
			G[i][j].name = -1;
	}

	for(i=0;i<m;i++){
		getchar();
		scanf("%c %c",&a,&b);
		
		x = corect(ch,a);
		y = corect(ch,b);

		input(x,y);
	}
}

void removeedge(int in){
	int i=1;

	while(1){
		if(G[in][i].name == -1)
			break;
		else{
			G[G[in][i].name][0].in--;
			if(G[G[in][i].name][0].in == 0)
				enque(G[in][i].name);
			G[in][i].name = -1;
			i++;
		}
	}
}

void topologicalSort(){
	int i;
	int in=1;
	int e;

	for(i=0;i<n;i++){
		if(G[i][0].in == 0)
			enque(i);
	}

	while(1){
		e = deque();
		if(e != -1)
			topSort[in] = e;
		else{
			topSort[0] = 0;
			return;
		}
		removeedge(topSort[in]);
		in++;
		if(in == n+1)
			break;
	}
}

void printff(char *ch){
	int i;
	int j;

	for(i=1;i<=n;i++){
		for(j=0;j<n;j++){
			if(j == topSort[i]){
				printf("%c ",ch[j]);
				break;
			}
		}
	}
}

int main(){
	int i;
	char ch[100];

	scanf("%d",&n);
	getchar();

	Q = (int*)malloc(sizeof(int)*(n+1));
	for(i=0;i<=n;i++)
		Q[i] = -1;
	topSort[0] = 1;

	for(i=0;i<n;i++){
		scanf("%c",&ch[i]);
		getchar();
	}
	
	scanf("%d",&m);

	buildGraph(ch);

	topologicalSort();

	if(topSort[0] == 1)
		printff(ch);
	else 
		printf("0");
}