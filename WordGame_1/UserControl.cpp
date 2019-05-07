#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;

void UserControl(person* user)
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
			<< "------------------------------------" << endl;

		int choice = 0;
		while (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(100, '\n');
		}

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
		default:
		{
			cout << "操作不存在，请重新输入！" << endl;
			break;
		}
		}
	}
}