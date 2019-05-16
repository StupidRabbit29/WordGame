#include"Class.h"

vector<player>Player;
vector<questioner>Questioner;
vector<player>::iterator itp;
vector<questioner>::iterator itq;
int PlayerID;
int QuestionerID;
const int MAX_USER_NUMBER = 1024;
bool DEBUG = false;
bool QuitSYSTEM = false;

int main()
{
	cout << "******************欢迎来到单词消除游戏_02****************" << endl;

	//进入游戏
	GameControl();

	return 0;
}