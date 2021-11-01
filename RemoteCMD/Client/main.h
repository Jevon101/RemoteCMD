#pragma once

#include <stdio.h>
#include <Winsock2.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")



BOOL PipeCmd(char* pszCmd, char* pszResultBuffer, DWORD dwResultBufferSize);
BOOL ConnectionPrepare(const char* IPAddress, int Port);
void SendMsg(char* pszSend);
void RecvMsg();
char* returnRevc();
UINT RecvThreadProc(LPVOID lpVoid);