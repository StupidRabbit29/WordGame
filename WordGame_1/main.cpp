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
	cout << "******************��ӭ��������������Ϸ_02****************" << endl;

	//������Ϸ
	GameControl();

	return 0;
}