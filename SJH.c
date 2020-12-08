#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXIMUM_NUMBER 100

// 이용자의 현재 상태를 나타냄.
typedef enum _MemberStatus
{
    Normal,
    Stopped,
    Terminated
}MemberStatus;

typedef struct _Member
{
    char* name[20];
    char* tel[20];
    int point;
    MemberStatus stat;  // 
}Member;

typedef struct _Transaction
{
    struct tm time;    // 시간을 나타내는 구조체
    size_t ID;  // 이용자의 ID를 저장함.

}Transaction;

// Member의 메소드 구현
int _Member_initialize(Member*);    // 구조체 초기화
int _Member_addPoint(Member*, int); // 포인트 추가 함수
int _Member_subPoint(Member*, int); // 포인트 감소 함수
int _Member_setName(Member*, const char*);  // name 설정 함수
int _Member_setTel(Member*, const char*);   // tel 설정 함수

const char* _Member_getName();  // name 반환 함수
const char* _Member_getTel();   // tel 반환 함수


int mainMenu(); // 메뉴번호를 return
int newMember(Member*);
int memberDPALL(Member*);
int addPoint(Member*, int);  // 포인트 추가 함수
int subPoint(Member*, int);  // 포인트 감소 함수
int clearMember(Member*);


