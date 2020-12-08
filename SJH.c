#include "SJH.h"

typedef struct _MENU
{
    Deposit,
    Withdraw,
    Join_Member,
    Delete_Member,
    Display_Member,
    View_History
}MENU;


int mainMenu(); // 메뉴를 선택하도록 하는 함수

/*
main() 함수에서는 거래원장 원본을 생성하고,
회원들을 저장할 구조체 포인터를 생성한다.
*/
int main()
{
    Ledger masterLedger;    // 거래원장 원본(최상위 거래원장)
    _Ledger_Initialize(&masterLedger);  // 거래원장 초기화
    MemberList masterMemberList;    // 최상위 이용자 명단
    _MemberList_Initialize(&masterMemberList);  // 명단 초기화
    
}

int mainMenu()
{
    system("cls");
    int menuVal =
}