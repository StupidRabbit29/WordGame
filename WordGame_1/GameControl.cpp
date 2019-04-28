#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern bool QuitSYSTEM;

using namespace std;
void GameControl(void)
{
	//读取文档，加载游戏

	while (!QuitSYSTEM)
	{
		cout << "                 欢迎来到单词消除游戏_01" << endl
			<< "*******************************************************************" << endl
			<< "                    您可以选择的操作有：" << endl
			<< "                    输入：   操作：" << endl
			<< "                    0：      退出系统" << endl
			<< "                    1：      用户注册" << endl
			<< "                    2：      用户登录" << endl
			<< "                    3：      查看帮助" << endl
			<< "*******************************************************************" << endl;

		int choice = 0;
		cin >> choice;
		cin.get();

		switch (choice)
		{
		case 0:
		{

			QuitSYSTEM = true;
			break;
		}
		case 1:
		{
			cout << "选择要注册的用户类型：闯关者（0） or 出题者（1）" << endl;
			bool righttype = false;
			while (!righttype)
			{
				int type = 0;
				cin >> type;
				cin.get();
				if (cin.good() && type == 0)
				{
					righttype = true;
					Sign_up(PLAYER);
				}
				else if (cin.good() && type == 1)
				{
					righttype = true;
					Sign_up(QUESTIONER);
				}
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "输入错误，请重新输入：" << endl;
				}
			}

			break;
		}
		case 2:
		{
			cout << "选择要登录的用户类型：闯关者（0） or 出题者（1）" << endl;
			bool righttype = false;
			while (!righttype)
			{
				int type = 0;
				cin >> type;
				cin.get();
				if (cin.good() && type == 0)
				{
					righttype = true;
					Sign_in(PLAYER);
				}
				else if (cin.good() && type == 1)
				{
					righttype = true;
					Sign_in(QUESTIONER);
				}
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "输入错误，请重新输入：" << endl;
				}
			}

			break;
		}
		case 3:
		{

			break;
		}
		default:
		{
			cout << "输入的操作不存在！" << endl;
			break;
		}
		}
	}

	//写文档，保存

}