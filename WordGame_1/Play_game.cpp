#include"Class.h"

extern bool DEBUG;

//��15����ÿ���ĵ����ѶȺ͵��ʸ����͵�����ʾʱ��
int GameDifficulty[15][3] = {
	{4, 1, 1900},
	{4, 2, 1900},
	{4, 3, 1900},
	{4, 4, 1900},
	{4, 5, 1900},
	{6, 3, 1800},
	{6, 4, 1800},
	{6, 5, 1800},
	{6, 6, 1700},
	{6, 7, 1600},
	{8, 5, 1500}, 
	{8, 6, 1400}, 
	{8, 7, 1300}, 
	{8, 8, 1200},
	{8, 9, 1100}
};

//��������������Ҫ��EXP
int PLevelUp[15] = {
	100,
	300,
	600,
	1200,
	1800,
	2500,
	3400,
	4500,
	6000,
	8000,
	11000,
	15000,
	20000,
	30000,
	50000
};

//��������������Ҫ�ĳ�����Ŀ
int QLevelUp[15] = {
	2,
	3,
	5,
	8,
	13,
	21,
	34,
	55,
	89,
	100,
	120,
	140,
	200,
	300,
	500
};

//�����ߵ���Ϸ
void player::Play()
{
	if (DEBUG)
		cout << "player::Play is called" << endl;

	//���ݴ����ߵȼ����ùؿ��Ѷ�
	int hard;
	int wordnum;
	int sleeptime;
	int userlevel = Getlevel();
	hard = GameDifficulty[userlevel - 1][0];
	wordnum = GameDifficulty[userlevel - 1][1];
	sleeptime = GameDifficulty[userlevel - 1][2];

	bool KO = true;

	//������Ϸ
	for (int i = 0; i < wordnum && KO == true; i++)
	{
		//�Ӵʿ��л�ȡ����
		string word = GetWord(hard, i + 1, wordnum);

		cout << "׼����\t";
		for (int j = 0; j < 5; j++)
		{		
			Sleep(500);
			cout << (5 - j) << "\t";
		}
		//չʾ����
		cout <<'\n'<< word;
		Sleep(sleeptime);
		cout << "\r" << "���������Ĵ𰸣�                                \n";

		clock_t start, finish, interval;
		start = clock();
		//��ȡ�û�����
		string ans;
		cin >> ans;
		finish = clock();
		interval = finish - start;

		//�жϴ�����
		if (strcmp(ans.c_str(), word.c_str()) == 0)
		{
			if(i<wordnum-1)
				cout << "����ȷ���ٽ����������ͣ�" << endl;

			EXP += 100 + (hard - 2) * 10 + (i + 1) * 5 - (interval / CLOCKS_PER_SEC) * 3;
		}
		else
		{
			KO = false;
			cout << "�𰸴�����Ϸ������" << endl;
		}
	}

	//�ɹ�����������
	if (KO == true)
	{
		round++;
		cout << "���سɹ���\n";
	}
	
	//�ж��Ƿ��������
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		if (PLevelUp[i] > EXP)
			break;
	}
	Setlevel(i);	

	cout << "��Ϸ������" << endl;
}

//�����߳���
void questioner::Play()
{
	if (DEBUG)
		cout << "questioner::Play is called" << endl;

	bool finish = false;

	while (!finish)
	{
		cout << "ϵͳ����������뵥�ʵĳ��ȣ�ע�ⲻ����20�����������Ϊ�����Ѷȣ����෽ʽ���£�" << endl
			<< "        4��      5���ַ�����" << endl
			<< "        6��      5-9���ַ�  " << endl
			<< "        8��      10���ַ�������,20���ַ�����" << endl;

		//��ȡ����
		cout << "����������Ҫ����ĵ��ʣ�һ��һ�����Իس����У���������׵Ļس���β" << endl;	
		string filename(".\\Dictionary.ini");
		char word[100] = { '\0' };

		while (cin.getline(word, 100, '\n')&&word[0]!='\0')
		{
			int length = 0;

			if (GoodWord(length, word))
				//���ݳ�����֯���ʣ�����ж����뵥�ʳ����Ƿ���Ϲ淶
			{
				if (SameWord(length, word))
				{
					memset(word, 0, sizeof(word));
					cout << "�õ����Ѵ��ڣ���������룡" << endl;
					continue;
				}
				stringstream ss;
				ss << length;
				string sectionname;
				ss >> sectionname;

				ss.str("");
				ss.clear();
				ss << GetPrivateProfileIntA(sectionname.c_str(), "number", 0, filename.c_str()) + 1;
				string keyname;
				ss >> keyname;

				//д���ĵ�����ˢ���ĵ��еĵ��ʸ���
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

		finish = true;
	}

	//�жϳ������Ƿ��������
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		if (QLevelUp[i] > Qnum)
			break;
	}
	Setlevel(i);

	cout << "��Ϸ������" << endl;
}

//�����Ѷȣ������ܹ��ĵ��������Լ���ǰ�ǵڼ������ʣ��Ӵʿ���ѡȡ�����ʵĵ���
string GetWord(int hard, int num, int allnum)
{
	if (DEBUG)
		cout << "GetWord is called!" << endl;

	srand(time(NULL));


	stringstream ss;
	string shard;
	ss << hard;
	ss >> shard;

	int number = GetPrivateProfileIntA(shard.c_str(), "number", 0, ".\\Dictionary.ini");

	ss.str("");
	ss.clear();
	ss << (rand() % (number / allnum) + (num - 1)*(number / allnum) + 1);
	string snum;
	ss >> snum;

	char word[30] = { '\0' };

	GetPrivateProfileStringA(shard.c_str(), snum.c_str(), "", word, sizeof(word), ".\\Dictionary.ini");

	return word;
}

//�жϳ����߸����ĵ����Ƿ�ϸ�
bool GoodWord(int& length, char *word)
{
	if (word[5] == '\0')
		length = 4;
	else if (word[5] != '\0'&&word[9] == '\0')
		length = 6;
	else if (word[9] != '\0'&&word[20] == '\0')
		length = 8;
	else
		return false;

	return true;
}

bool SameWord(int diff, char *word)
{
	bool Same = false;

	stringstream ss;
	ss << diff;
	string sdiff;
	ss >> sdiff;
	string filename(".\\Dictionary.ini");

	int num = GetPrivateProfileIntA(sdiff.c_str(), "number", 0, filename.c_str());

	for (int i = 1; i <= num; i++)
	{
		string skey;
		ss.str("");
		ss.clear();
		ss << i;
		ss >> skey;
		char tempword[100]{ '\0' };

		GetPrivateProfileStringA(sdiff.c_str(), skey.c_str(), "", tempword, sizeof(tempword), filename.c_str());
		
		if (strcmp(tempword, word) == 0)
			Same = true;
	}

	return Same;
}