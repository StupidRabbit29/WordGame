#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern bool QuitSYSTEM;

using namespace std;
void GameControl(void)
{
	//��ȡ�ĵ���������Ϸ

	while (!QuitSYSTEM)
	{
		cout << "                 ��ӭ��������������Ϸ_01" << endl
			<< "*******************************************************************" << endl
			<< "                    ������ѡ��Ĳ����У�" << endl
			<< "                    ���룺   ������" << endl
			<< "                    0��      �˳�ϵͳ" << endl
			<< "                    1��      �û�ע��" << endl
			<< "                    2��      �û���¼" << endl
			<< "                    3��      �鿴����" << endl
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
			cout << "ѡ��Ҫע����û����ͣ������ߣ�0�� or �����ߣ�1��" << endl;
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
					cout << "����������������룺" << endl;
				}
			}

			break;
		}
		case 2:
		{
			cout << "ѡ��Ҫ��¼���û����ͣ������ߣ�0�� or �����ߣ�1��" << endl;
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
					cout << "����������������룺" << endl;
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
			cout << "����Ĳ��������ڣ�" << endl;
			break;
		}
		}
	}

	//д�ĵ�������

}