#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int nodenum;
	int edgesize;
	struct Node *next;
}Node;

Node * newnode(int a,int b){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->edgesize = b;
	temp->nodenum = a;
	temp->next = NULL;
	return temp;
}

void init(Node **g){
	Node *temp;

	temp = g[1];
	temp->next = newnode(2,1);
	temp = temp->next;
	temp->next = newnode(3,1);
	temp = temp->next;
	temp->next = newnode(4,1);
	temp = temp->next;
	temp->next = newnode(6,2);

	temp = g[2];
	temp->next = newnode(1,1);
	temp = temp->next;
	temp->next = newnode(3,1);

	temp = g[3];
	temp->next = newnode(1,1);
	temp = temp->next;
	temp->next = newnode(2,1);
	temp = temp->next;
	temp->next = newnode(5,4);

	temp = g[4];
	temp->next = newnode(1,1);
	
	temp = g[5];
	temp->next = newnode(3,4);
	temp = temp->next;
	temp->next = newnode(5,4);
	temp = temp->next;
	temp->next = newnode(6,3);

	temp = g[6];
	temp->next = newnode(1,2);
	temp = temp->next;
	temp->next = newnode(5,3);
}
// 그래프 초기화

void print(Node **g,int num){
	Node *temp;

	if(num<1 || num>6){
		printf("-1\n");
		return;
	} // 정점의 번호가 아닐 경우

	temp = g[num]->next;

	if(temp == NULL){
		printf("-1\n");
		return;
	} // 간선이 없는 경우

	while(temp != NULL){
		printf(" %d %d",temp->nodenum,temp->edgesize);
		temp = temp->next;
	}
	printf("\n");
}

void insert(Node **g,int a,int b,int num){
	Node *temp;
	Node *n = newnode(b,num);
	Node *m = newnode(a,num);
	
	temp = g[a]; 

	while(1){
		if(temp->next == NULL){
			temp->next = n;
			break;
		}
		else{
			if(temp->next->nodenum > b){
				n->next = temp->next;
				temp->next = n;
				break;
			}
			else{
				temp = temp->next;
			}
		}
	} // a정점인 리스트에서 (b정점 간선 가중치 num)인 노드 삽입

	if(a==b)
		return;

	temp = g[b];

	while(1){
		if(temp->next == NULL){
			temp->next = m;
			break;
		}
		else{
			if(temp->next->nodenum > a){
				m->next = temp->next;
				temp->next = m;
				break;
			}
			else{
				temp = temp->next;
			}
		}
	}  // b정점인 리스트에서 (a정점 간선 가중치 num)인 노드 삽입
}

void change(Node **g,int a,int b,int num){
	Node *temp;
	int right=0;


	temp = g[a]->next;
	while(temp != NULL){
		if(temp->nodenum == b){
			temp->edgesize= num;
			right = 1;
			break;
		}
		temp = temp->next;
	} // a,b 간선이 있을 때 가중치 변경

	if(right == 0){
		insert(g,a,b,num);
		return;
	} // a,b를 연결하는 간선이 없는 경우

	if(a==b)
		return;

	temp = g[b]->next;
	while(temp != NULL){
		if(temp->nodenum == a){
			temp->edgesize= num;
			break;
		}
		temp = temp->next;
	} // a,b 간선이 있을 때 가중치 변경
}

void removenode(Node **g,int a,int b,int num){
	Node *temp;
	Node *rem;

	temp = g[a];

	while(temp->next->nodenum != b){
		temp = temp->next;
		if(temp->next == NULL){
			printf("-1\n");
			return;
		}
	}
	if(temp->next->next == NULL){
		free(temp->next);
		temp->next = NULL;
	}
	else{
		rem = temp->next;
		temp->next = temp->next->next;
		free(rem);
	} // a,b의 간선 제거

	if(a==b)
		return;

	temp = g[b];
	while(temp->next->nodenum != a)
		temp = temp->next;
	if(temp->next->next == NULL){
		free(temp->next);
		temp->next = NULL;
	}
	else{
		rem = temp->next;
		temp->next = temp->next->next;
		free(rem);
	} // a,b의 간선 제거
}

void putnode(Node **g){
	int i;
	Node *temp;
	Node *fr;

	for(i=1;i<=6;i++){
		temp = g[i];
		while(temp->next != NULL){
			fr = temp->next;
			temp->next = temp->next->next;
			free(fr);
		}
	} 
}

int main(){
	
	char a;
	int num;
	int start,end,edgenum;
	int i;
	Node **g = (Node**)malloc(sizeof(Node*)*7); // index 0인 구조체는 생략

	for(i=1;i<=6;i++)
		g[i] = newnode(i,0); // index 0인 구조체는 생략
	
	init(g); // 주어진 그래프로 초기화

	while(1){
		scanf("%c",&a);
		if(a == 'q'){
			break;
		}
		switch(a){
			case 'a':
				scanf("%d",&num);
				getchar();
				print(g,num); // num인 정점에 연결된 정점과 가중치 출력
				break;
			case 'm':
				scanf("%d %d %d",&start,&end,&edgenum);
				getchar();
				if((start < 1 || start > 6) || (end < 1 || end > 6)){
					printf("-1\n");
					break;
				}
				if(edgenum != 0)
					change(g,start,end,edgenum); // a,b의 간선 가중치의 값 변경 또는 삽입
				else
					removenode(g,start,end,edgenum); // a,b의 간선 제거
				break;
		}
	}

	putnode(g); // 메모리 해제
	
	free(g);
}
