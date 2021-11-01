#include "main.h"

int main()
{
	char ipaddr[20];
	char szCmd[512];
	char szResultBuffer[4096] = { 0 };
	DWORD dwResultBufferSize = 4096;
	int port;
	printf("请输入本机ip和所开端口,例如192.168.0.1 8888\n");
	scanf("%s %d", ipaddr, &port);

	if (FALSE == SocketPrepare(ipaddr, port))
	{
		printf("SocketPrepare Error,Error code: %d\n", WSAGetLastError());
		getchar();
		return -1;
	}
	printf("\nSocketPrepare OK\n");
	getchar();


	char szSendBuf[MAX_PATH] = { 0 };
	while (TRUE)
	{
		gets_s(szSendBuf);
		SendMsg(szSendBuf);
		ZeroMemory(szSendBuf, sizeof(szSendBuf));
	}

	return 0;
}