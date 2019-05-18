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
		//�û���ѡ�Ĳ�����ʾ
		string str1;
		if (type == PLAYER)
			str1 = "-----������:";
		else
			str1 = "-----������:";

		string str2 = user->Getname();
		string str3 = "----��ѡ����Ĳ���------\n";
		string str4 = "           0��     ��ʼ��Ϸ\n";
		string str5 = "           1��     �鿴����\n";
		string str6 = "           2��     �����û�\n";
		string str7 = "           3��     �˳�\n";
		string str8 = "           4��     �鿴�����б�\n";
		string str9 = "           5��     ��Ӻ���\n";
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
				char temp[MSGSIZE] = "�������������ѡ��";
				send(MsClient->sClient, temp, MSGSIZE, 0);
			}
			else
				Get = true;
		}

		switch (choice)
		{
		case 0:
			//��ʼ��Ϸ
		{
			user->Play(MsClient);

			break;
		}
		case 1:
			//�鿴����
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
			//��ѯģʽ
		{
			Search();
			break;
		}
		case 3: 
			//�˳���Ϸ
		{
			UserQuit = true;
			break;
		}
		case 4:
			//�鿴����
		{
			user->Showfriends();
			break;
		}
		case 5:
			//�Ӻ���
		{
			AddFriends(user, type);
			break;
		}
		default:
		{
			str0 = "���������ڣ����������룡\n";
			break;
		}
		}
	}
}

void AddFriends(person* user, playertype type)
{
	//��������û���
	bool rightname = false;
	char tempname[21] = { '\0' };

	while (!rightname)
	{
		cout << "��������Ҫ��Ϊ���ѵ��û�����������20���ַ���" << endl;
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

		if (rightname == true && type == PLAYER)
		{
			vector<player>::iterator ptemp;
			if (!findUser(tempname, ptemp))
			{
				rightname = false;
				cout << "�û������ڣ�" << endl;
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
				cout << "�û������ڣ�" << endl;
			}
			else
			{
				user->addfriend((*qtemp).GetID());
			}
		}
	}
}