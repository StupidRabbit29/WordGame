#pragma once
#include <Winsock2.h>
#include <mstcpip.h>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<windows.h>
#include<time.h>
#include<algorithm>
#include <process.h>

using namespace std;

enum playertype{ PLAYER, QUESTIONER };

#define PORT           51500    //端口号
#define MSGSIZE        1024     //最大数据长度
#define MAX_CLIENT     10       //最大客户端口数

// tcp keepalive结构体
typedef struct tcp_keepalive TCP_KEEPALIVE;

/*类定义*/
//基类：人
class person
{
public:
	person(const string& name, const string& password);
	person(const string&, const string&, int, int, int);
	virtual ~person();//虚析构函数

	void setbasicinfo(const string& name, const string& password);
	virtual void setID()=0;
	virtual void Play(struct MySoc * MsClient)=0;

	int Getlevel();
	int Getrank();
	int GetID();
	string Getname();
	string Getpassword();
	void Setlevel(int level);
	void Setrank(int rank);

	int FriendsNum();
	void addfriend(int ID);
	virtual void Showfriends()=0;
	string SFriendID();
protected:

	virtual void Showinfo(struct info& tempinfo);
	int ID;	
	vector<int>friends;
private:

	string name;
	string password;
	int level;
	int rank;
};

//闯关者类
class player :public person
{
public:
	player(const string& name, const string& password);
	player(const string&, const string&, int, int, int, int, int);
	virtual ~player();

	virtual void Showinfo(struct info& tempinfo)override;
	virtual void Play(struct MySoc * MsClient)override;
	virtual void setID()override;
	
	void SetEXP(int EXP);
	void Setround(int round);
	int GetEXP();
	int Getround();

	virtual void Showfriends()override;
private:
	int EXP;
	int round;
};

//出题者类定义
class questioner :public person
{
public:
	questioner(const string& name, const string& password);
	questioner(const string&, const string&, int, int, int, int);
	virtual ~questioner();

	virtual void Showinfo(struct info& tempinfo)override;
	virtual void Play(struct MySoc * MsClient)override;
	virtual void setID()override;

	void SetQnum(int Q);
	int GetQnum();

	virtual void Showfriends()override;
private:
	int Qnum;
};

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

typedef struct MySoc
{
	SOCKET sClient;
	SOCKADDR_IN ClientAddr;
	int iaddrSize;
	int TrdNum;
	vector<player>::iterator itp;
	vector<questioner>::iterator itq;
	int PlayerID;
	int QuestionerID;
}MySoc;


typedef struct game
{
	char word[30];
	bool right;
	int inter;
	int sleeptime;
	int i;
	int wordnum;
}Game;

void GameControl(MySoc * MsClient);
void Sign_up(playertype type, MySoc * MsClient);
void Sign_in(playertype type, MySoc * MsClient);
void Sign_out(playertype type, MySoc * MsClient);
bool samename(playertype type, const string& name);
void setpersonID(person* p);
bool findUser(string name, vector<player>::iterator& temp);
bool findUser(string name, vector<questioner>::iterator& temp);
bool findUser(int ID, vector<player>::iterator& temp);
bool findUser(int ID, vector<questioner>::iterator& temp);
bool checkpw(string password, person* user);
void WriteUserfile(vector<player>::iterator temp);
void WriteUserfile(vector<questioner>::iterator temp);
void ReadUserfile();
void UserControl(playertype type, MySoc * MsClient);
string GetWord(int hard, int num, int allnum);
bool GoodWord(int& length, char *word);
void Rank(playertype type, MySoc * MsClient);
bool cmp(player& a, player& b);
bool cmp1(player& a, player& b);
bool cmq(questioner& a, questioner& b);
void RefreshUser(const int ID, playertype type, MySoc * MsClient);
void ShowRank(MySoc * MsClient);
void Search(MySoc * MsClient);
void Findlevel(int level, playertype type, MySoc *MsClient);
void Findrank(int rank, playertype type, MySoc *MsClient);
void FindEXP(int EXP, MySoc *MsClient);
void Findround(int round, MySoc *MsClient);
void FindQnum(int Qnum, MySoc *MsClient);
void AddFriends(person* user, playertype type);
bool SameWord(int diff, char *word);
void VS(MySoc * MsClient1, MySoc * MsClient2);


unsigned __stdcall TrdController(void* pArguments);
unsigned __stdcall MySocketThread(void* pArguments);
bool Full(bool *p, int size);
int GetEmptyTrd(bool *p, int size);

