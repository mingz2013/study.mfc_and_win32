#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib,"WS2_32.lib")
int main()
{
 WSADATA data;
 WSAStartup(2,&data); 
hostent* host = gethostbyname("");
  char *IP = inet_ntoa(*(struct in_addr*)*(host->h_addr_list)); 
printf("Local IP:%s\n",IP);
  WSACleanup();
 return 0;
 } 