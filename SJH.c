#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXIMUM_NUMBER 100

typedef struct _Member
{
    char* name[20];
    char* tel[20];
    int point;
    short int flag;  // 현재 값이 초기값이면 0, 아니면 1
}Member;

// Member의 메소드 구현
int _Member_initialize(Member*);    // 구조체 초기화
int _Member_addPoint(Member*, int); // 포인트 추가 함수
int _Member_subPoint(Member*, int); // 포인트 감소 함수
int _Member_setName(Member*, const char*);  // 이름 설정 함수
int _Member_setTel(Member*, const char*);   // tel 설정 함수

const char* _Member_getName();  //


int mainMenu(); // 메뉴번호를 return
int newMember(Member*);
int memberDPALL(Member*);
int addPoint(Member*, int);  // 포인트 추가 함수
int subPoint(Member*, int);  // 포인트 감소 함수
int clearMember(Member*);


