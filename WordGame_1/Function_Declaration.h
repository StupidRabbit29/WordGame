#include"Class.h"

void GameControl(void);
void Sign_up(playertype type);
void Sign_in(playertype type);
bool samename(playertype type, const string& name);
void setpersonID(person* p);
bool findUser(string name, vector<player>::iterator& temp);
bool findUser(string name, vector<questioner>::iterator& temp);
bool checkpw(string password, person* user);



