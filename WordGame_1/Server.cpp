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
	//��ȡ�ĵ���������Ϸ
	ReadUserfile();

	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		return 0;
	}

	//�����׽���
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sListen == INVALID_SOCKET)
	{
		cout << "socket error!" << endl;
		return 0;
	}

	//��IP�Ͷ˿�
	SOCKADDR_IN local;
	local.sin_family = AF_INET;
	local.sin_port = htons(PORT);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sListen, (struct sockaddr *) &local, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		//	socket		�󶨸�socket�ĵ�ַ�����ص�ַ��  ��ַ�ĳ���
	{
		cout << "bind error!" << endl;
	}

	if (listen(sListen, MAX_CLIENT) == SOCKET_ERROR)
		//����sListen   sListen�������Ŷӵ���������
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

			const char* echo = "��������æ�����Ժ����ԣ�";
			send(MsClient->sClient, echo, strlen(echo), 0);

			closesocket(MsClient->sClient);
			delete MsClient;

			cout << "��������æ��" << endl;
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
			//�ж��û��߳��Ƿ��Ѿ��˳�
			if (socTrd_USE[i] == true && socTrd_CLOSE[i] == true)
			{
				cout << "�ѽ��һ��HANDLE��ռ��" << endl;
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

	//�������Ĳ����趨
	TCP_KEEPALIVE inKeepAlive = { 0, 0, 0 };
	unsigned long ulInLen = sizeof(TCP_KEEPALIVE);
	TCP_KEEPALIVE outKeepAlive = { 0, 0, 0 };
	unsigned long ulOutLen = sizeof(TCP_KEEPALIVE);
	unsigned long ulBytesReturn = 0;

	// ������������
	inKeepAlive.onoff = 1;                  // �Ƿ�����
	inKeepAlive.keepalivetime = 3000;       // ��tcpͨ������1000����� ��ʼ�������������
	inKeepAlive.keepaliveinterval = 500;    // �������ļ��ʱ����500����

											/*
											���������"������������"��
											��û�н��յ������������󣬶��ڲ�ͬ��Windows�汾���ͻ��˵��������Դ����ǲ�ͬ�ģ�
											���磬 ����Win XP/2003����, ����Դ�����5�Σ� ������Windows�汾Ҳ������ͬ��
											��Ȼ���� �������Linux�ϣ� ��ô�������Դ�ʱ��ʵ�ǿ����ڳ��������õġ�
											*/

											// ���ýӿڣ� ������������
	WSAIoctl(((MySoc*)pArguments)->sClient, SIO_KEEPALIVE_VALS,
		&inKeepAlive, ulInLen,
		&outKeepAlive, ulOutLen,
		&ulBytesReturn, NULL, NULL);
	
	//������Ϸ
	GameControl((MySoc*)pArguments);

	const char *sendData = "Server quit!";
	send(((MySoc*)pArguments)->sClient, sendData, strlen(sendData), 0);

	cout << "ɾ��" << inet_ntoa(((MySoc*)pArguments)->ClientAddr.sin_addr) << ":"
		<< ntohs(((MySoc*)pArguments)->ClientAddr.sin_port) << "��������socket" << endl;
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