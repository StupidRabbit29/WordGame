#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern bool QuitSYSTEM;

void GameControl(void)
{
	//读取文档，加载游戏
	ReadUserfile();

	while (!QuitSYSTEM)
	{
		//打印提示信息
		cout << "                       欢迎进入游戏 " << endl
			<< "*******************************************************************" << endl
			<< "                    您可以选择的操作有：" << endl
			<< "                    输入：   操作：" << endl
			<< "                    0：      退出系统" << endl
			<< "                    1：      用户注册" << endl
			<< "                    2：      用户登录" << endl
			<< "                    3：      查看帮助" << endl
			<< "*******************************************************************" << endl;

		//读取用户的选择
		int choice = 0;
		while (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		cin.get();

		switch (choice)
		{
		case 0:
			//退出系统
		{
			QuitSYSTEM = true;
			break;
		}
		case 1:
			//用户注册
		{
			cout << "选择要注册的用户类型：闯关者（0） or 出题者（1）" << endl;
			bool righttype = false;
			while (!righttype)
			{
				int type = 0;
				cin >> type;
				cin.get();

				//输入正确性检验
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
			//用户登录
		{
			cout << "选择要登录的用户类型：闯关者（0） or 出题者（1）" << endl;
			bool righttype = false;
			while (!righttype)
			{
				int type = 0;
				cin >> type;
				cin.get();

				//输入正确性检验
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
			//查看帮助
		{
			cout << "	单词消除游戏由两类参与者组成：闯关者（即游戏玩家），出题者（为游戏增加游戏中使用单词）。" << endl
				<< "游戏规则为，游戏每一轮，程序会根据该关卡难度，显示一个单词，一定时间后单词消失。" << endl
				<< "闯关者需要在相应地方输入刚刚显示并消失的单词，" << endl
				<< "如果闯关者输入正确（即闯关者输入的单词与刚刚显示的单词完全一致，包含大小写）则为通过。" << endl
				<< "一关可以由一轮或者多轮组成。" << endl;

			break;
		}
		default:
		{
			cout << "输入的操作不存在！" << endl;
			break;
		}
		}
	}
}