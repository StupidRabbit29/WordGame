#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;
extern int PlayerID;
extern int QuestionerID;

void Sign_out()
{
	if (DEBUG)
		cout << "Sign_out called" << endl;


}

void WriteUserfile(vector<player>::iterator temp)
{
	string filename = "User.ini";
	stringstream ss;
	
	ss << "Player" << (*temp).GetID();
	LPCSTR str1 = ss.str().c_str();
	LPCSTR str2 = filename.c_str();
	
	WritePrivateProfileStringA(str1, "name", (*temp).Getname().c_str(), str2);
	
	WritePrivateProfileStringA(str1, "password", (*temp).Getpassword().c_str(), str2);
	
	ss.str("");
	ss << (*temp).GetID();
	LPCSTR str3 = ss.str().c_str();
	WritePrivateProfileStringA(str1, "ID", str3, str2);
	
	ss.str("");
	ss << (*temp).Getlevel();
	LPCSTR str3 = ss.str().c_str();
	WritePrivateProfileStringA(str1, "level", str3, str2);
	
	ss.str("");
	ss << (*temp).Getrank();
	LPCSTR str3 = ss.str().c_str();
	WritePrivateProfileStringA(str1, "rank", str3, str2);
	
	ss.str("");
	ss << (*temp).GetEXP();
	LPCSTR str3 = ss.str().c_str();
	WritePrivateProfileStringA(str1, "EXP", str3, str2);
	
	ss.str("");
	ss << (*temp).Getround();
	LPCSTR str3 = ss.str().c_str();
	WritePrivateProfileStringA(str1, "round", str3, str2);
}

void WriteUserfile(vector<questioner>::iterator temp)
{
	string filename = "User.ini";
	stringstream ss;

	ss << "Questioner" << (*temp).GetID();
	LPCSTR str1 = ss.str().c_str();
	LPCSTR str2 = filename.c_str();

	WritePrivateProfileStringA(str1, "name", (*temp).Getname().c_str(), str2);

	WritePrivateProfileStringA(str1, "password", (*temp).Getpassword().c_str(), str2);

	ss.str("");
	ss << (*temp).GetID();
	LPCSTR str3 = ss.str().c_str();
	WritePrivateProfileStringA(str1, "ID", str3, str2);

	ss.str("");
	ss << (*temp).Getlevel();
	LPCSTR str3 = ss.str().c_str();
	WritePrivateProfileStringA(str1, "level", str3, str2);

	ss.str("");
	ss << (*temp).Getrank();
	LPCSTR str3 = ss.str().c_str();
	WritePrivateProfileStringA(str1, "rank", str3, str2);

	ss.str("");
	ss << (*temp).GetQnum();
	LPCSTR str3 = ss.str().c_str();
	WritePrivateProfileStringA(str1, "Qnum", str3, str2);
}

void ReadUserfile()
{

}