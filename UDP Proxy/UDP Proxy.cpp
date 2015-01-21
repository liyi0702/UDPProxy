#include<iostream>
#include<Winsock2.h>
#pragma comment(lib,"WS2_32")

#define BUF_SIZE 65535

using namespace std;

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
 
    wVersionRequested = MAKEWORD(1, 1);
 
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return 0;
    }
 
    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
        WSACleanup();
        return 0; 
    }

    SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
    
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    
    SOCKET sockCli = socket(AF_INET, SOCK_DGRAM, 0);
    SOCKADDR_IN addrCli;
	  addrCli.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    addrCli.sin_family = AF_INET;
    addrCli.sin_port = htons(6000);
    
    bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    
    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
    char recvBuf[BUF_SIZE];
	
  	char *buffer = new char[BUF_SIZE];
  	strcpy(buffer, "hello123123113");
	
    sendto(sockCli, buffer, strlen(buffer) + 1, 0, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    
    while(1) { 
	    recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
	    cout << recvBuf << endl;
	    
	    sendto(sockCli, recvBuf, strlen(recvBuf) + 1, 0, (SOCKADDR*)&addrCli, sizeof(SOCKADDR));
	}	
	
    closesocket(sockSrv);
    WSACleanup();
    //system("pause");
}


