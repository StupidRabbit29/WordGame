#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<windows.h>
#include<time.h>
#include<algorithm>

using namespace std;

enum playertype{ PLAYER, QUESTIONER };

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
	virtual void Play()=0;

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

	virtual void Showinfo();
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

	virtual void Showinfo()override;
	virtual void Play()override;
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

	virtual void Showinfo()override;
	virtual void Play()override;
	virtual void setID()override;

	void SetQnum(int Q);
	int GetQnum();

	virtual void Showfriends()override;
private:
	int Qnum;
};

void GameControl(void);
void Sign_up(playertype type);
void Sign_in(playertype type);
void Sign_out(playertype type);
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
void UserControl(person* user, playertype type);
string GetWord(int hard, int num, int allnum);
bool GoodWord(int& length, char *word);
void Rank(playertype type);
bool cmp(player& a, player& b);
bool cmq(questioner& a, questioner& b);
void RefreshUser(const int ID, playertype type);
void ShowRank();
void Search();
void Findlevel(int level, playertype type);
void Findrank(int rank, playertype type);
void FindEXP(int EXP);
void Findround(int round);
void FindQnum(int Qnum);
void AddFriends(person* user, playertype type);
