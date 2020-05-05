#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int edgesize;
}Node;

void init(Node ***g){
	Node *temp;
	int i,j;

	for(i=1;i<=6;i++){
		for(j=1;j<=6;j++)
			g[i][j]->edgesize = -1;
	}

	g[1][2]->edgesize = 1;
	g[1][3]->edgesize = 1;
	g[1][4]->edgesize = 1;
	g[1][6]->edgesize = 2;

	g[2][1]->edgesize = 1;
	g[2][3]->edgesize = 1;
	
	g[3][1]->edgesize = 1;
	g[3][2]->edgesize = 1;
	g[3][5]->edgesize = 4;

	g[4][1]->edgesize = 1;

	g[5][3]->edgesize = 4;
	g[5][5]->edgesize = 4;
	g[5][6]->edgesize = 3;

	g[6][1]->edgesize = 2;
	g[6][5]->edgesize = 3;
}
// �׷��� �ʱ�ȭ

void print(Node ***g,int num){
	int i;
	int k=0;

	if(num<1 || num>6){
		printf("-1\n");
		return;
	} // ������ ��ȣ�� ���� ���

	for(i=1;i<=6;i++){
		if(g[num][i]->edgesize == -1)
			continue;
		else{
			printf(" %d %d",i,g[num][i]->edgesize);
			k = 1;
		}
	}
	if(k==0)
		printf("-1");
		
	printf("\n");
}

void change(Node ***g,int a,int b,int num){

	if((g[a][b]->edgesize == -1) && (num == 0)){
		printf("-1\n");
	} // ����ġ�� ���µ� ����
	else if(g[a][b]->edgesize != -1 && num==0){
		g[a][b]->edgesize = -1;
		g[b][a]->edgesize = -1;
	} // ����ġ�� ���� �� ����
	else{
		g[a][b]->edgesize = num;
		g[b][a]->edgesize = num;
	}
}

int main(){
	char a;
	int num;
	int start,end,edgenum;
	int i,j;

	Node ***in = (Node***)malloc(sizeof(Node**)*7);

	for(i=1;i<=6;i++){
		in[i] = (Node**)malloc(sizeof(Node*)*7);
		for(j=1;j<=6;j++)
			in[i][j] = (Node*)malloc(sizeof(Node));
	}

	init(in); // �־��� �׷����� �ʱ�ȭ

	while(1){
		scanf("%c",&a);
		if(a == 'q'){
			break;
		}
		switch(a){
			case 'a':
				scanf("%d",&num);
				getchar();
				print(in,num); // num�� ������ ����� ������ ����ġ ���
				break;
			case 'm':
				scanf("%d %d %d",&start,&end,&edgenum);
				getchar();
				if((start < 1 || start > 6) || (end < 1 || end > 6)){
					printf("-1\n");
					break;
				}
				change(in,start,end,edgenum); // a,b�� ���� ����ġ�� �� ���� �Ǵ� ����
				break;
		}
	}

	for(i=1;i<=6;i++){
		for(j=1;j<=6;j++)
			free(in[i][j]);
		free(in[i]);
	}
	free(in);

}
