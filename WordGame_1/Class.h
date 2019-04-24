#pragma once
#include<iostream>
#include<string>

using namespace std;

const int MAX_USER_NUMBER = 1024;

/*类定义*/
//基类：人
class person
{
public:
	person();
	~person();

	void setbasicinfo(string, string);
	virtual void Showinfo()=0;
	virtual void Play()=0;

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