#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<windows.h>
#include<time.h>

using namespace std;

enum playertype{ PLAYER, QUESTIONER };

/*�ඨ��*/
//���ࣺ��
class person
{
public:
	person(const string& name, const string& password);
	person(const string&, const string&, int, int, int);
	virtual ~person();//����������

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
protected:
	virtual void Showinfo();
	int ID;

private:

	string name;
	string password;
	int level;
	int rank;
};

//��������
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
private:
	int EXP;
	int round;
};

//�������ඨ��
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
bool checkpw(string password, person* user);
void WriteUserfile(vector<player>::iterator temp);
void WriteUserfile(vector<questioner>::iterator temp);
void ReadUserfile();
void UserControl(person* user);
string GetWord(int hard, int num, int allnum);
bool GoodWord(int choice, char *word);
