#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;
extern int PlayerID;
extern int QuestionerID;

void Sign_out(playertype type)
{
	if (DEBUG)
		cout << "Sign_out called" << endl;

	//写文档
	if (type == PLAYER)
		WriteUserfile(itp);
	else
		WriteUserfile(itq);

	PlayerID = QuestionerID = 0;
}

void WriteUserfile(vector<player>::iterator temp)
{
	string filename = ".\\User.ini";
	string sectionname;
	string tempstr;
	stringstream ss;
	
	ss << "Player" << (*temp).GetID();
	ss >> sectionname;
	LPCSTR str1 = sectionname.c_str();
	LPCSTR str2 = filename.c_str();
	
	WritePrivateProfileStringA(str1, "name", (*temp).Getname().c_str(), str2);
	
	WritePrivateProfileStringA(str1, "password", (*temp).Getpassword().c_str(), str2);
	
	ss.str("");
	ss.clear();
	ss << (*temp).GetID();
	ss >> tempstr;
	LPCSTR str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "ID", str3, str2);
	
	ss.str("");
	ss.clear();
	ss << (*temp).Getlevel();
	ss >> tempstr;
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "level", str3, str2);
	
	ss.str("");
	ss.clear();
	ss << (*temp).Getrank();
	ss >> tempstr;
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "rank", str3, str2);
	
	ss.str("");
	ss.clear();
	ss << (*temp).GetEXP();
	ss >> tempstr;
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "EXP", str3, str2);
	
	ss.str("");
	ss.clear();
	ss << (*temp).Getround();
	ss >> tempstr;
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "round", str3, str2);

	ss.str("");
	ss.clear();
	ss << (*temp).FriendsNum();
	ss >> tempstr;
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "Fnum", str3, str2);

	tempstr = (*temp).SFriendID();
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "Friends", str3, str2);
}

void WriteUserfile(vector<questioner>::iterator temp)
{
	string filename = ".\\User.ini";
	string sectionname;
	string tempstr;
	stringstream ss;

	ss << "Questioner" << (*temp).GetID();
	ss >> sectionname;
	LPCSTR str1 = sectionname.c_str();
	LPCSTR str2 = filename.c_str();

	WritePrivateProfileStringA(str1, "name", (*temp).Getname().c_str(), str2);

	WritePrivateProfileStringA(str1, "password", (*temp).Getpassword().c_str(), str2);

	ss.str("");
	ss.clear();
	ss << (*temp).GetID();
	ss >> tempstr;
	LPCSTR str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "ID", str3, str2);

	ss.str("");
	ss.clear();
	ss << (*temp).Getlevel();
	ss >> tempstr;
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "level", str3, str2);

	ss.str("");
	ss.clear();
	ss << (*temp).Getrank();
	ss >> tempstr;
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "rank", str3, str2);

	ss.str("");
	ss.clear();
	ss << (*temp).GetQnum();
	ss >> tempstr;
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "Qnum", str3, str2);

	ss.str("");
	ss.clear();
	ss << (*temp).FriendsNum();
	ss >> tempstr;
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "Fnum", str3, str2);

	tempstr = (*temp).SFriendID();
	str3 = tempstr.c_str();
	WritePrivateProfileStringA(str1, "Friends", str3, str2);
}
//从文档中读取用户信息，写入容器中
void ReadUserfile()
{
	int playernum = 0;
	int questionernum = 0;
	string filename = ".\\User.ini";
	string tempstr;
	stringstream ss;
	ss << "Number";
	ss >> tempstr;
	LPCSTR str1 = tempstr.c_str();
	LPCSTR str2 = filename.c_str();

	playernum = GetPrivateProfileIntA(str1, "player", 0, str2);
	questionernum = GetPrivateProfileIntA(str1, "questioner", 0, str2);

	while (playernum > 0)
	{
		stringstream ss;
		ss << "Player" << playernum;
		ss >> tempstr;
		LPCSTR pstr = tempstr.c_str();

		char name[30];
		GetPrivateProfileStringA(pstr, "name", "", name, sizeof(name), str2);
		char password[30] = { '\0' };
		GetPrivateProfileStringA(pstr, "password", "", password, sizeof(password), str2);
		char Friends[50] = { '\0' };
		GetPrivateProfileStringA(pstr, "Friends", "", Friends, sizeof(Friends), str2);
		string Friend(Friends);

		int ID = 0;
		int level = 0;
		int rank = 0;
		int EXP = 0;
		int round = 0;
		int Fnum = 0;

		ID= GetPrivateProfileIntA(pstr, "ID", 0, str2);
		level= GetPrivateProfileIntA(pstr, "level", 0, str2);
		rank= GetPrivateProfileIntA(pstr, "rank", 0, str2);
		EXP= GetPrivateProfileIntA(pstr, "EXP", 0, str2);
		round = GetPrivateProfileIntA(pstr, "round", 0, str2);
		Fnum = GetPrivateProfileIntA(pstr, "Fnum", 0, str2);

		player temp(name, password, ID, level, rank, EXP, round);
		ss.str("");
		ss.clear();
		ss << Friend;
		for (int i = 0; i < Fnum; i++)
		{
			int ID;
			ss >> ID;
			temp.addfriend(ID);
		}

		Player.push_back(temp);

		playernum--;
	}

	while (questionernum > 0)
	{
		stringstream ss;
		ss << "Questioner" << questionernum;
		ss >> tempstr;
		LPCSTR qstr = tempstr.c_str();

		char name[30] = { '\0' };
		GetPrivateProfileStringA(qstr, "name", "", name, sizeof(name), str2);
		char password[30] = { '\0' };
		GetPrivateProfileStringA(qstr, "password", "", password, sizeof(password), str2);
		char Friends[50] = { '\0' };
		GetPrivateProfileStringA(qstr, "Friends", "", Friends, sizeof(Friends), str2);
		string Friend(Friends);

		int ID = 0;
		int level = 0;
		int rank = 0;
		int Qnum = 0;
		int Fnum = 0;

		ID = GetPrivateProfileIntA(qstr, "ID", 0, str2);
		level = GetPrivateProfileIntA(qstr, "level", 0, str2);
		rank = GetPrivateProfileIntA(qstr, "rank", 0, str2);
		Qnum = GetPrivateProfileIntA(qstr, "Qnum", 0, str2);
		Fnum = GetPrivateProfileIntA(qstr, "Fnum", 0, str2);

		questioner temp(name, password, ID, level, rank, Qnum);
		ss.str("");
		ss.clear();
		ss << Friend;
		for (int i = 0; i < Fnum; i++)
		{
			int ID;
			ss >> ID;
			temp.addfriend(ID);
		}

		Questioner.push_back(temp);

		questionernum--;
	}

	PlayerID = QuestionerID = 0;
}