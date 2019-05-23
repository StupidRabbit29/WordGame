#include"Class.h"

extern vector<player>Player;
extern vector<questioner>Questioner;
extern MySoc *TempBuffer[MAX_CLIENT];
extern int GameDifficulty[15][3];
extern int PLevelUp[15];

void VS(MySoc * MsClient1, MySoc * MsClient2)
{
	send(MsClient1->sClient, "��ʼ˫�˶�ս�������������ַ��Կ�ʼ��Ϸ��", MSGSIZE, 0);
	send(MsClient2->sClient, "��ʼ˫�˶�ս�������������ַ��Կ�ʼ��Ϸ��", MSGSIZE, 0);
	char start[MSGSIZE];
	recv(MsClient1->sClient, start, MSGSIZE, 0);
	recv(MsClient2->sClient, start, MSGSIZE, 0);

	vector<player>::iterator ptemp1;
	vector<player>::iterator ptemp2;
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (TempBuffer[i]&&TempBuffer[i]->PlayerID == MsClient1->PlayerID)
		{
			findUser(MsClient1->PlayerID, ptemp1);		
		}
		if (TempBuffer[i]&&TempBuffer[i]->PlayerID == MsClient2->PlayerID)
		{
			findUser(MsClient2->PlayerID, ptemp2);
		}
	}

	//���ݴ����ߵȼ����ùؿ��Ѷ�
	int hard;
	int wordnum;
	int sleeptime;
	int userlevel = (*ptemp1).Getlevel();
	hard = GameDifficulty[userlevel - 1][0];
	wordnum = GameDifficulty[userlevel - 1][1];
	sleeptime = GameDifficulty[userlevel - 1][2];

	bool KO = true;

	//������Ϸ
	for (int i = 0; i < wordnum && KO == true; i++)
	{
		//�Ӵʿ��л�ȡ����
		string word = GetWord(hard, i + 1, wordnum);
		char tempword[30] = { '\0' };
		strncpy_s(tempword, word.c_str(), 30);
		Game temp1;
		strcpy_s(temp1.word, tempword);
		temp1.sleeptime = sleeptime;
		temp1.inter = 0;
		temp1.right = false;
		temp1.i = i;
		temp1.wordnum = wordnum;

		Game temp2 = temp1;

		send(MsClient1->sClient, (char*)&temp1, sizeof(Game), 0);
		send(MsClient2->sClient, (char*)&temp2, sizeof(Game), 0);

		//�жϴ�����
		memset(&temp1, 0, sizeof(Game));
		memset(&temp2, 0, sizeof(Game));
		recv(MsClient1->sClient, (char*)&temp1, sizeof(Game), 0);
		recv(MsClient1->sClient, (char*)&temp2, sizeof(Game), 0);


		if (temp1.right == true&&(temp1.inter<=temp2.inter||temp2.right==false))
		{
			(*ptemp1).SetEXP((*ptemp1).GetEXP()+ 100 + (hard - 2) * 10 + (i + 1) * 5 - temp1.inter * 3);
		}
		else if (temp2.right == true && (temp1.inter > temp2.inter || temp1.right == false))
		{
			(*ptemp2).SetEXP((*ptemp2).GetEXP() + 100 + (hard - 2) * 10 + (i + 1) * 5 - temp2.inter * 3);
		}
		else
		{
			KO = false;
		}
	}

	string str1 = "��Ϸ���������������ַ����˳���Ϸ";
	string str2 = "";
	//�ɹ�����������
	if (KO == true)
	{
		(*ptemp1).Setround((*ptemp1).Getround() + 1);
		(*ptemp2).Setround((*ptemp2).Getround() + 1);
		str2 = "���سɹ���";
	}
	else
		str2 = "����ʧ�ܣ�";

	//�ж��Ƿ��������
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		if (PLevelUp[i] > (*ptemp1).GetEXP())
			break;
	}
	(*ptemp1).Setlevel(i);
	for (i = 0; i < 15; i++)
	{
		if (PLevelUp[i] >(*ptemp2).GetEXP())
			break;
	}
	(*ptemp2).Setlevel(i);

	str1 = str2 + str1;
	char end[MSGSIZE] = { '\0' };
	strcpy_s(end, str1.c_str());
	send(MsClient1->sClient, end, MSGSIZE, 0);
	send(MsClient2->sClient, end, MSGSIZE, 0);

	recv(MsClient1->sClient, end, MSGSIZE, 0);
	recv(MsClient2->sClient, end, MSGSIZE, 0);
}