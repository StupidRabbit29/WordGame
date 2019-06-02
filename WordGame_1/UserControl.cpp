#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;

void UserControl(person* user, playertype type)
{
	if (DEBUG)
		cout << "UserControl is called" << endl;

	bool UserQuit = false;

	while(!UserQuit)
	{
		//�û���ѡ�Ĳ�����ʾ
		if (type == PLAYER)
			cout << "-----������:";
		else
			cout << "-----������:";
		cout << user->Getname() <<"----��ѡ����Ĳ���------" << endl
			<< "           0��     ��ʼ��Ϸ" << endl
			<< "           1��     �鿴����" << endl
			<< "           2��     �����û�" << endl
			<< "           3��     �˳�" << endl
			<< "           4��     �鿴�����б�" << endl
			<< "           5��     ��Ӻ���" << endl
			<< "------------------------------------" << endl;

		int choice = 0;

		//��ȡ�û������ѡ��
		while (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		cin.ignore(100, '\n');

		switch (choice)
		{
		case 0:
			//��ʼ��Ϸ
		{
			user->Play();

			////�����������������
			//Rank(PLAYER);
			////�����г����߽�������
			//Rank(QUESTIONER);

			break;
		}
		case 1:
			//�鿴����
		{
			Rank(PLAYER);
			Rank(QUESTIONER);
			ShowRank();

			if (type == PLAYER)
				user = &(*itp);
			else
				user = &(*itq);

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
			cout << "���������ڣ����������룡" << endl;
			break;
		}
		}
	}
}

//��Ӻ���
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
			//�����û� 
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
			//�����û� 
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