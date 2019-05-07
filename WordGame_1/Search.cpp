#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;

void Search()
{
	if (DEBUG)
		cout << "Search is called" << endl;

	bool quit = false;

	while (!quit)
	{
		//确定查找类型
		playertype type;
		int choice = 0;
		cout << "请输入您想要查询的用户类型，闯关者（0），出题者（1）" << endl;

		while (!(cin >> choice && (choice == 0 || choice == 1)))
		{
			cout << "输入错误，重新输入" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		cin.ignore(100, '\n');

		if (choice == 0)
			type = PLAYER;
		else
			type = QUESTIONER;

		//打印提示信息
		cout << "*******************请输入您的查询方式*******************" << endl
			<< "                   0       按姓名查询" << endl
			<< "                   1       按等级查询" << endl
			<< "                   2       按排名查询" << endl;

		if (type == PLAYER)
			cout << "                   3       按经验值查询" << endl
			<< "                   4       按成功闯关数查询" << endl;
		else
			cout << "                   3       按出题数查询" << endl;

		cout << "                   5       退出查询" << endl;
		cout << "********************************************************" << endl;

		//读取用户输入的选择
		int searchtype = 0;
		while (!(cin >> searchtype && (searchtype >= 0 && searchtype <= 5)))
		{
			cout << "输入错误，重新输入" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		cin.ignore(100, '\n');

		//退出查询操作
		if (searchtype == 5)
		{
			quit = true;
			break;
		}

		if (type == PLAYER)
		{
			//按用户名查找相应用户
			if (searchtype == 0)
			{
				bool rightname = false;
				char tempname[21] = { '\0' };
				vector<player>::iterator ptemp;

				while (!rightname)
				{
					cout << "请输入要查询的用户名（不超过20个字符）" << endl;
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

					if (rightname == true)
					{
						if (!findUser(tempname, ptemp))
						{
							rightname = false;
							cout << "用户不存在！" << endl;
						}
					}
				}

				(*ptemp).Showinfo();
			}
			else if (searchtype == 1)
				//查找所有等级与用户输入相符的用户
			{
				int level = 0;
				cout << "请输入您想查询的等级" << endl;

				while (!(cin >> level&&level >= 0 && level <= 15))
				{
					cout << "输入错误，重新输入" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findlevel(level, PLAYER);
			}
			else if (searchtype == 2)
				//查找所有排名与用户输入相符的用户
			{
				int rank = 0;
				cout << "请输入您想查询的排名" << endl;

				while (!(cin >> rank && rank >= 0))
				{
					cout << "输入错误，重新输入" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findrank(rank, PLAYER);
			}
			else if (searchtype == 3)
				//查找所有EXP与用户输入相符的用户
			{
				int EXP = 0;
				cout << "请输入您想查询的EXP" << endl;

				while (!(cin >> EXP && EXP >= 0))
				{
					cout << "输入错误，重新输入" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				FindEXP(EXP);
			}
			else if (searchtype == 4)
				//查找所有闯关数与用户输入相符的用户
			{
				int round = 0;
				cout << "请输入您想查询的round" << endl;

				while (!(cin >> round && round >= 0))
				{
					cout << "输入错误，重新输入" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findround(round);
			}
			else
			{
				cout << "您输入的选择不存在" << endl;
			}
		}
		else
		{
			//按用户名查找相应用户
			if (searchtype == 0)
			{
				bool rightname = false;
				char tempname[21] = { '\0' };
				vector<questioner>::iterator qtemp;

				while (!rightname)
				{
					cout << "请输入要查询的用户名（不超过20个字符）" << endl;
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

					if (rightname == true)
					{
						if (!findUser(tempname, qtemp))
						{
							rightname = false;
							cout << "用户不存在！" << endl;
						}
					}
				}

				(*qtemp).Showinfo();
			}
			else if (searchtype == 1)
				//查找所有等级与用户输入相符的用户
			{
				int level = 0;
				cout << "请输入您想查询的等级" << endl;

				while (!(cin >> level&&level >= 0 && level <= 15))
				{
					cout << "输入错误，重新输入" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findlevel(level, QUESTIONER);
			}
			else if (searchtype == 2)
				//查找所有排名与用户输入相符的用户
			{
				int rank = 0;
				cout << "请输入您想查询的排名" << endl;

				while (!(cin >> rank && rank >= 0))
				{
					cout << "输入错误，重新输入" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findrank(rank, QUESTIONER);
			}
			else if (searchtype == 3)
				//查找所有出题数与用户输入相符的用户
			{
				int Qnum = 0;
				cout << "请输入您想查询的出题数" << endl;

				while (!(cin >> Qnum && Qnum >= 0))
				{
					cout << "输入错误，重新输入" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				FindQnum(Qnum);
			}
			else
			{
				cout << "您输入的选择不存在" << endl;
			}
		}
	}
	
	cout << "查询已结束！" << endl;
}
//查找等级
void Findlevel(int level, playertype type)
{
	if (type == PLAYER)
	{
		bool find = false;
		for (auto it = Player.begin(); it != Player.end(); it++)
		{
			if ((*it).Getlevel() == level)
			{
				(*it).Showinfo();
				find = true;
			}
		}

		if (!find)
			cout << "不存在等级为" << level << "的闯关者" << endl;
	}
	else
	{
		bool find = false;
		for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		{
			if ((*it).Getlevel() == level)
			{
				(*it).Showinfo();
				find = true;
			}
		}

		if (!find)
			cout << "不存在等级为" << level << "的出题人" << endl;
	}
}
//查找排名
void Findrank(int rank, playertype type)
{
	if (type == PLAYER)
	{
		bool find = false;
		for (auto it = Player.begin(); it != Player.end(); it++)
		{
			if ((*it).Getrank() == rank)
			{
				(*it).Showinfo();
				find = true;
			}
		}

		if (!find)
			cout << "不存在排名为" << rank << "的闯关者" << endl;
	}
	else
	{
		bool find = false;
		for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		{
			if ((*it).Getrank() == rank)
			{
				(*it).Showinfo();
				find = true;
			}
		}

		if (!find)
			cout << "不存在排名为" << rank << "的出题人" << endl;
	}
}
//查找经验值
void FindEXP(int EXP)
{
	bool find = false;
	for (auto it = Player.begin(); it != Player.end(); it++)
	{
		if ((*it).GetEXP() == EXP)
		{
			(*it).Showinfo();
			find = true;
		}
	}

	if (!find)
		cout << "不存在EXP为" << EXP << "的闯关者" << endl;
}
//查找闯关数
void Findround(int round)
{
	bool find = false;
	for (auto it = Player.begin(); it != Player.end(); it++)
	{
		if ((*it).Getround() == round)
		{
			(*it).Showinfo();
			find = true;
		}
	}

	if (!find)
		cout << "不存在round为" << round << "的闯关者" << endl;
}
//查找出题数
void FindQnum(int Qnum)
{
	bool find = false;
	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
	{
		if ((*it).GetQnum() == Qnum)
		{
			(*it).Showinfo();
			find = true;
		}
	}

	if (!find)
		cout << "不存在出题数为" << Qnum << "的出题人" << endl;
}
