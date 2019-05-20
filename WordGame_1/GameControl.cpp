#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;


void GameControl(MySoc *MsClient)
{
	////读取文档，加载游戏
	//ReadUserfile();
	if (DEBUG)
		cout << "Called GameControl" << endl;

	bool quit = false;
	while (!quit)
	{
		//打印提示信息
		string str1 = "******************欢迎来到单词消除游戏_03****************\n";
		string str2 = "                       欢迎进入游戏 \n";
		string str3 = "*******************************************************************\n";
		string str4 = "                    您可以选择的操作有：\n";
		string str5 = "                    输入：   操作：\n";
		string str6 = "                    0：      退出系统\n";
		string str7 = "                    1：      用户注册\n";
		string str8 = "                    2：      用户登录\n";
		string str9 = "                    3：      查看帮助\n";
		string str10 = "*******************************************************************";
		str1 = str1 + str2 + str3 + str4 + str5 + str6 + str7 + str8 + str9 + str10;

		char temp[MSGSIZE];
		strcpy_s(temp, str1.c_str());
		send(MsClient->sClient, temp, MSGSIZE, 0);
		
		int choice = -1;
		bool Get = false;
		while (!Get)
		{
			char GetChoice[MSGSIZE+1] = { '\0' };
			recv(MsClient->sClient, GetChoice, MSGSIZE, 0);
			stringstream ss;
			ss << GetChoice;
			ss >> choice;
			if (!(choice == 0 || choice == 1 || choice == 2 || choice == 3))
			{
				char temp[MSGSIZE] = "请重新输入操作选项";
				send(MsClient->sClient, temp, MSGSIZE, 0);
			}
			else
				Get = true;
		}

		string stemp;
		int choice2 = -1;
		Get = false;

		switch (choice)
		{
		case 0:
			//退出系统
		{
			quit = true;
			break;
		}
		case 1:
			//用户注册
		{
			memset(temp, 0, sizeof(temp));
			stemp = "选择要注册的用户类型：闯关者（0） or 出题者（1）";
			strcpy_s(temp, stemp.c_str());
			send(MsClient->sClient, temp, MSGSIZE, 0);

			while (!Get)
			{
				char GetChoice[MSGSIZE+1] = { '\0' };
				recv(MsClient->sClient, GetChoice, MSGSIZE, 0);
				stringstream ss;
				ss << GetChoice;
				choice2 = -1;
				ss >> choice2;
				if (!(choice2 == 0 || choice2 == 1))
				{
					char temp[MSGSIZE] = "请重新输入";
					send(MsClient->sClient, temp, MSGSIZE, 0);
				}
				else
					Get = true;
			}

			if (choice2 == 0)
			{
				Sign_up(PLAYER, MsClient);
			}
			else if (choice2 == 1)
			{
				Sign_up(QUESTIONER, MsClient);
			}

			break;
		}
		case 2:
			//用户登录
		{	
			memset(temp, 0, sizeof(temp));
			stemp = "选择要登录的用户类型：闯关者（0） or 出题者（1）";
			strcpy_s(temp, stemp.c_str());
			send(MsClient->sClient, temp, MSGSIZE, 0);

			while (!Get)
			{
				char GetChoice[MSGSIZE+1] = { '\0' };
				recv(MsClient->sClient, GetChoice, MSGSIZE, 0);
				stringstream ss;
				ss << GetChoice;
				choice2 = -1;
				ss >> choice2;
				if (!(choice2 == 0 || choice2 == 1))
				{
					char temp[MSGSIZE] = "请重新输入";
					send(MsClient->sClient, temp, MSGSIZE, 0);
				}
				else
					Get = true;
			}

			if (choice2 == 0)
			{
				Sign_in(PLAYER, MsClient);
			}
			else if (choice2 == 1)
			{
				Sign_in(QUESTIONER, MsClient);
			}
			
			break;
		}
		case 3:
		{
			char help[MSGSIZE] = "	单词消除游戏由两类参与者组成：闯关者（即游戏玩家），出题者（为游戏增加游戏中使用单词）。\n游戏规则为，游戏每一轮，程序会根据该关卡难度，显示一个单词，一定时间后单词消失。\n闯关者需要在相应地方输入刚刚显示并消失的单词，\n如果闯关者输入正确（即闯关者输入的单词与刚刚显示的单词完全一致，包含大小写）则为通过。\n一关可以由一轮或者多轮组成。";
			send(MsClient->sClient, help, MSGSIZE, 0);
			char Gethelp[MSGSIZE+1] = { '\0' };
			recv(MsClient->sClient, Gethelp, MSGSIZE, 0);

			break;
		}
		default:
		{
			break;
		}
		}
	}
}