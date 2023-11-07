#include<iostream>
#include<queue>
#include<string>
#include<algorithm>
using namespace std;
const int MaxSize=100;						//最多总结点个数


struct HTNode 								//哈夫曼树结点类
{	char data;								//结点值
	double weight;							//权值
	int parent;								//双亲结点
	int lchild;								//左孩子结点
	int rchild;								//右孩子结点
	bool flag;								//标识是双亲的左(True)或者右(False)孩子
	HTNode() 								//构造函数
  	{ 	
        parent=-1;
     	lchild=-1;
     	rchild=-1;
	}	
	HTNode(char d,double w) 				//重载构造函数
  	{	data=d;
    	weight=w;
     	parent=-1;
     	lchild=-1;
     	rchild=-1;
     	flag=true;
	}
};

HTNode ht[MaxSize];                 		//ht存放哈夫曼树,已经构建好了
string hcd[MaxSize];                		//hcd存放哈夫曼编码

struct HeapNode								//优先队列元素类型 
{
	double w;								//权值
	int i;									//对应哈夫曼树中结点编号
	HeapNode(double w1,int i1):w(w1),i(i1) {}	//构造函数 
	bool operator<(const HeapNode &s) const	
	{										//将当前对象跟对象s进行比较
		return w>s.w;						//按w越小越优先出队
	}	
};

void CreateHT(char D[], double W[], int n0)								
//构造哈夫曼树，n0是叶子结点数，D[]为叶子结点的值，W[]为叶子结点的权值
{
	//建立优先队列(w小根堆)-->(利用小根堆来选择两个权值最小的元素)
    //另外在创建huffman树的同时要判断其节点是为左或右孩子 ---> (便于后续编码);
    //然后设置flag值

    //创建优先队列 且在HeapNode重载比较符号，使大根堆转换为小根堆
    priority_queue<HeapNode> p;

    //放入小根堆中，方便后续直接提取最小的两个节点构造树
    for (int k = 0; k < n0; k++){
        p.push(HeapNode(W[k], k)); //推入
        ht[k].data = 'a'+ k;  // 记录数据
        ht[k].weight = W[k];  // 权重记录
    }

    //核心功能：
    for (int k = n0; k < n0*2-1; k++){
        //取出最小的两个节点
        int tmp1 = p.top().i;p.pop();
        int tmp2 = p.top().i;p.pop();
        //设置父节点
        ht[tmp1].parent = ht[tmp2].parent = k;
        ht[k].lchild = tmp1;
        ht[tmp1].flag = true;
        ht[k].rchild = tmp2;
        ht[tmp2].flag = false;
        ht[k].weight = ht[tmp1].weight +ht[tmp2].weight;
        //将此父节点，放入小根堆中
        p.push(HeapNode(ht[k].weight, k));
    }
}

void CreateHCode(int n0)						//根据哈夫曼树求哈夫曼编码，n0是叶子结点数
{   
    //基本思路：从叶子节点开始，向上回溯，直到根节点
    for (int i = 0; i < n0; i++){
        int c = i;
        int p = ht[i].parent;
        while (p != -1){
            if (ht[c].flag) hcd[i] += '0';
            else hcd[i] += '1';
            c = p;
            p = ht[c].parent;
        }
        //逆置
        reverse(hcd[i].begin(), hcd[i].end());
    }
}

void DispHT(int n0)                     //输出哈夫曼树，n0是叶子结点数
{
    printf("  i      ");
    for (int i=0;i<2*n0-1;i++)
        printf("%3d",i);
    printf("\n");
    printf("  D[i]   ");
    for (int i=0;i<2*n0-1;i++)
        printf("%3c",ht[i].data);
    printf("\n");
    printf("  W[i]   ");
    for (int i=0;i<2*n0-1;i++)
        printf("%3g",ht[i].weight);
    printf("\n");
    printf("  parent ");
    for (int i=0;i<2*n0-1;i++)
        printf("%3d",ht[i].parent);
    printf("\n");
    printf("  lchild ");
    for (int i=0;i<2*n0-1;i++)
        printf("%3d",ht[i].lchild);
    printf("\n");
    printf("  rchild ");
    for (int i=0;i<2*n0-1;i++)
        printf("%3d",ht[i].rchild);
    printf("\n");
}


void DispHCode(int n0)						//输出哈夫曼编码，n0是叶子结点数
{
    for (int i=0;i<n0;i++)
    	cout << "  " << ht[i].data << ":" << hcd[i] << endl;
    cout<< endl;
}


int main(){
    int n0 = 6;
    char s1[6] = {'a','b','c','d','e','f'};
    double num[6] = {5,9,12,13,16,45};
    CreateHT(s1, num, n0);
    DispHT(n0);
    CreateHCode(n0);
    DispHCode(n0);
}
/**
输入：
4
a,b,c,d
1,3,5,7
输出：
(1)建立哈夫曼树
(2)输出哈夫曼树
  i        0  1  2  3  4  5  6
  D[i]     a  b  c  d      `
  W[i]     1  3  5  7  4  9 16
  parent   4  4  5  6  5  6 -1
  lchild  -1 -1 -1 -1  0  4  3
  rchild  -1 -1 -1 -1  1  2  5
(3)建立哈夫曼编码
(4)输出哈夫曼编码
  a:100
  b:101
  c:11
  d:0

输入：
6
a,b,c,d,e,f
5,9,12,13,16,45
输出：
(1)建立哈夫曼树
(2)输出哈夫曼树
  i        0  1  2  3  4  5  6  7  8  9 10
  D[i]     a  b  c  d  e  f          `
  W[i]     5  9 12 13 16 45 14 25 30 55100
  parent   6  6  7  7  8 10  8  9  9 10 -1
  lchild  -1 -1 -1 -1 -1 -1  0  2  6  7  5
  rchild  -1 -1 -1 -1 -1 -1  1  3  4  8  9
(3)建立哈夫曼编码
(4)输出哈夫曼编码
  a:1100
  b:1101
  c:100
  d:101
  e:111
  f:0
  */

