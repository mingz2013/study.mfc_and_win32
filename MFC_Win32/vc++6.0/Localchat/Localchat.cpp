// Localchat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"WS2_32.lib")

#define BUF_SIZE 1024   // ��������С
#define PORT 27015     // �����˿�
#define GROUPADDR "224.0.0.1" // �鲥��ַ
#define MARK "lc" // ������ʼ�����ַ�



char GroupAddr[] = GROUPADDR;

SOCKET Socket;  // �����׽���
sockaddr_in RecvAddr; // Զ�˷�������ַ�����ڽ�������
int RecvAddrSize; // ���صĴ�С��
sockaddr_in SendAddr; // Զ�˷�������ַ�����ڷ�������
//int RecvAddrSize = sizeof(RecvAddr);
sockaddr_in ServAddr; // ���ط�������ַ,���ڰ󶨱���ip
char LocalIP[15]; // ����ip
char hostname[256]; // ��������
char SendIP[15]; // ����ip
char buf[BUF_SIZE]; // ������
int iResult; // �������
char AddrList[100][32]; // �����б�
char localstate[4] ;// ����״̬ lgin(����) lout(����) chat(������)  
HANDLE hThreadRecv; // �����߳� 



// �������ݸ�ʽ
// "lc"+�����ĸ��ֽ�+���ݲ���
// �����ĸ��ֽڣ�asks(��������),  agre(ͬ������)��deny(�ܾ�����)��quit(�˳�����)��msgs(��������)��
// lgin(��������)��lout(��������)��olin(��������);
// ���ݲ���




void sendmsg(char ip[],char buf[BUF_SIZE])
{
	char buf2[BUF_SIZE] = MARK;
	strcat(buf2,buf);
	printf("���͵���Ϣ��%s\n",buf2);
	
	SendAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	
	sendto(Socket,buf2,sizeof(buf2),0,(SOCKADDR*)&SendAddr,sizeof(SendAddr));
	
}


void chat(char ip[])
{//��ʼ����
	void quitchat(char ip[]);
	// ��ʼ��
	strcpy(localstate,"chat");
	//localstate = "chat";
	system("cls");
	system("color 34");
	system("mode con:cols=50 lines=30");
	char title[50];
	sprintf(title,"%s %s","title chating with",ip);
	system(title);
	
	char msg[BUF_SIZE];
	
	
	while(true)
	{
		ZeroMemory(msg,BUF_SIZE);
		printf("\n**<@>:");
		gets(msg);
		
		char msgs[BUF_SIZE];
		sprintf(msgs,"%s%s","msgs",msg);
		
		if(strcmp(msg,"quit") == 0)
		{
			quitchat(ip);
			break;
		}
		else if(strcmp(msg,"") == 0)
		{
			// ����Ϊ��
			continue;
		}
		else
		{
			char msgs[BUF_SIZE];
			sprintf(msgs,"%s%s","msgs",msg);
			sendmsg(ip,msgs);
			continue;
			
		}
		
		
		
	}
	return;
	
	
}
void denychat(char ip[])
{// �ܾ�����
	char msg[] = "deny"; 
	sendmsg(ip,msg);
	return;
	
}
void agrechat(char ip[])
{//ͬ������
	char msg[BUF_SIZE] = "agre";
	sendmsg(ip,msg);
	chat(ip);
}

void doasks(char ip[])
{//������������
	void doasks(char ip[]);
	
	
	printf("%s ��Ҫ�������죬ͬ��ظ�y/Y,��ͬ��ظ�n/N\r\n",ip);
	char yesno ;
	scanf("%c",&yesno);
	switch(yesno)
	{
	case'n':
	case'N':denychat(ip);break;
	case'y':
	case'Y':agrechat(ip);break;
	default:
		printf("������������������\n");
		doasks(ip);
	}
	return;
	
	
}
void doquit(char ip[])
{// �����˳�����
	//void help();
	//closesocket();
	//char msg[] = "quit";
	//	sendmsg(SendIP,msg);
	//localstate = "login";
	strcpy(localstate,"lgin");
	ZeroMemory(SendIP,15);
	printf("%s���˳������������\n",ip);
	char ch;
	getchar(ch);
	/*
	system("mode con:cols=80 lines=40"); 
	system("cls");
	printf("{{{{{{{{{{{{{{{{{����������}}}}}}}}}}}}}}}}}\n\n");
	help();
	*/
	return ;
	
}






// ������յ�������
void dobuf(char buf[BUF_SIZE],sockaddr_in RecvAddr)
{
	
	//������յ�������
	char str1[30];
	
	ZeroMemory(str1,30);
	strncpy(str1,buf,2);
	if(strcmp(str1,MARK) == 0)
	{  // ����Ч����
		char TempIP[15];
		strcpy(TempIP,inet_ntoa(RecvAddr.sin_addr));
		if(RecvAddr.sin_addr.S_un.S_addr == inet_addr(GroupAddr))
		{ // ��ר�ù㲥��ַ
			ZeroMemory(str1,30);
			strncpy(str1,buf+2,4); // ��buf4�������ַ����Ƶ�str1��
			if(strcmp(str1,"lgin") == 0)
			{// ���û�����join.....,,,ȡ����ip���������������б����㲥�Լ�����
				ZeroMemory(str1,30);
				strncpy(str1,buf+6,24); // ȡ����6���ַ��Ժ�ģ��ӵ������ʼ
				strcpy(AddrList[sizeof(AddrList)],str1);// �����������б�
				// �򿪷��������㲥����
				printf("������������������..\n");
				char olin[30] = "olin";
				strcat(olin,LocalIP);  
				//sendto(Socket,ipjoin,14,0,(SOCKADDR*)&RecvAddr,RecvAddrSize);
				sendmsg(GroupAddr,olin);
				return;
			}
			else if(strcmp(str1,"lout") == 0)
			{// �������˳�.........�����б���Ѱ�Ҹ�ip�����ҵ���ɾ�����Ҳ�������������
				ZeroMemory(str1,30);
				strncpy(str1,buf+6,24); // ȡ�����ĸ��ַ��Ժ�ģ��ӵ������ʼ
				int j = -1;
				for(int i = 0;i < sizeof(AddrList) ;i++)
				{
					if(strcmp(str1,AddrList[i]) == 0)// �ҵ�����
					{
						j = i;
						break;
						
					}
					
				}
				if(j > -1)
				{
					for(i = j + 1;i < sizeof(AddrList) + 1;i++)
					{
						ZeroMemory(AddrList[i - 1],30);
						strcpy(AddrList[i - 1],AddrList[i]);
						
					}
					
				}
				return;
				
				
				
			}
			else if(strcmp(str1,"olin") == 0)
			{// ���������ߣ������б����û�У������
				ZeroMemory(str1,30);
				strncpy(str1,buf+6,24); // ȡ����6���ַ��Ժ�ģ��ӵ������ʼ
				int j = -1;
				for(int i = 0;i < sizeof(AddrList) ;i++)
				{
					if(strcmp(str1,AddrList[i]) == 0)// �ҵ�����
					{
						j = i;
						break;
						
					}
					
				}
				if(j = -1) // û�ҵ�
				{
					strcpy(AddrList[sizeof(AddrList)],str1);// �����������б�
					return;
				}
				return;
			}
			else
			{ // ������Ч�����������
				return;
			}
			return;
			
		}
		else
		{// ����ר�ù㲥��ַ�����û�����
			strcmp(SendIP,TempIP);
			
			ZeroMemory(str1,30);
			strncpy(str1,buf+2,4); // ��buf4�������ַ����Ƶ�str1��
			if(strcmp(str1,"asks") == 0)
			{// ��������
				doasks(TempIP);
				return;
			}
			else if(strcmp(str1,"agre") == 0)
			{//�Է� ͬ������
				chat(TempIP);
				return;
			}
			else if(strcmp(str1,"deny") == 0)
			{// �Է��ܾ�����
				printf("--%s �ܾ��������������� \n",TempIP);
				return;
			}
			else if(strcmp(str1,"quit") == 0)
			{// �Է��˳���������
				doquit(TempIP);
				return;
			}
			else if(strcmp(str1,"msgs") == 0)
			{// ��������
				printf("���յ�����������---%s---\n",buf);
				char buf3[BUF_SIZE] ;
				ZeroMemory(buf3,BUF_SIZE);
				strncpy(buf3,buf+6,BUF_SIZE - 6); 
				printf("�ӵ�����%s����Ϣ��%s\n",TempIP,buf3);
				return;
			}
			else
			{// ���������������
				return;
				
			}
			return ;
		}
		return;
	}
	else
	{// ������Ч����,��������
		return ;
	}
	return;
}

DWORD WINAPI receive(LPVOID lpParameter)
{// ��������
	DWORD WINAPI receive(LPVOID lpParameter);
	// ����recvfrom() �����ڰ󶨵�Socket�Ͻ�������
	printf("����������ݺ���.....\n");
	
	RecvAddr.sin_addr.S_un.S_addr = inet_addr("");; // Զ�˷�������ַ�����ڽ�������
	RecvAddrSize = sizeof(RecvAddr); // ���صĴ�С��
	printf("�����ַ�ȴ���������.....\n");
	
	recvfrom(Socket,buf,BUF_SIZE,0,(SOCKADDR*)&RecvAddr,&RecvAddrSize);//MSG_WAITALL �����������������ǽ��ղ������ݾ͵ȴ�
	printf("�ȴ���������....���ܵ������ݣ�-----%s----.\n",buf);
	
	// ��������
	dobuf(buf,RecvAddr);
	printf("���������ݣ�.....\r\n");
	receive(lpParameter);
	return 0;
	
}

int login()
{
	// ��ʼ��WS2_32.dll
	WSADATA wsaData; // WSADATA���������ڳ�ʼ��Windows Socket
	WORD sockVersion = MAKEWORD(2,2);
	iResult = ::WSAStartup(sockVersion,&wsaData);
	if(iResult != NO_ERROR)
	{
		printf("Error at WSAStartup \n");
	}
	
	
	
	// ����UDP Socket
	Socket = ::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(Socket == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		::WSACleanup();
		return -1;
	}
	
        // �õ�������----------------------------------------����
	printf("��ȡ������������������\n");
	
	int res = gethostname(hostname, sizeof(hostname));
	if (res != 0) {
		printf("Error: %u\n", WSAGetLastError());
		return -1;
	}
	printf("hostname=%s\n", hostname);
	/*/ ��ñ���ip
	hostent* pHostent = gethostbyname(hostname);
	if (pHostent==NULL) {
	printf("Error: %u\n", WSAGetLastError());
	return -1;
	}
	hostent& he = *pHostent;
	printf("name=%s\naliases=%s\naddrtype=%d\nlength=%d\n",
	he.h_name, he.h_aliases, he.h_addrtype, he.h_length);
	sockaddr_in sa;
	for (int nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++) {
	memcpy ( &sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
	
	  printf("Address: %s\n", inet_ntoa(sa.sin_addr)); 
	  }
	*/
	//----------------------------------------------------------------;;;;	
	// ��ñ���ip
	
	hostent* host = gethostbyname("");
	char* IP = inet_ntoa(*(struct in_addr*)*(host->h_addr_list)); 
	sprintf(LocalIP,"%s",IP); // �ϲ��ַ����� ip ��
	printf("-----%s-------\n",LocalIP);
	
	
	
	
	// �󶨱��ض˿�
	
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(PORT);
	ServAddr.sin_addr.S_un.S_addr = inet_addr(LocalIP);
	iResult = bind(Socket,(SOCKADDR*)&ServAddr,sizeof(ServAddr));
	if(iResult == SOCKET_ERROR)
	{
		printf("bind failed \n");
		closesocket(Socket);
		return -1;
	}
	printf("�󶨱��ض˿ڳɹ�\n");
	
	// �������ڽ��յĵ�ַ  
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(PORT);
	//RecvAddr.sin_addr.S_un.S_addr = inet_addr(GroupAddr);
	
	// �������ڷ��͵ĵ�ַ  
	SendAddr.sin_family = AF_INET;
	SendAddr.sin_port = htons(PORT);
	// �򿪷��������㲥����
	printf("Sending 'localchat.join' to GroupAddr.....\n");
	char join[30] = "lgin";
	
	strcat(join,LocalIP);  // ������ԭ������,δ���û�������С ����Ϊ30
	printf("�㲥����Ϣ��%s\n",join);
	//sendto(Socket,ipjoin,14,0,(SOCKADDR*)&RecvAddr,RecvAddrSize);
	sendmsg(GroupAddr,join);  
	
	//localstate = "login";
	strcpy(localstate,"lgin");
	printf("��ʼ�����....... \n");
	
	
	
	return 0;
	
}


void help()
{
	printf("|****************�����˵�****************8|\n");
	printf("|.help--��ʾ�����˵�                     8|\n");
	printf("|.list--��ʾ�����б�                     8|\n");
	printf("|.chat--��������                         8|\n");
	printf("|.quit--�˳�����                         8|\n");
	printf("|.exit--�˳�����                         8|\n");
	printf("|.login--��¼                            8|\n");
	printf("|.logout--�˳�                           8|\n");
	printf("|.mkroon--����������                     8|\n");
	printf("|.localip--�鿴������Ϣ                  8|\n");
	printf("|.login--��¼                            8|\n");
	printf("|.login--��¼                            8|\n");
	printf("|****************************************8|\n");
	return;
	
}
void showlist()
{
	int j;
	printf("|**************���������б�************8|\n");
	for(int i = 0;i < strlen(AddrList[100]) ;i++)
	{
		j = i - 1;
		printf("|%d.%s                           8|\n",i,AddrList[i]);
	}
	if(j < 0)
	{
		j = 0;
	}
	printf("|----------����������Ŀ��%d -------------8|\n",j);
	printf("|****************************************8|\n");
	
	return;
}




void logout()
{
	
	sendmsg(GroupAddr,"lout");
	CloseHandle(hThreadRecv); // ���ٽ������ݽ���
	closesocket(Socket);
	WSACleanup();
	//localstate = "logout";
	strcpy(localstate,"lout");
	printf("���˳���¼\n");
	return;
	
}

void dochat()
{// ��������
	char ip[15];
	printf("������Է�ip : ");
	//scanf("%s",&ip);
	gets(ip);
	char msg[] = "asks";
	sendmsg(ip,msg);
	printf("���������ѷ������ȴ��Է���Ӧ������\n");
	return;
}

void quitchat(char ip[])
{// �����˳�����
	//closesocket();
	char msg[] = "quit";
	sendmsg(ip,msg);
	//localstate = "login";
	strcpy(localstate,"lgin");
	ZeroMemory(SendIP,15);
	printf("�������˳�\n");
	/*
	system("mode con:cols=80 lines=40"); 
	system("cls");
	printf("{{{{{{{{{{{{{{{{{����������}}}}}}}}}}}}}}}}}\n\n");
	help();
	*/
	return ;
	
}
/*
void exitsy()
{
logout();
return;

  }	
*/

void docmd()
{
	while(true)
	{
		char cmd[10];
		printf(">>");
		//scanf("%s",&cmd);
		gets(cmd);
		//	printf("|--%s--|\n",cmd);
		
		if(strlen(cmd) == 0)
		{
			//printf(">>");
			continue;
		}
		else if(strcmp(cmd,"help") == 0)
		{
			help();
			continue;
		}
		else if(strcmp(cmd,"list") == 0)
		{
			if(strcmp(localstate,"lout") == 0)
			{
				printf("���ȵ�¼--\n");
			}
			else
			{
				showlist();
			}
			continue;
		}
		else if(strcmp(cmd,"chat") == 0)
		{
			if(strcmp(localstate,"lout") == 0)
			{
				printf("���ȵ�¼--\n");
			}
			else
			{
				dochat();
			}
			
			continue;
		}
		
		else if(strcmp(cmd,"quit") == 0)
		{
			if(strcpy(localstate,"chat") == 0)
			{
				quitchat(SendIP);// �˳�����
			}
			else
			{
				printf("��δ��������״̬\n");
			}
			continue;
		}
		
		else if(strcmp(cmd,"exit") == 0)
		{
			logout();
			break;
		}
		else if(strcmp(cmd,"login") == 0)
		{
			if(strcmp(localstate,"lout") == 0)
			{
				printf("����login���������\n");
				int i ;
				i = login();
				printf("login() ���ء���������\n");
				if(i == -1)
				{
					printf("login()ʧ�ܡ�����\n");
					continue;
				}
				else if(i == 0)
				{
					printf("��ʼ���ɹ�,login()����0\n");
				}
				
				printf("��ʼ�����߳�....... \n");
				
				
				DWORD dwThreadId;
				// ��������
				// receive();
				
				
				// ����һ���߳�
				hThreadRecv = ::CreateThread(
					NULL,// Ĭ�ϰ�ȫ����
					NULL,// Ĭ�϶�ջ��С
					receive,// �߳���ڵ�ַ��ִ���̵߳ĺ�����
					NULL,// ���ݸ������Ĳ���
					0,// ָ���߳���������
					&dwThreadId);// �����̵߳�ID��
				printf("Now another thread has been created. ID = %d \n",dwThreadId);
				/*/ �ȴ����߳����н���
				::WaitForSingleObject(hThread,INFINITE);
				::CloseHandle(hThreadRecv);
				*/
			}
			else
			{
				printf("���ѵ�¼�������ظ���¼");
			}
			continue;
			
		}
		else if(strcmp(cmd,"logout") == 0)
		{
			if(strcmp(localstate,"lout") == 0)
			{
				printf("�������� �������ظ�����\n");
			}
			else
			{
				logout();
			}
			continue;
		}
		else if(strcmp(cmd,"mkroom") == 0)
		{
			printf("�˹�����δ��ɣ���������������\n");
			help();
			continue;
		}
		else if(strcmp(cmd,"localip") == 0)
		{
			if(strcmp(localstate,"lout") == 0)
			{
				printf("�������ߣ����ȵ�¼\n");
			}
			else
			{
				printf("localip:%s \n",LocalIP);
			}
			continue;
		}
		else
		{
			printf("error cmd,you can take 'help'\n");
			help();
			continue;
			
		}
		
		
		
		}
		return;
}

void init()
{
	printf("���ڳ�ʼ��....... \n");
	
	
	// ���ô�����ʾ
	//system();// ִ��dos����
	system("title ����������----��������--QQ��xxx");
	system("color 5f");
	//	char setting[30]; 
	//	sprintf(setting,"mode con:cols=%d lines=%d",x,y); 
	system("mode con:cols=80 lines=40"); 
	system("cls");
	//localstate = "logout";
	strcpy(localstate,"lout");
	printf("{{{{{{{{{{{{{{{{{����������}}}}}}}}}}}}}}}}}\n\n");
	help();
	
	
	
	return ;
}

int main(int argc, char* argv[])
{
/*
void dobuf(char buf[BUF_SIZE],sockaddr_in RecvAddr);// ����buf
void help();       // ��������
void login();      // ��¼
void init()��// ��ʼ��
void docmd();  // ��������
void showlist(); // ��ʾ��������
void logout(); // �˳���¼
viod exitsy();

  void dowantchat(char ip[]);// ������������
  void nochat(char ip[]); // �ܾ�����
  void yeschat(char ip[]); // ͬ������
  void chat(char ip[]); // ��ʼ���죬��������
  void dochat();// ��������
  void quitchat();// �˳�����
  
    void sendmsg(char ip[],char buf[BUF_SIZE]); // ������Ϣ
    void receive(); // ��������
    
      
	*/
	
	
	init();// ��ʼ��
	//login();
	docmd();
	
	return 0;
	
}









