#pragma once
#include<iostream>
#include<string>

using namespace std;

const int MAX_USER_NUMBER = 1024;
bool DEBUG = true;

/*�ඨ��*/
//���ࣺ��
class person
{
public:
	person();//Ĭ�Ϲ��캯��
	virtual ~person();//����������

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