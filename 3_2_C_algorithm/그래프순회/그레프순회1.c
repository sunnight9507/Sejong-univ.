#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int nodenum;
	int edgesize;
	int visit;
	struct Node *next;
}Node;

Node * newnode(int a){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->nodenum = a;
	temp->next = NULL;
	temp->visit = 0;
	return temp;
}

void insert(Node **g,int a,int b){
	Node *temp;
	Node *n = newnode(b);
	Node *m = newnode(a);
	
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
	} // a������ ����Ʈ���� b������ ���� ��� ����

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
	}  // b������ ����Ʈ���� a������ ���� ��� ����
}

void putnode(Node **g,int a){
	int i;
	Node *temp;
	Node *fr;

	for(i=1;i<=a;i++){
		temp = g[i];
		while(temp->next != NULL){
			fr = temp->next;
			temp->next = temp->next->next;
			free(fr);
		}
	} 
}

void DFSprint(Node **g,int a){
	Node *temp;

	g[a]->visit = 1;
	temp = g[a]->next;

	printf("%d\n",a);

	while(temp!=NULL){
		if(g[temp->nodenum]->visit == 1){
			temp = temp->next;
			continue;
		}
		DFSprint(g,temp->nodenum);
		temp = temp->next;
	}

	return;
}

int main(){
	
	char a;
	int num;
	int i;
	int n,m,s;
	int x,y;

	Node **k;

	scanf("%d %d %d",&n,&m,&s);

	k = (Node**)malloc(sizeof(Node*)*(n+1)); // index 0�� ����ü�� ���� & 1-n���� ����ü �迭 �Ҵ�

	for(i=1;i<=n;i++)
		k[i] = newnode(i);

	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		insert(k,x,y);
	}

	DFSprint(k,s);

	putnode(k,n); // �޸� ����
	
	free(k);
}
