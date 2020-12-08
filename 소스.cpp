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

int mainMenu();  // 메뉴번호를 return해주는 함수 선택된
void Newmember(bool*, Membership*);
// 새로운 고객 정보을 Membership(struct)에 저장해주는함수, bool* OX를 flag로 이용하여 배열의 할당 안된 부분에 할당
void MemberDPALL(bool*, Membership*);
// Membership(struct)형태에 저장된 회원 정보를 출력해주는 함수
void pointIn(MS*, HD** hisARR, bool** HOX);
// strcmp를 이용하여 입력된 전화번호와 저장된 전화번호를 대조하여 Membership(struct),MS(struct)에서 해당 전화번호의 위치를 찾아 포인트 추가
void pointOut(MS*, HD** hisARR, bool** HOX);
// void(MS*)와 동일하지만 포인트 차감 원리 동일
void Memberclear(bool*, MS*, HD** hisARR, bool** HOX);
// // strcmp를 이용하여 입력된 전화번호와 저장된 전화번호를 대조하여 Membership(struct),MS(struct)에서 해당 전화번호의 위치를 찾아 회원정보 말소
void history_make(int TYP, int point, int, HD**,bool**);



int main()
{
	int ERR = 10101;  // main함수는 모두 while문에서 작동하는데 ERR값이 10101일때만 작동, 값을 바꿔 프로그램 종료
	Membership* list;  // 회원의 이름, 전화번호, 포인트가 저장되는 구조체
	list = (Membership*)malloc(sizeof(Membership) * Maximum_member);
	for (int i = 0; i < Maximum_member; i++)
	{
		memset(&list[i], 0, sizeof(Membership));
	}
	// 구조체 배열을 메모리에 할당하고 초기화
	bool* OX;  // flag로 사용되는 bool배열
	OX = (bool*)malloc(sizeof(bool) * Maximum_member);
	for (int i = 0; i < Maximum_member; i++)
	{
		memset(&OX[i], 0, sizeof(bool));
	}
	//배열을 메모리에 할당하고 초기화
	History** hisARR;
	hisARR = (HD**)malloc(8 * Maximum_member);
	for (int i = 0; i < Maximum_member; i++)
	{
		hisARR[i] = (HD*)malloc(sizeof(HD) * MAXIMUM_HISTORY_DATA);
		memset(&hisARR[i], 0, sizeof(HD));
	}
	// 포인터 형태의 2중배열을 만들고 메모리를 할당 및 초기화
	bool** HOX;
	HOX = (bool**)malloc(8 * Maximum_member);
	for (int i = 0; i < Maximum_member; i++)
	{
		HOX[i] = (bool*)malloc(sizeof(bool) * MAXIMUM_HISTORY_DATA);
		memset(&HOX[i], 0, sizeof(bool));
	}
	// 포인터 형태의 2중배열을 만들고 메모리를 할당 및 초기화 , 내역의 flag로 활용되는 배열


	while (ERR == 10101)  // 기본적으로 작동하는 함수는 모두 이 while문에서 작동 , 종료시에 ERR값을 바꿔 종료
	{
		system("cls");
		int Menuval = mainMenu();
		// 콘솔창을 정리하고 메뉴 선택 함수 호출
		switch (Menuval)  // switch 문을 이용하여 mainMenu() 함수에서 반환된 값에 해당하는 기능으로 이동시켜줌
		{
		case 0: // 포인트 적립
		{
			system("cls");
			pointIn(list,hisARR,HOX);
			break;
		}//case
		case 1: // 포인트 사용
		{
			system("cls");
			pointOut(list,hisARR,HOX);
			break;
		}//case
		case 2: // 신규 고객
		{
			system("cls");
			Newmember(OX, list);
			break;
		}//case
		case 3: // 고객 말소
		{
			system("cls");
			Memberclear(OX, list,hisARR,HOX);
			break;
		}//case
		case 4: // 고객 조회
		{
			system("cls");
			MemberDPALL(OX, list);
			break;
		}//case
		case 5: // 이용내역
		{
			system("cls");
			printf("\n\n\t\t\t미구현 기능");
			Sleep(2000);
			break;
		}//case
		case 10: // 종료
		{
			system("cls");
			printf("=============================================================\n");

			for (int i = 1; i < 6; i++)
			{
				ERR = 0;  // ERR값을 바꿔 더이상 while문을 탈출하여 종료시킴
				int x = 6 - i;  // 카운트 다운 효과를 위해 사용
				printf("프로그램을 종료합니다.(%d초후 자동종료)", x);
				Sleep(1000);
				system("cls");
				printf("=============================================================\n");
			}
			break;
		}//case
		}
	}

}


int mainMenu()  // 메뉴를 선택하도록 하는 함수 선택된 값에 따라서 다른 정수값 반환 main함수의 switch 문으로 처리
{
	int val = 10101;
	int cal = 10101;
	printf("\t\t   고객 포인트 관리\n");
	printf("=============================================================\n");
	printf("\t적립     : %d \t\t사용 : %d\n\t고객관리 : %d\t        종료 : %d\n",point_in,point_out,manage_member,manage_end);
	// 0=적립, 1=사용, 2=신규 고객, 3=고객 삭제, 4=고객조회, 5=이용내역, 10=종료
	printf("=============================================================\n");
	printf(" 메뉴 번호 : ");
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
		printf("\t\t\t 고객 관리\n");
		printf("=============================================================\n");
		printf("\t신규     : %d \t\t삭제 : %d\n\t고객조회 : %d\t        내역 : %d\n",new_member,clear_member,dp_member,history);
		printf("=============================================================\n");
		printf(" 메뉴 번호 : ");
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


void Newmember(bool* OX, Membership* list)  // 새로운 고객정보를 저장하는 함수
{

	int val = 0;
	for (int i = 0; i < Maximum_member; i++)  // flag로 사용되는 bool* OX 배열을 확인하여 MS* list배열의 미사용 원소를 확인하여 int val에 저장
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
	printf(" 회원 이름 : ");
	scanf_s("%s", &(list[val].name), 20);
	printf(" 회원 전화번호 : ");
	scanf_s("%s", &(list[val]).tel, 20);
	OX[val] = TRUE;  // flag로 사용되는 OX*를 수정
}
void MemberDPALL(bool* OX, Membership* list)  //저장된 모든 회원정보 저장
{
	printf("\t\t  전체 회원 조회\n");
	printf("=============================================================\n");
	printf("이름\t\t 전화번호\t\t 포인트\n");
	printf("=============================================================\n");
	for (int i = 0; i < Maximum_member; i++)
	{
		if (OX[i] == 1)
			printf("%s\t\t %s\t\t %d\n", list[i].name, list[i].tel, list[i].point);
		else
		{

		}
	}
	system("pause");  //퍼즈를 걸어 정보확인 하게함

}

void pointIn(MS* list, HD** hisARR, bool** HOX)
{
	char innum[20];
	int Ival = 10101;
	int pointval = 0;
	memset(&innum, 0, sizeof(innum));
	printf("\t\t  포인트 적립\n");
	printf("=============================================================\n");
	printf("회원 전화번호 : ");
	scanf_s("%s", &innum, sizeof(innum));
	for (int i = 0; i < Maximum_member; i++)  // 입력된 전화번호와 저장된 회원의 전화번호를 대조 strcmp함수 이용
	{
		int cal = strcmp(innum, list[i].tel);
		if (cal == 0)  //같으면 Ival의 값을 i로 저장하여 MS* 구조체에서의 위치 확인(원소번호)
		{
			Ival = i;
		}
		else
		{

		}//일치하는 전화번호가 없으면 Ival은 초기값인 10101로 유지
	}
	if (Ival == 10101)  // Ival이 10101이면 
	{
		system("cls");
		printf("\t\t  포인트 적립\n");
		printf("=============================================================\n");
		printf("\n\t\t회원조회 불가");
		Sleep(2000);
	}
	else  // Ival이 10101이 아니면
	{
		system("cls");
		printf("\t\t  포인트 적립\n");
		printf("=============================================================\n");
		printf("회원 이름 : %s\n 적립할 포인트 : ", list[Ival].name);
		scanf_s("%d", &pointval);
		list[Ival].point += pointval;
		history_make(1,pointval,Ival,hisARR,HOX);
		system("cls");
		printf("\t\t  포인트 적립\n");
		printf("=============================================================\n");
		printf("\t\t회원명 : %s\n\n\t\t%dpoint 적립\n\n\t\t총 포인트 : %d", list[Ival].name, pointval, list[Ival].point);
		Sleep(2000);
	}

}
void pointOut(MS* list, HD** hisARR, bool** HOX)  // void pointIn(MS* list)와 동일 포인트 가감만 다름
{
	char innum[20];
	int Ival = 10101;
	int pointval = 0;
	memset(&innum, 0, sizeof(innum));
	printf("\t\t  포인트 차감\n");
	printf("=============================================================\n");
	printf("회원 전화번호 : ");
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
		printf("\t\t  포인트 차감\n");
		printf("=============================================================\n");
		printf("\n\t\t회원조회 불가");
		Sleep(2000);
	}
	else
	{
		system("cls");
		printf("\t\t  포인트 차감\n");
		printf("=============================================================\n");
		printf("회원 이름 : %s\n 차감할 포인트 : ", list[Ival].name);
		scanf_s("%d", &pointval);
		list[Ival].point -= pointval;
		history_make(0, pointval, Ival, hisARR, HOX);
		system("cls");
		printf("\t\t  포인트 적립\n");
		printf("=============================================================\n");
		printf("\t\t회원명 : %s\n\n\t\t%dpoint 차감\n\n\t\t잔여 포인트 : %d", list[Ival].name, pointval, list[Ival].point);
		Sleep(2000);
	}

}

void Memberclear(bool* OX, MS* list, HD** hisARR, bool** HOX)
{
	char innum[20];
	int Ival = 10101;
	int check = 0;

	memset(&innum, 0, sizeof(innum));
	printf("\t\t  회원 탈퇴\n");
	printf("=============================================================\n");
	printf("회원 전화번호 : ");
	scanf_s("%s", &innum, sizeof(innum));
	for (int i = 0; i < Maximum_member; i++)  // void pointIn(MS* list),void pointOut(MS* list) 함수와 동일한 부문 
	{
		int cal = strcmp(innum, list[i].tel);
		if (cal == 0)
		{
			Ival = i;
		}
		else
		{

		}
	}      // 여기까지 동일함
	if (Ival == 10101)
	{
		system("cls");
		printf("\t\t  회원 탈퇴\n");
		printf("=============================================================\n");
		printf("\n\t\t회원조회 불가");
		Sleep(2000);
	}
	else  //회원정보흫 말소
	{
		system("cls");
		printf("\t\t  회원 탈퇴\n");
		printf("=============================================================\n");
		printf("\t\t회원 이름 : %s\t\t\n\n회원 전화번호 : %s\t\t\n\n보유 포인트 : %d\n", list[Ival].name, list[Ival].tel, list[Ival].point);
		printf("\n\n\t\t 일치하면 1 아니면 0을 입력하세요.\n\t\t : ");
		scanf_s("%d", &check);
		if (check == 1)
		{
			memset(&list[Ival], 0, sizeof(MS));
			memset(&list[Ival], 0, sizeof(bool));
			OX[Ival] = FALSE;
			memset(&HOX[Ival], 0, sizeof(bool)*MAXIMUM_HISTORY_DATA);
			memset(&hisARR[Ival], 0, sizeof(HD) * MAXIMUM_HISTORY_DATA);
			system("cls");
			printf("\t\t  회원 탈퇴\n");
			printf("=============================================================\n");
			printf("\n\n\t\t 처리완료!!!!");
			Sleep(2000);

		}
		else
		{
			system("cls");
			printf("\t\t  회원 탈퇴\n");
			printf("=============================================================\n");
			printf("\n\n\t\t 미처리");
			Sleep(2000);
		}
	}
}


void history_make(int TYP, int point, int MN, HD** hisARR, bool** HOX)
{
	int val = 0;
	for (int i = 0; i < Maximum_member; i++)  // flag로 사용되는 bool* OX 배열을 확인하여 MS* list배열의 미사용 원소를 확인하여 int val에 저장
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