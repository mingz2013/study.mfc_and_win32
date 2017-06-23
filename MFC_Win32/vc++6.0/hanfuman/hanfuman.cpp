// hanfuman.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include<stdio.h> 

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

void decode(treenode htree[],int c[],int n,int num){ 
	
	int ch,m=0; 
	
	
	
	ch=c[m]; 
	
	while(m<n){   
		
		int i; 
		
		for(i=2*num-2;htree[i].l!=-1;){ 
			
			if(ch==0)     i=htree[i].l; 
			
			else 
				
				i=htree[i].r; 
			
			m++; 
			
			ch=c[m]; 
			
		} 
		
		printf("%c",htree[i].c); 
		
	}  
	
} 

void main() 

{ 
	
	int str[1000],i,j,k,l,n,c[1000]; 
	
	FILE *fp; 
	
	treenode htree[57];    
	
	shuju a[29]; 
	
	char b[100]; 
	
	printf("请输入明文的长度n:"); 
		
		scanf("%d",&n); 
	
	printf("请输入明文："); 
		
		for(i=0;i<=n;i++) 
			
			scanf("%c",&b[i]); 
		
	//	fp=fopen("D:\\hanfuman\\shuju.txt","r"); 
		fp=fopen("shuju.txt","r"); 
		for( i=0;i<29;i++) 
			
		{ 
			
			fscanf(fp,"%c%d\n",&a[i].str,&a[i].data); 
			
		} 
		
		fclose(fp); 
		
		sort(a,29); 
		
		huffman(a,htree,29); 
		
		printf("输出译码是："); 
			
			for(i=0;i<=n;i++) 
				
			{ 
				for(j=0;j<29;j++) 
					
				{ 
					
					if(b[i]==a[j].str) 
						
					{ 
						
						l=getcode(j,str,htree); 
						
						
						
						for(k=l-1;k>=0;k--) 
							
							printf("%d",str[k]); 
						
					} 
					
				} 
				
				
				
			} 
			
			printf("\n"); printf("请输入译码的长度："); 
				
				scanf("%d",&n); 
			
			printf("请输入译码："); 
				
				for(i=0;i<n;i++) 
					
					scanf("%d",&c[i]); 
				
				printf("输出解码为："); 
				decode(htree,c,n,29); 
				
				printf("\n"); 
				
} 
