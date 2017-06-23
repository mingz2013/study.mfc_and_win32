#include <wsnwlink.h>
 #include <winsock.h>
 #include <wsipx.h>
 #include <stdio.h>
 
int main()
 {
    WORD wVersionRequested = MAKEWORD(1, 1);
    WSADATA wsaData;
    if (WSAStartup(wVersionRequested, &wsaData)) {
       printf("WSAStartup failed %s\n", WSAGetLastError());
       return -1;
    }
 
   char hostname[256];
    int res = gethostname(hostname, sizeof(hostname));
    if (res != 0) {
       printf("Error: %u\n", WSAGetLastError());
       return -1;
    }
    printf("hostname=%s\n", hostname);
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
  
    WSACleanup();
    return 0;
 } 