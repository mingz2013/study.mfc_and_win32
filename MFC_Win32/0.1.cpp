/*魔板由8个大小相同方块组成，分别用涂上不同颜色，用1到8的数字表示。

其初始状态是
 1 2 3 4
 8 7 6 5
对魔板可进行三种基本操作：
A操作（上下行互换）：
	8 7 6 5
	1 2 3 4
B操作（每次以行循环右移一个）：
	  4 1 2 3
	  5 8 7 6
C操作（中间四小块顺时针转一格）：
	1 7 2 4
	8 6 3 5
	用上述三种基本操作，可将任一种状态装换成另一种状态。 
	Input
	输入包括多个要求解的魔板，每个魔板用三行描述
	第一行步数N（不超过10的整数），表示最多容许的步数。
									  
	第二、第三行表示目标状态，按照魔板的形状，颜色用1到8的表示。
										
	 当N等于-1的时候，表示输入结束。 
										  
											
	  Output
	对于每一个要求解的魔板，输出一行。
												  
	首先是一个整数M，表示你找到解答所需要的步数。
	接着若干个空格之后，从第一步开始按顺序给出M步操作（每一步是A、B或C），相邻两个操作之间没有任何空格。
													
	  注意：如果不能达到，则M输出-1即可。 
													  
														
	  Sample Input	 
	  4 
	  5 8 7 6 
	  4 1 2 3 
	  3 
	  8 7 6 5  
	  1 2 3 4 
	  -1
	  Sample Output
	  2 AB  
	  1 A   评分：M超过N或者给出的操作不正确均不能得分。   
	 OK，看到这题的话，是要在规定的步数内找到是否能符合目标状态的魔板操作。
	 因为有步数的限制，所以我们选择广搜而不是深搜，深搜可能可以找出答案，但是时间复杂度太高了。
	 我们就把一开始魔板的开始状态打进队列，有3种魔板操作，则说明对每一个队头元素都有3种情况可以选择，
	 所以我们就依次对这些状态进行检测，打入队列，用广搜的思想最后算出答案。  
  这里有个处理就是搜索要有一个visit[]数组来判断状态是否走过，而这里的状态是一块魔板，而不是一个数，所以我们要把它翻译成一个数。
  这样的话，我们就可以通过使用哈希函数的方法来确定每个状态所对应的数。
  sicily 1150简单魔板的数据范围不大，所以我们可以把魔板的状态用string变量来存，比如开始状态设置为string s="12348765"。
  然后用stl里的map容器，将string变量和int个对应起来，如果走过，则map[s]=1。
  这样我们就是使用map容器来充当了visit数组的作用。  
代码如下：*/
#include <iostream>
#include <queue> 
#include <cstring> 
#include <string> 
#include <map>  
using namespace std; 
int n; 
string target; 
map<string,int> m;   //充当visit的作用 

struct graph 
{     
	string s;   //魔板的状态 
	string ans;  //操作的字符串
};   //每个状态的结构 
void change(graph g,graph& next,int ope)    //操作函数
{        
	if(ope==1)    
	{           
		for(int i=4;i<8;i++)     
			next.s+=g.s[i];    
		for(int i=0;i<4;i++)     
			next.s+=g.s[i];        
		next.ans=g.ans+'A';  
	}  
	else if(ope==2)  
	{             
		next.s="11111111";  
		next.s[0]=g.s[3];  
		next.s[4]=g.s[7];     
		for(int i=1;i<4;i++)       
			next.s[i]=g.s[i-1];   
		for(int i=5;i<8;i++)       
			next.s[i]=g.s[i-1];    
		next.ans=g.ans+'B';   
	}     
	else if(ope==3)  
	{            
		next.s="11111111"; 
		next.s[0]=g.s[0];next.s[3]=g.s[3];next.s[4]=g.s[4];next.s[7]=g.s[7];    
		next.s[1]=g.s[5];next.s[2]=g.s[1];next.s[6]=g.s[2];next.s[5]=g.s[6];    
		next.ans=g.ans+'C';   
	}
} 
void bfs(graph g)   //广搜
{      
	queue<graph> q;     
	q.push(g);   
	m[g.s]=1;  
	while(!q.empty())    
		
	{            
		graph temp=q.front();    
		q.pop();       
		if(temp.ans.size()>n)     
		{                   
			cout<<"-1"<<endl;     
			return ;          
		}          
		for(int i=1;i<4;i++)   
		{                 
			graph t_g;      
			change(temp,t_g,i);     
			if(t_g.s==target)     
			{                  
				cout<<t_g.ans.size()<<" "<<t_g.ans<<endl;     
				return ;         
			}                      
			if(m[t_g.s]!=1)              
			{                         
				m[t_g.s]=1;           
				q.push(t_g);             
			}      
		}     
	}
} 
int main() {   
	while(cin>>n && n!=-1)
	{              
		char temp;    
		m.clear();     
		graph g;         
		target="";           
		for(int i=0;i<8;i++)   
		{                   
			cin>>temp;      
			target+=temp;    
		}           
		g.s="12348765";     
		g.ans="";        
		bfs(g);     
	}     return 0; 
}  
/*sicily 1151魔板的话，数据范围要大点，如果使用stl的string和map容器来存状态和建哈希的话会超时。
所以最后还是用了一个小二维矩阵a[2][4]来存魔板的状态，然后使用康托函数来返回哈希地址。
康托函数只需要使用8！的空间，起到了很好的压缩作用。如果简单使用魔板里数的线性组合，会产生runtime error的错误。
其他思想啧和sicily 1150差不多。*/
 /*/代码如下：
#include <iostream> 
#include <string>
#include <cstring>
#include <queue> 
 using namespace std;
 int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};  //康托因子
 bool visit[50000]; 
 struct graph
 {  
 int Map[2][4];   //魔板图  
 string s;   //操作的字符串
 }target;   //魔板状态结构 
 bool if_same(graph gg)
 {   
	 bool flag=1;  
	 for(int i=0;i<2;i++)   
		 for(int j=0;j<4;j++)     
			 if(target.Map[i][j]!=gg.Map[i][j])     
			 {              
				 flag=0;      
				 break;      
			 }    
			 if(flag)    
				 return 1; 
			 else      
				 return 0;
 } 
 int cantor(int a[2][4]) //康托状态压缩
 {    
	 int rank,i,j,k=0; 
	 int t[8],num=1;   
	 for(i=0;i<2;i++)      
	 for(j=0;j<4;j++)         
		 t[k++]=a[i][j]; 
	 for(i=0;i<7;i++)  
	 {       
		 rank=0;   
		 for(j=i+1;j<8;j++) 
			 if(t[i]>t[j])   
				 rank++;      
			 num+=rank*fac[7 - i];  
	 }   
	 return num;
} 
void change(graph g,graph& next,int ope)  
//操作函数
{  
	
	if(ope==1)  
	{       
		for(int i=0;i<4;i++)   
		{             
			next.Map[1][i]=g.Map[0][i];    
			next.Map[0][i]=g.Map[1][i];   
		}      
		next.s=g.s+"A"; 
	}   
	else if(ope==2)   
	{       
		next.Map[0][0]=g.Map[0][3];   
		next.Map[1][0]=g.Map[1][3];   
		for(int i=1;i<4;i++)     
		{         
			next.Map[0][i]=g.Map[0][i-1]; 
			next.Map[1][i]=g.Map[1][i-1];   
		}               
		next.s=g.s+"B";  
	}    
	else if(ope==3)  
	{      
		next.Map[0][0]=g.Map[0][0];  
		next.Map[1][0]=g.Map[1][0];  
		next.Map[0][3]=g.Map[0][3];   
		next.Map[1][3]=g.Map[1][3];    
		next.Map[0][1]=g.Map[1][1];     
		next.Map[0][2]=g.Map[0][1];    
		next.Map[1][2]=g.Map[0][2];    
		next.Map[1][1]=g.Map[1][2];     
		next.s=g.s+"C";  
	}
} 
void bfs(graph g,int num)   //广度优先搜索
{    
	if(if_same(g))
    {     
		cout<<"0"<<endl; 
		return ;  
	}     
	queue<graph> q;  
	q.push(g);   
	visit[cantor(g.Map)]=1;   
	while(1) 
	{      
		graph t1=q.front();   
		q.pop();     
		if(t1.s.size()>=num)  
		{        
			cout<<"-1"<<endl;  
			return ; 
		}     
		for(int i=1;i<4;i++)
        {        
			graph t2;   
			change(t1,t2,i);   
			if(if_same(t2))   
			{          
				cout<<t2.s.size()<<" "<<t2.s<<endl;   
				return ;      
			}        
			if(!visit[cantor(t2.Map)])    
			{              
				visit[cantor(t2.Map)]=1;    
				q.push(t2);        
			}      
		}  
	}
} 
int main()
{   
	int n; 
    while(cin>>n && n!=-1)  
	{      
		memset(visit,0,sizeof(visit));  
		int count=1;  
		graph g;     
		for(int i=0;i<4;i++)   
		{        
			g.Map[0][i]=count;  
			count++;     
		}       
		for(int i=3;i>=0;i--)   
		{          
			g.Map[1][i]=count;   

count++;      
  }       
  for(int i=0;i<2;i++)  
	  for(int j=0;j<4;j++)    
		  cin>>target.Map[i][j];    
	  g.s="";     
	  bfs(g,n); 
   }   
   return 0;
}        
*/