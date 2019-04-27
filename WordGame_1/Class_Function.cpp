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
	
	//设置用户名和用户密码
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