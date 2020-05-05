#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int d;
	struct Node* l;
	struct Node* r;
}Node;

Node* getnode(){
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->l = NULL;
	newnode->r = NULL;
	return newnode;
}

void init(Node* node){
	int data,le,ri;
	scanf("%d %d %d",&data,&le,&ri);
	node->d = data;
	if(le==0 && ri==0)
		return;
	if(ri==0){
		node->l = getnode();
		node->l->d = le;
		init(node->l);
	}
	if(le==0){
		node->r = getnode();
		node->r->d = ri;
		init(node->r);
	}
	if(le && ri){
		node->l = getnode();
		node->l->d = le;
		init(node->l);
		node->r = getnode();
		node->r->d = ri;
		init(node->r);
	}
	return;
}

void travel(Node* root,char *a){
	int i=0;
	Node* temp;

	temp = root;
	while(1){
		if(a[i] == '\0'){
			printf(" %d\n",temp->d);
			break;
		}
		printf(" %d",temp->d);
		if(a[i] == 'R')
			temp = temp->r;
		else if(a[i] == 'L')
			temp = temp->l;
		i++;
	}
}

int main(){
	int k,n;
	char a[101];
	Node root;

	scanf("%d",&k);
	init(&root);

	scanf("%d",&n);
	while(1){
		scanf("%s",a);
		travel(&root,a);
		n--;
		if(n==0)
			break;
	}
}
