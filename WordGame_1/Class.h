#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

const int MAX_USER_NUMBER = 1024;
bool DEBUG = true;
enum playertype{ PLAYER, QUESTIONER };

/*�ඨ��*/
//���ࣺ��
class person
{
public:
	person();//Ĭ�Ϲ��캯��
	person(const string& name, const string& password);
	virtual ~person();//����������

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

//��������
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

//�������ඨ��
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