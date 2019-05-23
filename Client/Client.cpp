#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WINSOCK2.H>  
#include <mstcpip.h>
#include <iostream> 
#include <string>
#include <ctime>

//定义程序中使用的常量      
#define SERVER_ADDRESS "10.122.193.42" //服务器端IP地址      
#define PORT           51500         //服务器的端口号      
#define MSGSIZE        1024         //收发缓冲区的大小     

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

	//远程服务器的地址信息
	SOCKADDR_IN serAddr;
	memset(&serAddr, 0, sizeof(SOCKADDR_IN));
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(PORT);
	serAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		//		客户端socket   服务器端的地址   地址长度
	{  //连接失败 
		printf("connect error !");
		closesocket(sclient);
		return 0;
	}

	bool bOptVal = true;
	int bOptLen = sizeof(bool);

	setsockopt(sclient, SOL_SOCKET, SO_KEEPALIVE, (char*)&bOptVal, bOptLen);
	
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
	WSAIoctl(sclient, SIO_KEEPALIVE_VALS,
		&inKeepAlive, ulInLen,
		&outKeepAlive, ulOutLen,
		&ulBytesReturn, NULL, NULL);
	
	cout << "与客户端连接成功！" << endl;

	bool quit = false;

	char recData[MSGSIZE+1];
	int ret = recv(sclient, recData, MSGSIZE, 0);
	if (ret>0)
	{
		recData[ret] = '\0';
		cout << recData << endl;
	}

	if (strcmp(recData, "Server quit!") == 0 || strcmp(recData, "服务器繁忙！请稍后重试！") == 0)
	{
		cout << "客户端退出" << endl;
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
		//send()用来将数据由指定的socket传给对方主机
		//int send(int s, const void * msg, int len, unsigned int flags)
		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 

		char recData[MSGSIZE+1];
		int ret = recv(sclient, recData, MSGSIZE, 0);
		if (ret>0)
		{
			recData[ret] = '\0';

			if (strcmp(recData, "BeginToSendRankTable") != 0)
				cout << recData << endl;
		}

		if (strcmp(recData, "Server quit!") == 0 || strcmp(recData, "服务器繁忙！请稍后重试！") == 0)
		{
			quit = true;
			cout << "客户端退出" << endl;
			Sleep(2000);
		}

		if (strcmp(recData, "已进入闯关者游戏，请输入任意字符以开始游戏！") == 0)
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
		
		if (strcmp(recData, "已进入出题者游戏，请输入任意字符以开始游戏！") == 0)
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

		if (strcmp(recData, "开始双人对战！") == 0)
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

	cout << "准备！\t";
	for (int j = 0; j < 5; j++)
	{
		Sleep(500);
		cout << (5 - j) << "\t";
	}
	//展示单词
	cout << '\n' << temp.word;
	Sleep(temp.sleeptime);
	cout << "\r" << "请输入您的答案：                                \n";

	clock_t start, finish, interval;
	start = clock();
	//读取用户输入
	string ans;
	cin >> ans;
	finish = clock();
	interval = finish - start;

	if (strcmp(ans.c_str(), temp.word) == 0)
	{
		if (temp.i<temp.wordnum - 1)
			cout << "答案正确，再接再厉，加油！" << endl;
		
		temp.right = true;
		temp.inter = (interval / CLOCKS_PER_SEC);
	}
	else
	{
		temp.right = false;
		cout << "答案错误，游戏结束！" << endl;
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
	//打印用户基本信息
	cout.setf(ios_base::left, ios_base::adjustfield);

	cout.width(5);
	cout << "用户名:";
	cout.width(20);
	cout << tempinfo.name;

	cout.width(4);
	cout << "等级:";
	cout.width(5);
	cout << tempinfo.level;

	cout.width(4);
	cout << "排名:";
	cout.width(5);
	cout << tempinfo.rank;

	cout.setf(ios_base::right, ios_base::adjustfield);

	if (tempinfo.type == PLAYER)
	{
		//打印游戏者信息
		cout.setf(ios_base::left, ios_base::adjustfield);

		cout.width(5);
		cout << "经验值:";
		cout.width(6);
		cout << tempinfo.EXP;

		cout.width(7);
		cout << "成功闯关数:";
		cout.width(3);
		cout << tempinfo.round;

		cout.setf(ios_base::right, ios_base::adjustfield);

		cout << endl;
	}
	else
	{
		//打印出题人信息
		cout.setf(ios_base::left, ios_base::adjustfield);

		cout.width(5);
		cout << "出题数:";
		cout.width(5);
		cout << tempinfo.Qnum;

		cout.setf(ios_base::right, ios_base::adjustfield);

		cout << endl;
	}
	
}