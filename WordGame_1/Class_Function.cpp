#include"Class.h"

void person::setbasicinfo(string name, string password)
{
	if (DEBUG)
		cout << "person::setbasicinfo\n";
	
	//�����û������û�����
	this->name = name;
	this->password = password;
}


/*3����Ϣ�����������Ϸ�ߺͳ����˵���Ϣ�����������û���Ϣ���*/
//�û���Ϣ���
void person::Showinfo()
{
	if (DEBUG)
		cout << "person::Showinfo" << endl;

	//��ӡ�û�������Ϣ
	cout << "�û���:" << name << endl 
		<< "�ȼ�:" << level << endl 
		<< "����:" << rank << endl;
}
//��Ϸ�ߵ���Ϣ���
void player::Showinfo()
{
	person::Showinfo();

	if (DEBUG)
		cout << "player::Showinfo" << endl;

	//��ӡ��Ϸ����Ϣ
	cout << "����ֵ:" << EXP << endl
		<< "�ɹ�������:" << round << endl;
}
//�����˵���Ϣ���
void questioner::Showinfo()
{
	person::Showinfo();

	if (DEBUG)
		cout << "questioner::Showinfo" << endl;

	//��ӡ��������Ϣ
	cout << "������:" << Qnum << endl;
}