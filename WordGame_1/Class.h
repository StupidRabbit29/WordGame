#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

const int MAX_USER_NUMBER = 1024;
bool DEBUG = true;
enum playertype{ PLAYER, QUESTIONER };

/*类定义*/
//基类：人
class person
{
public:
	person();//默认构造函数
	person(const string& name, const string& password);
	virtual ~person();//虚析构函数

	void setbasicinfo(const string& name, const string& password);
	virtual void setID()=0;
	virtual void Play()=0;

	int Getlevel();
	int Getrank();
	int GetID();
	string Getname();
protected:
	virtual void Showinfo();
	int ID;

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
	player();
	player(const string& name, const string& password);
	~player();

	virtual void Showinfo()override;
	virtual void Play()override;
	virtual void setID()override;

	int GetEXP();
	int Getround();
private:
	int EXP;
	int round;
};

//出题者类定义
class questioner :public person
{
public:
	questioner();
	questioner(const string& name, const string& password);
	~questioner();

	virtual void Showinfo()override;
	virtual void Play()override;
	virtual void setID()override;

	int GetQnum();
private:
	int Qnum;
};