#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;


void GameControl(MySoc *MsClient)
{
	////��ȡ�ĵ���������Ϸ
	//ReadUserfile();
	if (DEBUG)
		cout << "Called GameControl" << endl;

	bool quit = false;
	while (!quit)
	{
		//��ӡ��ʾ��Ϣ
		string str1 = "******************��ӭ��������������Ϸ_03****************\n";
		string str2 = "                       ��ӭ������Ϸ \n";
		string str3 = "*******************************************************************\n";
		string str4 = "                    ������ѡ��Ĳ����У�\n";
		string str5 = "                    ���룺   ������\n";
		string str6 = "                    0��      �˳�ϵͳ\n";
		string str7 = "                    1��      �û�ע��\n";
		string str8 = "                    2��      �û���¼\n";
		string str9 = "                    3��      �鿴����\n";
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
				char temp[MSGSIZE] = "�������������ѡ��";
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
			//�˳�ϵͳ
		{
			quit = true;
			break;
		}
		case 1:
			//�û�ע��
		{
			memset(temp, 0, sizeof(temp));
			stemp = "ѡ��Ҫע����û����ͣ������ߣ�0�� or �����ߣ�1��";
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
					char temp[MSGSIZE] = "����������";
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
			//�û���¼
		{	
			memset(temp, 0, sizeof(temp));
			stemp = "ѡ��Ҫ��¼���û����ͣ������ߣ�0�� or �����ߣ�1��";
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
					char temp[MSGSIZE] = "����������";
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
			char help[MSGSIZE] = "	����������Ϸ�������������ɣ������ߣ�����Ϸ��ң��������ߣ�Ϊ��Ϸ������Ϸ��ʹ�õ��ʣ���\n��Ϸ����Ϊ����Ϸÿһ�֣��������ݸùؿ��Ѷȣ���ʾһ�����ʣ�һ��ʱ��󵥴���ʧ��\n��������Ҫ����Ӧ�ط�����ո���ʾ����ʧ�ĵ��ʣ�\n���������������ȷ��������������ĵ�����ո���ʾ�ĵ�����ȫһ�£�������Сд����Ϊͨ����\nһ�ؿ�����һ�ֻ��߶�����ɡ�";
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