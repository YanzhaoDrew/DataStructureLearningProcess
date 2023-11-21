#include<iostream>
#include<vector>
using namespace std;
/*
1.创建二叉搜索树，2.二叉搜索树的搜索算法，3.插入算法，4.删除算法。
*/

template <typename T1,typename T2>
struct BSTNode											//BST结点类模板 
{	T1 key;							        			//存放关键字,假设关键字为T1类型
    T2 data;                                 			//存放数据项,假设数据项为T2类型
    BSTNode *lchild;						   			//存放左孩子指针
    BSTNode *rchild;						   			//存放右孩子指针
    BSTNode(T1 k,T2 d)    								//构造方法
    {	key=k;
        data=d;
        lchild=rchild=NULL;
	}
};
template <typename T1,typename T2>
class BSTClass								  			//BST类
{
public:
	BSTNode<T1,T2> *r;  								//BST根结点
	BSTNode<T1,T2> *f;    								//用于存放待删除结点的双亲结点
    BSTClass()                             				//构造方法
    {	r=NULL;  						        		//BST根结点
        f=NULL;    						        		//用于存放待删除结点的双亲结点
	}
	~BSTClass()											//析构函数
	{
		DestroyBTree(r);								//调用DestroyBTree()函数
		r=NULL;
	}
	void DestroyBTree(BSTNode<T1,T2> *b)				//释放所有的结点空间
	{
		if (b!=NULL)
		{
			DestroyBTree(b->lchild);					//递归释放左子树
			DestroyBTree(b->rchild);					//递归释放右子树
			delete b;									//释放根结点
		}
	}
    //BST的基本运算算法
    void InsertBST(T1 k,T2 d)			    			//插入一个(k,d)结点
    {
	    r=_InsertBST(r,k,d);
	}

    BSTNode<T1,T2> *_InsertBST(BSTNode<T1,T2> *p,T1 k,T2 d)   //在以p为根的BST中插入关键字为k的结点
    {	
        if (p==NULL){
            p = new BSTNode<T1, T2>(k, d);
            return p;
        };//判断根节点是否为空
        BSTNode<T1, T2>* current = SearchBST(k);
        if (current != NULL) return p;
        else {
            BSTNode<T1, T2> *s= new BSTNode<T1,T2>(k, d);
            if (k > f->key){
                f->rchild = s;
            }else {
                f->lchild = s;
            }
        }
        return p;
        
	}

    void CreateBST(vector<T1> &a,vector<T2> &b)			
	//由a和b向量创建一棵BST，a为关键字集合，b为其他data集合
    {	
        this->r = NULL;
        //遍历a
        for (int i = 0; i < a.size(); i++){
            InsertBST(a[i], b[i]);
        }
	}
	BSTNode<T1,T2> *SearchBST(T1 k)		        		//在BST中查找关键字为k的结点
    {
	    return _SearchBST(r,k);							//r为BST的根结点
	}

	BSTNode<T1,T2> *_SearchBST(BSTNode<T1,T2> *p,T1 k) 	//被SearchBST方法调用
    {	//空树返回null
        //找到后返回p
        f = NULL;//作为父节点
        while(p != NULL){
            if (p->key == k) return p;
            else {
                f = p;
                if (k > p->key) p = p->rchild;
                else p = p->lchild;
            }
        }
        return p;
	}

    bool DeleteBST(T1 k)					        	//删除关键字为k的结点
    {	f=NULL;
        return _DeleteBST(r,k,-1);		    			//r为BST的根结点
	}

    bool _DeleteBST(BSTNode<T1,T2> *p,T1 k,int flag)  	//被DeleteBST方法调用
	//flag==-1为根
    //flag==0，p为f的左孩子
    //flag==1，p为f的右孩子
    {	if (p==NULL)
            return false;						    	//空树返回False
        if (p->key==k)
            return DeleteNode(p,f,flag);				//找到后删除p结点
        if (k<p->key)
		{	f=p;
            return _DeleteBST(p->lchild,k,0);			//在左子树中递归查找
        }
        else
		{	f=p;
            return _DeleteBST(p->rchild,k,1);			//在右子树中递归查找
        }
	}

    bool DeleteNode(BSTNode<T1,T2> *p,BSTNode<T1,T2> *f,int flag) //删除结点p（其双亲为f）
   //flag==-1为根，flag==0，p为f的左孩子，flag==1，p为f的右孩子
	{	
        BSTNode<T1,T2> *s;
        BSTNode<T1,T2> *pr;
        if (flag == -1){
            if (p->lchild == NULL && p->rchild == NULL){
                this->r = NULL;
                delete p;
                return true;
            }
            if (p->lchild != NULL && p->rchild != NULL){
                //选择接到右子树中序下第一个节点，以右子树为根节点
                // s = p->rchild;
                // this->r = s;
                // while (s->lchild != NULL){pr = s; s = s->lchild;}
                // s->lchild = p->lchild;
                // delete p;
                // return true;
                
                //选择左子树
                s = p->lchild;
                this->r = s;
                while (s->rchild){pr = s; s = s->rchild;}
                s->rchild = p->rchild;
                delete p;
                return true;
            }
            if (p->lchild == NULL){
                f = p;
                p = p->rchild;
                delete f;
                this->r = p;
                return true;
            }
            else{
                f = p;
                p = p->lchild;
                delete f;
                this->r = p;
                return true;
            }
            
        }
        else if (flag == 0){    
            if (p->lchild == NULL && p->rchild == NULL){f->lchild = NULL; delete p;return true;}
            if (p->lchild != NULL && p->rchild != NULL){
                s = p->lchild;
                pr = p;
                while(s->rchild!=NULL) {pr = s; s = s->rchild;} //到了Rightmost
                p->data = s->data;p->key = s->key;//Rightmost值是第二大的，所以用第二大的值替代删除节点
                if (s->lchild != NULL){pr->rchild = s->lchild;}
                else {pr->rchild = NULL; delete s;}
                return true;
            }
            if (p->lchild == NULL){
                s = p->rchild;
                f->lchild = s;
                delete p;
                return true;
            }else {
                s = p->lchild;
                f->lchild = s;
                delete p;
                return true;
            }
        }
        else {
            if (p->lchild == NULL && p->rchild == NULL){f->rchild = NULL; delete p;return true;}
            if (p->lchild != NULL && p->rchild != NULL){
                s = p->lchild;
                pr = p;
                while(s->rchild!=NULL) {pr = s; s = s->rchild;} //到了Rightmost
                p->data = s->data;p->key = s->key;//Rightmost值是第二大的，所以用第二大的值替代删除节点
                pr->rchild = NULL;
                if (s->lchild != NULL){pr->rchild = s->lchild;}
                else {pr->rchild = NULL; delete s;}
                return true;
            }
            if (p->lchild == NULL){
                s = p->rchild;
                f->rchild = s;
                delete p;
                return true;
            }else {
                s = p->lchild;
                f->rchild = s;
                delete p;
                return true;
            }
        }
        return true;
    }

    void DispBST()						        		//输出BST的括号表示串(不含data)
    {
	    _DispBST(r);
	}
    void  _DispBST(BSTNode<T1,T2> *p)           		//被DispBST方法调用
    {	if (p!=NULL)
    	{	cout << p->key;								//输出根结点值
            if (p->lchild!=NULL || p->rchild!=NULL)
            {	cout << "(";   			    			//有孩子结点时才输出"("
                _DispBST(p->lchild);			    	//递归处理左子树
                if (p->rchild!=NULL)
                    cout << ",";   		    			//有右孩子结点时才输出","
                _DispBST(p->rchild);			    	//递归处理右子树
                cout << ")";   			    			//有孩子结点时才输出")"
			}
		}
	}
 
};

int main(){
    vector<int> a = {25, 18, 46, 2, 53, 39, 32, 4, 74, 67, 60, 11};
    vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10 ,11, 12};
    BSTClass<int, int> bst;
    cout << "(1)关键字序列" << endl;
    for (int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "(2)创建BSTbst" << endl;
    bst.CreateBST(a, b);
    cout << "(3)输出BST" << endl;
    bst.DispBST();
    cout << endl;
    cout << "(4)删除操作" << endl;
    cout << "删除 2后: ";
    bst.DeleteBST(2);
    bst.DispBST();
    cout << endl;
    cout << "删除 4后: ";
    bst.DeleteBST(4);
    bst.DispBST();
    cout << endl;
    cout << "删除60后: ";
    bst.DeleteBST(60);
    bst.DispBST();
    cout << endl;
    cout << "删除25后:";
    bst.DeleteBST(25);
    bst.DispBST();
    cout << endl;
    cout << "删除32后:";
    bst.DeleteBST(32);
    bst.DispBST();
    cout << endl;
    return 0;
}
/*
预期输出
  (1)关键字序列
    25 18 46 2 53 39 32 4 74 67 60 11 
  (2)创建BSTbst
  (3)输出BST
    BST: 25(18(2(,4(,11))),46(39(32),53(,74(67(60)))))
  (4)删除操作
    删除 2后: 25(18(4(,11)),46(39(32),53(,74(67(60)))))
    删除 4后: 25(18(11),46(39(32),53(,74(67(60)))))
    删除60后: 25(18(11),46(39(32),53(,74(67))))
    删除25后: 18(11,46(39(32),53(,74(67))))
    删除32后: 18(11,46(39,53(,74(67))))
    删除11后: 18(,46(39,53(,74(67))))
  (5)插入操作
    插入32后: 18(,46(39(32),53(,74(67))))
    插入11后: 18(11,46(39(32),53(,74(67))))
    插入 1后: 18(11(1),46(39(32),53(,74(67))))
    */
