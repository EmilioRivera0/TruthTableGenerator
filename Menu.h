// macro protection
#ifndef MENU_H
#define MENU_H
// necessary headers ---------------------------->
#include <stdio.h>

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: display the program's menu
-----------------------------------------------------------------------------------------------------------------------------------*/
int menu()
{
    int option;
    printf("\n\t\t-> Truth Table Generator <-\n\n");
    printf("1.- Generate Truth Table\n");
    printf("2.- Help\n");
    printf("0.- Exit\n\tOption -> ");
    scanf("%d", &option);
    return option;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: display the user help message
-----------------------------------------------------------------------------------------------------------------------------------*/
void help()
{
    printf("\n****************************HELP****************************\n");
    printf("\n- A PAIR PARENTHESES MUST ENCAPSULE THE WHOLE EXPRESSION!!!");
    printf("\n- Logic Operators:\n\t> Union/OR =\"U\"\n\t> Intersection/AND = \"^\" (alt + 94)\n\t> Conditional = \"->\"\n\t> Biconditional = \"<->\"\n\t> Negation/NOT = \"! / ~\" (alt + 126)");
    printf("\n- Variables must be LOWERCASE");
    printf("\n- You can use spaces if you want \' \'");
    printf("\n- Supports the use of \"[]\", \"{}\" and \"()\"\n");
    printf("\n*********************************************************\n");
}
#endif // !MENU_H