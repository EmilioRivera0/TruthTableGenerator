// macro protection
#ifndef VARIABLE_H
#define VARIABLE_H
// necessary headers ---------------------------->
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// data type declaration ---------------------------->
// struct that will store each variable from the logic expression
struct Variable
{
    // pointer to the variable in the main logic expression
    char *variable;
    // int pointer to store an array of the values that the variable will have in the truth table
    int *values;
    struct Variable *next;
};

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: simple function to queue a new variable in the variable_list
-----------------------------------------------------------------------------------------------------------------------------------*/
struct Variable *queue(struct Variable *list, char *var)
{
    struct Variable *q;
    struct Variable *p = (struct Variable *)malloc(sizeof(struct Variable));
    p->variable = var;
    p->values = NULL;
    p->next = NULL;

    if (list == NULL)
        list = p;
    else
    {
        q = list;
        while (q->next != NULL)
        {
            q = q->next;
        }
        q->next = p;
    }
    return list;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: checks if the current variable is already stored in the variable_list
-----------------------------------------------------------------------------------------------------------------------------------*/
bool check_if_var_repeats(struct Variable *list, char *c)
{
    bool repeats = false;
    while (list != NULL)
    {
        if (*(list->variable) == *c)
        {
            repeats = true;
            break;
        }
        list = list->next;
    }
    return repeats;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: set the basic values for each variable (either 0 or 1)
-----------------------------------------------------------------------------------------------------------------------------------*/
struct Variable *set_var_values(struct Variable *list, int *num_values)
{
    // case when there are no variables
    if (*num_values == 1)
        return list;
    // case with when there is only one variable
    else if (*num_values == 2)
    {
        int values[] = {0, 1};
        list->values = values;
    }
    // case when there are 2 or more vaiables
    else
    {
        // variable pointer to iterate through each variable
        struct Variable *p = list;
        // constant array used to allocate all the new value arrays for each variable
        const int ARR[*num_values];
        int *values_pointer;
        // counts the amount of times each value (1/0) repeats in the array
        int count = 1;
        // can only be 1 or 0 (used to fill the values of each variable)
        int val = 0;
        // represents the times a value (0/1) has been inserted in the array, so the funcion knows when to change the value (0/1)
        int rep = 1;
        // iterating through all the variables
        while (p != NULL)
        {
            // assign newly allocated array to each variable
            p->values = values_pointer = (int *)malloc(sizeof(ARR));
            // iterate through each array element and assign it its corresponding value
            for (int i = 1; i <= *num_values; i++)
            {
                if (rep < count)
                {
                    *values_pointer = val;
                    rep++;
                }
                else if (rep == count)
                {
                    *values_pointer = val;
                    rep = 1;
                    if (val == 1)
                        val = 0;
                    else
                        val = 1;
                }
                values_pointer++;
            }
            count *= 2;
            p = p->next;
        }
    }
    return list;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: iterate through the logic expression to identify and queue variables
-----------------------------------------------------------------------------------------------------------------------------------*/
struct Variable *set_variables(struct Variable *list, char *expression, int *num_values)
{
    bool is_var;

    // iterate through the entire expression looking for any letter
    while (*expression != '\000')
    {
        is_var = true;
        switch (*expression)
        {
        case 'U':
            is_var = false;
            break;
        case '^':
            is_var = false;
            break;
        case '-':
            is_var = false;
            break;
        case '<':
            is_var = false;
            break;
        case '>':
            is_var = false;
            break;
        case '!':
            is_var = false;
            break;
        case '~':
            is_var = false;
            break;
        case '{':
            is_var = false;
            break;
        case '}':
            is_var = false;
            break;
        case '(':
            is_var = false;
            break;
        case ')':
            is_var = false;
            break;
        case '[':
            is_var = false;
            break;
        case ']':
            is_var = false;
            break;
        case ' ':
            is_var = false;
        }

        // if it is a new variable, queue it to the variable_list
        if (is_var && !check_if_var_repeats(list, expression))
        {
            list = queue(list, expression);
            // multiply by 2 the current number of possible values for each variable
            *num_values = *num_values * 2;
            
        }
        expression++;
    }
    // set values of each variable
    list = set_var_values(list, num_values);
    return list;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: output variables on the console
-----------------------------------------------------------------------------------------------------------------------------------*/
void write_variables(struct Variable *list, int num_values)
{
    // here the program will store the amount of variables the list contains
    int num_var = 0;
    int *beginning;
    for (int i = num_values; i != 1; i = i / 2)
        num_var++;
    printf("\n-----------------------------------\n");
    for (int j = 1; j <= num_var; j++)
    {
        printf(" %c -> ", *(list->variable));
        beginning = list->values;
        for (int k = 1; k <= num_values; k++)
        {
            printf("%i ", *(list->values));
            list->values++;
        }
        printf("\n");
        list->values = beginning;
        list = list->next;
    }
    printf("-----------------------------------\n");
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: deallocate all the memory used by each variable struct and the variable_list
-----------------------------------------------------------------------------------------------------------------------------------*/
void deallocate_variables(struct Variable *variable_list)
{
    struct Variable *temp;
    while (variable_list != NULL)
    {
        temp = variable_list;
        free(variable_list->values);
        variable_list = variable_list->next;
        free(temp);
    }
}
#endif // !VARIABLE_H