#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;

void UserControl(playertype type, MySoc * MsClient)
{
	if (DEBUG)
		cout << "UserControl is called" << endl;

	person *user;
	if (type == PLAYER)
		user = &(*(MsClient->itp));
	else
		user = &(*(MsClient->itq));
	
	bool UserQuit = false;
	string str0 = "";

	while(!UserQuit)
	{
		//用户可选的操作提示
		string str1;
		if (type == PLAYER)
			str1 = "-----闯关者:";
		else
			str1 = "-----出题者:";

		string str2 = user->Getname();
		string str3 = "----请选择你的操作------\n";
		string str4 = "           0：     开始游戏\n";
		string str5 = "           1：     查看排名\n";
		string str6 = "           2：     查找用户\n";
		string str7 = "           3：     退出\n";
		string str8 = "           4：     查看好友列表\n";
		string str9 = "           5：     添加好友\n";
		string str10 = "------------------------------------";
		str1 = str0 + str1 + str2 + str3 + str4 + str5 + str6 + str7 + str8 + str9 + str10;
		char temp[MSGSIZE] = { '\0' };
		strcpy_s(temp, str1.c_str());
		send(MsClient->sClient, temp, MSGSIZE, 0);

		int choice = -1;
		bool Get = false;
		while (!Get)
		{
			char GetChoice[MSGSIZE + 1] = { '\0' };
			recv(MsClient->sClient, GetChoice, MSGSIZE, 0);
			stringstream ss;
			ss << GetChoice;
			ss >> choice;
			if (!(choice == 0 || choice == 1 || choice == 2 || choice == 3||choice==4||choice==5))
			{
				char temp[MSGSIZE] = "请重新输入操作选项";
				send(MsClient->sClient, temp, MSGSIZE, 0);
			}
			else
				Get = true;
		}

		switch (choice)
		{
		case 0:
			//开始游戏
		{
			user->Play(MsClient);

			break;
		}
		case 1:
			//查看排名
		{
			Rank(PLAYER, MsClient);
			Rank(QUESTIONER, MsClient);
			ShowRank();

			if (type == PLAYER)
				user = &(*(MsClient->itp));
			else
				user = &(*(MsClient->itq));

			break;
		}
		case 2:
			//查询模式
		{
			Search();
			break;
		}
		case 3: 
			//退出游戏
		{
			UserQuit = true;
			break;
		}
		case 4:
			//查看好友
		{
			user->Showfriends();
			break;
		}
		case 5:
			//加好友
		{
			AddFriends(user, type);
			break;
		}
		default:
		{
			str0 = "操作不存在，请重新输入！\n";
			break;
		}
		}
	}
}

void AddFriends(person* user, playertype type)
{
	//输入合适用户名
	bool rightname = false;
	char tempname[21] = { '\0' };

	while (!rightname)
	{
		cout << "请输入想要加为好友的用户名（不超过20个字符）" << endl;
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
			vector<player>::iterator ptemp;
			if (!findUser(tempname, ptemp))
			{
				rightname = false;
				cout << "用户不存在！" << endl;
			}
			else
			{
				user->addfriend((*ptemp).GetID());
			}
		}
		else if (rightname == true && type == QUESTIONER)
		{
			vector<questioner>::iterator qtemp;
			if (!findUser(tempname, qtemp))
			{
				rightname = false;
				cout << "用户不存在！" << endl;
			}
			else
			{
				user->addfriend((*qtemp).GetID());
			}
		}
	}
}