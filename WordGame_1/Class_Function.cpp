#include"Class.h"

void person::setbasicinfo(string name, string password)
{
	if (DEBUG)
		cout << "person::setbasicinfo\n";
	
	//设置用户名和用户密码
	this->name = name;
	this->password = password;
}


/*3个信息输出函数，游戏者和出题人的信息输出均会调用用户信息输出*/
//用户信息输出
void person::Showinfo()
{
	if (DEBUG)
		cout << "person::Showinfo" << endl;

	//打印用户基本信息
	cout << "用户名:" << name << endl 
		<< "等级:" << level << endl 
		<< "排名:" << rank << endl;
}
//游戏者的信息输出
void player::Showinfo()
{
	person::Showinfo();

	if (DEBUG)
		cout << "player::Showinfo" << endl;

	//打印游戏者信息
	cout << "经验值:" << EXP << endl
		<< "成功闯关数:" << round << endl;
}
//出题人的信息输出
void questioner::Showinfo()
{
	person::Showinfo();

	if (DEBUG)
		cout << "questioner::Showinfo" << endl;

	//打印出题人信息
	cout << "出题数:" << Qnum << endl;
}