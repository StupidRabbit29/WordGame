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


}