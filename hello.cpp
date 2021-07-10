#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define M 5000 //����������֮��û��·��,��5000����ʾ
int b, w;
typedef struct vexsinfo     //��Ŷ�����Ϣ�Ľṹ��
{
	int park;               //���ʵı�־,park=0��δ�����ʹ�
	int num;                //����ı��
	char name[32000];          //���������
	//char introduction[256]; //����Ľ���
}vexsinfo;
typedef struct MGraph
{
	int r;                  //��¼���·�����ʹ��ľ�����Ŀ
	int minrude;            //��¼���·���ĳ���
	int min[50];            //��¼���·�������Ķ�����Ϣ
	int a[50];              //��¼·�ߵ�����
	vexsinfo vexs[50];      //��Ŷ����ŵ����飬��vexsinfo�ṹ��ı���vexsinfo���壬������
						   //�������Ŷ�����Ϣ            
	int arc[50][50];        //�������֮��Ȩֵ���ڽӾ���
	int v, e;                //�������ͱ���
} MGraph;

MGraph* CreateGraph()
{
	MGraph* G;
	int i, j, k;
	G = (MGraph*)malloc(sizeof(MGraph));

	//��ʼ�����ʱ�־
	for (i = 1; i <=10; i++) {
		G->vexs[i].park = 0;
	}

	//��ʼ��������Ŀ��·����Ŀ
	G->v = 10;
	G->e = 13;

	//������������
	for (i = 1; i <= G->v; i++)
		G->vexs[i].num = i;
	for (j = 1; j <= 10; j++)
		for (k = 1; k <= 10; k++)
		{
			G->arc[j][k] = M;
		}
	//��ʼ��������Ϣ
	strcpy(G->vexs[1].name, "�϶���");
	strcpy(G->vexs[2].name, "���ɴ���");
	strcpy(G->vexs[3].name, "������");
	strcpy(G->vexs[4].name, "����");
	strcpy(G->vexs[5].name, "��ѧ�������");
	strcpy(G->vexs[6].name, "ʵ������");
	strcpy(G->vexs[7].name, "����");
	strcpy(G->vexs[8].name, "��������");
	strcpy(G->vexs[9].name, "���ʽ�������");
	strcpy(G->vexs[10].name, "��ϢѧԺ");
	//��ʼ������,����ÿ����Ȩֵ
	G->arc[1][2] = 5;
	G->arc[2][1] = 5;
	G->arc[1][3] = 5;
	G->arc[3][1] = 5;
	G->arc[2][6] = 7;
	G->arc[6][2] = 7;
	G->arc[4][3] = 5;
	G->arc[3][4] = 5;
	G->arc[4][5] = 7;
	G->arc[5][4] = 7;
	G->arc[9][5] = 9;
	G->arc[5][9] = 9;
	G->arc[6][10] = 5;
	G->arc[10][6] = 5;
	G->arc[7][8] = 15;
	G->arc[8][7] = 15;
	G->arc[10][7] = 9;
	G->arc[7][10] = 9;
	G->arc[8][9] = 9;
	G->arc[9][8] = 9;
	return G;
}
void RudeGraph(MGraph* G, int b, int w, int k, int sum) {
	int p, j, n;

	if (b == w) {
		for (p = 0; p < k; p++) {
			printf("%d->", G->a[p]);
		}
		printf("%d  ", G->a[k]);
		printf("·���ܳ���%dkm\n", sum);
		if (sum < G->minrude) {
			G->r = k;
			G->minrude = sum;
			for (p = 0; p <= k; p++) {
				G->min[p] = G->a[p];
			}
		}
		return;
	}
	else {
		for (j = 1; j <= 10; j++) {

			if (G->arc[b][j] < 5000 && G->vexs[j].park == 0) {
				k++;
				G->a[k] = j;
				sum += G->arc[b][j];
				G->vexs[j].park = 1;
				RudeGraph(G, j, w, k, sum);    //ͨ���ݹ������·�������������
				k--;                       //�ݹ鷵����һ���Զ�����Ϣ�������³�ʼ��
				G->vexs[j].park = 0;
				sum -= G->arc[b][j];
			}

		}
	}

	return;
}

int main(void)
{
	int c, i, p, k;
	MGraph* T;
	T = CreateGraph();
	while (1) {
		printf("**********************************\n");
		printf("��ӭ����**��ѧ���㵼��ϵͳ\n");
		printf("1.������Ϣ��ѯ\n");
		printf("2.·�߲�ѯ����\n");
		printf("3.�˳�\n");
		printf("**********************************\n");
		printf("��ѡ����Ҫ��ѯ�Ĺ��ܣ�\n");

		scanf("%d", &c);
		if (c == 1) {
			printf("**********************************\n");
			printf("**��ѧ��������ʮ�����㣺\n");
			for (i = 1; i <= 10; i++) {
				printf("%d ", T->vexs[i].num);
				printf("%s\n", T->vexs[i].name);
			}
		}

		else if (c == 2)
		{
			printf("**********************************\n");
			printf("�����뵱ǰ�����ź�����Ҫȥ�ľ����ţ�\n");
			printf("(ע�������ſ��ڹ���1�ڲ�ѯ)\n");
			for (i = 0; i < 10; i++)
			{
				T->vexs[i].park = 0;
			}
			scanf("%d %d", &b, &w);
			while (b < 1 || b>10 || w < 1 || w>10) {
				printf("�����������������:\n");
				scanf("%d %d", &b, &w);
			}
			if (b == w) {
				printf("���Ѿ��ڴ˾���,���������룺\n");
				scanf("%d %d", &b, &w);
			}
			else {
				T->a[0] = b;
				T->vexs[b].park = 1;
				printf("�Ӿ���%d������%d��������·����\n", b, w);
				RudeGraph(T, b, w, 0, 0);
				
				T->minrude = 100;                        //���³�ʼ�����·������

			}

		}
		else if (c == 3) break;
		else printf("����������������룺\n");
	}
	printf("ף��������죬�ټ�^v^");
	return 0;
}

