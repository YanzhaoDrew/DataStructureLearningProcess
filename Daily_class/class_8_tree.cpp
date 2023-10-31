#include <iostream>
#include<stack>
using namespace std;
struct BTNode									//二叉链中结点类型
{
	char data;									//数据元素
	BTNode *lchild;								//指向左孩子结点
	BTNode *rchild;								//指向右孩子结点
	BTNode()									//构造函数 
	{
		lchild=rchild=NULL;
	}
	BTNode(char d)								//重载构造函数 
	{
		data=d;
		lchild=rchild=NULL;
	}
};
class BTree										//二叉树类
{
public:											//为了简单，所有成员设计为公有属性 
	BTNode *r;									//二叉树的根结点r
	//二叉树的基本运算
	BTree()										//构造函数,建立一棵空树
	{
		r=NULL;
	}
	~BTree()									//析构函数
	{
		DestroyBTree(r);						//调用DestroyBTree()函数
		r=NULL;
		cout << "销毁二叉树\n";						//释放根结点

	}
	void DestroyBTree(BTNode *b)						//释放所有的结点空间 firstly后序遍历
	{
		if (b == NULL) return;
        else {
            DestroyBTree(b->lchild);
            DestroyBTree(b->rchild);
            delete b;
        }
	}

    /**
     * @brief CreateBTree
     * @param str
     * @details
     * 1. 用栈来实现
     * 2. 用递归来实现
     * 整体思路为：利用栈来存储结点，遇到左括号入栈，遇到右括号出栈，遇到逗号标记左右子树
     */
	void CreateBTree(string str)				//创建以r为根结点的二叉链存储结构 secondly stack
	{
		//借助栈来实现
        //A(B(D(,G)),C(E,F)) #输入的字符串
        //创建二叉树
        stack<BTNode *> s;
        //根结点
        BTNode *p = NULL;
        //标记什么时候是左子树，什么时候是右子树
        int k = 0;
        //遍历字符串
        for (int i = 0; i < str.length(); i++){
            char ch = str[i];
            //判断字符
            switch (ch){
                //左括号，入栈,并且标记左子树,再将p置空
                case '(': s.push(p);p=NULL; k = 1; break;
                //右括号，出栈
                case ')': s.pop(); break;
                //逗号，标记右子树
                case ',': k = 2; break;
                //其他字符，创建结点,并且判断根结点是否为空。
                //为空时，将p置为根结点，否则根据k值的不同将p插入到栈顶结点的左右子树中
                default:
                    p = new BTNode(ch);
                    if (r == NULL) r = p;
                    else {
                        BTNode *t = s.top();
                        if (k == 1) t->lchild = p;
                        else t->rchild = p;
                    }
            }
        }

	}
	void DispBTree()							//将二叉链转换成括号表示法
	{
		DispBTree1(r);
	}
	void DispBTree1(BTNode *b)					//被DispBTree函数调用
	{
		//输出二叉树bt:A(B(D(,G)),C(E,F))
        if (b == NULL) return;
        else {
            cout << b->data;
            //递归输出左右子树
            if (b->lchild != NULL || b->rchild != NULL){
                cout << "(";
                DispBTree1(b->lchild);
                if (b->rchild != NULL) cout << ",";
                DispBTree1(b->rchild);
                cout << ")";
            }
        }

	}
	BTNode *FindNode(char x)					//查找值为x的结点算法
	{
		return FindNode1(r,x);
	}
	BTNode *FindNode1(BTNode *b,char x)			//被FindNode函数调用
	{   
        //b为空时返回NULL
        if (b == NULL) return NULL;
        //b所指结点值为x时返回t
        else if (b->data == x) return b;
        else {
            BTNode *p = FindNode1(b->lchild, x);
            if (p != NULL) return p;
            else return FindNode1(b->rchild, x);
        }
	}
	int Height()								//求二叉树高度的算法
	{
		return Height1(r);
	}
	int Height1(BTNode *b)						//被Height函数调用
	{
		//空树的高度为0
        if (b == NULL) return 0;
        else {
            return max(Height1(b->lchild), Height1(b->rchild)) + 1;
        }
	}
};
int main(){
    BTree b;
    // string a = "A(B(D(,G)),C(E,F))";
    string a = "1(2(4),3)";
    b.CreateBTree(a);
    b.DispBTree();
    cout << b.Height();
    if (b.FindNode1(b.r, '3') != NULL) cout << b.FindNode1(b.r, '3')->data;
    else cout << "False";
    return 0;
}
/**
输入：
A(B(D(,G)),C(E,F)) #输入的字符串
E   #要查找的节点

输出：
二叉树bt:A(B(D(,G)),C(E,F))
bt的高度:4
bt中找到值为E的结点
销毁二叉树 

=================================
输入：
1(2(4),3)
8

输出：
二叉树bt:1(2(4),3)
bt的高度:3
bt中没有找到值为8的结点
销毁二叉树
*/

