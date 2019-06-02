#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;

//�û�ע�����
void Sign_up(playertype type, MySoc * MsClient)
{
	if (DEBUG)
		cout << "Sign_up called" << endl;

	//��������û���
	bool rightname = false;
	char tempname[21] = { '\0' };

	string str1 = "�������û�����������20���ַ���";
	string str2 = "";
	while (!rightname)
	{
		char temp[MSGSIZE] = { '\0' };
		string str = str2 + str1;
		strcpy_s(temp, str.c_str());
		send(MsClient->sClient, temp, MSGSIZE, 0);

		char Get[MSGSIZE] = { '\0' };

		//�����û���
		recv(MsClient->sClient, Get, MSGSIZE, 0);

		str2.erase();

		//������ȷ�Լ���
		if (Get[0] != '\0')
		{
			rightname = true;
			strncpy_s(tempname, Get, 20);
			tempname[20] = '\0';
		}
		else
			str2 = "�������,";
		
		//�ж��Ƿ�������
		if (rightname)
		{
			if (samename(type, tempname))
			{
				rightname = false;
				str2 = "�û����Ѵ���,";
			}
		}
	}

	//������ʵ�����
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

		//��������
		recv(MsClient->sClient, Get, MSGSIZE, 0);

		str2.erase();

		if (Get[8] != '\0')
		{
			rightpw = true;
			strncpy_s(temppw, Get, 20);
			temppw[20] = '\0';
		}
		else
			str2 = "�������,";
	}

	if (type == PLAYER)
	{
		//��������
		player temp(tempname, temppw);
		Player.push_back(temp);

		auto it = Player.end();
		it--;
		MsClient->itp = it;
		setpersonID(&(*it));
		WriteUserfile(it);
		MsClient->PlayerID = (*it).GetID();
		MsClient->QuestionerID = 0;
		
		//д�ĵ�
		stringstream ss;
		string str;
		ss << Player.size();
		ss >> str;
		WritePrivateProfileStringA("Number", "player", str.c_str(), ".\\User.ini");
	}
	else
	{
		//��������
		questioner temp(tempname, temppw);
		Questioner.push_back(temp);

		auto it = Questioner.end();
		it--;
		MsClient->itq = it;
		setpersonID(&(*it));
		WriteUserfile(it);
		MsClient->QuestionerID = (*it).GetID();
		MsClient->PlayerID = 0;

		//д�ĵ�
		stringstream ss;
		string str;
		ss << Questioner.size();
		ss >> str;
		WritePrivateProfileStringA("Number", "questioner", str.c_str(), ".\\User.ini");
	}

	if (type == PLAYER)
		UserControl(PLAYER, MsClient);
	else
		UserControl(QUESTIONER, MsClient);

	Sign_out(type, MsClient);
}

//��������ĳ���
bool samename(playertype type, const string& name)
{
	bool same = false;
	if (type == PLAYER)
	{
		vector<player>::iterator it;
		for (it = Player.begin(); it != Player.end(); it++)
			if ((*it).Getname() == name)
				same = true;

		return same;
	}
	else
	{
		vector<questioner>::iterator it;
		for (it = Questioner.begin(); it != Questioner.end(); it++)
			if ((*it).Getname() == name)
				same = true;

		return same;
	}
}

//�����û�ID
void setpersonID(person* p)
{
	p->setID();
}