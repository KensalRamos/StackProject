/*
 *
 * COP 3502C Midterm Assignment One
 * This program is written by: Kensal J Ramos
 * 
 * Description: This program will take an infix as input, and display the postfix
 * expression of the input. After displaying the postfix, it should evaluate the 
 * postfix and display the result.
 * 
 * Input: 
 * - Infix expression (max length 50)
 * - Only positive integers
 * - Numbers can by single or multiple digits
 * - Infix symbols: +, -, /, *, ^, %, (,)
 * - Expression my contains imbalanced parantheses, check for it
 * - White-space allowed only between numbers and operators
 * 
 * Output:
 * - Postfix expression
 * - Result of postfix expression  
 * 
 * Requirements:
 * - Must use a stack
 * - Use main function provided
 * - Use the following functions:
 * (a) char* menu(): Display menu. 'e' to enter infix, 'x' to exit
 *               'e' - Take infix as input, and copy it into a dynamically allocated
 *                     string and return to main function.
 *               'x' - Copy 'exit' to a dynamically allocated string and return it.
 * 
 * (b) int isBalancedParenthesis(char *) - Take infix as expression and check balance.
 *                                         '1' - Balanced  
 *                                         '0' - Unbalanced
 * 
 * (c) int isOperator(char c) - Takes a char.
 *                              '1' - Operator
 *                              '0' - Not an operator
 * 
 * (d) int getOperatorProperty(char c) - Take an operator and return priority
 * 
 * (e) int convertToInt(char c) - Converts char digit to int digit
 * 
 * (f) int calculate(int a, int b, char op) - Returns result of operation
 *                                            Ex: '5,6,'+'' returns 11
 * 
 * CAN ONLY ADD 10 LINES TO MAIN FUNCTION
 * 
 */

// Pre-processor directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Stack structure
struct stack {
    char items[50];
    int top;
};

// Prototypes
char* menu();
int verify(char *);
int isBalancedParenthesis(char *);
int isOperator(char c);
int getOperatorProperty(char c);
int convertToInt(char c);
int calculate(int a, int b, char op);
void evaluate(char *);
// Stack operations
void push(struct stack *, char);
char pop(struct stack *);
void setTop(struct stack *);
void fill(struct stack *, char *);
char * convertToPostFix(struct stack *, char *);
int testPriority(char);




int main(void) {
    
    char *str;
    char postFix[50] = {0};
    struct stack stack;

    while (strcmp(str = menu(), "exit") != 0) {

       if (isBalancedParenthesis(str)) {
            setTop(&stack);
            fill(&stack, str);
            convertToPostFix(&stack, postFix);
            printf("Converted to postFix.");
            evaluate(postFix);
        }
        else
            printf("Parenthesis imbalanced");
            

        printf("\nPostfix is: ");
        for (int i = 0; postFix[i] != '\0'; i++) {
            printf("For loop %d: %c ", i, postFix[i]); 
        }

        while(getchar() != '\n'); 
    }

    return 0;
}

char * menu() {

    char *str;
    char c;
    char choice;
    int verif = 1;
    int i = 0;

    str = (char *) malloc(50 * sizeof(char));

    printf("\n- \t Welcome \t -");
    printf("\nEnter 'e' to evaluate an expression.");
    printf("\nEnter 'x' to exit\n");
    scanf("%c", &choice);

    do {
        if (choice == 'e') {

            printf("\nEnter an expression: ");
            scanf("%s", str);
            printf("You entered: %s", str);
            
            verif = verify(str);
            if (verif == 0) 
                printf("\nInvalid character entered. Please try again.");
            else 
                printf("\nSUCCESSFUL!");

        }
        else if (choice == 'x') {
            str = "exit";
            verif = 1;
        }
        else {
            printf("Invalid choice entered. Try again.\n");
            verif == 1;
        }
        
    } while (verif == 0);

    return str;
}

int verify(char *str) {

    int i = 0;
    int num;
    int result;

    while(str[i] != '\0') {
        num = (int) str[i];
        printf("\nstr[%d] is = %d\n", i, num);
        printf("It is ");
        if (isOperator(str[i]))
            printf("an operator.\n");
        else
            printf("not an aperator.\n");
            

        // Compares using ASCII table values
        if ((num >= 40 && num <= 43) || (num >= 47 && num <= 57) || num == 94 || num == 45 || num == 37) {
            result = 1;
        } 
        else {
            result = 0;
            break;
        }
        
        if (result == 0)
            break;
        i++;
    }

    return result;
}

int isBalancedParenthesis(char *str) {

    struct stack stack;
    int i = 0;
    int count;

    setTop(&stack);
    count = 0;


    while (str[i] != '\0') {
        
        if ((int)str[i] == 40) 
            push(&stack, str[i]);

        else if ((int)str[i] == 41) 
            if((int)pop(&stack) == 126)
                count = 1;
            else
                count = 0;

        i++;
    }

    if (stack.top == -1 && count == 0) 
        return 1;
    else 
        return 0;

}

int isOperator(char c) {

    int num = (int) c;

    if (num == 37 || (num >= 40 && num <= 43) || num == 45 || num == 47 || num == 94) 
        return 1;
    else
        return 0;
    
}

void push(struct stack *stack, char c) {

    // If it isn't full...
    if (stack->top < 50) {
        stack->items[++(stack->top)] = c;
        printf("\nAdded %c to a stack.", stack->items[stack->top]);
    }
    else
        printf("\nStack is full!");
    

}

char pop(struct stack *stack) {

    if (stack->top > -1) {
        stack->top--;
        return stack->items[stack->top + 1];
    }
    else if (stack->top == -1) {
        printf("\nStack is empty!");
        return '~';
    }
    

}

void setTop(struct stack *stack) {
    stack->top = -1;
}

void fill(struct stack *stack, char *str) {

    int i = 0;

    while(str[i] != '\0') {

        push(stack, str[i]);
        i++;

    }

}

char * convertToPostFix(struct stack *stack, char *postFix) {

    /*
    * Encounter Operand - appent to postfix string (str)
    * Encounter Operator - Check top of stack. If current operator has higher priority than
    *                       top of stack, push to top. Otherwise, if operator has lower
    *                       priority, pop until you get to a higher priority or end of stack
    */
    struct stack tempStack;
    int j = 0;
    int k = 0;

    // reset postFix values
    for (int i = 0; i < 50; i++)
        postFix[i] = '\0';


    setTop(&tempStack);
    for (int i = 0; i < stack->top + 1; i++) {

        printf("\n\nTop is: %d", tempStack.top);
        if (isOperator(stack->items[i])) {
            // If it is an open parentheses -> push it
            if ((int)stack->items[i] == 40) {
                printf("\nOpen parentheses detected. Pushing...");
                push(&tempStack, stack->items[i]);
            }

            // If it is a closed parentheses -> pop until open parentheses is found.
            else if ((int)stack->items[i] == 41) {
                printf("\nClosed parentheses detected. Pushing...");
                while ((int)tempStack.items[tempStack.top] != 40) {
                    j = 0;
                    // Get next empty space
                    while(postFix[j] != '\0')
                        j++;
                    postFix[j] = pop(&tempStack);
                } 
                j = 0;
            }
            // If the operator inside the temp array has greater priority -> push
            // Should also be the case if it is a number
            else if (testPriority(stack->items[i]) > testPriority(tempStack.items[tempStack.top])) {
                
                printf("\nItem in stack has greater priority than operator in tempStack. Pushed.");
                printf("\nTop is %d", tempStack.top);
                push(&tempStack, stack->items[i]);
                printf("\nTop is %d", tempStack.top);
                printf("\ntempStack now has %c at %d -> %c", tempStack.items[i], i, stack->items[i]);

            }
            // If the operator inside the postFix has same or lesses priority -> pop until empty or top case found
            else {
                j = 0;

                if (tempStack.top == -1) {
                    printf("\nEmpty stack. Pushing...");
                    push(&tempStack, stack->items[i]);
                }
                else {
                    printf("\nItem in stack has lesser priority than operator in tempStack. Popping until otherwise."); 

                    do {
                        // Get next empty space
                        while(postFix[j] != '\0') {
                            j++;
                        }
                        postFix[j] = pop(&tempStack);
                        printf("POSTFIX IS %c AT %d", postFix[j], j);
                        j = 0;
                    } while (testPriority(stack->items[i]) > testPriority(tempStack.items[i]) && tempStack.top != -1);

                    push(&tempStack, stack->items[i]);

                }
                j = 0;
            }
        }
        else {
            printf("\nItem %d, %c, in stack is a number. Appending to postFix.", i, stack->items[i]);

            // Get next empty space
            while(postFix[j] != '\0')
                j++;

            postFix[j] = stack->items[i];
            j = 0;
        }

    }
    j = 0;

    // We want to empty tempStack and put it into postFix. No overrites!

    printf("\n\ntempStack.top is %d", tempStack.top);
    while (tempStack.top != -1) {
        while (postFix[j] != '\0') 
            j++;

        if(tempStack.items[tempStack.top] != '(' || tempStack.items[tempStack.top] != '(')
            postFix[j] = pop(&tempStack);
        else
            pop(&tempStack);
             
        printf("\npostFix now has: %c at %d", postFix[j], j);
        j = 0;
    }

    return postFix;

}

// Char a will be the one inside tempStack.items
// Char b will be the one inside stack->items
// True if b has higher priority
int testPriority(char a) {


    switch(a) {
        case '^':
            return 3;
            break;
        case '*':
        case '/':
        case '%':
            return 2;
            break;
        case '+':
        case '-':
            return 1;
            break;
        default:
            return 0;
    }
        

}

int convertToInt(char c) {

    return (c - '0');
}

int calculate(int a, int b, char op) {

    switch(op) {
        case '*':
            return (a * b);
        case '/':
            return (a / b);
        case '^':
            return (pow(a, b));
        case '%':
            return (a % b);
        case '+':
            printf("\nAdding a and b");
            return (a + b);
        case '-':
            return (a - b);
        
    }

}

void evaluate(char *postFix) {

    struct stack temp;
    int i = 0, max = 0;
    char a, b;

    setTop(&temp);

    // Get the length of postFix
    while (postFix[max] != '\0')
        max++;

    for (i = 0; i < max; i++) {

        // If its a number... else
        if(!isOperator(postFix[i])) {
            printf("\nEncountered %c at %d", postFix[i], i);
            push(&temp, postFix[i]);
        }
        else {
            a = pop(&temp);
            printf("\na is: %c", a);
            b = pop(&temp);
            printf("\nb is: %c", b);
            printf("\nconvertToInt(a) = %d", convertToInt(a));
            printf("\nOperator is: %c", postFix[i]);
            push(&temp, calculate(convertToInt(a), convertToInt(b), postFix[i]));
        }
    }

    printf("\n\nResult is: %d", temp.items[temp.top]);

}