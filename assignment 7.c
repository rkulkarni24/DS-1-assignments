/* 
    Assignment 7 - expression evaluation
    Problem Statement -     Write a C program to evaluate postfix expression using stack.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

int evalStk[MAX];
int evalTop = -1;

int isFull() {
    if (evalTop == MAX - 1) {
        return 1;
    } else {
        return 0;
    }
}

int isEmpty() {
    if (evalTop == -1) {
        return 1;
    } else {
        return 0;
    }
}

void pushEval(int val) {
    if (evalTop < MAX - 1) {
        evalStk[++evalTop] = val;
    }
}

int popEval() {
    if (evalTop == -1) {
        return 0;
    }
    return evalStk[evalTop--];
}

bool isOp(char o) {
    return (o == '+' || o == '-' || o == '*' || o == '/' || o == '%' || o == '^');
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+' : return a + b;
        case '-' : return a - b;
        case '*' : return a * b;
        case '/' : return (b != 0) ? (a / b) : 0;
        case '%' : return (b != 0) ? (a % b) : 0;
        case '^' : return (int)round(pow(a, b));
        default:   return 0;
    }
}

int evalPostfix(char psf[]) {
    int valTable[26];
    bool hasVal[26];

    for (int i = 0; i < 26; i++) {
        valTable[i] = 0;
        hasVal[i] = false;
    }

    evalTop = -1;

    for (int i = 0; psf[i] != '\0'; i++) {
        char ch = psf[i];

        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
            continue;
        }

        if (isalpha((unsigned char)ch)) {
            int idx = tolower((unsigned char)ch) - 'a';

            if (!hasVal[idx]) {
                printf("Enter value for %c: ", ch);
                scanf("%d", &valTable[idx]);
                hasVal[idx] = true;
            }
            if (!isFull()) {
                pushEval(valTable[idx]);
            }
        } 
        else if (isdigit((unsigned char)ch)) {
            if (!isFull()) {
                pushEval(ch - '0');
            }
        } 
        else if (isOp(ch)) {
            if (evalTop >= 1) {
                int op2 = popEval();
                int op1 = popEval();
                if (!isFull()) {
                    pushEval(applyOp(op1, op2, ch));
                }
            } else {
                printf("Error: Insufficient operands for operator '%c'\n", ch);
                return 0;
            }
        }
    }

    if (!isEmpty()) {
        return popEval();
    }
    return 0;
}

int main() {
    char psfExp[MAX];
    int choice;

    do {
        printf("Enter 1 to Evaluate Postfix Expression\n");
        printf("Enter 0 to Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter Postfix Expression: ");
                scanf(" %99[^\n]", psfExp);
                printf("Evaluation Result: %d\n", evalPostfix(psfExp));
                break;

            case 0:
                printf("Exiting program\n");
                break;

            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);

    return 0;
}