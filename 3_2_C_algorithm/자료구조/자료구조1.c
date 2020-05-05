#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	char ch;
	struct Node* next;
	struct Node* prev;
}node;

typedef struct List{
	node *head;
	node *trail;
	int cnt;
}li;

node* getnode(){
	node* newnode;
	newnode = (node*)malloc(sizeof(node));
	newnode->ch = NULL;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}

void init(li* list){
	list->head = getnode();
	list->trail = getnode();
	list->head->next = list->trail;
	list->trail->prev = list->head;
}

void add(li* list,int a,char na){
	int i;
	node* newnode = getnode();
	newnode->ch = na;
	newnode->next = list->head;
	while(a!=0){
		newnode->next = newnode->next->next;
		if(newnode->next == NULL){
			printf("invalid position\n");
			return;
		}
		a--;
	}

	newnode->prev = newnode->next->prev;
	newnode->next->prev = newnode;
	newnode->prev->next = newnode;

}

void delet(li* list,int a){
	int i;
	node* newnode = getnode();
	newnode->next = list->head;
	while(a!=0){
		newnode->next = newnode->next->next;
		if(newnode->next == NULL || newnode->next->ch == NULL){
			printf("invalid position\n");
			return;
		}
		a--;
	}
	newnode->next->next->prev = newnode->next->prev;
	newnode->next->prev->next = newnode->next->next;
	free(newnode);
}

char get(li* list,int a){
	int i;
	char c='0';
	node* newnode = getnode();
	newnode->next = list->head;
	while(a!=0){
		newnode->next = newnode->next->next;
		if(newnode->next == NULL || newnode->next->ch == NULL){
			printf("invalid position\n");
			return c;
		}
		a--;
	}
	c = newnode->next->ch;
	free(newnode);
	return c;
}

void print(li* list){
	int i;
	node* temp = (node *)malloc(sizeof(node));
	temp->next = list->head->next;
	while(temp->next->ch != NULL){
		printf("%c",temp->next->ch);
		temp->next = temp->next->next;
	}
	printf("\n");
	free(temp);
}

int main(){

	int n,k;
	char a,name,c;
	li list;
	node* newnode = getnode();

	init(&list);

	scanf("%d",&n);
	while(n!=0){
		scanf(" %c",&a);
		switch(a)
		{
		case 'A':
			scanf(" %d %c",&k,&name);
			add(&list,k,name);
			break;
		case 'G':
			scanf(" %d",&k);
			c = get(&list,k);
			if(c=='0') break;
			printf("%c\n",c);
			break;
		case 'D':
			scanf(" %d",&k);
			delet(&list,k);
			break;
		case 'P':
			print(&list);
			break;
		}
		n--;
}



	newnode = list.head->next;
	while(newnode != NULL){
		node* next = newnode->next;
		free(newnode);
		newnode = next;
	}
	free(list.head);
}
