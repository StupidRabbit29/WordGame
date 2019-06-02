#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;

//用户登录
void Sign_in(playertype type, MySoc *MsClient)
{

	if (DEBUG)
		cout << "Sign_in called" << endl;

	bool rightname = false;
	char tempname[21] = { '\0' };
	vector<player>::iterator ptemp;
	vector<questioner>::iterator qtemp;

	string str1 = "请输入要登录的用户名（不超过20个字符）";
	string str2 = "";

	//判断用户输入的名字是否存在
	while (!rightname)
	{
		char temp[MSGSIZE] = { '\0' };
		string str = str2 + str1;
		strcpy_s(temp, str.c_str());
		send(MsClient->sClient, temp, MSGSIZE, 0);
		
		char Get[MSGSIZE] = { '\0' };
		//读取用户名
		recv(MsClient->sClient, Get, MSGSIZE, 0);

		if (Get[0] != '\0')
		{
			rightname = true;
			memset(tempname, 0, sizeof(tempname));
			strncpy_s(tempname, Get, 20);
			if (DEBUG)
				cout << tempname << endl;
			tempname[20] = '\0';
		}
		else
			str2 = "输入错误,";

		//判断用户输入的名字是否存在
		if (rightname == true && type == PLAYER)
		{
			if (!findUser(tempname, ptemp))
			{
				rightname = false;
				str2.erase();
				str2 = "用户不存在！";
			}
		}
		else if(rightname==true && type==QUESTIONER)
		{
			if (!findUser(tempname, qtemp))
			{
				rightname = false;
				str2.erase();
				str2 = "用户不存在！";
			}
		}
	}

	//用户输入正确的密码
	bool rightpw = false;
	char temppw[21] = { '\0' };

	str1 = "请输入密码（多于8个字符且不超过20个字符）：";
	str2 = "";
	while (!rightpw)
	{
		char temp[MSGSIZE] = { '\0' };
		string str = str2 + str1;
		strcpy_s(temp, str.c_str());
		send(MsClient->sClient, temp, MSGSIZE, 0);

		char Get[MSGSIZE] = { '\0' };
		//读取密码
		recv(MsClient->sClient, Get, MSGSIZE, 0);

		if (Get[8] != '\0')
		{
			rightpw = true;
			strncpy_s(temppw, Get, 20);
			temppw[20] = '\0';
		}
		else
			str2 = "输入错误,";
	
		//判断用户输入的名字是否存在
		if (rightpw && type == PLAYER)
		{
			if (!checkpw(temppw, &(*ptemp)))
			{
				rightpw = false;
				str2.erase();
				str2 = "密码错误，请重新输入！";
			}
		}
		else if (rightpw && type == QUESTIONER)
		{
			if (!checkpw(temppw, &(*qtemp)))
			{
				rightpw = false;
				str2.erase();
				str2 = "密码错误，请重新输入！";
			}
		}
	}

	if (type == PLAYER)
	{
		MsClient->itp = ptemp;
		MsClient->PlayerID = (*ptemp).GetID();	
		MsClient->QuestionerID = 0;
	}
	else
	{
		MsClient->itq = qtemp;
		MsClient->QuestionerID = (*qtemp).GetID();
		MsClient->PlayerID = 0;
	}

	if (type == PLAYER)
		UserControl(PLAYER, MsClient);
	else
		UserControl(QUESTIONER, MsClient);

	Sign_out(type, MsClient);
}

//根据名字在游戏者中查找用户
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

//根据名字在出题者中查找用户
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
//根据ID在游戏者中查找用户
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
//根据ID在出题者中查找用户
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