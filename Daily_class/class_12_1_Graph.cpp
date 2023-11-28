#include <iostream>
using namespace std; 
#ifndef MAXV
#define MAXV 100										//图中最多的顶点数
#define INF 0x3f3f3f3f								//用INF表示
#endif 

/**
 * Statement: 
 *  编写一个将邻接矩阵转为邻接表存储的程序。
*/

struct ArcNode										//边结点类型 
{	
    int adjvex;										//邻接点 
	int weight;										//权值 
	ArcNode *nextarc;								//指向下一条边的边结点 
};

struct HNode										//头结点类型 ***
{
	string info;									//顶点信息
	ArcNode *firstarc;								//指向第一条边的边结点
};

class AdjGraph										//图邻接表类
{
public:
	HNode adjlist[MAXV];							//头结点数组
	int n,e;										//顶点数，边数
	AdjGraph()										//构造函数
	{
		for (int i=0;i<MAXV;i++)					//头结点的firstarc置为空 
			adjlist[i].firstarc=NULL;
	}
	~AdjGraph()										//析构函数,释放图的邻接表空间
	{
        ArcNode *del, *current;
        for (int i = 0; i < n; i++){
            current = adjlist[i].firstarc;
            while(current != NULL){
                del = current;
                current = current->nextarc;
                delete del;  // 释放边节点
            }
        }
	}
	void CreateAdjGraph(int a[][MAXV],int n,int e)	//通过边数组a、顶点数n和边数e来建立图的邻接表
	{   
        this->n = n;
        this->e = e;
        ArcNode *p;
        for (int i = 0; i < n; i++){
            for (int j = n-1; j >= 0; j--){ //这里反过来了
                if (a[i][j] != 0 && a[i][j] != INF){
					//头插法
                    p = new ArcNode;
					p->adjvex = j;
                    p->weight = a[i][j];
					//头插到firstarc中，firstarc指向新的p
                    p->nextarc = adjlist[i].firstarc;
                    adjlist[i].firstarc = p;
                }
            }
        }
	}

	
	void DispAdjGraph()								//输出图的邻接表
	{
		ArcNode *p;
		for (int i=0;i<n;i++)						//遍历每个头结点 
		{
			printf("   [%d]",i);
			p=adjlist[i].firstarc;					//p指向第一个邻接点
			if (p!=NULL)  printf("→");
			while (p!=NULL)							//遍历第i个单链表 
			{
				printf(" (%d,%d)",p->adjvex,p->weight);
				p=p->nextarc;						//p移向下一个邻接点
			}
			printf("\n");
		}
	}
};
// int main(){
//     int a[MAXV][MAXV]={{0,8,INF,5,INF},
//                        {INF,0,3,INF,INF},
//                        {INF,INF,0,INF,6},
//                        {INF,INF,9,0,INF},
//                        {INF,INF,INF,INF,0}};
//     AdjGraph g;
//     g.CreateAdjGraph(a,5,7);
//     printf("图的邻接表:\n");
//     g.DispAdjGraph();
//     printf("销毁图\n");
//     return 0;
// }

/*
输入：
{{0,8,INF,5,INF},
 {INF,0,3,INF,INF},
 {INF,INF,0,INF,6},
 {INF,INF,9,0,INF},
 {INF,INF,INF,INF,0}}
输出：(different from)
图的邻接表:
   [0]→ (1,8) (3,5)
   [1]→ (2,3)
   [2]→ (4,6)
   [3]→ (2,9)
   [4]
销毁图
*/
