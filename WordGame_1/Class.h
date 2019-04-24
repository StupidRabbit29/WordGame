#pragma once
#include<iostream>
#include<string>

using namespace std;

const int MAX_USER_NUMBER = 1024;

/*�ඨ��*/
//���ࣺ��
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

//��������
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

//�������ඨ��
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