#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WINSOCK2.H>  
#include <mstcpip.h>
#include <iostream> 
#include <string>
#include <ctime>

//���������ʹ�õĳ���      
#define SERVER_ADDRESS "10.122.193.42" //��������IP��ַ      
#define PORT           51500         //�������Ķ˿ں�      
#define MSGSIZE        1024         //�շ��������Ĵ�С     

#pragma comment(lib, "ws2_32.lib") 

enum playertype { PLAYER, QUESTIONER };

typedef struct game
{
	char word[30];
	bool right;
	int inter;
	int sleeptime;
	int i;
	int wordnum;
}Game;

typedef struct info
{
	char name[30];
	int level;
	int rank;
	playertype type;
	int EXP;
	int round;
	int Qnum;
}Info;

typedef struct tcp_keepalive TCP_KEEPALIVE;

bool PlayerGame(SOCKET& sclient);
void QuestionerGame(SOCKET& sclient);
void PrintInfo(Info& tempinfo);

using namespace std;
int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket!");
		return 0;
	}

	//Զ�̷������ĵ�ַ��Ϣ
	SOCKADDR_IN serAddr;
	memset(&serAddr, 0, sizeof(SOCKADDR_IN));
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(PORT);
	serAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		//		�ͻ���socket   �������˵ĵ�ַ   ��ַ����
	{  //����ʧ�� 
		printf("connect error !");
		closesocket(sclient);
		return 0;
	}

	bool bOptVal = true;
	int bOptLen = sizeof(bool);

	setsockopt(sclient, SOL_SOCKET, SO_KEEPALIVE, (char*)&bOptVal, bOptLen);
	
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
	WSAIoctl(sclient, SIO_KEEPALIVE_VALS,
		&inKeepAlive, ulInLen,
		&outKeepAlive, ulOutLen,
		&ulBytesReturn, NULL, NULL);
	
	cout << "��ͻ������ӳɹ���" << endl;

	bool quit = false;

	char recData[MSGSIZE+1];
	int ret = recv(sclient, recData, MSGSIZE, 0);
	if (ret>0)
	{
		recData[ret] = '\0';
		cout << recData << endl;
	}

	if (strcmp(recData, "Server quit!") == 0 || strcmp(recData, "��������æ�����Ժ����ԣ�") == 0)
	{
		cout << "�ͻ����˳�" << endl;
		quit = true;
	}
	bool jump = false;
	
	while (!quit)
	{
		if (!jump)
		{
			cout << "Send:";
			char data[100] = { '\0' };
			while (!(cin.getline(data, 100, '\n') && data[0] != '\0'))
			{
				cin.clear();
				if (data[0] != '\0')
					cin.ignore(100, '\n');
				memset(data, 0, sizeof(data));
			}
			send(sclient, data, strlen(data), 0);
		}
		
		jump = false;
		//send()������������ָ����socket�����Է�����
		//int send(int s, const void * msg, int len, unsigned int flags)
		//sΪ�ѽ��������ӵ�socket��msgָ���������ݣ�len��Ϊ���ݳ��ȣ�����flagsһ����0
		//�ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����error 

		char recData[MSGSIZE+1];
		int ret = recv(sclient, recData, MSGSIZE, 0);
		if (ret>0)
		{
			recData[ret] = '\0';

			if (strcmp(recData, "BeginToSendRankTable") != 0)
				cout << recData << endl;
		}

		if (strcmp(recData, "Server quit!") == 0 || strcmp(recData, "��������æ�����Ժ����ԣ�") == 0)
		{
			quit = true;
			cout << "�ͻ����˳�" << endl;
			Sleep(2000);
		}

		if (strcmp(recData, "�ѽ��봳������Ϸ�������������ַ��Կ�ʼ��Ϸ��") == 0)
		{
			string temp;
			cin >> temp;
			send(sclient, temp.c_str(), temp.length(), 0);
			jump = true;

			while(jump)
				jump = PlayerGame(sclient);

			char temprecv[MSGSIZE] = { '\0' };
			recv(sclient, temprecv, MSGSIZE, 0);
			cout << temprecv << endl;
		}
		
		if (strcmp(recData, "�ѽ����������Ϸ�������������ַ��Կ�ʼ��Ϸ��") == 0)
		{
			string temp;
			cin >> temp;
			send(sclient, temp.c_str(), temp.length(), 0);

			QuestionerGame(sclient);

			jump = true;
		}

		if (strcmp(recData, "BeginToSendRankTable") == 0)
		{
			char temp[MSGSIZE] = { '\0' };
			while (true)
			{
				recv(sclient, temp, MSGSIZE, 0);

				if (strcmp(temp, "BeginToShowInfo") == 0)
				{
					Info tempinfo;
					recv(sclient, (char*)&tempinfo, MSGSIZE, 0);
					PrintInfo(tempinfo);
				}
				else if (strcmp(temp, "SendRankTableEND") == 0)
					break;
				else
					cout << temp << endl;

				memset(temp, 0, sizeof(temp));
			}

			jump = true;
		}

		if (strcmp(recData, "��ʼ˫�˶�ս��") == 0)
		{
			string temp;
			cin >> temp;
			send(sclient, temp.c_str(), temp.length(), 0);
			jump = true;

			while (jump)
				jump = PlayerGame(sclient);

			char temprecv[MSGSIZE] = { '\0' };
			recv(sclient, temprecv, MSGSIZE, 0);
			cout << temprecv << endl;
		}
	}

	closesocket(sclient);
	WSACleanup();
	return 0;
}

bool PlayerGame(SOCKET& sclient)
{
	Game temp;
	recv(sclient, (char*)&temp, sizeof(Game), 0);

	cout << "׼����\t";
	for (int j = 0; j < 5; j++)
	{
		Sleep(500);
		cout << (5 - j) << "\t";
	}
	//չʾ����
	cout << '\n' << temp.word;
	Sleep(temp.sleeptime);
	cout << "\r" << "���������Ĵ𰸣�                                \n";

	clock_t start, finish, interval;
	start = clock();
	//��ȡ�û�����
	string ans;
	cin >> ans;
	finish = clock();
	interval = finish - start;

	if (strcmp(ans.c_str(), temp.word) == 0)
	{
		if (temp.i<temp.wordnum - 1)
			cout << "����ȷ���ٽ����������ͣ�" << endl;
		
		temp.right = true;
		temp.inter = (interval / CLOCKS_PER_SEC);
	}
	else
	{
		temp.right = false;
		cout << "�𰸴�����Ϸ������" << endl;
	}

	send(sclient, (char*)&temp, sizeof(Game), 0);

	if (temp.right == false || temp.right == true && temp.i == temp.wordnum - 1)
		return false;
	else
		return true;
}

void QuestionerGame(SOCKET& sclient)
{
	char start[MSGSIZE+1] = { '\0' };
	recv(sclient, start, MSGSIZE, 0);
	cout << start << endl;

	bool quit = false;
	char word[100] = { '\0' };
	cin.ignore(100, '\n');
	while (!quit)
	{

		if (cin.getline(word, 99, '\n') && word[0] != '\0')
		{
			send(sclient, word, sizeof(word), 0);
			memset(word, 0, sizeof(word));
		}
		else
		{
			send(sclient, "QUITQUITQUITQUITQUITQUITQUITQUITQUITQUIT", MSGSIZE, 0);
			memset(word, 0, sizeof(word));
			quit = true;
		}

		char temp[MSGSIZE] = { '\0' };
		recv(sclient, temp, sizeof(temp), 0);

		if (strcmp(temp, "quit") == 0)
			quit = true;
		else if(strcmp(temp, "Go On")!=0)
			cout << temp << endl;
	}
}

void PrintInfo(Info& tempinfo)
{
	//��ӡ�û�������Ϣ
	cout.setf(ios_base::left, ios_base::adjustfield);

	cout.width(5);
	cout << "�û���:";
	cout.width(20);
	cout << tempinfo.name;

	cout.width(4);
	cout << "�ȼ�:";
	cout.width(5);
	cout << tempinfo.level;

	cout.width(4);
	cout << "����:";
	cout.width(5);
	cout << tempinfo.rank;

	cout.setf(ios_base::right, ios_base::adjustfield);

	if (tempinfo.type == PLAYER)
	{
		//��ӡ��Ϸ����Ϣ
		cout.setf(ios_base::left, ios_base::adjustfield);

		cout.width(5);
		cout << "����ֵ:";
		cout.width(6);
		cout << tempinfo.EXP;

		cout.width(7);
		cout << "�ɹ�������:";
		cout.width(3);
		cout << tempinfo.round;

		cout.setf(ios_base::right, ios_base::adjustfield);

		cout << endl;
	}
	else
	{
		//��ӡ��������Ϣ
		cout.setf(ios_base::left, ios_base::adjustfield);

		cout.width(5);
		cout << "������:";
		cout.width(5);
		cout << tempinfo.Qnum;

		cout.setf(ios_base::right, ios_base::adjustfield);

		cout << endl;
	}
	
}