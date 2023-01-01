// macro protection
#ifndef SUBEXPRESSION_H
#define SUBEXPRESSION_H
#include <stdio.h>
#include "Parentheses_Stack.h"

// data type delclaration ---------------------------->
// struct used to store each sub expression inside the main logic expression
struct Sub_Expression
{
    // pointers to enclosure the sub exrpession inside the main logic expression
    char *beginning, *end;
    // pointer to the logic operator of the sub expression
    char *op;
    // pointer to the array of values (1s and 0s) of the sub expression
    int *values;
    /* already_negated is to check if the sub expressions values had already been negated 
    to prevent obtaining the original values instead of the negated ones*/
    int already_negated;
    struct Sub_Expression *next;
};

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: declare, initialize and insert at the beginning of the sub_expression_list the new sub exrpession
-----------------------------------------------------------------------------------------------------------------------------------*/
struct Sub_Expression *insert_at_beginning(struct Sub_Expression *list, char *beginning, char *end, char *op, int num_values)
{
    // constant array used to allocate all the new value arrays for each variable
    int ARR[num_values];
    // declaration and initialization of the new sub expression to insert
    struct Sub_Expression *n = (struct Sub_Expression *)malloc(sizeof(struct Sub_Expression));
    // initializing the struct variables
    n->beginning = beginning;
    n->end = end;
    n->op = op;
    n->already_negated = 0;
    n->values = (int *)malloc(sizeof(ARR));
    n->next = NULL;
    if (list == NULL)
        list = n;
    else
    {
        n->next = list;
        list = n;
    }

    return list;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: initializes the sub_expression_list with all the sub expressions contained in the main logic expression
-----------------------------------------------------------------------------------------------------------------------------------*/
struct Sub_Expression *set_sub_expressions(struct Sub_Expression *sub_expression_list, char *expression, int num_values)
{
    // variable to work as the parentheses stack
    struct Parentheses_Stack *parentheses_stack = NULL;
    // pointers used to indicate the important parts of the expression
    char *end, *op = NULL;

    // iterating through the whole main logic expression
    do
    {
        // "({[" represent the beginning of a sub expression 
        if (*expression == '(' || *expression == '{' || *expression == '[')
        {
            // push the current "({[" into the stack
            parentheses_stack = push(parentheses_stack, expression);
            // initialize end and op to the its new values
            end = expression + 1;
            op = NULL;

            /* iterate through the rest of the main logic expression until the end of the sub expression is found (empty parentheses stack)
            or the end of the main expression is found */
            while (*end != '\000' && parentheses_stack != NULL)
            {

                // if a new openning "({[" is found, push it to the parentheses stack
                if (*end == '(' || *end == '{' || *end == '[')
                    parentheses_stack = push(parentheses_stack, end);
                // check if the current character is the corresponding operator to the current sub expression
                else if ((*end == 'U' || *end == '^' || *end == '-' || *end == '<') && parentheses_stack->next == NULL && op == NULL)
                    op = end;
                // if a closing "({[" is found, pop one element from the parentheses stack
                else if (*end == ')' || *end == '}' || *end == ']')
                {
                    /* if there is only one element left in the stack (meaning that the end of the current sub expression is reached)
                    insert the current sub expression into the sub_expression_list */
                    if (parentheses_stack->next == NULL)
                        sub_expression_list = insert_at_beginning(sub_expression_list, expression, end, op, num_values);

                    parentheses_stack = pop(parentheses_stack);
                }
                end++;
            }
        }
        expression++;
    } while (*expression != '\000');

    return sub_expression_list;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: output the sub expressions on the console
-----------------------------------------------------------------------------------------------------------------------------------*/
void write_sub_expresions(struct Sub_Expression *sub_expression_list, int num_values)
{
    char temp;
    int *beginning;
    printf("\n-----------------------------------\n");

    while (sub_expression_list != NULL)
    {
        sub_expression_list->end++;
        temp = *sub_expression_list->end;
        *sub_expression_list->end = '\000';
        if (*(sub_expression_list->beginning - 1) == '!' || *(sub_expression_list->beginning - 1) == '~')
            printf("Expression: !%s\n", sub_expression_list->beginning);
        else
            printf("Expression: %s\n", sub_expression_list->beginning);
        *sub_expression_list->end = temp;
        sub_expression_list->end--;
        printf("  -> ");
        beginning = sub_expression_list->values;
        for (int i = 1; i <= num_values; i++)
        {
            printf("%i ", *(sub_expression_list->values));
            sub_expression_list->values++;
        }
        printf("\n");
        sub_expression_list->values = beginning;
        sub_expression_list = sub_expression_list->next;
    }
    printf("-----------------------------------\n");
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: deallocate all the memory used by each variable struct and the sub_expression_list
-----------------------------------------------------------------------------------------------------------------------------------*/
void deallocate_expressions(struct Sub_Expression *sub_expression_list)
{
    struct Sub_Expression *temp;
    while (sub_expression_list != NULL)
    {
        temp = sub_expression_list;
        free(sub_expression_list->values);
        sub_expression_list = sub_expression_list->next;
        free(temp);
    }
}
#endif // !SUBEXPRESSION_H