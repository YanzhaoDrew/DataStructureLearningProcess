// #include"MatGraph.cpp"								//包含图(邻接矩阵)的基本运算算法，注意类
#include<vector>
#include <iostream>
using namespace std; 
#define MAXV 100										//图中最多的顶点数
#define INF 0x3f3f3f3f								//用INF表示
class MatGraph                        //图邻接矩阵类
{
public:
    int edges[MAXV][MAXV];            //邻接矩阵数组，假设元素为int类型
    int n,e;                        //顶点数，边数
    string vexs[MAXV];                //存放顶点信息
    void CreateMatGraph(int a[][MAXV],int n,int e) //通过边数组a、顶点数n和边数e来建立图的邻接矩阵
    {
        this->n=n; this->e=e;                //置顶点数和边数
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                this->edges[i][j]=a[i][j];
    }
    void DispMatGraph()    {}                    //输出图的邻接矩阵
};


int Degree1(MatGraph &g,int v)	   					//无向图邻接矩阵g中求顶点v的度,return 度
{	
    int res = 0;
    for (int i = 0; i < g.n; i++){
        if (i == v){
            for (int j = 0; j < g.n ; j++){
                res += g.edges[i][j];
            }
            return res;
        }
    }
    return -1;
}
vector<int> Degree2(MatGraph &g,int v) 				//有向图邻接矩阵g中求顶点v的出度和入度
{
	vector<int> ans={0,0};                       	//ans[0]累计出度,ans[1]累计入度
	//补充
    for (int i = 0; i < g.n; i++)
    {
        /* code */
        if (i == v){
            for (int j = 0; j < g.n; j++){
                if (g.edges[i][j] > 0 && g.edges[i][j] < INF) ans[0] += 1;
                if (g.edges[j][i] > 0 && g.edges[j][i] < INF) ans[1] += 1;
            }
            break;
        }
    }
   return ans;//改变完ans数组里的值，再返回
	
}






