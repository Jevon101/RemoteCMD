#pragma once

#include <stdio.h>
#include <Winsock2.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")

BOOL SocketPrepare(const char* lpszIp, int iPort);
void SendMsg(char* pszSend);
void AcceptRecvMsg();
UINT RecvThreadProc(LPVOID lpVoid);