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
		//ȷ����������
		playertype type;
		int choice = 0;
		cout << "����������Ҫ��ѯ���û����ͣ������ߣ�0���������ߣ�1��" << endl;

		while (!(cin >> choice && (choice == 0 || choice == 1)))
		{
			cout << "���������������" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		cin.ignore(100, '\n');

		if (choice == 0)
			type = PLAYER;
		else
			type = QUESTIONER;

		//��ӡ��ʾ��Ϣ
		cout << "*******************���������Ĳ�ѯ��ʽ*******************" << endl
			<< "                   0       ��������ѯ" << endl
			<< "                   1       ���ȼ���ѯ" << endl
			<< "                   2       ��������ѯ" << endl;

		if (type == PLAYER)
			cout << "                   3       ������ֵ��ѯ" << endl
			<< "                   4       ���ɹ���������ѯ" << endl;
		else
			cout << "                   3       ����������ѯ" << endl;

		cout << "                   5       �˳���ѯ" << endl;
		cout << "********************************************************" << endl;

		//��ȡ�û������ѡ��
		int searchtype = 0;
		while (!(cin >> searchtype && (searchtype >= 0 && searchtype <= 5)))
		{
			cout << "���������������" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		cin.ignore(100, '\n');

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

				while (!rightname)
				{
					cout << "������Ҫ��ѯ���û�����������20���ַ���" << endl;
					if (cin.getline(tempname, 20) && tempname[0] != '\0')
						rightname = true;
					else
					{
						cout << "�������,";
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
							cout << "�û������ڣ�" << endl;
						}
					}
				}

				(*ptemp).Showinfo();
			}
			else if (searchtype == 1)
				//�������еȼ����û�����������û�
			{
				int level = 0;
				cout << "�����������ѯ�ĵȼ�" << endl;

				while (!(cin >> level&&level >= 0 && level <= 15))
				{
					cout << "���������������" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findlevel(level, PLAYER);
			}
			else if (searchtype == 2)
				//���������������û�����������û�
			{
				int rank = 0;
				cout << "�����������ѯ������" << endl;

				while (!(cin >> rank && rank >= 0))
				{
					cout << "���������������" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findrank(rank, PLAYER);
			}
			else if (searchtype == 3)
				//��������EXP���û�����������û�
			{
				int EXP = 0;
				cout << "�����������ѯ��EXP" << endl;

				while (!(cin >> EXP && EXP >= 0))
				{
					cout << "���������������" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				FindEXP(EXP);
			}
			else if (searchtype == 4)
				//�������д��������û�����������û�
			{
				int round = 0;
				cout << "�����������ѯ��round" << endl;

				while (!(cin >> round && round >= 0))
				{
					cout << "���������������" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findround(round);
			}
			else
			{
				cout << "�������ѡ�񲻴���" << endl;
			}
		}
		else
		{
			//���û���������Ӧ�û�
			if (searchtype == 0)
			{
				bool rightname = false;
				char tempname[21] = { '\0' };
				vector<questioner>::iterator qtemp;

				while (!rightname)
				{
					cout << "������Ҫ��ѯ���û�����������20���ַ���" << endl;
					if (cin.getline(tempname, 20) && tempname[0] != '\0')
						rightname = true;
					else
					{
						cout << "�������,";
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
							cout << "�û������ڣ�" << endl;
						}
					}
				}

				(*qtemp).Showinfo();
			}
			else if (searchtype == 1)
				//�������еȼ����û�����������û�
			{
				int level = 0;
				cout << "�����������ѯ�ĵȼ�" << endl;

				while (!(cin >> level&&level >= 0 && level <= 15))
				{
					cout << "���������������" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findlevel(level, QUESTIONER);
			}
			else if (searchtype == 2)
				//���������������û�����������û�
			{
				int rank = 0;
				cout << "�����������ѯ������" << endl;

				while (!(cin >> rank && rank >= 0))
				{
					cout << "���������������" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				Findrank(rank, QUESTIONER);
			}
			else if (searchtype == 3)
				//�������г��������û�����������û�
			{
				int Qnum = 0;
				cout << "�����������ѯ�ĳ�����" << endl;

				while (!(cin >> Qnum && Qnum >= 0))
				{
					cout << "���������������" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				FindQnum(Qnum);
			}
			else
			{
				cout << "�������ѡ�񲻴���" << endl;
			}
		}
	}
	
	cout << "��ѯ�ѽ�����" << endl;
}
//���ҵȼ�
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
			cout << "�����ڵȼ�Ϊ" << level << "�Ĵ�����" << endl;
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
			cout << "�����ڵȼ�Ϊ" << level << "�ĳ�����" << endl;
	}
}
//��������
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
			cout << "����������Ϊ" << rank << "�Ĵ�����" << endl;
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
			cout << "����������Ϊ" << rank << "�ĳ�����" << endl;
	}
}
//���Ҿ���ֵ
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
		cout << "������EXPΪ" << EXP << "�Ĵ�����" << endl;
}
//���Ҵ�����
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
		cout << "������roundΪ" << round << "�Ĵ�����" << endl;
}
//���ҳ�����
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
		cout << "�����ڳ�����Ϊ" << Qnum << "�ĳ�����" << endl;
}
