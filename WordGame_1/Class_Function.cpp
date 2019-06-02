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

/*修改对象中的信息*/
//person
void person::setbasicinfo(const string& name, const string& password)
{
	if (DEBUG)
		cout << "person::setbasicinfo\n";
	
	//设置用户名和用户密码
	this->name = name;
	this->password = password;
}
void person::Setlevel(int level)
{
	//设置等级
	this->level = level;
}
void person::Setrank(int rank)
{
	//设置排名
	this->rank = rank;
}
//player
void player::setID()
{
	//设置ID
	ID = Player.size();
}
void player::SetEXP(int EXP)
{
	//设置经验
	this->EXP = EXP;
}
void player::Setround(int round)
{
	//设置闯关数
	this->round = round;
}
//questioner
void questioner::setID()
{
	//设置ID
	ID = Questioner.size();
}
void questioner::SetQnum(int Q)
{
	//设置出题数
	this->Qnum = Q;
}


/*3个信息输出函数，游戏者和出题人的信息输出均会调用用户信息输出*/
//用户信息输出
void person::Showinfo()
{
	if (DEBUG)
		cout << "person::Showinfo" << endl;

	//打印用户基本信息
	cout.setf(ios_base::left, ios_base::adjustfield);

	cout.width(5);
	cout << "用户名:";
	cout.width(20);
	cout << name;

	cout.width(4);
	cout << "等级:";
	cout.width(5);
	cout << level;

	cout.width(4);
	cout << "排名:";
	cout.width(5);
	cout << rank;

	cout.setf(ios_base::right, ios_base::adjustfield);
}
//游戏者的信息输出
void player::Showinfo()
{
	if (DEBUG)
		cout << "player::Showinfo" << endl;

	person::Showinfo();

	//打印游戏者信息
	cout.setf(ios_base::left, ios_base::adjustfield);

	cout.width(5);
	cout << "经验值:";
	cout.width(6);
	cout << EXP;

	cout.width(7);
	cout << "成功闯关数:";
	cout.width(3);
	cout << round;

	cout.setf(ios_base::right, ios_base::adjustfield);

	cout << endl;
}
//出题人的信息输出
void questioner::Showinfo()
{
	if (DEBUG)
		cout << "questioner::Showinfo" << endl;

	person::Showinfo();

	//打印出题人信息
	cout.setf(ios_base::left, ios_base::adjustfield);

	cout.width(5);
	cout << "出题数:";
	cout.width(5);
	cout << Qnum;

	cout.setf(ios_base::right, ios_base::adjustfield);

	cout << endl;
}

/*获取类私有、保护信息的接口，只读*/
//基类
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
//闯关者
int player::GetEXP()
{
	return EXP;
}
int player::Getround()
{
	return round;
}
//出题者
int questioner::GetQnum()
{
	return Qnum;
}

/*FRIEND*/
int person::FriendsNum()
{
	return friends.size();
}
//添加好友
void person::addfriend(int ID)
{
	bool exist = false;
	for (auto it = friends.begin(); it != friends.end(); it++)
		if ((*it) == ID)
			exist = true;

	if (!exist)
		friends.push_back(ID);
	else
		cout << "Ta已经是您的好友" << endl;
}
//将好友列表转换成字符串
string person::SFriendID()
{
	char Friend[30];
	stringstream ss;

	for (auto it = friends.begin(); it != friends.end(); it++)
		ss << *it << ' ';

	ss.getline(Friend, sizeof(Friend));	
	return Friend;
}
//显示好友列表
void player::Showfriends()
{
	if (FriendsNum() > 0)
	{
		cout << "朋友圈：" << endl;
		for (auto it = friends.begin(); it != friends.end(); )
		{
			vector<player>::iterator temp;
			if (findUser(*it, temp))
			{
				(*temp).Showinfo();
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
		cout << "您还没有好友" << endl;
	}
}
//显示好友列表
void questioner::Showfriends()
{
	if (FriendsNum() > 0)
	{
		cout << "朋友圈：" << endl;
		for (auto it = friends.begin(); it != friends.end(); )
		{
			vector<questioner>::iterator temp;
			if (findUser(*it, temp))
			{
				(*temp).Showinfo();
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
		cout << "您还没有好友" << endl;
	}
}