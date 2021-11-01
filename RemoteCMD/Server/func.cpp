#include "main.h"


SOCKET ServerSocket;
SOCKET ClientSocket;


BOOL SocketPrepare(const char* IPAddress, int iPort)
{

	WSADATA wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == ServerSocket)
	{
		return FALSE;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(iPort);
	addr.sin_addr.S_un.S_addr = inet_addr(IPAddress);

	if (0 != bind(ServerSocket, (sockaddr*)(&addr), sizeof(addr)))
	{
		return FALSE;
	}

	if (0 != listen(ServerSocket, 1))
	{
		return FALSE;
	}

	//如果不创建子线程，程序准备阶段会一直处于接受的死循环中
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)RecvThreadProc, NULL, NULL, NULL);

	return TRUE;
}


void SendMsg(char* pszSend)
{
	send(ClientSocket, pszSend, (1 + lstrlen(pszSend)), 0);
}



void AcceptRecvMsg()
{
	sockaddr_in addr = { 0 };

	int iLen = sizeof(addr);

	ClientSocket = accept(ServerSocket, (sockaddr*)(&addr), &iLen);
	printf("Successful reception of client messages!\n");
	printf("Please enter the CMD command:\n");

	char szBuf[MAX_PATH] = { 0 };
	while (TRUE)
	{
		// 接收数据
		int iRet = recv(ClientSocket, szBuf, MAX_PATH, 0);
		if (0 >= iRet)
		{
			continue;
		}
		printf("【RECV】%s\n", szBuf);
	}
}


// 子线程接收数据
UINT RecvThreadProc(LPVOID lpVoid)
{
	AcceptRecvMsg();
	return 0;
}

