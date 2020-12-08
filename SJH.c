#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXIMUM_NUMBER 100

// 이용자의 현재 상태를 나타냄
typedef enum _MemberStatus
{
    Normal,
    Stopped,
    Terminated
}MemberStatus;

// 이용자의 정보를 저장함
typedef struct _Member
{
    char* name[20];
    char* tel[20];
    MemberStatus stat;  // 이용자의 현재 상태를 나타냄
    size_t ID;  // 이용자의 ID를 저장함.
    char* PW[4];    // 이용자의 PW를 저장함.
}Member;

// 거래 내역의 한 행을 구성함.
typedef struct _Transaction
{
    struct tm time;    // 시간을 나타내는 구조체
    size_t Member_ID;  // 이용자의 ID를 저장함
    size_t Transaction_ID;  // 해당 거래의 ID를 저장함
    int volume; // 거래금액을 나타냄
    char* comment[20];  // 적요 항목을 저장
}Transaction;

// 거래 내역 전반을 구성함
typedef struct _Ledger
{
    Transaction* trasnactionList;   // 거래 내역을 저장함
}Ledger;

// Member의 메소드 구현
int _Member_initialize(Member*);    // 구조체 초기화(ID 부여)
int _Member_setName(Member*, const char*);  // name 설정 함수
int _Member_setTel(Member*, const char*);   // tel 설정 함수
int _Member_setPW(Member*, const char*);    // PW 설정 함수

const char* _Member_getName();  // name 반환 함수
const char* _Member_getTel();   // tel 반환 함수

// Ledger의 메소드 구현
int _Ledger_Withdraw(Ledger*, Member*, int, const char*, const char*);  // 출금 기능
int _Ledger_Deposit(Ledger*, Member*, int, const char*);    // 입금 기능 구현
Ledger _Ledger_Search_Member_ID(Ledger*, size_t);   // 검색 기능 구현
Ledger _Ledger_Search_Member_Ptr(Ledger, Member*);  // 검색 기능 구현


int mainMenu(); // 메뉴번호를 return
int newMember(Member*);
int memberDPALL(Member*);
int addPoint(Member*, int);  // 포인트 추가 함수
int subPoint(Member*, int);  // 포인트 감소 함수
int clearMember(Member*);


