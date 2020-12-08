#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<time.h>

#define Maximum_member 100
#define  MAXIMUM_HISTORY_DATA 100

typedef struct _membership
{
	char name[20];
	char tel[20];
	int point;
}Membership, MS;

typedef struct _history_detail
{
	int IO;
	int point;
}History, HD;

enum MENU {point_in=1,point_out=2,new_member=1,clear_member=2,dp_member=3,history=4,manage_end=4,manage_member=3};

int mainMenu();  // �޴���ȣ�� return���ִ� �Լ� ���õ�
void Newmember(bool*, Membership*);
// ���ο� �� ������ Membership(struct)�� �������ִ��Լ�, bool* OX�� flag�� �̿��Ͽ� �迭�� �Ҵ� �ȵ� �κп� �Ҵ�
void MemberDPALL(bool*, Membership*);
// Membership(struct)���¿� ����� ȸ�� ������ ������ִ� �Լ�
void pointIn(MS*, HD** hisARR, bool** HOX);
// strcmp�� �̿��Ͽ� �Էµ� ��ȭ��ȣ�� ����� ��ȭ��ȣ�� �����Ͽ� Membership(struct),MS(struct)���� �ش� ��ȭ��ȣ�� ��ġ�� ã�� ����Ʈ �߰�
void pointOut(MS*, HD** hisARR, bool** HOX);
// void(MS*)�� ���������� ����Ʈ ���� ���� ����
void Memberclear(bool*, MS*, HD** hisARR, bool** HOX);
// // strcmp�� �̿��Ͽ� �Էµ� ��ȭ��ȣ�� ����� ��ȭ��ȣ�� �����Ͽ� Membership(struct),MS(struct)���� �ش� ��ȭ��ȣ�� ��ġ�� ã�� ȸ������ ����
void history_make(int TYP, int point, int, HD**,bool**);



int main()
{
	int ERR = 10101;  // main�Լ��� ��� while������ �۵��ϴµ� ERR���� 10101�϶��� �۵�, ���� �ٲ� ���α׷� ����
	Membership* list;  // ȸ���� �̸�, ��ȭ��ȣ, ����Ʈ�� ����Ǵ� ����ü
	list = (Membership*)malloc(sizeof(Membership) * Maximum_member);
	for (int i = 0; i < Maximum_member; i++)
	{
		memset(&list[i], 0, sizeof(Membership));
	}
	// ����ü �迭�� �޸𸮿� �Ҵ��ϰ� �ʱ�ȭ
	bool* OX;  // flag�� ���Ǵ� bool�迭
	OX = (bool*)malloc(sizeof(bool) * Maximum_member);
	for (int i = 0; i < Maximum_member; i++)
	{
		memset(&OX[i], 0, sizeof(bool));
	}
	//�迭�� �޸𸮿� �Ҵ��ϰ� �ʱ�ȭ
	History** hisARR;
	hisARR = (HD**)malloc(8 * Maximum_member);
	for (int i = 0; i < Maximum_member; i++)
	{
		hisARR[i] = (HD*)malloc(sizeof(HD) * MAXIMUM_HISTORY_DATA);
		memset(&hisARR[i], 0, sizeof(HD));
	}
	// ������ ������ 2�߹迭�� ����� �޸𸮸� �Ҵ� �� �ʱ�ȭ
	bool** HOX;
	HOX = (bool**)malloc(8 * Maximum_member);
	for (int i = 0; i < Maximum_member; i++)
	{
		HOX[i] = (bool*)malloc(sizeof(bool) * MAXIMUM_HISTORY_DATA);
		memset(&HOX[i], 0, sizeof(bool));
	}
	// ������ ������ 2�߹迭�� ����� �޸𸮸� �Ҵ� �� �ʱ�ȭ , ������ flag�� Ȱ��Ǵ� �迭


	while (ERR == 10101)  // �⺻������ �۵��ϴ� �Լ��� ��� �� while������ �۵� , ����ÿ� ERR���� �ٲ� ����
	{
		system("cls");
		int Menuval = mainMenu();
		// �ܼ�â�� �����ϰ� �޴� ���� �Լ� ȣ��
		switch (Menuval)  // switch ���� �̿��Ͽ� mainMenu() �Լ����� ��ȯ�� ���� �ش��ϴ� ������� �̵�������
		{
		case 0: // ����Ʈ ����
		{
			system("cls");
			pointIn(list,hisARR,HOX);
			break;
		}//case
		case 1: // ����Ʈ ���
		{
			system("cls");
			pointOut(list,hisARR,HOX);
			break;
		}//case
		case 2: // �ű� ��
		{
			system("cls");
			Newmember(OX, list);
			break;
		}//case
		case 3: // �� ����
		{
			system("cls");
			Memberclear(OX, list,hisARR,HOX);
			break;
		}//case
		case 4: // �� ��ȸ
		{
			system("cls");
			MemberDPALL(OX, list);
			break;
		}//case
		case 5: // �̿볻��
		{
			system("cls");
			printf("\n\n\t\t\t�̱��� ���");
			Sleep(2000);
			break;
		}//case
		case 10: // ����
		{
			system("cls");
			printf("=============================================================\n");

			for (int i = 1; i < 6; i++)
			{
				ERR = 0;  // ERR���� �ٲ� ���̻� while���� Ż���Ͽ� �����Ŵ
				int x = 6 - i;  // ī��Ʈ �ٿ� ȿ���� ���� ���
				printf("���α׷��� �����մϴ�.(%d���� �ڵ�����)", x);
				Sleep(1000);
				system("cls");
				printf("=============================================================\n");
			}
			break;
		}//case
		}
	}

}


int mainMenu()  // �޴��� �����ϵ��� �ϴ� �Լ� ���õ� ���� ���� �ٸ� ������ ��ȯ main�Լ��� switch ������ ó��
{
	int val = 10101;
	int cal = 10101;
	printf("\t\t   �� ����Ʈ ����\n");
	printf("=============================================================\n");
	printf("\t����     : %d \t\t��� : %d\n\t������ : %d\t        ���� : %d\n",point_in,point_out,manage_member,manage_end);
	// 0=����, 1=���, 2=�ű� ��, 3=�� ����, 4=����ȸ, 5=�̿볻��, 10=����
	printf("=============================================================\n");
	printf(" �޴� ��ȣ : ");
	scanf_s("%d", &cal);
	switch (cal)
	{
	case 1:
	{
		system("cls");
		val = 0;
		break;
	}
	case 2:
	{
		system("cls");
		val = 1;
		break;
	}
	case 3:
	{
		int cal2 = 10101;
		system("cls");
		printf("\t\t\t �� ����\n");
		printf("=============================================================\n");
		printf("\t�ű�     : %d \t\t���� : %d\n\t����ȸ : %d\t        ���� : %d\n",new_member,clear_member,dp_member,history);
		printf("=============================================================\n");
		printf(" �޴� ��ȣ : ");
		scanf_s("%d", &cal2);
		switch (cal2)
		{
		case 1:
		{
			system("cls");
			val = 2;
			break;
		}
		case 2:
		{
			system("cls");
			val = 3;
			break;
		}
		case 3:
		{
			system("cls");
			val = 4;
			break;
		}
		case 4:
		{
			system("cls");
			val = 5;
			break;
		}
		}
		break;
	}
	case 4:
	{
		system("cls");
		val = 10;
		break;
	}
	}
	return val;
}


void Newmember(bool* OX, Membership* list)  // ���ο� �������� �����ϴ� �Լ�
{

	int val = 0;
	for (int i = 0; i < Maximum_member; i++)  // flag�� ���Ǵ� bool* OX �迭�� Ȯ���Ͽ� MS* list�迭�� �̻�� ���Ҹ� Ȯ���Ͽ� int val�� ����
	{
		val = i;
		if (OX[i] == 0)
		{
			break;
		}
		else
		{

		}
	}
	printf(" ȸ�� �̸� : ");
	scanf_s("%s", &(list[val].name), 20);
	printf(" ȸ�� ��ȭ��ȣ : ");
	scanf_s("%s", &(list[val]).tel, 20);
	OX[val] = TRUE;  // flag�� ���Ǵ� OX*�� ����
}
void MemberDPALL(bool* OX, Membership* list)  //����� ��� ȸ������ ����
{
	printf("\t\t  ��ü ȸ�� ��ȸ\n");
	printf("=============================================================\n");
	printf("�̸�\t\t ��ȭ��ȣ\t\t ����Ʈ\n");
	printf("=============================================================\n");
	for (int i = 0; i < Maximum_member; i++)
	{
		if (OX[i] == 1)
			printf("%s\t\t %s\t\t %d\n", list[i].name, list[i].tel, list[i].point);
		else
		{

		}
	}
	system("pause");  //��� �ɾ� ����Ȯ�� �ϰ���

}

void pointIn(MS* list, HD** hisARR, bool** HOX)
{
	char innum[20];
	int Ival = 10101;
	int pointval = 0;
	memset(&innum, 0, sizeof(innum));
	printf("\t\t  ����Ʈ ����\n");
	printf("=============================================================\n");
	printf("ȸ�� ��ȭ��ȣ : ");
	scanf_s("%s", &innum, sizeof(innum));
	for (int i = 0; i < Maximum_member; i++)  // �Էµ� ��ȭ��ȣ�� ����� ȸ���� ��ȭ��ȣ�� ���� strcmp�Լ� �̿�
	{
		int cal = strcmp(innum, list[i].tel);
		if (cal == 0)  //������ Ival�� ���� i�� �����Ͽ� MS* ����ü������ ��ġ Ȯ��(���ҹ�ȣ)
		{
			Ival = i;
		}
		else
		{

		}//��ġ�ϴ� ��ȭ��ȣ�� ������ Ival�� �ʱⰪ�� 10101�� ����
	}
	if (Ival == 10101)  // Ival�� 10101�̸� 
	{
		system("cls");
		printf("\t\t  ����Ʈ ����\n");
		printf("=============================================================\n");
		printf("\n\t\tȸ����ȸ �Ұ�");
		Sleep(2000);
	}
	else  // Ival�� 10101�� �ƴϸ�
	{
		system("cls");
		printf("\t\t  ����Ʈ ����\n");
		printf("=============================================================\n");
		printf("ȸ�� �̸� : %s\n ������ ����Ʈ : ", list[Ival].name);
		scanf_s("%d", &pointval);
		list[Ival].point += pointval;
		history_make(1,pointval,Ival,hisARR,HOX);
		system("cls");
		printf("\t\t  ����Ʈ ����\n");
		printf("=============================================================\n");
		printf("\t\tȸ���� : %s\n\n\t\t%dpoint ����\n\n\t\t�� ����Ʈ : %d", list[Ival].name, pointval, list[Ival].point);
		Sleep(2000);
	}

}
void pointOut(MS* list, HD** hisARR, bool** HOX)  // void pointIn(MS* list)�� ���� ����Ʈ ������ �ٸ�
{
	char innum[20];
	int Ival = 10101;
	int pointval = 0;
	memset(&innum, 0, sizeof(innum));
	printf("\t\t  ����Ʈ ����\n");
	printf("=============================================================\n");
	printf("ȸ�� ��ȭ��ȣ : ");
	scanf_s("%s", &innum, sizeof(innum));
	for (int i = 0; i < Maximum_member; i++)
	{
		int cal = strcmp(innum, list[i].tel);
		if (cal == 0)
		{
			Ival = i;
		}
		else
		{

		}
	}
	if (Ival == 10101)
	{
		system("cls");
		printf("\t\t  ����Ʈ ����\n");
		printf("=============================================================\n");
		printf("\n\t\tȸ����ȸ �Ұ�");
		Sleep(2000);
	}
	else
	{
		system("cls");
		printf("\t\t  ����Ʈ ����\n");
		printf("=============================================================\n");
		printf("ȸ�� �̸� : %s\n ������ ����Ʈ : ", list[Ival].name);
		scanf_s("%d", &pointval);
		list[Ival].point -= pointval;
		history_make(0, pointval, Ival, hisARR, HOX);
		system("cls");
		printf("\t\t  ����Ʈ ����\n");
		printf("=============================================================\n");
		printf("\t\tȸ���� : %s\n\n\t\t%dpoint ����\n\n\t\t�ܿ� ����Ʈ : %d", list[Ival].name, pointval, list[Ival].point);
		Sleep(2000);
	}

}

void Memberclear(bool* OX, MS* list, HD** hisARR, bool** HOX)
{
	char innum[20];
	int Ival = 10101;
	int check = 0;

	memset(&innum, 0, sizeof(innum));
	printf("\t\t  ȸ�� Ż��\n");
	printf("=============================================================\n");
	printf("ȸ�� ��ȭ��ȣ : ");
	scanf_s("%s", &innum, sizeof(innum));
	for (int i = 0; i < Maximum_member; i++)  // void pointIn(MS* list),void pointOut(MS* list) �Լ��� ������ �ι� 
	{
		int cal = strcmp(innum, list[i].tel);
		if (cal == 0)
		{
			Ival = i;
		}
		else
		{

		}
	}      // ������� ������
	if (Ival == 10101)
	{
		system("cls");
		printf("\t\t  ȸ�� Ż��\n");
		printf("=============================================================\n");
		printf("\n\t\tȸ����ȸ �Ұ�");
		Sleep(2000);
	}
	else  //ȸ������ň ����
	{
		system("cls");
		printf("\t\t  ȸ�� Ż��\n");
		printf("=============================================================\n");
		printf("\t\tȸ�� �̸� : %s\t\t\n\nȸ�� ��ȭ��ȣ : %s\t\t\n\n���� ����Ʈ : %d\n", list[Ival].name, list[Ival].tel, list[Ival].point);
		printf("\n\n\t\t ��ġ�ϸ� 1 �ƴϸ� 0�� �Է��ϼ���.\n\t\t : ");
		scanf_s("%d", &check);
		if (check == 1)
		{
			memset(&list[Ival], 0, sizeof(MS));
			memset(&list[Ival], 0, sizeof(bool));
			OX[Ival] = FALSE;
			memset(&HOX[Ival], 0, sizeof(bool)*MAXIMUM_HISTORY_DATA);
			memset(&hisARR[Ival], 0, sizeof(HD) * MAXIMUM_HISTORY_DATA);
			system("cls");
			printf("\t\t  ȸ�� Ż��\n");
			printf("=============================================================\n");
			printf("\n\n\t\t ó���Ϸ�!!!!");
			Sleep(2000);

		}
		else
		{
			system("cls");
			printf("\t\t  ȸ�� Ż��\n");
			printf("=============================================================\n");
			printf("\n\n\t\t ��ó��");
			Sleep(2000);
		}
	}
}


void history_make(int TYP, int point, int MN, HD** hisARR, bool** HOX)
{
	int val = 0;
	for (int i = 0; i < Maximum_member; i++)  // flag�� ���Ǵ� bool* OX �迭�� Ȯ���Ͽ� MS* list�迭�� �̻�� ���Ҹ� Ȯ���Ͽ� int val�� ����
	{
		val = i;
		if (HOX[MN][i] == 0)
		{
			break;
		}
		else
		{

		}
	}
	HOX[MN][val] = TRUE;
	hisARR[MN][val].IO = TYP;
	hisARR[MN][val].point = point;

}