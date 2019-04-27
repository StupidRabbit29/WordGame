#include"Class.h"
#include"Function_Declaration.h"
#include<algorithm>
#include<numeric>
extern vector<player>Player;
extern vector<questioner>Questioner;
extern int PlayerID;
extern int QuestionerID;

void Sign_in(playertype type)
{
	if (DEBUG)
		cout << "Sign_in called" << endl;

	bool rightname = false;
	char tempname[21] = { '\0' };

	while (!rightname)
	{
		cout << "请输入要登录的用户名（不超过20个字符）" << endl;
		if (cin.getline(tempname, 20) && tempname[0] != '\0')
			rightname = true;
		else
		{
			cout << "输入错误,";
			memset(tempname, 0, sizeof(tempname));
			cin.clear();
			cin.ignore(100, '\n');
		}

		if (rightname)
		{
			if ()
			{
				rightname = false;
				cout << "用户名已存在，";
			}
		}
	}

	bool rightpw = false;
	char temppw[21] = { '\0' };

	while (!rightpw)
	{
		cout << "请输入密码（多于8个字符且不超过20个字符）" << endl;
		if (cin.getline(temppw, 20) && temppw[8] != '\0')
			rightpw = true;
		else
		{
			cout << "输入错误,";
			memset(temppw, 0, sizeof(temppw));
			cin.clear();
			cin.ignore(100, '\n');
		}
	}

	if (type == PLAYER)
	{
		player temp(tempname, temppw);
		Player.push_back(temp);
		auto it = Player.end();
		it--;
		setpersonID(&(*it));
		PlayerID = (*it).GetID();
		QuestionerID = 0;
	}
	else
	{
		questioner temp(tempname, temppw);
		Questioner.push_back(temp);
		auto it = Questioner.end();
		it--;
		setpersonID(&(*it));
		QuestionerID = (*it).GetID();
		PlayerID = 0;
	}
}