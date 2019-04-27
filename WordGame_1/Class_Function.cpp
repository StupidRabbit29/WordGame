#include"Class.h"

extern vector<player>Player;
extern vector<questioner>Questioner;

/*constructor*/
//person
person::person(const string& name, const string& password)
{
	if (DEBUG)
		cout << "Two arguments constructor of person called" << endl;

	setbasicinfo(name, password);
}
//player
player::player(const string& name, const string& password)
	:person(name, password)
{
	if (DEBUG)
		cout << "Two arguments constructor of player called" << endl;
}
//questioner
questioner::questioner(const string& name, const string& password)
	:person(name, password)
{
	if (DEBUG)
		cout << "Two arguments constructor of questioner called" << endl;
}

/*destructor*/
//person
person::~person()
{
	if (DEBUG)
		cout << "Destructor of person called" << endl;
}



void person::setbasicinfo(const string& name, const string& password)
{
	if (DEBUG)
		cout << "person::setbasicinfo\n";
	
	//�����û������û�����
	this->name = name;
	this->password = password;
}

void player::setID()
{
	ID = Player.size();
}

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