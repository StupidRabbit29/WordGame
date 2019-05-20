#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;

void Search(MySoc * MsClient)
{
	if (DEBUG)
		cout << "Search is called" << endl;

	bool quit = false;

	while (!quit)
	{
		//确定查找类型
		send(MsClient->sClient, "请输入您想要查询的用户类型，闯关者（0），出题者（1）", MSGSIZE, 0);
		
		playertype type;
		int choice = -1;
		bool Get = false;
		while (!Get)
		{
			stringstream ss;
			char temp[MSGSIZE + 1] = { '\0' };
			recv(MsClient->sClient, temp, MSGSIZE, 0);
			ss << temp;
			ss >> choice;

			if (!(choice == 0 || choice == 1))
			{
				char temp[MSGSIZE] = "请重新输入操作选项";
				send(MsClient->sClient, temp, MSGSIZE, 0);
			}
			else
				Get = true;
		}

		if (choice == 0)
			type = PLAYER;
		else
			type = QUESTIONER;

		//打印提示信息

		string str1 = "*******************请输入您的查询方式*******************\n";
		string str2 = "                   0       按姓名查询\n";
		string str3 = "                   1       按等级查询\n";
		string str4 = "                   2       按排名查询\n";
		string str5 = "                   3       按经验值查询\n";
		string str6 = "                   4       按成功闯关数查询\n";
		string str7 = "                   3       按出题数查询\n";
		string str8 = "                   5       退出查询\n";
		string str9 = "********************************************************\n";
		
		string str;

		if (type == PLAYER)
			str = str1 + str2 + str3 + str4 + str5 + str6 + str8 + str9;
		else
			str = str1 + str2 + str3 + str4 + str7 + str8 + str9;

		char temp[MSGSIZE] = { '\0' };
		strcpy_s(temp, str.c_str());
		send(MsClient->sClient, temp, MSGSIZE, 0);

		//读取用户输入的选择
		int searchtype = -1;
		Get = false;
		while (!Get)
		{
			stringstream ss;
			char temp[MSGSIZE + 1] = { '\0' };
			recv(MsClient->sClient, temp, MSGSIZE, 0);
			ss << temp;
			ss >> searchtype;

			if (!(searchtype >= 0 && searchtype <= 5))
			{
				char temp[MSGSIZE] = "输入错误，重新输入";
				send(MsClient->sClient, temp, MSGSIZE, 0);
			}
			else
				Get = true;
		}
		
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

				string str1 = "请输入要查询的用户名（不超过20个字符）";
				string str2 = "";

				while (!rightname)
				{
					char temp[MSGSIZE] = { '\0' };
					string str = str2 + str1;
					strcpy_s(temp, str.c_str());
					send(MsClient->sClient, temp, MSGSIZE, 0);

					char Get[MSGSIZE] = { '\0' };
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

					if (rightname == true)
					{
						if (!findUser(tempname, ptemp))
						{
							rightname = false;
							str2 = "用户不存在！";
						}
					}
				}

				send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*ptemp).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);

				send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
			}
			else if (searchtype == 1)
				//查找所有等级与用户输入相符的用户
			{
				send(MsClient->sClient, "请输入您想查询的等级", MSGSIZE, 0);
				int level = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> level;

					if (!(level >= 0 && level <= 15))
					{
						char temp[MSGSIZE] = "输入错误，重新输入";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}

				Findlevel(level, PLAYER, MsClient);
			}
			else if (searchtype == 2)
				//查找所有排名与用户输入相符的用户
			{
				send(MsClient->sClient, "请输入您想查询的排名", MSGSIZE, 0);
				int rank = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> rank;

					if (rank < 0)
					{
						char temp[MSGSIZE] = "输入错误，重新输入";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}

				Findrank(rank, PLAYER, MsClient);
			}
			else if (searchtype == 3)
				//查找所有EXP与用户输入相符的用户
			{
				send(MsClient->sClient, "请输入您想查询的EXP", MSGSIZE, 0);
				int EXP = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> EXP;

					if (EXP < 0)
					{
						char temp[MSGSIZE] = "输入错误，重新输入";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}
				
				FindEXP(EXP, MsClient);
			}
			else if (searchtype == 4)
				//查找所有闯关数与用户输入相符的用户
			{
				send(MsClient->sClient, "请输入您想查询的round", MSGSIZE, 0);
				int round = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> round;

					if (round < 0)
					{
						char temp[MSGSIZE] = "输入错误，重新输入";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}
			
				Findround(round, MsClient);
			}
			else
			{
				send(MsClient->sClient, "您输入的选择不存在", MSGSIZE, 0);
			}
		}
		else
		{
			if (searchtype == 0)
			{
				//按用户名查找相应用户
				bool rightname = false;
				char tempname[21] = { '\0' };
				vector<questioner>::iterator qtemp;

				string str1 = "请输入要查询的用户名（不超过20个字符）";
				string str2 = "";

				while (!rightname)
				{
					char temp[MSGSIZE] = { '\0' };
					string str = str2 + str1;
					strcpy_s(temp, str.c_str());
					send(MsClient->sClient, temp, MSGSIZE, 0);

					char Get[MSGSIZE] = { '\0' };
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

					if (rightname == true)
					{
						if (!findUser(tempname, qtemp))
						{
							rightname = false;
							str2 = "用户不存在！";
						}
					}
				}

				send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*qtemp).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);

				send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
			}
			else if (searchtype == 1)
				//查找所有等级与用户输入相符的用户
			{
				send(MsClient->sClient, "请输入您想查询的等级", MSGSIZE, 0);
				int level = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> level;

					if (!(level >= 0 && level <= 15))
					{
						char temp[MSGSIZE] = "输入错误，重新输入";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}

				Findlevel(level, QUESTIONER, MsClient);
			}
			else if (searchtype == 2)
				//查找所有排名与用户输入相符的用户
			{
				send(MsClient->sClient, "请输入您想查询的排名", MSGSIZE, 0);
				int rank = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> rank;

					if (rank < 0)
					{
						char temp[MSGSIZE] = "输入错误，重新输入";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}

				Findrank(rank, QUESTIONER, MsClient);
			}
			else if (searchtype == 3)
				//查找所有出题数与用户输入相符的用户
			{
				send(MsClient->sClient, "请输入您想查询的出题数", MSGSIZE, 0);
				int Qnum = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> Qnum;

					if (Qnum < 0)
					{
						char temp[MSGSIZE] = "输入错误，重新输入";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}
				
				FindQnum(Qnum, MsClient);
			}
			else
			{
				send(MsClient->sClient, "您输入的选择不存在", MSGSIZE, 0);
			}
		}
	}
	
	//send(MsClient->sClient, "查询已结束！", MSGSIZE, 0);
}
//查找等级
void Findlevel(int level, playertype type, MySoc *MsClient)
{
	send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

	if (type == PLAYER)
	{
		bool find = false;
		for (auto it = Player.begin(); it != Player.end(); it++)
		{
			if ((*it).Getlevel() == level)
			{
				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*it).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
				find = true;
			}
		}

		if (!find)
			send(MsClient->sClient, "查找的用户不存在！", MSGSIZE, 0);
	}
	else
	{
		bool find = false;
		for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		{
			if ((*it).Getlevel() == level)
			{
				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*it).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
				find = true;
			}
		}

		if (!find)
			send(MsClient->sClient, "查找的用户不存在！", MSGSIZE, 0);
	}

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
//查找排名
void Findrank(int rank, playertype type, MySoc *MsClient)
{
	send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

	if (type == PLAYER)
	{
		bool find = false;
		for (auto it = Player.begin(); it != Player.end(); it++)
		{
			if ((*it).Getrank() == rank)
			{
				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*it).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
				find = true;
			}
		}

		if (!find)
			send(MsClient->sClient, "查找的用户不存在！", MSGSIZE, 0);
	}
	else
	{
		bool find = false;
		for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		{
			if ((*it).Getrank() == rank)
			{
				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*it).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
				find = true;
			}
		}

		if (!find)
			send(MsClient->sClient, "查找的用户不存在！", MSGSIZE, 0);
	}

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
//查找经验值
void FindEXP(int EXP, MySoc *MsClient)
{
	send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

	bool find = false;
	for (auto it = Player.begin(); it != Player.end(); it++)
	{
		if ((*it).GetEXP() == EXP)
		{
			send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
			Info info;
			(*it).Showinfo(info);
			send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
			find = true;
		}
	}

	if (!find)
		send(MsClient->sClient, "查找的用户不存在！", MSGSIZE, 0);

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
//查找闯关数
void Findround(int round, MySoc *MsClient)
{
	send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

	bool find = false;
	for (auto it = Player.begin(); it != Player.end(); it++)
	{
		if ((*it).Getround() == round)
		{
			send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
			Info info;
			(*it).Showinfo(info);
			send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
			find = true;
		}
	}

	if (!find)
		send(MsClient->sClient, "查找的用户不存在！", MSGSIZE, 0);

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
//查找出题数
void FindQnum(int Qnum, MySoc *MsClient)
{
	send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

	bool find = false;
	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
	{
		if ((*it).GetQnum() == Qnum)
		{
			send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
			Info info;
			(*it).Showinfo(info);
			send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
			find = true;
		}
	}

	if (!find)
		send(MsClient->sClient, "查找的用户不存在！", MSGSIZE, 0);

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
