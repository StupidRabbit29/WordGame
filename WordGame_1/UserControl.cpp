#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;

void UserControl(person* user, playertype type)
{
	if (DEBUG)
		cout << "UserControl is called" << endl;

	bool UserQuit = false;

	while(!UserQuit)
	{
		//用户可选的操作提示
		cout << "-----------请选择你的操作-----------" << endl
			<< "           0：     开始游戏" << endl
			<< "           1：     查看排名" << endl
			<< "           2：     查找用户" << endl
			<< "           3：     退出" << endl
			<< "           4：     查看好友列表" << endl
			<< "           5：     添加好友" << endl
			<< "------------------------------------" << endl;

		int choice = 0;
		while (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		cin.ignore(100, '\n');

		switch (choice)
		{
		case 0:
			//开始游戏
		{
			user->Play();
			break;
		}
		case 1:
			//查看排名
		{
			Rank(PLAYER);
			Rank(QUESTIONER);
			ShowRank();
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
			cout << "操作不存在，请重新输入！" << endl;
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