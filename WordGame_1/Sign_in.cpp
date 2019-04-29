#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;
extern int PlayerID;
extern int QuestionerID;

void Sign_in(playertype type)
{
	if (DEBUG)
		cout << "Sign_in called" << endl;

	bool rightname = false;
	char tempname[21] = { '\0' };
	vector<player>::iterator ptemp;
	vector<questioner>::iterator qtemp;

	while (!rightname)
	{
		cout << "������Ҫ��¼���û�����������20���ַ���" << endl;
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
			if (!findUser(tempname, ptemp))
			{
				rightname = false;
				cout << "�û������ڣ�" << endl;
			}
		}
		else if(rightname==true && type==QUESTIONER)
		{
			if (!findUser(tempname, qtemp))
			{
				rightname = false;
				cout << "�û������ڣ�" << endl;
			}
		}
	}

	bool rightpw = false;
	char temppw[21] = { '\0' };

	while (!rightpw)
	{
		cout << "���������루����8���ַ��Ҳ�����20���ַ�����" << endl;
		if (cin.getline(temppw, 20) && temppw[8] != '\0')
			rightpw = true;
		else
		{
			cout << "�������,";
			memset(temppw, 0, sizeof(temppw));
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
		}

		if (rightpw && type == PLAYER)
		{
			if (!checkpw(temppw, &(*ptemp)))
			{
				rightpw = false;
				cout << "����������������룡" << endl;
			}
		}
		else if (rightpw && type == QUESTIONER)
		{
			if (!checkpw(temppw, &(*qtemp)))
			{
				rightpw = false;
				cout << "����������������룡" << endl;
			}
		}
	}

	if (type == PLAYER)
	{
		itp = ptemp;
		PlayerID = (*itp).GetID();
		QuestionerID = 0;
	}
	else
	{
		itq = qtemp;
		QuestionerID = (*itq).GetID();
		PlayerID = 0;
	}

	if (type == PLAYER)
		UserControl(&(*itp));
	else
		UserControl(&(*itq));

	Sign_out(type);
}

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

bool checkpw(string password, person* user)
{
	if (password == user->Getpassword())
		return true;
	else
		return false;
}