// macro protection
#ifndef PARENTHESESSTACK_H
#define PARENTHESESSTACK_H
// necessary headers ---------------------------->
#include <stdlib.h>

// data type declaration ---------------------------->
// simple stack to push and pop parentheses to check if the expression is correctly written and identify sub expressions
struct Parentheses_Stack
{
    char *parentheses;
    struct Parentheses_Stack *next;
};

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: push a parentheses into the parentheses_stack
-----------------------------------------------------------------------------------------------------------------------------------*/
struct Parentheses_Stack *push(struct Parentheses_Stack *stack, char *parentheses)
{
    // allocate memory to push the parentheses
    struct Parentheses_Stack *t = (struct Parentheses_Stack *)malloc(sizeof(struct Parentheses_Stack));
    t->parentheses = parentheses;
    t->next = NULL;
    if (stack == NULL)
        stack = t;
    else
    {
        t->next = stack;
        stack = t;
    }
    return stack;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: pop a parentheses from the parentheses_stack
-----------------------------------------------------------------------------------------------------------------------------------*/
struct Parentheses_Stack *pop(struct Parentheses_Stack *stack)
{
    struct Parentheses_Stack *t = NULL;
    if (stack != NULL)
    {
        t = stack;
        stack = stack->next;
        // deallocate memory of the eliminated Parentheses_Stack struct
        free(t);
    }
    return stack;
}
#endif // !PARENTHESESSTACH_H