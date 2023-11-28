#include"class_12_1_Graph.cpp"						//包含图(邻接表)的基本运算算法（第一关）
#include<vector>
//本关任务：编写一个求给定顶点的度，或者出度与入度的程序。
int Degree1(AdjGraph &G,int v)	   			//无向图邻接表G中求顶点v的度
{	
    int res = 0;
    ArcNode *current;
    for (int i = 0; i < G.n; i++){
        if (i == v){
            current = G.adjlist[i].firstarc;
            while (current != NULL){current = current->nextarc;res++;}
            break;
        }
    }
    return res;
}
	
vector<int> Degree2(AdjGraph &G,int v) 		//有向图邻接表G中求顶点v的出度和入度
{
	vector<int> ans={0,0};                  //ans[0]累计出度,ans[1]累计入度
   //补充完整
    ArcNode *current;
    for (int i = 0; i < G.n; i++){
        if (i == v){
            current = G.adjlist[i].firstarc;
            //计算出度
            while (current != NULL){current = current->nextarc;ans[0]++;}
            break;
        }
    }
    //计算入度
    for (int j = 0; j < G.n; j++){
        current = G.adjlist[j].firstarc;
        while (current != NULL){
            if (current->adjvex == v){ans[1]++;break;}
            current = current->nextarc;
        }
    }
 	return ans;						   		//返回出度和入度
}
int main(){
    int a[MAXV][MAXV]={{0,1,0,1,1},{1,0,1,1,0},{0,1,0,1,1},{1,1,1,0,1},{1,0,1,1,0}};
    AdjGraph G;
    G.CreateAdjGraph(a,5,8);
    G.DispAdjGraph();
    cout<<"求解结果"<<endl;
    for (int i=0;i<G.n;i++)
        cout<<"  顶点"<<i<<"的度: "<<Degree1(G,i)<<endl;
    cout<<endl;
    cout<<"求解结果"<<endl;
    for (int i=0;i<G.n;i++)
    {
        vector<int> ans=Degree2(G,i);
        cout<<"  顶点"<<i<<"的出度: "<<ans[0]<<endl;
        cout<<"  顶点"<<i<<"的入度: "<<ans[1]<<endl;
    }
    return 0;
}
/*
输入：
{{0,1,0,1,1},{1,0,1,1,0},{0,1,0,1,1},{1,1,1,0,1},{1,0,1,1,0}}

输出：
图G1(无向图)
   [0]→ (1,1) (3,1) (4,1)
   [1]→ (0,1) (2,1) (3,1)
   [2]→ (1,1) (3,1) (4,1)
   [3]→ (0,1) (1,1) (2,1) (4,1)
   [4]→ (0,1) (2,1) (3,1)
求解结果
  顶点0的度: 3
  顶点1的度: 3
  顶点2的度: 3
  顶点3的度: 4
  顶点4的度: 3

输入：
{{0,8,INF,5,INF},{INF,0,3,INF,INF},{INF,INF,0,INF,6},{INF,INF,9,0,INF},{INF,INF,INF,INF,0}}
输出：

图G2(有向图)
   [0]→ (1,8) (3,5)
   [1]→ (2,3)
   [2]→ (4,6)
   [3]→ (2,9)
   [4]
求解结果
  顶点0: 出度=2 入度=0 度=2
  顶点1: 出度=1 入度=1 度=2
  顶点2: 出度=1 入度=2 度=3
  顶点3: 出度=1 入度=1 度=2
  顶点4: 出度=0 入度=1 度=1
*/
