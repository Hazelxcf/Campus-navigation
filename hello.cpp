#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define M 5000 //假设两顶点之间没有路径,用5000来表示
int b, w;
typedef struct vexsinfo     //存放顶点信息的结构体
{
	int park;               //访问的标志,park=0是未被访问过
	int num;                //景点的编号
	char name[32000];          //景点的名称
	//char introduction[256]; //景点的介绍
}vexsinfo;
typedef struct MGraph
{
	int r;                  //记录最短路径访问过的景点数目
	int minrude;            //记录最短路径的长度
	int min[50];            //记录最短路径经过的顶点信息
	int a[50];              //记录路线的数组
	vexsinfo vexs[50];      //存放顶点编号的数组，用vexsinfo结构体的变量vexsinfo定义，可以用
						   //该数组存放顶点信息            
	int arc[50][50];        //存放两点之间权值的邻接矩阵
	int v, e;                //定点数和边数
} MGraph;

MGraph* CreateGraph()
{
	MGraph* G;
	int i, j, k;
	G = (MGraph*)malloc(sizeof(MGraph));

	//初始化访问标志
	for (i = 1; i <=10; i++) {
		G->vexs[i].park = 0;
	}

	//初始化顶点数目和路线数目
	G->v = 10;
	G->e = 13;

	//给景点数组编号
	for (i = 1; i <= G->v; i++)
		G->vexs[i].num = i;
	for (j = 1; j <= 10; j++)
		for (k = 1; k <= 10; k++)
		{
			G->arc[j][k] = M;
		}
	//初始化顶点信息
	strcpy(G->vexs[1].name, "南二门");
	strcpy(G->vexs[2].name, "沂蒙大讲堂");
	strcpy(G->vexs[3].name, "体育场");
	strcpy(G->vexs[4].name, "篮球场");
	strcpy(G->vexs[5].name, "大学生活动中心");
	strcpy(G->vexs[6].name, "实验中心");
	strcpy(G->vexs[7].name, "九州");
	strcpy(G->vexs[8].name, "艺术中心");
	strcpy(G->vexs[9].name, "国际交流中心");
	strcpy(G->vexs[10].name, "信息学院");
	//初始化矩阵,赋予每条边权值
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
		printf("路线总长：%dkm\n", sum);
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
				RudeGraph(G, j, w, k, sum);    //通过递归对所有路径进行深度搜索
				k--;                       //递归返回这一层后对顶点信息进行重新初始化
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
		printf("欢迎来到**大学景点导航系统\n");
		printf("1.景点信息查询\n");
		printf("2.路线查询服务\n");
		printf("3.退出\n");
		printf("**********************************\n");
		printf("请选择你要查询的功能：\n");

		scanf("%d", &c);
		if (c == 1) {
			printf("**********************************\n");
			printf("**大学共有如下十处景点：\n");
			for (i = 1; i <= 10; i++) {
				printf("%d ", T->vexs[i].num);
				printf("%s\n", T->vexs[i].name);
			}
		}

		else if (c == 2)
		{
			printf("**********************************\n");
			printf("请输入当前景点编号和你想要去的景点编号：\n");
			printf("(注：景点编号可在功能1内查询)\n");
			for (i = 0; i < 10; i++)
			{
				T->vexs[i].park = 0;
			}
			scanf("%d %d", &b, &w);
			while (b < 1 || b>10 || w < 1 || w>10) {
				printf("输入错误，请重新输入:\n");
				scanf("%d %d", &b, &w);
			}
			if (b == w) {
				printf("您已经在此景点,请重新输入：\n");
				scanf("%d %d", &b, &w);
			}
			else {
				T->a[0] = b;
				T->vexs[b].park = 1;
				printf("从景点%d到景点%d共有如下路径：\n", b, w);
				RudeGraph(T, b, w, 0, 0);
				
				T->minrude = 100;                        //重新初始化最短路径长度

			}

		}
		else if (c == 3) break;
		else printf("输入错误，请重新输入：\n");
	}
	printf("祝您生活愉快，再见^v^");
	return 0;
}

