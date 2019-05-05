#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;

/*constructor*/
//person
person::person(const string& name, const string& password)
{
	if (DEBUG)
		cout << "Two arguments constructor of person" << ID << " called" << endl;

	setbasicinfo(name, password);
	ID = rank = 0;
	level = 1;
}
person::person(const string& name, const string& password, int ID, int level, int rank)
{
	if(DEBUG)
		cout << "Five arguments constructor of person" << ID << " called" << endl;

	setbasicinfo(name, password);
	this->ID = ID;
	this->rank = rank;
	this->level = level;
}
//player
player::player(const string& name, const string& password)
	:person(name, password)
{
	if (DEBUG)
		cout << "Two arguments constructor of player" << ID << " called" << endl;

	EXP = round = 0;
}
player::player(const string& name, const string& password, int ID, int level, int rank, int EXP, int round)
	:person(name, password, ID, level, rank)
{
	if (DEBUG)
		cout << "Seven arguments constructor of player" << ID << " called" << endl;

	this->EXP = EXP;
	this->round = round;
}
//questioner
questioner::questioner(const string& name, const string& password)
	:person(name, password)
{
	if (DEBUG)
		cout << "Two arguments constructor of questioner" << ID << " called" << endl;

	Qnum = 0;
}
questioner::questioner(const string& name, const string& password, int ID, int level, int rank, int Qnum)
	: person(name, password, ID, level, rank)
{
	if (DEBUG)
		cout << "Six arguments constructor of questioner" << ID << " called" << endl;

	this->Qnum = Qnum;
}


/*destructor*/
//person
person::~person()
{
	if (DEBUG)
		cout << "Destructor of person" << ID << " called" << endl;
}
//player
player::~player()
{
	if (DEBUG)
		cout << "Destructor of player" << ID << " called" << endl;
}
//questioner
questioner::~questioner()
{
	if (DEBUG)
		cout << "Destructor of questioner" << ID << " called" << endl;
}


//person
void person::setbasicinfo(const string& name, const string& password)
{
	if (DEBUG)
		cout << "person::setbasicinfo\n";
	
	//�����û������û�����
	this->name = name;
	this->password = password;
}
void person::Setlevel(int level)
{
	this->level = level;
}
void person::Setrank(int rank)
{
	this->rank = rank;
}
//player
void player::setID()
{
	ID = Player.size();
}
//questioner
void questioner::setID()
{
	ID = Questioner.size();
}


/*3����Ϣ�����������Ϸ�ߺͳ����˵���Ϣ�����������û���Ϣ���*/
//�û���Ϣ���
void person::Showinfo()
{
	if (DEBUG)
		cout << "person::Showinfo" << endl;

	//��ӡ�û�������Ϣ
	cout.setf(ios_base::left, ios_base::adjustfield);

	cout.width(5);
	cout << "�û���:";
	cout.width(20);
	cout << name;

	cout.width(4);
	cout << "�ȼ�:";
	cout.width(5);
	cout << level;

	cout.width(4);
	cout << "����:";
	cout.width(5);
	cout << rank;

	cout.setf(ios_base::right, ios_base::adjustfield);
}
//��Ϸ�ߵ���Ϣ���
void player::Showinfo()
{
	if (DEBUG)
		cout << "player::Showinfo" << endl;

	person::Showinfo();

	//��ӡ��Ϸ����Ϣ
	cout.setf(ios_base::left, ios_base::adjustfield);
	
	cout.width(5);
	cout << "����ֵ:";
	cout.width(6);
	cout << EXP;

	cout.width(7);
	cout << "�ɹ�������:";
	cout.width(3);
	cout << round;
	
	cout.setf(ios_base::right, ios_base::adjustfield);
	
	cout << endl;
}
//�����˵���Ϣ���
void questioner::Showinfo()
{
	if (DEBUG)
		cout << "questioner::Showinfo" << endl;

	person::Showinfo();

	//��ӡ��������Ϣ
	cout.setf(ios_base::left, ios_base::adjustfield);
	
	cout.width(5);
	cout << "������:";
	cout.width(5);
	cout << Qnum;
	
	cout.setf(ios_base::right, ios_base::adjustfield);
	
	cout << endl;
}


/*��ȡ��˽�С�������Ϣ�Ľӿڣ�ֻ��*/
//����
int person::Getlevel()
{
	return level;
}
int person::Getrank()
{
	return rank;
}
string person::Getname()
{
	return name;
}
string person::Getpassword()
{
	return password;
}
int person::GetID()
{
	return ID;
}
//������
int player::GetEXP()
{
	return EXP;
}
int player::Getround()
{
	return round;
}
//������
int questioner::GetQnum()
{
	return Qnum;
}

/*�޸Ķ����е���Ϣ*/
//����
//������
void player::SetEXP(int EXP)
{
	this->EXP = EXP;
}
void player::Setround(int round)
{
	this->round = round;
}
//������
void questioner::SetQnum(int Q)
{
	this->Qnum = Q;
}