#include"Class.h"

extern bool DEBUG;
extern vector<player>Player;
extern vector<questioner>Questioner;
extern MySoc *TempBuffer[MAX_CLIENT];

//排名
void Rank(playertype type, MySoc * MsClient)
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

		//由于改变了排序，需要刷新迭代器位置
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			if (TempBuffer[i] && TempBuffer[i]->PlayerID != 0)
				RefreshUser(TempBuffer[i]->PlayerID, PLAYER, TempBuffer[i]);
		}
		
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

		//由于改变了排序，需要刷新迭代器位置
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			if (TempBuffer[i] && TempBuffer[i]->QuestionerID != 0)
				RefreshUser(TempBuffer[i]->QuestionerID, PLAYER, TempBuffer[i]);
		}
	}
}

//对player比较，用于sort
bool cmp(player& a, player& b)
{
	return (a.Getlevel() > b.Getlevel()
		|| a.Getlevel() == b.Getlevel() && a.GetEXP() > b.GetEXP());
}
bool cmp1(player& a, player& b)
{
	return (a.Getround() > b.Getround());
}

//对questioner比较，用于sort
bool cmq(questioner& a, questioner& b)
{
	return (a.Getlevel() > b.Getlevel()
		|| a.Getlevel() == b.Getlevel() && a.GetQnum() > b.GetQnum());
}

//根据ID刷新迭代器
void RefreshUser(const int ID, playertype type, MySoc * MsClient)
{
	if (type == PLAYER)
	{
		for (auto it = Player.begin(); it != Player.end(); it++)
		{
			//找到用户，刷新迭代器
			if ((*it).GetID() == ID)
			{
				MsClient->itp = it;
				break;
			}
		}
	}
	else
	{
		for (auto it = Questioner.begin(); it != Questioner.end(); it++)
		{
			//找到用户，刷新迭代器
			if ((*it).GetID() == ID)
			{
				MsClient->itq = it;
				break;
			}
		}
	}
}

//展示排名
void ShowRank(MySoc * MsClient)
{
	//开始发送排名
	send(MsClient->sClient, "BeginToSendRankTable", MSGSIZE, 0);
	
	send(MsClient->sClient, "闯关者排名：", MSGSIZE, 0);
	for (auto it = Player.begin(); it != Player.end(); it++)
	{
		send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
		Info info;
		(*it).Showinfo(info);
		//发送闯关者信息
		send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
	}

	send(MsClient->sClient, "出题者排名：", MSGSIZE, 0);
	for (auto it = Questioner.begin(); it != Questioner.end(); it++)
	{
		send(MsClient->sClient, "BeginToShowInfo", MSGSIZE, 0);
		Info info;
		(*it).Showinfo(info);
		//发送出题者信息
		send(MsClient->sClient, (char*)&info, MSGSIZE, 0);
	}

	send(MsClient->sClient, "SendRankTableEND", MSGSIZE, 0);
}

