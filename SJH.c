#include "SJH.h"

typedef enum _MENU
{
    MENU_DEPOSIT,
    MENU_WITHDRAW,
    MENU_JOIN_MEMBER,
    MENU_DELETE_MEMBER,
    MENU_DISPLAY_MEMBER,
    MENU_VIEW_HISTORY,
    MENU_EXIT
}MENU;


MENU mainMenu();    // 메뉴를 선택하도록 하는 서브루틴

void printBar();    // 선을 출력해주는 서브루틴

// 메뉴들에 해당하는 서브루틴
int func_DEPOSIT(MemberList*, Ledger*);
int func_WITHDRAW(MemberList*, Ledger*);
int func_JOIN_MEMBER(MemberList*, Ledger*);
int func_DELETE_MEMBER(MemberList*, Ledger*);
int func_DISPLAY_MEMBER(MemberList*, Ledger*);
int func_VIEW_HISTORY(MemberList*, Ledger*);

/*
main() 함수에서는 거래원장 원본을 생성하고,
회원들을 저장할 구조체 포인터를 생성한다.
*/

int main()
{
    MemberList masterMemberList;    // 최상위 이용자 명단
    _MemberList_Initialize(&masterMemberList);  // 명단 초기화
    Ledger masterLedger;    // 거래원장 원본(최상위 거래원장)
    _Ledger_Initialize(&masterLedger);  // 거래원장 초기화

    // mainMenu() 함수 무한루프
    while (1)
    {
        switch (mainMenu())
        {
        case MENU_DEPOSIT:
            func_DEPOSIT(&masterMemberList, &masterLedger);
            break;

        case MENU_WITHDRAW:
            func_WITHDRAW(&masterMemberList, &masterLedger);
            break;
        
        case MENU_JOIN_MEMBER:
            func_JOIN_MEMBER(&masterMemberList, &masterLedger);
            break;
        
        case MENU_DELETE_MEMBER:
            func_DELETE_MEMBER(&masterMemberList, &masterLedger);
            break;
        
        case MENU_DISPLAY_MEMBER:
            func_DISPLAY_MEMBER(&masterMemberList, &masterLedger);
            break;
        
        case MENU_VIEW_HISTORY:
            func_VIEW_HISTORY(&masterMemberList, &masterLedger);
            break;
        
        default:
            system("cls");
            printBar();
            for (size_t i = 0; i < 5; ++i)
            {
                printf("Shut down after %d seconds", 5-i);
                Sleep(1000);
            }            
            return 0;
            break;
        }
    }
    
}

void printBar()
{
    printf("=============================================================\n");
}

MENU mainMenu()
{
    int menuNum = 0;

    system("cls");
    printf("Client point managing\n");
    printBar();
    printf("Add points : 1\n");
    printf("Use points : 2\n");
    printf("Client managing : 3\n");
    printf("Exit : else\n");
    printBar();
    printf("Input menu number : ");
    scanf_s("%d", &menuNum);

    switch (menuNum)
    {
    case 1:
        return MENU_DEPOSIT;
        break;
    
    case 2:
        return MENU_WITHDRAW;
        break;
    
    case 3:
        break;

    default:
        return MENU_EXIT;
        break;
    }

    menuNum = 0;
    
    system("cls");
    printf("Client manging");
    printBar();
    printf("Add client : 1\n");
    printf("Delete client : 2\n");
    printf("Display all cilent : 3\n");
    printf("Display client's history : 4\n");
    printf("Exit : else\n");
    printBar();
    printf("Input menu number : ");
    scanf_s("%d", &menuNum);

    switch (menuNum)
    {
    case 1:
        return MENU_JOIN_MEMBER;
        break;
    
    case 2:
        return MENU_DELETE_MEMBER;
        break;
    
    case 3:
        return MENU_DISPLAY_MEMBER;
        break;
    
    case 4:
        return MENU_VIEW_HISTORY;
        break;

    default:
        return MENU_EXIT;
        break;
    }
}

int func_DEPOSIT(MemberList* memberlistPtr, Ledger* ledgerPtr)
{
    system("cls");
    char buff[SIZE_OF_MEMBER_TEL];
    int amount;
    size_t targetIdx = 0;
    printf("Add points\n");
    printBar();
    printf("Client's TEL. : ");
    scanf_s("%s", &buff, SIZE_OF_MEMBER_TEL);

    for (size_t i = 0; i < memberlistPtr->len; ++i)
    {
        if (strcmp(memberlistPtr->memberPtr[i].tel, buff))
        {
            targetIdx = i + 1;
            break;
        }
    }
    
    if (targetIdx)
    {
        printf("Couldn't find the client with TEL.\n");
        return 1;
    }
    
    targetIdx -= 1;
    Member* targetMember = &(memberlistPtr->memberPtr[targetIdx]);
    memset(buff, 0, sizeof(buff));

    system("cls");
    printf("Add point\n");
    printBar();
    printf("Name of the client : %s\n", targetMember->name);
    printf("Points to add : ");
    scanf_s("%d", &amount);
    _Ledger_Deposit(ledgerPtr, targetMember, amount, "");
    printf("Points added successfully.\n");

    return 0;
}

int func_WITHDRAW(MemberList* memberlistPtr, Ledger* ledgerPtr)
{
    system("cls");
    char buff[SIZE_OF_MEMBER_TEL];
    int amount;
    size_t targetIdx = 0;
    printf("Use points\n");
    printBar();
    printf("Client's TEL. : ");
    scanf_s("%s", &buff, SIZE_OF_MEMBER_TEL);

    for (size_t i = 0; i < memberlistPtr->len; ++i)
    {
        if (strcmp(memberlistPtr->memberPtr[i].tel, buff))
        {
            targetIdx = i + 1;
            break;
        }
    }
    
    if (targetIdx)
    {
        printf("Couldn't find the client with TEL.\n");
        return 1;
    }
    
    targetIdx -= 1;
    Member* targetMember = &(memberlistPtr->memberPtr[targetIdx]);
    memset(buff, 0, sizeof(buff));

    system("cls");
    printf("Use point\n");
    printBar();
    printf("Name of the client : %s\n", targetMember->name);
    printf("Points to use : ");
    scanf_s("%d", &amount);

    printf("Password : ");
    scanf_s("%s", &buff, sizeof(char)*SIZE_OF_MEMBER_PW);

    if (!_Ledger_Withdraw(ledgerPtr, targetMember, amount, buff, ""))
    {
        printf("Points are used successfully.\n");
        return 0;
    }
    else
    {
        printf("Points are not used.\n");
        return 1;
    }    
}

int func_JOIN_MEMBER(MemberList* memberlistPtr, Ledger* ledgerPtr)
{
    
}