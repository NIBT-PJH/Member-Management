#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXIMUM_NUMBER 100
#define SIZE_OF_MEMBER_NAME 20
#define SIZE_OF_MEMBER_TEL 20
#define SIZE_OF_MEMBER_PW 4
#define SIZE_OF_TRANSACTION_COMMENT 20
#define SIZE_OF_LEDGER_ALLOCATE 20

// 이용자의 현재 상태를 나타냄
typedef enum _MemberStatus
{
    Normal,
    Stopped,
    Terminated
}MemberStatus;

// 시간을 정의함
typedef struct tm TimeStruct;

// 이용자의 정보를 저장함
typedef struct _Member
{
    char* name[SIZE_OF_MEMBER_NAME];
    char* tel[SIZE_OF_MEMBER_TEL];
    MemberStatus status;  // 이용자의 현재 상태를 나타냄
    size_t ID;  // 이용자의 ID를 저장함.
    char* PW[SIZE_OF_MEMBER_PW];    // 이용자의 PW를 저장함.
}Member;

// 거래 내역의 한 행을 구성함.
typedef struct _Transaction
{
    TimeStruct time;    // 시간을 나타내는 구조체
    size_t memberID;    // 이용자의 ID를 저장함
    size_t transactionID;   // 해당 거래의 ID를 저장함
    int amount; // 거래금액을 나타냄
    char* comment[SIZE_OF_TRANSACTION_COMMENT];  // 적요 항목을 저장
}Transaction;

// 거래 내역 전반을 구성함
typedef struct _Ledger
{
    Transaction* trasnactionList;   // 거래 내역을 저장함
    size_t ledgerLen;   // 거래 내역의 개수를 저장함
    size_t ledgerMaxLen;    // 할당받은 원장의 길이를 저장함
}Ledger;

// Member의 메소드 프로토타입
int _Member_initialize(Member*, size_t);    // 구조체 초기화(ID 부여)
int _Member_setName(Member*, const char*);  // name 설정 함수
int _Member_setTel(Member*, const char*);   // tel 설정 함수
int _Member_setPW(Member*, const char*);    // PW 설정 함수
int _Member_setStatus(Member*, MemberStatus);   // status 설정 함수

char* _Member_getName(Member*);    // name 반환 함수
char* _Member_getTel(Member*);  // tel 반환 함수
size_t _Member_getID(Member*);  // ID 반환 함수
MemberStatus _Member_getStatus(Member*);    // status 반환 함수

int _Member_checkPW(Member*, const char*);   // PW 확인 함수, 이상이 없으면 0 반환

// Transaction의 메소드 프로토타입
int _Transaction_initialize(Transaction*);  // Transaction의 초기화 함수
int _Transaction_setItem(Transaction*, TimeStruct, size_t, size_t, int, const char*);   // Transaction의 값 설정
int _Transaction_copy(Transaction*, Transaction*);  // Transcation의 복사 함수

// Ledger의 메소드 프로토타입
int _Ledger_initialize(Ledger*);    // 구조체 초기화(동적 할당)

int _Ledger_Withdraw(Ledger*, Member*, int, const char*, const char*);  // 출금 기능
int _Ledger_Deposit(Ledger*, Member*, int, const char*);    // 입금 기능 구현
int _Ledger_Write(Ledger*, size_t, int, const char*);   // 원장 기록 기능 구현
int _Ledger_Write_Transaction(Ledger*, Transaction*);   // 원장 기록 기능 구현(복사 전용)
int _Ledger_sizeCheck(Ledger*); // 원장의 길이의 여유분이 부족한 경우 메모리를 다시 할당받음

Ledger _Ledger_Search_Member(Ledger*, size_t);   // 검색 기능 구현
inline Ledger _Ledger_Search_Member_Ptr(Ledger*, Member*);  // 검색 기능 구현

int _Ledger_Balance(Ledger*);   // 원장 상의 잔액 조회

// 메소드 구현부

int _Member_initialize(Member* memberPtr, size_t ID)
{
    memset(memberPtr, 0, sizeof(Member));
    memberPtr->ID = ID;
    return 0;
}

int _Member_setName(Member* memberPtr, const char* name)
{
    if (strlen(name) > SIZE_OF_MEMBER_NAME)
    {
        return 1;   // name의 길이가 필드의 최대 길이를 넘어가면 에러 발생
    }
    strcpy(memberPtr->name, name);  // name을 복사한다.
    return 0;
}

int _Member_setTel(Member* memberPtr, const char* tel)
{
    if (strlen(tel) > SIZE_OF_MEMBER_TEL)
    {
        return 1;   // tel의 길이가 필드의 최대 길이를 넘어가면 에러 발생
    }
    strcpy(memberPtr->tel, tel);    // tel을 복사한다.
    return 0;
}

int _Member_setPW(Member* memberPtr, const char* PW)
{
    if (strlen(PW) > SIZE_OF_MEMBER_PW)
    {
        return 1;   // PW의 길이가 필드의 최대 길이를 넘어가면 에러 발생
    }
    strcpy(memberPtr->PW, PW);  // PW를 복사한다.
    return 0;
}

int _Member_setStatus(Member* memberPtr, MemberStatus status)
{
    memberPtr->status = status;
    return 0;
}

char* _Member_getName(Member* memberPtr)
{
    char returnName[SIZE_OF_MEMBER_NAME];
    strcpy(returnName, memberPtr->name);    // name을 복사함
    return returnName;
}

char* _Member_getTel(Member* memberPtr)
{
    char returnTel[SIZE_OF_MEMBER_TEL];
    strcpy(returnTel, memberPtr->tel);  // tel을 복사함
    return returnTel;
}

size_t _Member_getID(Member* memberPtr)
{
    return memberPtr->ID;
}

MemberStatus _Member_getStatus(Member* memberPtr)
{
    return memberPtr->status;
}

int _Member_checkPW(Member* memberPtr, const char* PW)
{
    if (strlen(PW) > SIZE_OF_MEMBER_PW)
    {
        return 1;   // PW의 길이가 필드의 최대 길이를 넘어가면 에러 발생
    }
    return strcmp(memberPtr->PW, PW);   // PW의 비교 결과를 return
}

int _Transaction_initialize(Transaction* transactionPtr)
{
    memset(transactionPtr, 0, sizeof(Transaction));
    return 0;
}

int _Transaction_setItem(Transaction* transactionPtr, TimeStruct time, size_t memberID, size_t transactionID, int amount, const char* comment)
{
    if (strlen(comment) > SIZE_OF_TRANSACTION_COMMENT)
    {
        return 1;   // comment의 길이가 필드의 최대 길이를 넘어가면 에러 발생
    }
    transactionPtr->time = time;
    transactionPtr->memberID = memberID;
    transactionPtr->transactionID = transactionID;
    transactionPtr->amount = amount;
    strcpy(transactionPtr->comment, comment);
    return 0;
}

int _Transaction_copy(Transaction* _dst, Transaction* _src)
{
    _dst->time = _src->time;
    _dst->memberID = _src->memberID;
    _dst->transactionID = _dst->transactionID;
    _dst->amount = _src->amount;
    strcpy(_dst->comment, _src->comment);
    return 0;
}

int _Ledger_initialize(Ledger* ledgerPtr)
{
    memset(ledgerPtr, 0, sizeof(Ledger));
    ledgerPtr->trasnactionList = (Transaction*)malloc(SIZE_OF_LEDGER_ALLOCATE*sizeof(Transaction));
    ledgerPtr->ledgerMaxLen = SIZE_OF_LEDGER_ALLOCATE;
    return 0;
}

int _Ledger_Withdraw(Ledger* ledgerPtr, Member* memberPtr, int amount, const char* PW, const char* comment)
{
    if (_Member_checkPW(memberPtr, PW))
    {
        return 1;   // PW가 실제와 다른 경우 에러
    }
    return _Ledger_Write(ledgerPtr, _Member_getID(memberPtr), amount, comment);
}

int _Ledger_Deposit(Ledger* ledgerPtr, Member* memberPtr, int amount, const char* comment)
{
    return _Ledger_Write(ledgerPtr, _Member_getID(memberPtr), amount*-1, comment);
}

int _Ledger_Write(Ledger* ledgerPtr, size_t memberID, int amount, const char* comment)
{
    _Ledger_sizeCheck(ledgerPtr);
    Transaction* targetTransaction = &ledgerPtr->trasnactionList[ledgerPtr->ledgerLen;
    
    time_t curTime;
    TimeStruct curTimeStruct;
    time(&curTime);
    localtime_s(&curTimeStruct, &curTime);

    if (!_Transaction_setItem(targetTransaction, curTimeStruct, memberID, ledgerPtr->ledgerLen, amount, comment))
    {
        // 정상적으로 입력된 경우 종료
        ++(ledgerPtr->ledgerLen);
        return 0;
    }
    else
    {
        // 정상적으로 입력되지 않은 경우 값을 초기화함
        _Transaction_initialize(targetTransaction);
        return 1;
    }    
}

int _Ledger_Write_Transaction(Ledger* ledgerPtr, Transaction* transactionPtr)
{
    _Ledger_sizeCheck(ledgerPtr);
    Transaction* targetTransaction = &(ledgerPtr->trasnactionList[ledgerPtr->ledgerLen]);

}

int _Ledger_sizeCheck(Ledger* ledgerPtr)
{
    if (ledgerPtr->ledgerLen == ledgerPtr->ledgerMaxLen)
    {
        // ledger에 여유분이 없는 경우 메모리를 다시 할당받아옴
        ledgerPtr = (Ledger*)realloc(ledgerPtr, ledgerPtr->ledgerMaxLen + SIZE_OF_LEDGER_ALLOCATE);
        ledgerPtr->ledgerMaxLen += SIZE_OF_LEDGER_ALLOCATE;
        for (size_t i = ledgerPtr->ledgerLen; i < ledgerPtr->ledgerMaxLen; ++i)
        {
            // 새로 할당받은 값들에 대해 값을 초기화함
            _Transaction_initialize(&ledgerPtr[i]);
        }
    }
    return 0;
}

Ledger _Ledger_Search_Member(Ledger* ledgerPtr, size_t memberID)
{
    Ledger returnLedger;
    _Ledger_initialize(&returnLedger);
    Transaction* transactionPtr = ledgerPtr->trasnactionList;
    for (size_t i = 0; i < ledgerPtr->ledgerLen; ++i)
    {
        // ledgerPtr의 기록 중에서 memberID와 일치하는 것이 있으면 returnLedger에 기록함
        if (transactionPtr->memberID == memberID)
        {
            _Ledger_Write_Transaction(&returnLedger, &transactionPtr[i]);
        }
    }
    return returnLedger;
}

inline Ledger _Ledger_Search_Member_Ptr(Ledger* ledgerPtr, Member* memberPtr)
{
    return _Ledger_Search_Member(ledgerPtr, memberPtr->ID);
}

int _Ledger_Balance(Ledger* ledgerPtr)
{
    int balance = 0;
    Transaction* transactionPtr = ledgerPtr->trasnactionList;
    for (size_t i = 0; i < ledgerPtr->ledgerLen; ++i)
    {
        balance += transactionPtr[i].amount;
    }
    return balance;
}