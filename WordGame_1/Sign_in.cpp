#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;

//�û���¼
void Sign_in(playertype type, MySoc *MsClient)
{

	if (DEBUG)
		cout << "Sign_in called" << endl;

	bool rightname = false;
	char tempname[21] = { '\0' };
	vector<player>::iterator ptemp;
	vector<questioner>::iterator qtemp;

	string str1 = "������Ҫ��¼���û�����������20���ַ���";
	string str2 = "";

	//�ж��û�����������Ƿ����
	while (!rightname)
	{
		char temp[MSGSIZE] = { '\0' };
		string str = str2 + str1;
		strcpy_s(temp, str.c_str());
		send(MsClient->sClient, temp, MSGSIZE, 0);
		
		char Get[MSGSIZE] = { '\0' };
		//��ȡ�û���
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

		//�ж��û�����������Ƿ����
		if (rightname == true && type == PLAYER)
		{
			if (!findUser(tempname, ptemp))
			{
				rightname = false;
				str2.erase();
				str2 = "�û������ڣ�";
			}
		}
		else if(rightname==true && type==QUESTIONER)
		{
			if (!findUser(tempname, qtemp))
			{
				rightname = false;
				str2.erase();
				str2 = "�û������ڣ�";
			}
		}
	}

	//�û�������ȷ������
	bool rightpw = false;
	char temppw[21] = { '\0' };

	str1 = "���������루����8���ַ��Ҳ�����20���ַ�����";
	str2 = "";
	while (!rightpw)
	{
		char temp[MSGSIZE] = { '\0' };
		string str = str2 + str1;
		strcpy_s(temp, str.c_str());
		send(MsClient->sClient, temp, MSGSIZE, 0);

		char Get[MSGSIZE] = { '\0' };
		//��ȡ����
		recv(MsClient->sClient, Get, MSGSIZE, 0);

		if (Get[8] != '\0')
		{
			rightpw = true;
			strncpy_s(temppw, Get, 20);
			temppw[20] = '\0';
		}
		else
			str2 = "�������,";
	
		//�ж��û�����������Ƿ����
		if (rightpw && type == PLAYER)
		{
			if (!checkpw(temppw, &(*ptemp)))
			{
				rightpw = false;
				str2.erase();
				str2 = "����������������룡";
			}
		}
		else if (rightpw && type == QUESTIONER)
		{
			if (!checkpw(temppw, &(*qtemp)))
			{
				rightpw = false;
				str2.erase();
				str2 = "����������������룡";
			}
		}
	}

	if (type == PLAYER)
	{
		MsClient->itp = ptemp;
		MsClient->PlayerID = (*ptemp).GetID();	
		MsClient->QuestionerID = 0;
	}
	else
	{
		MsClient->itq = qtemp;
		MsClient->QuestionerID = (*qtemp).GetID();
		MsClient->PlayerID = 0;
	}

	if (type == PLAYER)
		UserControl(PLAYER, MsClient);
	else
		UserControl(QUESTIONER, MsClient);

	Sign_out(type, MsClient);
}

//������������Ϸ���в����û�
bool findUser(string name, vector<player>::iterator& temp)
{
	bool find = false;

	for(auto it=Player.begin();it!=Player.end();it++)
		if ((*it).Getname() == name)
		{
			find = true;
			temp = it;
			break;
		}

	return find;
}

//���������ڳ������в����û�
bool findUser(string name, vector<questioner>::iterator& temp)
{
	bool find = false;

	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		if ((*it).Getname() == name)
		{
			find = true;
			temp = it;
			break;
		}

	return find;
}
//����ID����Ϸ���в����û�
bool findUser(int ID, vector<player>::iterator& temp)
{
	bool find = false;

	for (auto it = Player.begin(); it != Player.end(); it++)
		if ((*it).GetID() == ID)
		{
			find = true;
			temp = it;
			break;
		}

	return find;
}
//����ID�ڳ������в����û�
bool findUser(int ID, vector<questioner>::iterator& temp)
{
	bool find = false;

	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		if ((*it).GetID() == ID)
		{
			find = true;
			temp = it;
			break;
		}

	return find;
}

//���������ȷ��
bool checkpw(string password, person* user)
{
	if (password == user->Getpassword())
		return true;
	else
		return false;
}