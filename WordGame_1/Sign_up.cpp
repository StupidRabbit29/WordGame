#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;
extern int PlayerID;
extern int QuestionerID;

//用户注册程序
void Sign_up(playertype type)
{
	if (DEBUG)
		cout << "Sign_up called" << endl;

	//输入合适用户名
	bool rightname = false;
	char tempname[21] = { '\0' };

	while (!rightname)
	{
		cout << "请输入用户名（不超过20个字符）" << endl;
		if (cin.getline(tempname, 20) && tempname[0] != '\0')
			rightname = true;
		else
		{
			cout << "输入错误,";
			memset(tempname, 0, sizeof(tempname));
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}			
		}

		//判断是否有重名
		if (rightname)
		{
			if (samename(type, tempname))
			{
				rightname = false;
				cout << "用户名已存在，";
			}
		}
	}

	//输入合适的密码
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
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
		}
	}

	if (type == PLAYER)
	{
		//加入容器
		player temp(tempname, temppw);
		Player.push_back(temp);

		auto it = Player.end();
		it--;
		itp = it;
		setpersonID(&(*it));
		WriteUserfile(it);
		PlayerID = (*it).GetID();
		QuestionerID = 0;

		//写文档
		stringstream ss;
		string str;
		ss << Player.size();
		ss >> str;
		WritePrivateProfileStringA("Number", "player", str.c_str(), ".\\User.ini");
	}
	else
	{
		//加入容器
		questioner temp(tempname, temppw);
		Questioner.push_back(temp);

		auto it = Questioner.end();
		it--;
		itq = it;
		setpersonID(&(*it));
		WriteUserfile(it);
		QuestionerID = (*it).GetID();
		PlayerID = 0;

		//写文档
		stringstream ss;
		string str;
		ss << Questioner.size();
		ss >> str;
		WritePrivateProfileStringA("Number", "questioner", str.c_str(), ".\\User.ini");
	}

	if (type == PLAYER)
		UserControl(&(*itp), PLAYER);
	else
		UserControl(&(*itq), QUESTIONER);

	Sign_out(type);
}

//检测重名的程序
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

void setpersonID(person* p)
{
	p->setID();
}