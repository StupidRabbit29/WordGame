#include"Class.h"

extern bool DEBUG;

//共15级，每级的单词难度和单词个数
int GameDifficulty[15][2] = {
	{4, 1},
	{4, 2},
	{4, 3},
	{4, 4},
	{4, 5},
	{6, 3},
	{6, 4},
	{6, 5},
	{6, 6},
	{6, 7},
	{8, 5}, 
	{8, 6}, 
	{8, 7}, 
	{8, 8},
	{8, 9}
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
	int userlevel = Getlevel();
	hard = GameDifficulty[userlevel - 1][0];
	wordnum = GameDifficulty[userlevel - 1][1];

	bool KO = true;

	//进入游戏
	for (int i = 0; i < wordnum && KO == true; i++)
	{
		//从词库中获取单词
		string word = GetWord(hard, i + 1, wordnum);
		cout << word;
		//展示单词
		Sleep(2000);
		cout << "\r" << "请输入您的答案：";
		//读取用户输入
		string ans;
		cin >> ans;

		//判断答案正误
		if (strcmp(ans.c_str(), word.c_str()) == 0)
		{
			cout << "答案正确，再接再厉，加油！" << endl;
			EXP += 100;
		}
		else
		{
			KO = false;
			cout << "答案错误，游戏结束！" << endl;
		}
	}

	//成功闯关数增加
	if (KO == true)
		round++;
	
	//判断是否可以升级
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		if (PLevelUp[i] > EXP)
			break;
	}
	Setlevel(i);

	//对所有玩家重新排名
	Rank(PLAYER);

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
		cout << "输入1，退出游戏！" << endl << "请输入你想要添加的单词难度，4级（4），6级（6），8级（8）：" << endl
			<< "              4级      5个字符以内" << endl
			<< "              6级      5-9个字符  " << endl
			<< "              8级      10个字符及以上,20个字符以下" << endl;

		int choice = 1;
		//用户选择
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

		//退出游戏
		if (choice == 1)
			break;

		//读取单词
		cout << "请输入你想要输入的单词，一行一个，以回车换行，最后以行首的回车结尾" << endl;	
		string filename(".\\Dictionary.ini");
		stringstream ss;
		ss << choice;
		string sectionname;
		ss >> sectionname;				
		char word[21] = { '\0' };

		while (cin.getline(word, 20, '\n')&&word[0]!='\0')
		{
			if (GoodWord(choice, word))
				//根据长度组织单词，因此判断输入单词长度是否符合规范
			{
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
	}

	//判断出题者是否可以升级
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		if (QLevelUp[i] > Qnum)
			break;
	}
	Setlevel(i);

	//对所有出题者进行排名
	Rank(QUESTIONER);

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