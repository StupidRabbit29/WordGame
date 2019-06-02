#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern bool QuitSYSTEM;

void GameControl(void)
{
	//��ȡ�ĵ���������Ϸ
	ReadUserfile();

	while (!QuitSYSTEM)
	{
		//��ӡ��ʾ��Ϣ
		cout << "                       ��ӭ������Ϸ " << endl
			<< "*******************************************************************" << endl
			<< "                    ������ѡ��Ĳ����У�" << endl
			<< "                    ���룺   ������" << endl
			<< "                    0��      �˳�ϵͳ" << endl
			<< "                    1��      �û�ע��" << endl
			<< "                    2��      �û���¼" << endl
			<< "                    3��      �鿴����" << endl
			<< "*******************************************************************" << endl;

		//��ȡ�û���ѡ��
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
			//�˳�ϵͳ
		{
			QuitSYSTEM = true;
			break;
		}
		case 1:
			//�û�ע��
		{
			cout << "ѡ��Ҫע����û����ͣ������ߣ�0�� or �����ߣ�1��" << endl;
			bool righttype = false;
			while (!righttype)
			{
				int type = 0;
				cin >> type;
				cin.get();

				//������ȷ�Լ���
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
			//�û���¼
		{
			cout << "ѡ��Ҫ��¼���û����ͣ������ߣ�0�� or �����ߣ�1��" << endl;
			bool righttype = false;
			while (!righttype)
			{
				int type = 0;
				cin >> type;
				cin.get();

				//������ȷ�Լ���
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
			//�鿴����
		{
			cout << "	����������Ϸ�������������ɣ������ߣ�����Ϸ��ң��������ߣ�Ϊ��Ϸ������Ϸ��ʹ�õ��ʣ���" << endl
				<< "��Ϸ����Ϊ����Ϸÿһ�֣��������ݸùؿ��Ѷȣ���ʾһ�����ʣ�һ��ʱ��󵥴���ʧ��" << endl
				<< "��������Ҫ����Ӧ�ط�����ո���ʾ����ʧ�ĵ��ʣ�" << endl
				<< "���������������ȷ��������������ĵ�����ո���ʾ�ĵ�����ȫһ�£�������Сд����Ϊͨ����" << endl
				<< "һ�ؿ�����һ�ֻ��߶�����ɡ�" << endl;

			break;
		}
		default:
		{
			cout << "����Ĳ��������ڣ�" << endl;
			break;
		}
		}
	}
}