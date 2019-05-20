#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include"Class.h"


#pragma comment(lib, "ws2_32.lib")

vector<player>Player;
vector<questioner>Questioner;

const int MAX_USER_NUMBER = 1024;
bool DEBUG = true;


HANDLE sockThread[MAX_CLIENT];
MySoc *TempBuffer[MAX_CLIENT] = { NULL };
bool socTrd_USE[MAX_CLIENT] = { false };
bool socTrd_CLOSE[MAX_CLIENT] = { true };

using namespace std;

int main()
{
	//读取文档，加载游戏
	ReadUserfile();

	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		return 0;
	}

	//创建套接字
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sListen == INVALID_SOCKET)
	{
		cout << "socket error!" << endl;
		return 0;
	}

	//绑定IP和端口
	SOCKADDR_IN local;
	local.sin_family = AF_INET;
	local.sin_port = htons(PORT);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sListen, (struct sockaddr *) &local, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		//	socket		绑定给socket的地址（本地地址）  地址的长度
	{
		cout << "bind error!" << endl;
	}

	if (listen(sListen, MAX_CLIENT) == SOCKET_ERROR)
		//监听sListen   sListen最大可以排队的连接数量
	{
		cout << "listen error!\n";
		return 0;
	}

	HANDLE Controller = (HANDLE)_beginthreadex(NULL, 0, TrdController, NULL, 0, NULL);

	while (true)
	{
		MySoc *MsClient = new MySoc;
		MsClient->iaddrSize = sizeof(SOCKADDR_IN);

		cout << "waiting for connect...\n";
		MsClient->sClient = accept(sListen, (struct sockaddr *) &(MsClient->ClientAddr), &(MsClient->iaddrSize));
		//Server socket      Client socket address    address size
		if (MsClient->sClient == INVALID_SOCKET)
		{
			cout << "accept error!\n";
			return 0;
		}

		cout << "Accept a connection:" << inet_ntoa(MsClient->ClientAddr.sin_addr) << ":"
			<< ntohs(MsClient->ClientAddr.sin_port) << endl;

		if (!Full(socTrd_USE, MAX_CLIENT))
		{
			int TrdNum = GetEmptyTrd(socTrd_USE, MAX_CLIENT);
			socTrd_USE[TrdNum] = true;
			socTrd_CLOSE[TrdNum] = false;
			TempBuffer[TrdNum] = MsClient;
			MsClient->TrdNum = TrdNum;
			sockThread[TrdNum] = (HANDLE)_beginthreadex(NULL, 0, MySocketThread, MsClient, 0, NULL);
		}
		else
		{
			char szMessage[MSGSIZE] = { '\0' };
			recv(MsClient->sClient, szMessage, sizeof(szMessage), 0);

			const char* echo = "服务器繁忙！请稍后重试！";
			send(MsClient->sClient, echo, strlen(echo), 0);

			closesocket(MsClient->sClient);
			delete MsClient;

			cout << "服务器繁忙！" << endl;
			Sleep(3000);
		}
	}

	WaitForSingleObject(Controller, INFINITE);
	CloseHandle(Controller);
	closesocket(sListen);
	WSACleanup();
	if (DEBUG)
		Sleep(10000);
	return 0;
}

unsigned __stdcall TrdController(void* pArguments)
{
	while (true)
	{
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			//判断用户线程是否已经退出
			if (socTrd_USE[i] == true && socTrd_CLOSE[i] == true)
			{
				cout << "已解除一个HANDLE的占用" << endl;
				socTrd_USE[i] = false;
				CloseHandle(sockThread[i]);
				delete TempBuffer[i];
				TempBuffer[i] = NULL;
			}
		}
		Sleep(3000);
	}

	_endthreadex(0);
	return 0;
}

unsigned __stdcall MySocketThread(void* pArguments)
{
	bool bOptVal = true;
	int bOptLen = sizeof(bool);

	if (setsockopt(((MySoc*)pArguments)->sClient, SOL_SOCKET, SO_KEEPALIVE, (char*)&bOptVal, bOptLen) == SOCKET_ERROR)
	{
		cout << "setsockopt error!\n";
	}
	else
	{
		cout << inet_ntoa(((MySoc*)pArguments)->ClientAddr.sin_addr) << ":"
			<< ntohs(((MySoc*)pArguments)->ClientAddr.sin_port) << "::" << "SO_KEEPALIVE is ON\n";
	}

	//心跳检测的参数设定
	TCP_KEEPALIVE inKeepAlive = { 0, 0, 0 };
	unsigned long ulInLen = sizeof(TCP_KEEPALIVE);
	TCP_KEEPALIVE outKeepAlive = { 0, 0, 0 };
	unsigned long ulOutLen = sizeof(TCP_KEEPALIVE);
	unsigned long ulBytesReturn = 0;

	// 设置心跳参数
	inKeepAlive.onoff = 1;                  // 是否启用
	inKeepAlive.keepalivetime = 3000;       // 在tcp通道空闲1000毫秒后， 开始发送心跳包检测
	inKeepAlive.keepaliveinterval = 500;    // 心跳包的间隔时间是500毫秒

											/*
											补充上面的"设置心跳参数"：
											当没有接收到服务器反馈后，对于不同的Windows版本，客户端的心跳尝试次数是不同的，
											比如， 对于Win XP/2003而言, 最大尝试次数是5次， 其它的Windows版本也各不相同。
											当然啦， 如果是在Linux上， 那么这个最大尝试此时其实是可以在程序中设置的。
											*/

											// 调用接口， 启用心跳机制
	WSAIoctl(((MySoc*)pArguments)->sClient, SIO_KEEPALIVE_VALS,
		&inKeepAlive, ulInLen,
		&outKeepAlive, ulOutLen,
		&ulBytesReturn, NULL, NULL);
	
	//进入游戏
	GameControl((MySoc*)pArguments);

	const char *sendData = "Server quit!";
	send(((MySoc*)pArguments)->sClient, sendData, strlen(sendData), 0);

	cout << "删除" << inet_ntoa(((MySoc*)pArguments)->ClientAddr.sin_addr) << ":"
		<< ntohs(((MySoc*)pArguments)->ClientAddr.sin_port) << "服务器端socket" << endl;
	if (socTrd_CLOSE[((MySoc*)pArguments)->TrdNum] == false)
		closesocket(((MySoc*)pArguments)->sClient);
	socTrd_CLOSE[((MySoc*)pArguments)->TrdNum] = true;
	//delete (MySoc*)pArguments;

	_endthreadex(0);
	return 0;
}

bool Full(bool *p, int size)
{
	for (int i = 0; i < size; i++)
		if (p[i] == false)
			return false;

	return true;
}

int GetEmptyTrd(bool *p, int size)
{
	int i = 0;
	for (; i < size; i++)
		if (p[i] == false)
			break;

	return i;
}