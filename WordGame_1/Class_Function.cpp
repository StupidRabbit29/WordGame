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

/*�޸Ķ����е���Ϣ*/
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
	//���õȼ�
	this->level = level;
}
void person::Setrank(int rank)
{
	//��������
	this->rank = rank;
}
//player
void player::setID()
{
	//����ID
	ID = Player.size();
}
void player::SetEXP(int EXP)
{
	//���þ���
	this->EXP = EXP;
}
void player::Setround(int round)
{
	//���ô�����
	this->round = round;
}
//questioner
void questioner::setID()
{
	//����ID
	ID = Questioner.size();
}
void questioner::SetQnum(int Q)
{
	//���ó�����
	this->Qnum = Q;
}


/*3����Ϣ�����������Ϸ�ߺͳ����˵���Ϣ�����������û���Ϣ���*/
//�û���Ϣ���
void person::Showinfo(struct info& tempinfo)
{
	if (DEBUG)
		cout << "person::Showinfo" << endl;

	strncpy_s(tempinfo.name, name.c_str(), 29);
	tempinfo.level = level;
	tempinfo.rank = rank;
}
//��Ϸ�ߵ���Ϣ���
void player::Showinfo(struct info& tempinfo)
{
	if (DEBUG)
		cout << "player::Showinfo" << endl;

	person::Showinfo(tempinfo);

	tempinfo.type = PLAYER;
	tempinfo.EXP = EXP;
	tempinfo.round = round;
}
//�����˵���Ϣ���
void questioner::Showinfo(struct info& tempinfo)
{
	if (DEBUG)
		cout << "questioner::Showinfo" << endl;

	person::Showinfo(tempinfo);

	tempinfo.type = QUESTIONER;
	tempinfo.Qnum = Qnum;
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

/*FRIEND*/
int person::FriendsNum()
{
	return friends.size();
}
//��Ӻ���
void person::addfriend(int ID)
{
	bool exist = false;
	for (auto it = friends.begin(); it != friends.end(); it++)
		if ((*it) == ID)
			exist = true;

	if (!exist)
		friends.push_back(ID);
	else
		cout << "Ta�Ѿ������ĺ���" << endl;
}
//�������б�ת�����ַ���
string person::SFriendID()
{
	char Friend[30];
	stringstream ss;

	for (auto it = friends.begin(); it != friends.end(); it++)
		ss << *it << ' ';

	ss.getline(Friend, sizeof(Friend));	
	return Friend;
}
//��ʾ�����б�
void player::Showfriends()
{
	if (FriendsNum() > 0)
	{
		cout << "����Ȧ��" << endl;
		for (auto it = friends.begin(); it != friends.end(); )
		{
			vector<player>::iterator temp;
			if (findUser(*it, temp))
			{
				Info tempinfo;
				//��ӡ������Ϣ
				(*temp).Showinfo(tempinfo);
				it++;
			}
			else
			{
				it = friends.erase(it);
			}
		}
	}
	else
	{
		cout << "����û�к���" << endl;
	}
}
//��ʾ�����б�
void questioner::Showfriends()
{
	if (FriendsNum() > 0)
	{
		cout << "����Ȧ��" << endl;
		for (auto it = friends.begin(); it != friends.end(); )
		{
			vector<questioner>::iterator temp;
			if (findUser(*it, temp))
			{
				Info tempinfo;
				//��ӡ������Ϣ
				(*temp).Showinfo(tempinfo);
				it++;
			}
			else
			{
				it = friends.erase(it);
			}
		}
	}
	else
	{
		cout << "����û�к���" << endl;
	}
}
