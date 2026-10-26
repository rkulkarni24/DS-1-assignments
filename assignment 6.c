/*
    ASSIGNMENT 6 - EXPRESSION CONVERSION
    Problem Statement -
    Implement stack as an ADT and apply it for different expression conversions 
    (infix to postfix or infix to prefix (Any one), prefix to postfix or prefix to infix, 
    postfix to infix or postfix to prefix (Any one)).
*/ 

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#define MAX 100

int top = -1;
char stk[MAX];

int topS = -1;
char stkS[MAX][MAX];

int isFull() {
    if (top == MAX - 1) {
        return 1;
    } else {
        return 0;
    }
}

int isEmpty() {
    if (top == -1) {
        return 1;
    } else {
        return 0;
    }
}

int isFullS() {
    if (topS == MAX - 1) {
        return 1;
    } else {
        return 0;
    }
}

int isEmptyS() {
    if (topS == -1) {
        return 1;
    } else {
        return 0;
    }
}

void push(char s) {
    if (top < MAX - 1) {
        top++;
        stk[top] = s;
    }
}

char pop() {
    if (top == -1) {
        return '\0';
    }
    char save = stk[top];
    top--;
    return save;
}

void pushS(char s[MAX]) {
    if (topS < MAX - 1) {
        topS++;
        strcpy(stkS[topS], s);
    }
}

void popS(char elem[MAX]) {
    strcpy(elem, stkS[topS]);
    topS--;
}

int icpPS(char c) {
    if (c == '(') return 5;
    else if (c == '^') return 4;
    else if (c == '*' || c == '/' || c == '%') return 2;
    else if (c == '+' || c == '-') return 1;
    else return 0;
}

int ispPS(char c) {
    if (c == '(') return 0;
    else if (c == '^') return 3;
    else if (c == '*' || c == '/' || c == '%') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

int icpPF(char c) {
    if (c == ')') return 5;
    else if (c == '^') return 3;
    else if (c == '*' || c == '/' || c == '%') return 2;
    else if (c == '+' || c == '-') return 1;
    else return 0;
}

int ispPF(char c) {
    if (c == ')') return 0;
    else if (c == '^') return 4;
    else if (c == '*' || c == '/' || c == '%') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

bool isOp(char o) {
    return (o == '+' || o == '-' || o == '*' || o == '/' || o == '%' || o == '^' || o == '(' || o == ')');
}

void inToPostfix(char inf[MAX], char psf[MAX]) {
    int i = 0, k = 0;
    char ch;
    top = -1;

    while (inf[i] != '\0') {
        if (!isOp(inf[i])) {
            psf[k++] = inf[i];
        } else {
            if (inf[i] == '(') {
                push('(');
            } else if (inf[i] == ')') {
                while (!isEmpty() && (ch = pop()) != '(') {
                    psf[k++] = ch;
                }
            } else {
                while (!isEmpty() && ispPS(stk[top]) >= icpPS(inf[i])) {
                    ch = pop();
                    psf[k++] = ch;
                }
                push(inf[i]);
            }
        }
        i++;
    }

    while (!isEmpty()) {
        ch = pop();
        psf[k++] = ch;
    }

    psf[k] = '\0';
}

void prefixToInfix(char prf[MAX], char inf[MAX]) {
    char op1[MAX], op2[MAX], temp[MAX];
    char opStr[2] = {'\0', '\0'};
    int len = strlen(prf);
    topS = -1;

    for (int i = len - 1; i >= 0; i--) {
        if (!isOp(prf[i])) {
            char opnd[2] = {prf[i], '\0'};
            pushS(opnd);
        } else {
            popS(op1);
            popS(op2);

            opStr[0] = prf[i];

            strcpy(temp, "(");
            strcat(temp, op1);
            strcat(temp, opStr);
            strcat(temp, op2);
            strcat(temp, ")");

            pushS(temp);
        }
    }

    popS(inf);
}

void postfixToPrefix(char psf[MAX], char prf[MAX]) {
    char op1[MAX], op2[MAX], temp[MAX];
    char opStr[2] = {'\0', '\0'};
    topS = -1;

    for (int i = 0; psf[i] != '\0'; i++) {
        if (!isOp(psf[i])) {
            char opnd[2] = {psf[i], '\0'};
            pushS(opnd);
        } else {
            popS(op2);
            popS(op1);

            opStr[0] = psf[i];

            strcpy(temp, opStr);
            strcat(temp, op1);
            strcat(temp, op2);

            pushS(temp);
        }
    }

    popS(prf);
}

int main() {
    char infExp1[MAX];
    char posExp1[MAX];
    char prfExp2[MAX];
    char infExp2[MAX];
    char posExp3[MAX];
    char prfExp3[MAX];
    int choice;

    do {
        printf("\nEnter 1 to Convert Infix to Postfix\nEnter 2 to Convert Prefix to Infix\nEnter 3 to Convert Postfix to Prefix\nEnter 0 to Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter an Infix Expression: ");
                scanf("%s", infExp1);
                inToPostfix(infExp1, posExp1);
                printf("Output Postfix Expression : %s\n", posExp1);
                break;
            case 2:
                printf("Enter a Prefix Expression : ");
                scanf("%s", prfExp2);
                prefixToInfix(prfExp2, infExp2);
                printf("Output Infix Expression : %s\n", infExp2);
                break;
            case 3:
                printf("Enter a Postfix Expression : ");
                scanf("%s", posExp3);
                postfixToPrefix(posExp3, prfExp3);
                printf("Output Prefix Expression : %s\n", prfExp3);
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