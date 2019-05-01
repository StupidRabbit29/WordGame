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
		cout << "����1���˳���Ϸ��" << endl << "����������Ҫ��ӵĵ����Ѷȣ�4����4����6����6����8����8����" << endl;
		int choice = 1;
		while (!(cin >> choice && (choice == 1 || choice == 4 || choice == 6 || choice == 8)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
			else
				cout << "�����������������" << endl;
		}

		cin.ignore(100, '\n');
		if (choice == 1)
			break;

		cout << "����������Ҫ����ĵ���(20���ַ�����)��һ��һ�����Իس����У���������׵Ļس���β" << endl;

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

	cout << "��Ϸ������" << endl;
}