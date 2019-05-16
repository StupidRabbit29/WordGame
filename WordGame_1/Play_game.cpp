#include"Class.h"

extern bool DEBUG;

//共15级，每级的单词难度和单词个数和单词显示时间
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

//闯关者升级所需要的EXP
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

//出题者升级所需要的出题数目
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

//闯关者的游戏
void player::Play()
{
	if (DEBUG)
		cout << "player::Play is called" << endl;

	//根据闯关者等级设置关卡难度
	int hard;
	int wordnum;
	int sleeptime;
	int userlevel = Getlevel();
	hard = GameDifficulty[userlevel - 1][0];
	wordnum = GameDifficulty[userlevel - 1][1];
	sleeptime = GameDifficulty[userlevel - 1][2];

	bool KO = true;

	//进入游戏
	for (int i = 0; i < wordnum && KO == true; i++)
	{
		//从词库中获取单词
		string word = GetWord(hard, i + 1, wordnum);

		cout << "准备！\t";
		for (int j = 0; j < 5; j++)
		{		
			Sleep(500);
			cout << (5 - j) << "\t";
		}
		//展示单词
		cout <<'\n'<< word;
		Sleep(sleeptime);
		cout << "\r" << "请输入您的答案：                                \n";

		clock_t start, finish, interval;
		start = clock();
		//读取用户输入
		string ans;
		cin >> ans;
		finish = clock();
		interval = finish - start;

		//判断答案正误
		if (strcmp(ans.c_str(), word.c_str()) == 0)
		{
			if(i<wordnum-1)
				cout << "答案正确，再接再厉，加油！" << endl;

			EXP += 100 + (hard - 2) * 10 + (i + 1) * 5 - (interval / CLOCKS_PER_SEC) * 3;
		}
		else
		{
			KO = false;
			cout << "答案错误，游戏结束！" << endl;
		}
	}

	//成功闯关数增加
	if (KO == true)
	{
		round++;
		cout << "闯关成功！\n";
	}
	
	//判断是否可以升级
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		if (PLevelUp[i] > EXP)
			break;
	}
	Setlevel(i);	

	cout << "游戏结束！" << endl;
}

//出题者出题
void questioner::Play()
{
	if (DEBUG)
		cout << "questioner::Play is called" << endl;

	bool finish = false;

	while (!finish)
	{
		cout << "系统会根据你输入单词的长度（注意不超过20个），将其分为三类难度，分类方式如下：" << endl
			<< "        4级      5个字符以内" << endl
			<< "        6级      5-9个字符  " << endl
			<< "        8级      10个字符及以上,20个字符以下" << endl;

		//读取单词
		cout << "请输入你想要输入的单词，一行一个，以回车换行，最后以行首的回车结尾" << endl;	
		string filename(".\\Dictionary.ini");
		char word[100] = { '\0' };

		while (cin.getline(word, 100, '\n')&&word[0]!='\0')
		{
			int length = 0;

			if (GoodWord(length, word))
				//根据长度组织单词，因此判断输入单词长度是否符合规范
			{
				if (SameWord(length, word))
				{
					memset(word, 0, sizeof(word));
					cout << "该单词已存在，请继续输入！" << endl;
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

				//写入文档，并刷新文档中的单词个数
				WritePrivateProfileStringA(sectionname.c_str(), keyname.c_str(), word, filename.c_str());
				WritePrivateProfileStringA(sectionname.c_str(), "number", keyname.c_str(), filename.c_str());
				
				memset(word, 0, sizeof(word));
				Qnum++;
			}
			else
			{
				cout << "单词长度不合适！请继续输入" << endl;
				memset(word, 0, sizeof(word));
			}
		}

		finish = true;
	}

	//判断出题者是否可以升级
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		if (QLevelUp[i] > Qnum)
			break;
	}
	Setlevel(i);

	cout << "游戏结束！" << endl;
}

//根据难度，本轮总共的单词数，以及当前是第几个单词，从词库中选取出合适的单词
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

//判断出题者给出的单词是否合格
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