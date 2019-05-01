#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;

void player::Play()
{
	if (DEBUG)
		cout << "player::Play is called" << endl;



}

void questioner::Play()
{
	if (DEBUG)
		cout << "questioner::Play is called" << endl;

	bool finish = false;

	while (!finish)
	{
		cout << "输入1，退出游戏！" << endl << "请输入你想要添加的单词难度，4级（4），6级（6），8级（8）：" << endl;
		int choice = 1;
		while (!(cin >> choice && (choice == 1 || choice == 4 || choice == 6 || choice == 8)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
			else
				cout << "输入错误，请重新输入" << endl;
		}

		cin.ignore(100, '\n');
		if (choice == 1)
			break;

		cout << "请输入你想要输入的单词(20个字符以内)，一行一个，以回车换行，最后以行首的回车结尾" << endl;

		string filename(".\\Dictionary.ini");

		stringstream ss;
		ss << choice;
		string sectionname;
		ss >> sectionname;
				
		char word[21] = { '\0' };

		while (cin.getline(word, 21, '\n')&&word[0]!='\0')
		{
			ss.str("");
			ss.clear();
			ss << GetPrivateProfileIntA(sectionname.c_str(), "number", 0, filename.c_str()) + 1;
			string keyname;
			ss >> keyname;

			WritePrivateProfileStringA(sectionname.c_str(), keyname.c_str(), word, filename.c_str());
			WritePrivateProfileStringA(sectionname.c_str(), "number", keyname.c_str(), filename.c_str());
			memset(word, 0, sizeof(word));
			Qnum++;
		}
	}

	cout << "游戏结束！" << endl;
}