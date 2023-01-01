// macro protection
#ifndef EXPRESSIONSOLVER_H
#define EXPRESSIONSOLVER_H
// necessary headers ---------------------------->
#include "Variable.h"
#include "Sub-Expressions.h"

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: return the array of values of either the variable or the expression that the character parameter points to
-----------------------------------------------------------------------------------------------------------------------------------*/
int *get_values(struct Sub_Expression *sub_expression_list, struct Variable *variable_list, char *character, int num_values)
{
    // check if the current character corresponds to a variable
    while (variable_list != NULL)
    {
        if (*variable_list->variable == *character)
        {
            // check if the variable is negated
            if (*(character - 1) == '!' || *(character - 1) == '~')
            {
                // original values
                int *begginning_values = variable_list->values;
                // new list for the negated values
                int *negated_values = (int *)malloc(sizeof(int[num_values]));
                // pointer to iterate through the new negated values array
                int *beggining_negated_values = negated_values;
                // negating each value from the original values array
                for (int i = 0; i < num_values; i++)
                {
                    if (*begginning_values == 1)
                        *beggining_negated_values = 0;
                    else
                        *beggining_negated_values = 1;

                    begginning_values++;
                    beggining_negated_values++;
                }
                return negated_values;
            }
            return variable_list->values;
        }

        variable_list = variable_list->next;
    }
    // check if the current character corresponds to a sub expression
    while (sub_expression_list != NULL)
    {
        if ((sub_expression_list->beginning == character) || (sub_expression_list->end == character))
        {
            // check if the sub expression is negated
            if ((*(sub_expression_list->beginning - 1) == '!' || *(sub_expression_list->beginning - 1) == '~') && sub_expression_list->already_negated != 1)
            {
                // original values
                int *begginning_values = sub_expression_list->values;
                // new list for the negated values
                int *negated_values = (int *)malloc(sizeof(int[num_values]));
                // pointer to iterate through the new negated values array
                int *beggining_negated_values = negated_values;
                // negating each value from the original values array
                for (int i = 0; i < num_values; i++)
                {
                    if (*begginning_values == 1)
                        *beggining_negated_values = 0;
                    else
                        *beggining_negated_values = 1;

                    begginning_values++;
                    beggining_negated_values++;
                }
                return negated_values;
            }
            return sub_expression_list->values;
        }

        sub_expression_list = sub_expression_list->next;
    }
    return NULL;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
- Functionality: solve the main logic expression by solving each sub expression, from smaller/simpler sub expression to the outter 
    and more complex sub expressions until 
-----------------------------------------------------------------------------------------------------------------------------------*/
void expression_solver(struct Sub_Expression *sub_expression_list, struct Variable *variable_list, int num_values)
{
    // pointer to iterate through the sub_expression_list
    struct Sub_Expression *temp = sub_expression_list;
    // pointer to store the values array of temp 
    int *beginning;

    // pointers to store the character and values of the left and right sides of each sub expression
    char *left_char = NULL;
    int *left_values = NULL;
    char *right_char = NULL;    
    int *right_values = NULL;

    /* iterating through each sub expression and solving it, starting from smaller and inner sub expression to the more complex 
    and outer ones */
    while (temp != NULL)
    {
        beginning = temp->values;
        /* identifying the operator of the sub expression and based on it, solve and initialize the values array of that given 
        expression */
        switch (*(temp->op))
        {
        // union/or
        case 'U':
            right_char = temp->op + 1;
            if (*right_char == '!' || *right_char == '~')
                right_char++;
            left_char = temp->op - 1;

            right_values = get_values(sub_expression_list, variable_list, right_char, num_values);
            left_values = get_values(sub_expression_list, variable_list, left_char, num_values);

            for (int i = 1; i <= num_values; i++)
            {
                if ((*right_values == 1) || (*left_values == 1))
                    *(temp->values) = 1;
                else
                    *(temp->values) = 0;

                right_values++;
                left_values++;
                temp->values++;
            }
            break;
        // intersection/and
        case '^':
            right_char = temp->op + 1;
            if (*right_char == '!' || *right_char == '~')
                right_char++;
            left_char = temp->op - 1;

            right_values = get_values(sub_expression_list, variable_list, right_char, num_values);
            left_values = get_values(sub_expression_list, variable_list, left_char, num_values);

            for (int i = 1; i <= num_values; i++)
            {
                if ((*right_values == 1) && (*left_values == 1))
                    *(temp->values) = 1;
                else
                    *(temp->values) = 0;

                right_values++;
                left_values++;
                temp->values++;
            }
            break;
        // biconditional
        // <->
        case '<':
            right_char = temp->op + 3;
            if (*right_char == '!' || *right_char == '~')
                right_char++;
            left_char = temp->op - 1;

            right_values = get_values(sub_expression_list, variable_list, right_char, num_values);
            left_values = get_values(sub_expression_list, variable_list, left_char, num_values);

            for (int i = 1; i <= num_values; i++)
            {
                if (*left_values == *right_values)
                    *(temp->values) = 1;
                else
                    *(temp->values) = 0;

                right_values++;
                left_values++;
                temp->values++;
            }
            break;
        // conditional
        // ->
        case '-':
            right_char = temp->op + 2;
            if (*right_char == '!' || *right_char == '~')
                right_char++;
            left_char = temp->op - 1;

            right_values = get_values(sub_expression_list, variable_list, right_char, num_values);
            left_values = get_values(sub_expression_list, variable_list, left_char, num_values);

            for (int i = 1; i <= num_values; i++)
            {
                if (*left_values == 1 && *right_values == 0)
                    *(temp->values) = 0;
                else
                    *(temp->values) = 1;

                right_values++;
                left_values++;
                temp->values++;
            }
            break;
        }
        
        
        // negate the values obtained for the given sub expression if it is negated 
        if (*(temp->beginning - 1) == '!' || *(temp->beginning - 1) == '~')
        {
            int *begginning_values = beginning;
            temp->already_negated = 1;
            for (int i = 0; i < num_values; i++)
            {
                if (*begginning_values == 1)
                    *begginning_values = 0;
                else
                    *begginning_values = 1;

                begginning_values++;
            }
        }
        
        temp->values = beginning;
        temp = temp->next;
    }
}
#endif // !EXPRESSIONSOLVER_H