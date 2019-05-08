#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;
extern int PlayerID;
extern int QuestionerID;
//用户登录
void Sign_in(playertype type)
{
	if (DEBUG)
		cout << "Sign_in called" << endl;

	bool rightname = false;
	char tempname[21] = { '\0' };
	vector<player>::iterator ptemp;
	vector<questioner>::iterator qtemp;

	//判断用户输入的名字是否存在
	while (!rightname)
	{
		cout << "请输入要登录的用户名（不超过20个字符）" << endl;
		if (cin.getline(tempname, 20) && tempname[0] != '\0')
			rightname = true;
		else
		{
			cout << "输入错误,";
			memset(tempname, 0, sizeof(tempname));
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
		}

		if (rightname == true && type == PLAYER)
		{
			if (!findUser(tempname, ptemp))
			{
				rightname = false;
				cout << "用户不存在！" << endl;
			}
		}
		else if(rightname==true && type==QUESTIONER)
		{
			if (!findUser(tempname, qtemp))
			{
				rightname = false;
				cout << "用户不存在！" << endl;
			}
		}
	}

	//用户输入正确的密码
	bool rightpw = false;
	char temppw[21] = { '\0' };

	while (!rightpw)
	{
		cout << "请输入密码（多于8个字符且不超过20个字符）：" << endl;
		if (cin.getline(temppw, 20) && temppw[8] != '\0')
			rightpw = true;
		else
		{
			cout << "输入错误,";
			memset(temppw, 0, sizeof(temppw));
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
		}

		if (rightpw && type == PLAYER)
		{
			if (!checkpw(temppw, &(*ptemp)))
			{
				rightpw = false;
				cout << "密码错误，请重新输入！" << endl;
			}
		}
		else if (rightpw && type == QUESTIONER)
		{
			if (!checkpw(temppw, &(*qtemp)))
			{
				rightpw = false;
				cout << "密码错误，请重新输入！" << endl;
			}
		}
	}

	if (type == PLAYER)
	{
		itp = ptemp;
		PlayerID = (*itp).GetID();
		QuestionerID = 0;
	}
	else
	{
		itq = qtemp;
		QuestionerID = (*itq).GetID();
		PlayerID = 0;
	}

	if (type == PLAYER)
		UserControl(&(*itp), PLAYER);
	else
		UserControl(&(*itq), QUESTIONER);

	Sign_out(type);
}
//在游戏者中查找用户
bool findUser(string name, vector<player>::iterator& temp)
{
	bool find = false;

	for(auto it=Player.begin();it!=Player.end();it++)
		if ((*it).Getname() == name)
		{
			find = true;
			temp = it;
			break;
		}

	return find;
}
//在出题者中查找用户
bool findUser(string name, vector<questioner>::iterator& temp)
{
	bool find = false;

	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		if ((*it).Getname() == name)
		{
			find = true;
			temp = it;
			break;
		}

	return find;
}
//在游戏者中查找用户
bool findUser(int ID, vector<player>::iterator& temp)
{
	bool find = false;

	for (auto it = Player.begin(); it != Player.end(); it++)
		if ((*it).GetID() == ID)
		{
			find = true;
			temp = it;
			break;
		}

	return find;
}
//在出题者中查找用户
bool findUser(int ID, vector<questioner>::iterator& temp)
{
	bool find = false;

	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		if ((*it).GetID() == ID)
		{
			find = true;
			temp = it;
			break;
		}

	return find;
}
//检查密码正确性
bool checkpw(string password, person* user)
{
	if (password == user->Getpassword())
		return true;
	else
		return false;
}