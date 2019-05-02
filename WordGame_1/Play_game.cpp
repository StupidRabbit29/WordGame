#include"Class.h"

extern bool DEBUG;

void player::Play()
{
	if (DEBUG)
		cout << "player::Play is called" << endl;

	int hard;
	int wordnum;
	int level = Getlevel();
	if (level < 5)
	{
		hard = 4;
		wordnum = 1 + level;
	}
	else if (level < 8)
	{
		hard = 6;
		wordnum = 1 + level - 5;
	}
	else if (level < 10)
	{
		hard = 6;
		wordnum = 3 + level - 7;
	}
	else if (level < 15)
	{
		hard = 8;
		wordnum = 3 + level - 15;
	}




	string word = GetWord(1,1);
	cout << word;
	Sleep(2000);
	cout << "\r" << "���������Ĵ𰸣�";

	string ans;
	cin >> ans;

	if (strcmp(ans.c_str(), word.c_str()) == 0)
	{
		cout << "����ȷ����ϲ��" << endl;
		EXP += 100;
		round++;
	}
	else
	{
		cout << "�𰸴�����Ϸ������" << endl;
	}
}

void questioner::Play()
{
	if (DEBUG)
		cout << "questioner::Play is called" << endl;

	bool finish = false;

	while (!finish)
	{
		cout << "����1���˳���Ϸ��" << endl << "����������Ҫ��ӵĵ����Ѷȣ�4����4����6����6����8����8����" << endl
			<< "              4��      5���ַ�����" << endl
			<< "              6��      5-9���ַ�  " << endl
			<< "              8��      10���ַ�������,20���ַ�����" << endl;

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

		cout << "����������Ҫ����ĵ��ʣ�һ��һ�����Իس����У���������׵Ļس���β" << endl;
			
		string filename(".\\Dictionary.ini");

		stringstream ss;
		ss << choice;
		string sectionname;
		ss >> sectionname;
				
		char word[21] = { '\0' };

		while (cin.getline(word, 20, '\n')&&word[0]!='\0')
		{
			if (GoodWord(choice, word))
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
			else
			{
				cout << "���ʳ��Ȳ����ʣ����������" << endl;
				memset(word, 0, sizeof(word));
			}
		}
	}

	cout << "��Ϸ������" << endl;
}

string GetWord(int hard, int num)
{
	if (DEBUG)
		cout << "GetWord is called!" << endl;

	srand(time(NULL));

	int number = GetPrivateProfileIntA("4", "number", 0, ".\\Dictionary.ini");

	stringstream ss;
	string str;
	ss << (rand() % number + 1);
	ss >> str;

	string shard;
	ss.str("");
	ss.clear();
	ss << hard;
	ss >> shard;

	char word[30] = { '\0' };

	GetPrivateProfileStringA(shard.c_str(), str.c_str(), "", word, sizeof(word), ".\\Dictionary.ini");

	return word;
}

bool GoodWord(int choice, char *word)
{
	if (choice == 4)
	{
		if (word[5] == '\0')
			return true;
	}
	else if (choice == 6)
	{
		if (word[5] != '\0'&&word[9] == '\0')
			return true;
	}
	else
	{
		if (word[9] != '\0')
			return true;
	}

	return false;
}