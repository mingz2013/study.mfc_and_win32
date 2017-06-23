/*ħ����8����С��ͬ������ɣ��ֱ���Ϳ�ϲ�ͬ��ɫ����1��8�����ֱ�ʾ��

���ʼ״̬��
 1 2 3 4
 8 7 6 5
��ħ��ɽ������ֻ���������
A�����������л�������
	8 7 6 5
	1 2 3 4
B������ÿ������ѭ������һ������
	  4 1 2 3
	  5 8 7 6
C�������м���С��˳ʱ��תһ�񣩣�
	1 7 2 4
	8 6 3 5
	���������ֻ����������ɽ���һ��״̬װ������һ��״̬�� 
	Input
	����������Ҫ����ħ�壬ÿ��ħ������������
	��һ�в���N��������10������������ʾ�������Ĳ�����
									  
	�ڶ��������б�ʾĿ��״̬������ħ�����״����ɫ��1��8�ı�ʾ��
										
	 ��N����-1��ʱ�򣬱�ʾ��������� 
										  
											
	  Output
	����ÿһ��Ҫ����ħ�壬���һ�С�
												  
	������һ������M����ʾ���ҵ��������Ҫ�Ĳ�����
	�������ɸ��ո�֮�󣬴ӵ�һ����ʼ��˳�����M��������ÿһ����A��B��C����������������֮��û���κοո�
													
	  ע�⣺������ܴﵽ����M���-1���ɡ� 
													  
														
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
	  1 A   ���֣�M����N���߸����Ĳ�������ȷ�����ܵ÷֡�   
	 OK����������Ļ�����Ҫ�ڹ涨�Ĳ������ҵ��Ƿ��ܷ���Ŀ��״̬��ħ�������
	 ��Ϊ�в��������ƣ���������ѡ����Ѷ��������ѣ����ѿ��ܿ����ҳ��𰸣�����ʱ�临�Ӷ�̫���ˡ�
	 ���ǾͰ�һ��ʼħ��Ŀ�ʼ״̬������У���3��ħ���������˵����ÿһ����ͷԪ�ض���3���������ѡ��
	 �������Ǿ����ζ���Щ״̬���м�⣬������У��ù��ѵ�˼���������𰸡�  
  �����и������������Ҫ��һ��visit[]�������ж�״̬�Ƿ��߹����������״̬��һ��ħ�壬������һ��������������Ҫ���������һ������
  �����Ļ������ǾͿ���ͨ��ʹ�ù�ϣ�����ķ�����ȷ��ÿ��״̬����Ӧ������
  sicily 1150��ħ������ݷ�Χ�����������ǿ��԰�ħ���״̬��string�������棬���翪ʼ״̬����Ϊstring s="12348765"��
  Ȼ����stl���map��������string������int����Ӧ����������߹�����map[s]=1��
  �������Ǿ���ʹ��map�������䵱��visit��������á�  
�������£�*/
#include <iostream>
#include <queue> 
#include <cstring> 
#include <string> 
#include <map>  
using namespace std; 
int n; 
string target; 
map<string,int> m;   //�䵱visit������ 

struct graph 
{     
	string s;   //ħ���״̬ 
	string ans;  //�������ַ���
};   //ÿ��״̬�Ľṹ 
void change(graph g,graph& next,int ope)    //��������
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
void bfs(graph g)   //����
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
/*sicily 1151ħ��Ļ������ݷ�ΧҪ��㣬���ʹ��stl��string��map��������״̬�ͽ���ϣ�Ļ��ᳬʱ��
�������������һ��С��ά����a[2][4]����ħ���״̬��Ȼ��ʹ�ÿ��к��������ع�ϣ��ַ��
���к���ֻ��Ҫʹ��8���Ŀռ䣬���˺ܺõ�ѹ�����á������ʹ��ħ��������������ϣ������runtime error�Ĵ���
����˼������sicily 1150��ࡣ*/
 /*/�������£�
#include <iostream> 
#include <string>
#include <cstring>
#include <queue> 
 using namespace std;
 int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};  //��������
 bool visit[50000]; 
 struct graph
 {  
 int Map[2][4];   //ħ��ͼ  
 string s;   //�������ַ���
 }target;   //ħ��״̬�ṹ 
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
 int cantor(int a[2][4]) //����״̬ѹ��
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
//��������
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
void bfs(graph g,int num)   //�����������
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