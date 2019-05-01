#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;
extern int PlayerID;
extern int QuestionerID;

void UserControl(person* user)
{
	if (DEBUG)
		cout << "UserControl is called" << endl;

	bool UserQuit = false;

	while(!UserQuit)
	{
		cout << "-----------��ѡ����Ĳ���-----------" << endl
			<< "           0��     ��ʼ��Ϸ" << endl
			<< "           1��     �鿴����" << endl
			<< "           2��     �����û�" << endl
			<< "           3��     �˳�" << endl
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
		{
			user->Play();
			break;
		}
		case 1:
		{

			break;
		}
		case 2:
		{

			break;
		}
		case 3: 
		{
			UserQuit = true;
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