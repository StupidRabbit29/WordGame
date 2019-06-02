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
		//ȷ����������
		send(MsClient->sClient, "����������Ҫ��ѯ���û����ͣ������ߣ�0���������ߣ�1��", MSGSIZE, 0);
		
		playertype type;
		int choice = -1;
		bool Get = false;
		while (!Get)
		{
			stringstream ss;
			char temp[MSGSIZE + 1] = { '\0' };

			//��ȡ�û�����ѡ��
			recv(MsClient->sClient, temp, MSGSIZE, 0);
			ss << temp;
			ss >> choice;

			//������ȷ�Լ���
			if (!(choice == 0 || choice == 1))
			{
				char temp[MSGSIZE] = "�������������ѡ��";
				send(MsClient->sClient, temp, MSGSIZE, 0);
			}
			else
				Get = true;
		}

		if (choice == 0)
			type = PLAYER;
		else
			type = QUESTIONER;

		//��ӡ��ʾ��Ϣ
		string str1 = "*******************���������Ĳ�ѯ��ʽ*******************\n";
		string str2 = "                   0       ��������ѯ\n";
		string str3 = "                   1       ���ȼ���ѯ\n";
		string str4 = "                   2       ��������ѯ\n";
		string str5 = "                   3       ������ֵ��ѯ\n";
		string str6 = "                   4       ���ɹ���������ѯ\n";
		string str7 = "                   3       ����������ѯ\n";
		string str8 = "                   5       �˳���ѯ\n";
		string str9 = "********************************************************\n";
		
		string str;

		if (type == PLAYER)
			str = str1 + str2 + str3 + str4 + str5 + str6 + str8 + str9;
		else
			str = str1 + str2 + str3 + str4 + str7 + str8 + str9;

		char temp[MSGSIZE] = { '\0' };
		strcpy_s(temp, str.c_str());
		send(MsClient->sClient, temp, MSGSIZE, 0);

		//��ȡ�û������ѡ��
		int searchtype = -1;
		Get = false;
		while (!Get)
		{
			stringstream ss;
			char temp[MSGSIZE + 1] = { '\0' };
			recv(MsClient->sClient, temp, MSGSIZE, 0);
			ss << temp;
			ss >> searchtype;

			//������ȷ�Լ���
			if (!(searchtype >= 0 && searchtype <= 5))
			{
				char temp[MSGSIZE] = "���������������";
				send(MsClient->sClient, temp, MSGSIZE, 0);
			}
			else
				Get = true;
		}
		
		//�˳���ѯ����
		if (searchtype == 5)
		{
			quit = true;
			break;
		}

		if (type == PLAYER)
		{
			//���û���������Ӧ�û�
			if (searchtype == 0)
			{
				bool rightname = false;
				char tempname[21] = { '\0' };
				vector<player>::iterator ptemp;

				string str1 = "������Ҫ��ѯ���û�����������20���ַ���";
				string str2 = "";

				while (!rightname)
				{
					char temp[MSGSIZE] = { '\0' };
					string str = str2 + str1;
					strcpy_s(temp, str.c_str());
					send(MsClient->sClient, temp, MSGSIZE, 0);

					//��ȡ�û���
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
						str2 = "�������,";

					//�ж��û��Ƿ����
					if (rightname == true)
					{
						if (!findUser(tempname, ptemp))
						{
							rightname = false;
							str2 = "�û������ڣ�";
						}
					}
				}

				//���Ͳ��ҵ����û���Ϣ
				send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*ptemp).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);

				send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
			}
			else if (searchtype == 1)
				//�������еȼ����û�����������û�
			{
				send(MsClient->sClient, "�����������ѯ�ĵȼ�", MSGSIZE, 0);
				int level = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };

					//��ȡ�û�����
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> level;

					//������ȷ�Լ���
					if (!(level >= 0 && level <= 15))
					{
						char temp[MSGSIZE] = "���������������";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}

				//���ȼ������û�
				Findlevel(level, PLAYER, MsClient);
			}
			else if (searchtype == 2)
				//���������������û�����������û�
			{
				send(MsClient->sClient, "�����������ѯ������", MSGSIZE, 0);
				int rank = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					//��ȡ�û�����
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> rank;

					//������ȷ�Լ���
					if (rank < 0)
					{
						char temp[MSGSIZE] = "���������������";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}

				//�����������û�
				Findrank(rank, PLAYER, MsClient);
			}
			else if (searchtype == 3)
				//��������EXP���û�����������û�
			{
				send(MsClient->sClient, "�����������ѯ��EXP", MSGSIZE, 0);
				int EXP = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };

					//��ȡ�û�����
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> EXP;

					//������ȷ�Լ���
					if (EXP < 0)
					{
						char temp[MSGSIZE] = "���������������";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}
				
				//������ֵ�����û�
				FindEXP(EXP, MsClient);
			}
			else if (searchtype == 4)
				//�������д��������û�����������û�
			{
				send(MsClient->sClient, "�����������ѯ��round", MSGSIZE, 0);
				int round = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					//��ȡ�û�����
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> round;

					//������ȷ�Լ���
					if (round < 0)
					{
						char temp[MSGSIZE] = "���������������";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}
				
				//�������������û�
				Findround(round, MsClient);
			}
			else
			{
				send(MsClient->sClient, "�������ѡ�񲻴���", MSGSIZE, 0);
			}
		}
		else
		{
			if (searchtype == 0)
			{
				//���û���������Ӧ�û�
				bool rightname = false;
				char tempname[21] = { '\0' };
				vector<questioner>::iterator qtemp;

				string str1 = "������Ҫ��ѯ���û�����������20���ַ���";
				string str2 = "";

				while (!rightname)
				{
					char temp[MSGSIZE] = { '\0' };
					string str = str2 + str1;
					strcpy_s(temp, str.c_str());
					send(MsClient->sClient, temp, MSGSIZE, 0);

					//��ȡ�û���
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
						str2 = "�������,";

					//�ж��û��Ƿ����
					if (rightname == true)
					{
						if (!findUser(tempname, qtemp))
						{
							rightname = false;
							str2 = "�û������ڣ�";
						}
					}
				}

				//���Ͳ��ҵ����û���Ϣ
				send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*qtemp).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);

				send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
			}
			else if (searchtype == 1)
				//�������еȼ����û�����������û�
			{
				send(MsClient->sClient, "�����������ѯ�ĵȼ�", MSGSIZE, 0);
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
						char temp[MSGSIZE] = "���������������";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}

				Findlevel(level, QUESTIONER, MsClient);
			}
			else if (searchtype == 2)
				//���������������û�����������û�
			{
				send(MsClient->sClient, "�����������ѯ������", MSGSIZE, 0);
				int rank = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					//��ȡ�û�����
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> rank;

					//������ȷ�Լ���
					if (rank < 0)
					{
						char temp[MSGSIZE] = "���������������";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}

				//�����������û�
				Findrank(rank, QUESTIONER, MsClient);
			}
			else if (searchtype == 3)
				//�������г��������û�����������û�
			{
				send(MsClient->sClient, "�����������ѯ�ĳ�����", MSGSIZE, 0);
				int Qnum = -1;
				bool Get = false;
				while (!Get)
				{
					stringstream ss;
					char temp[MSGSIZE + 1] = { '\0' };
					//��ȡ�û�����
					recv(MsClient->sClient, temp, MSGSIZE, 0);
					ss << temp;
					ss >> Qnum;

					//������ȷ�Լ���
					if (Qnum < 0)
					{
						char temp[MSGSIZE] = "���������������";
						send(MsClient->sClient, temp, MSGSIZE, 0);
					}
					else
						Get = true;
				}
				
				//�������������û�
				FindQnum(Qnum, MsClient);
			}
			else
			{
				send(MsClient->sClient, "�������ѡ�񲻴���", MSGSIZE, 0);
			}
		}
	}
}
//���ҵȼ�
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
				//�ҵ���Ӧ�û������û���Ϣ
				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*it).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
				find = true;
			}
		}

		if (!find)
			send(MsClient->sClient, "���ҵ��û������ڣ�", MSGSIZE, 0);
	}
	else
	{
		bool find = false;
		for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		{
			if ((*it).Getlevel() == level)
			{
				//�ҵ���Ӧ�û������û���Ϣ
				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*it).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
				find = true;
			}
		}

		if (!find)
			send(MsClient->sClient, "���ҵ��û������ڣ�", MSGSIZE, 0);
	}

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
//��������
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
				//�ҵ���Ӧ�û������û���Ϣ
				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*it).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
				find = true;
			}
		}

		if (!find)
			send(MsClient->sClient, "���ҵ��û������ڣ�", MSGSIZE, 0);
	}
	else
	{
		bool find = false;
		for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		{
			if ((*it).Getrank() == rank)
			{
				//�ҵ���Ӧ�û������û���Ϣ
				send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
				Info info;
				(*it).Showinfo(info);
				send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
				find = true;
			}
		}

		if (!find)
			send(MsClient->sClient, "���ҵ��û������ڣ�", MSGSIZE, 0);
	}

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
//���Ҿ���ֵ
void FindEXP(int EXP, MySoc *MsClient)
{
	send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

	bool find = false;
	for (auto it = Player.begin(); it != Player.end(); it++)
	{
		if ((*it).GetEXP() == EXP)
		{
			//�ҵ���Ӧ�û������û���Ϣ
			send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
			Info info;
			(*it).Showinfo(info);
			send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
			find = true;
		}
	}

	if (!find)
		send(MsClient->sClient, "���ҵ��û������ڣ�", MSGSIZE, 0);

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
//���Ҵ�����
void Findround(int round, MySoc *MsClient)
{
	send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

	bool find = false;
	for (auto it = Player.begin(); it != Player.end(); it++)
	{
		if ((*it).Getround() == round)
		{
			//�ҵ���Ӧ�û������û���Ϣ
			send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
			Info info;
			(*it).Showinfo(info);
			send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
			find = true;
		}
	}

	if (!find)
		send(MsClient->sClient, "���ҵ��û������ڣ�", MSGSIZE, 0);

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
//���ҳ�����
void FindQnum(int Qnum, MySoc *MsClient)
{
	send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);

	bool find = false;
	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
	{
		if ((*it).GetQnum() == Qnum)
		{
			//�ҵ���Ӧ�û������û���Ϣ
			send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
			Info info;
			(*it).Showinfo(info);
			send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
			find = true;
		}
	}

	if (!find)
		send(MsClient->sClient, "���ҵ��û������ڣ�", MSGSIZE, 0);

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}
