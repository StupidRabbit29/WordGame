#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;
extern int PlayerID;
extern int QuestionerID;

//排名
void Rank(playertype type)
{
	if (DEBUG)
		cout << "rank is called" << endl;

	if (type == PLAYER)
		//对闯关者排名
	{
		sort(Player.begin(), Player.end(), cmp);

		//设置闯关者的rank
		int i = 1;
		for (auto it = Player.begin(); it != Player.end(); it++)
		{
			(*it).Setrank(i);
			WriteUserfile(it);
			i++;
		}

		if (PlayerID != 0)
			RefreshUser(PlayerID, PLAYER);
	}
	else
		//对出题者排名
	{
		sort(Questioner.begin(), Questioner.end(), cmq);

		//设置出题者的rank
		int i = 1;
		for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		{
			(*it).Setrank(i);
			WriteUserfile(it);
			i++;
		}

		if (QuestionerID != 0)
			RefreshUser(QuestionerID, QUESTIONER);
	}
}

//对player比较，用于sort
bool cmp(player& a, player& b)
{
	return (a.Getlevel() > b.Getlevel()
		|| a.Getlevel() == b.Getlevel() && a.GetEXP() > b.GetEXP());
}
//对questioner比较，用于sort
bool cmq(questioner& a, questioner& b)
{
	return (a.Getlevel() > b.Getlevel()
		|| a.Getlevel() == b.Getlevel() && a.GetQnum() > b.GetQnum());
}

void RefreshUser(const int ID, playertype type)
{
	if (type == PLAYER)
	{
		for (auto it = Player.begin(); it != Player.end(); it++)
		{
			if ((*it).GetID() == ID)
			{
				itp = it;
				break;
			}
		}
	}
	else
	{
		for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		{
			if ((*it).GetID() == ID)
			{
				itq = it;
				break;
			}
		}
	}
}

//展示排名
void ShowRank()
{
	cout << "闯关者排名：" << endl;
	for (auto it = Player.begin(); it != Player.end(); it++)
		(*it).Showinfo();

	cout << "出题者排名：" << endl;
	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		(*it).Showinfo();
}
