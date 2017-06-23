// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<winsock2.h>
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")
struct shuju{ 
	
	char str; 
	
	int  data; 
	
}; 

struct treenode{   
	
	char c;   
	
	int w;     
	
	int f;  
	
	int l;      
	
	int r;     
	
}; 

void sort(shuju a[],int num) { 
	
	int i,j; 
	
	shuju  t; 
	
	for(i=0;i<num;i++){    
		
		
		
		int m=i;             
		
		for(j=i+1;j<num;j++) 
			
			if(a[j].data<a[m].data) 
				
				m=j; 
			
			t=a[m]; 
			
			a[m]=a[i]; 
			
			a[i]=t; 
			
	} 
	
} 

void huffman(shuju a[],treenode htree[],int num) 

{ 
	
	int i,j,k,n; 
	
	for(i=0; i<num; i++){    
		
		htree[i].c=a[i].str; 
		
		htree[i].w=a[i].data; 
		
		htree[i].l=-1; 
		
		htree[i].f=-1; 
		
		htree[i].r=-1; 
		
	} 
	
	j=0;    
	
	k=num;    
	for(n=num;n<2*num-1;n++) 
		
		htree[n].w=0; 
	
	for(n=num;n<2*num-1;n++){   
		
		int r=0,s=0; 
		
		htree[n].l=-1; 
		
		htree[n].f=-1; 
		
		htree[n].r=-1;  
		
		while(r<2){ 
			
			if((htree[k].w==0 || htree[k].w>htree[j].w) && j<num){ 
				
				s=s+htree[j].w;   
				
				if(r==0) htree[n].l = j;  
				
				else htree[n].r=j;   
				
				htree[j].f=n;    
				
				j++; 
				
			} 
			
			else{    
				
				s=s+htree[k].w;   
				
				if(r==0) htree[n].l = k;  
				
				else htree[n].r=k; 
				
				htree[k].f=n; 
				
				k++; 
				
			}  
			
			r++; 
			
		} 
		
		htree[n].w=s;   
		
	} 
	
} 

int getcode(int i, int str[],treenode htree[]){   
	
	int n,l=0; 
	
	for(n=i;htree[n].f!=-1;n=htree[n].f){ 
		
		int m=htree[n].f; 
		
		if(n==htree[m].l) 
			
			str[l++]=0;   
		
		else 
			
			str[l++]=1;   
		
	} 
	
	return l; 
	
} 


int main(int argc, char* argv[])
{
	// ��ʼ��WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2,0);
	::WSAStartup(sockVersion,&wsaData);
	// ����TCP Socket
	SOCKET s = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		::WSACleanup();
		return 0;
	}
	// ���sockaddr_in �ṹ
	sockaddr_in sin;
	sin.sin_family = AF_INET;
        // �˿�
	int port;
	printf("������󶨵ı��ض˿ں�:");
	scanf("%d",&port);
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	// ������׽��ֵ�һ�����ص�ַ
	if(::bind(s,(LPSOCKADDR)&sin,sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Failed bind() \n");
		::WSACleanup();
		return 0;
	}
	// �л�������״̬
	if(::listen(s,2) == SOCKET_ERROR)
	{
		printf("Failed listen()");
		return 0;
	}
	printf("������� %d �˿ڼ����С�����\n\n",port);
	
	
	SOCKET client; // ִ��accept()���½�����������ͨ�ŵ��׽���
	sockaddr_in remoteAddr; // ���ڽ��ս����ַ
        int len = sizeof(remoteAddr);
	// �ȴ����ս�������
	client = ::accept(s,(SOCKADDR*)&remoteAddr,&len);
	if(client == INVALID_SOCKET)
	{
		printf("Failed accept()"); // ��ӡ�������
		return 0;
	}
	else
	{
		printf(" �ӵ����ӣ� %s : %d \r\n",inet_ntoa(remoteAddr.sin_addr),remoteAddr.sin_port); // ��ӡ�����ַ
	}
	printf("������Ҫ���͵���Ϣ��");
	char szText[256];
	char b[256];
	scanf("%s",&b);
	printf("����hanfuman���룺");
        // �����Ľ��б���
	int str[256],i,j,k,l; 
	
	FILE *fp; 
	
	treenode htree[57];    
	
	shuju a[29];  
	
	/*	printf("���������ĵĳ���n:"); 
	
	  scanf("%d",&n); 
	  
	    printf("���������ģ�"); 
	    
	      for(i=0;i<=n;i++) 
	      
		scanf("%c",&b[i]); 
	*/		
	//	fp=fopen("D:\\hanfuman\\shuju.txt","r"); 
	fp=fopen("shuju.txt","r"); 
	for( i=0;i<29;i++) 
		
	{ 
		
		fscanf(fp,"%c%d\n",&a[i].str,&a[i].data); 
		
	} 
	
	fclose(fp); 
	
	sort(a,29); 
	
	huffman(a,htree,29); 
	
	printf("��������ǣ�"); 
	for(i=0;i<=strlen(szText);i++) 
		
	{ 
		for(j=0;j<29;j++) 
			
		{ 
			
			if(b[i]==a[j].str) 
				
			{ 
				
				l=getcode(j,str,htree); 
				
				
				
				for(k=l-1;k>=0;k--) 
				{
				//	szText[k] = str[k];
					printf("%d",str[k]);
				}
				
			} 
			
		} 
	}
	printf("\n");

//	::send(client,str,l,0);
	::send(client,szText,strlen(szText),0);
	// �ر�ͬ�ͻ��˵�����
	::closesocket(client);
	// �رռ����׽���
	::closesocket(s);
	// �ͷ�WS2_32��
	::WSACleanup();
	return 0;
}
