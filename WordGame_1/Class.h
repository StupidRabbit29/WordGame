#pragma once
#include<iostream>
#include<string>

using namespace std;

const int MAX_USER_NUMBER = 1024;
bool DEBUG = true;

/*类定义*/
//基类：人
class person
{
public:
	person();//默认构造函数
	virtual ~person();//虚析构函数

	void setbasicinfo(string, string);
	virtual void Play()=0;

protected:
	virtual void Showinfo();

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
	~player();

	virtual void Showinfo()override;
	virtual void Play()override;
	int ShowEXP();
	int Showround();
private:
	int EXP;
	int round;
};

//出题者类定义
class questioner :public person
{
public:
	questioner();
	~questioner();

	virtual void Showinfo()override;
	virtual void Play()override;
	int ShowQnum();
private:
	int Qnum;
};