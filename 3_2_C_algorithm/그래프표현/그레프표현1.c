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
// �׷��� �ʱ�ȭ

void print(Node **g,int num){
	Node *temp;

	if(num<1 || num>6){
		printf("-1\n");
		return;
	} // ������ ��ȣ�� �ƴ� ���

	temp = g[num]->next;

	if(temp == NULL){
		printf("-1\n");
		return;
	} // ������ ���� ���

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
	} // a������ ����Ʈ���� (b���� ���� ����ġ num)�� ��� ����

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
	}  // b������ ����Ʈ���� (a���� ���� ����ġ num)�� ��� ����
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
	} // a,b ������ ���� �� ����ġ ����

	if(right == 0){
		insert(g,a,b,num);
		return;
	} // a,b�� �����ϴ� ������ ���� ���

	if(a==b)
		return;

	temp = g[b]->next;
	while(temp != NULL){
		if(temp->nodenum == a){
			temp->edgesize= num;
			break;
		}
		temp = temp->next;
	} // a,b ������ ���� �� ����ġ ����
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
	} // a,b�� ���� ����

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
	} // a,b�� ���� ����
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
	Node **g = (Node**)malloc(sizeof(Node*)*7); // index 0�� ����ü�� ����

	for(i=1;i<=6;i++)
		g[i] = newnode(i,0); // index 0�� ����ü�� ����
	
	init(g); // �־��� �׷����� �ʱ�ȭ

	while(1){
		scanf("%c",&a);
		if(a == 'q'){
			break;
		}
		switch(a){
			case 'a':
				scanf("%d",&num);
				getchar();
				print(g,num); // num�� ������ ����� ������ ����ġ ���
				break;
			case 'm':
				scanf("%d %d %d",&start,&end,&edgenum);
				getchar();
				if((start < 1 || start > 6) || (end < 1 || end > 6)){
					printf("-1\n");
					break;
				}
				if(edgenum != 0)
					change(g,start,end,edgenum); // a,b�� ���� ����ġ�� �� ���� �Ǵ� ����
				else
					removenode(g,start,end,edgenum); // a,b�� ���� ����
				break;
		}
	}

	putnode(g); // �޸� ����
	
	free(g);
}
