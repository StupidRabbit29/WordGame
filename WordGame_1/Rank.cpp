#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern vector<player>::iterator itp;
extern vector<questioner>::iterator itq;
extern int PlayerID;
extern int QuestionerID;

//����
void Rank(playertype type)
{
	if (DEBUG)
		cout << "rank is called" << endl;

	if (type == PLAYER)
		//�Դ���������
	{
		sort(Player.begin(), Player.end(), cmp);

		//���ô����ߵ�rank
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
		//�Գ���������
	{
		sort(Questioner.begin(), Questioner.end(), cmq);

		//���ó����ߵ�rank
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

//��player�Ƚϣ�����sort
bool cmp(player& a, player& b)
{
	return (a.Getlevel() > b.Getlevel()
		|| a.Getlevel() == b.Getlevel() && a.GetEXP() > b.GetEXP());
}
//��questioner�Ƚϣ�����sort
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

//չʾ����
void ShowRank()
{
	cout << "������������" << endl;
	for (auto it = Player.begin(); it != Player.end(); it++)
		(*it).Showinfo();

	cout << "������������" << endl;
	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		(*it).Showinfo();
}
