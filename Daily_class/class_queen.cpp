//递归方法求解n皇后问题
#include <iostream>
#define N 20
using namespace std;
int n;//皇后总数n
int sum=0;//n皇后问题的摆法


/*-------------代码开始----------------*/
//自行定义并实现函数，用于求解N皇后问题	
int queen_pos[N];
bool displace(int i, int j){
	if (i == 1) return true; //first queen could be accept
	int k = 1;
	while (k < i){
		if (queen_pos[k] == j || abs(queen_pos[k] - j) == abs(i-k)) return false;
		k++;
	}
	return true;
}

void queen_prob(int i, int n){
	if (i > n) {
		sum++;
		return;
	}
	else {
		for (int j = 1; j <= n; j++)
			if (displace(i, j)){
				queen_pos[i] = j;
				queen_prob(i + 1, n);
			}
	}
}
/*-------------代码结束----------------*/


int main(){	
	cin>>n;
	/*-------------代码开始----------------*/
	//在此处调用用于求解n皇后问题的函数
	//用全局变量sum保存n皇后问题的摆法
	queen_prob(1, n);
	/*-------------代码结束----------------*/
	cout<<sum<<endl;
	return 0;
}