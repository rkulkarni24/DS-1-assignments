/* 
    Assignment 5 - Circular Linked Lists Operations 
    Problem Statement - 
    Write a program to implement polynomial operations using a Circular Linked List. 
    The program should support the following operations:
    1.	Create a polynomial by inserting terms (coefficient and exponent). 
    2.	Display the polynomial in a readable mathematical form. 
    3.	Add two polynomials and display the resultant polynomial

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct polyTerm {
    float coef;
    int exp;
    struct polyTerm *next;
} polyTerm;

void createPoly(polyTerm *head) {
    char choice;
    printf("Do you want to add a term? Enter Y or N: ");
    scanf(" %c", &choice);

    while (choice == 'Y') {

        polyTerm *temp = (polyTerm *)malloc(sizeof(polyTerm));
        if (temp == NULL) {
            printf("Memory allocation failed\n");
            return;
        }

        printf("Enter coefficient: ");
        scanf("%f", &temp->coef);
        printf("Enter exponent: ");
        scanf("%d", &temp->exp);

        polyTerm *curr = head;
        while (curr->next != head) {
            curr = curr->next;
        }
        curr->next = temp;
        temp->next = head;

        printf("Do you want to add a term? Enter Y or N: ");
        scanf(" %c", &choice);
    }
}

void display(polyTerm *head) {
    if (head->next == head) {
        printf("Empty Polynomial\n");
        return;
    }

    polyTerm *temp = head->next;
    while (temp != head) {
        printf("%.2f*x^%d", temp->coef, temp->exp);
        temp = temp->next;
        if (temp != head) {
            printf(" + ");
        }
    }
    printf("\n");
}

void sortPoly(polyTerm *head) {
    if (head->next == head) {
        return;
    }

    polyTerm *curr1 = head->next;
    while (curr1 != head) {
        polyTerm *curr2 = curr1->next;
        while (curr2 != head) {
            if (curr1->exp < curr2->exp) {
                
                int etemp = curr1->exp;
                curr1->exp = curr2->exp;
                curr2->exp = etemp;

                
                float ctemp = curr1->coef;
                curr1->coef = curr2->coef;
                curr2->coef = ctemp;
            }
            curr2 = curr2->next;
        }
        curr1 = curr1->next;
    }
}

double evalPoly(polyTerm *head, int var) {
    polyTerm *temp = head->next;
    double result = 0;

    while (temp != head) {
        result = result + (temp->coef) * pow(var, temp->exp);
        temp = temp->next;
    }

    return result;
}

void addPoly(polyTerm *p1, polyTerm *p2, polyTerm *res) {
    polyTerm *temp1 = p1->next;
    polyTerm *temp2 = p2->next;
    polyTerm *last = res;

    while (temp1 != p1 && temp2 != p2) {
        polyTerm *newNode = NULL;

        if (temp1->exp == temp2->exp) {
            float com = temp1->coef + temp2->coef;
            if (com != 0) {
                newNode = (polyTerm *)malloc(sizeof(polyTerm));
                newNode->coef = com;
                newNode->exp = temp1->exp;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        } 
        else if (temp1->exp > temp2->exp) {
            newNode = (polyTerm *)malloc(sizeof(polyTerm));
            newNode->coef = temp1->coef;
            newNode->exp = temp1->exp;
            temp1 = temp1->next;
        } 
        else {
            newNode = (polyTerm *)malloc(sizeof(polyTerm));
            newNode->coef = temp2->coef;
            newNode->exp = temp2->exp;
            temp2 = temp2->next;
        }

        if (newNode != NULL) {
            newNode->next = res;
            last->next = newNode;
            last = newNode;
        }
    }

    while (temp1 != p1) {
        polyTerm *newNode = (polyTerm *)malloc(sizeof(polyTerm));
        newNode->coef = temp1->coef;
        newNode->exp = temp1->exp;
        newNode->next = res;
        last->next = newNode;
        last = newNode;
        temp1 = temp1->next;
    }

    while (temp2 != p2) {
        polyTerm *newNode = (polyTerm *)malloc(sizeof(polyTerm));
        newNode->coef = temp2->coef;
        newNode->exp = temp2->exp;
        newNode->next = res;
        last->next = newNode;
        last = newNode;
        temp2 = temp2->next;
    }
}

int main() {
    polyTerm *head1 = (polyTerm *)malloc(sizeof(polyTerm));
    head1->next = head1;

    polyTerm *head2 = (polyTerm *)malloc(sizeof(polyTerm));
    head2->next = head2;

    polyTerm *result = (polyTerm *)malloc(sizeof(polyTerm));
    result->next = result;

    printf("Create Polynomial 1\n");
    createPoly(head1);

    printf("\nCreate Polynomial 2\n");
    createPoly(head2);

    int choice;
    int p, var;
    double res;

    do {
        printf("\nEnter 1 to display polynomial\n");
        printf("Enter 2 to add polynomials\n");
        printf("Enter 3 to evaluate polynomial\n");
        printf("Enter your choice (or 0 to exit): ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("\nPolynomial 1 :\n");
                display(head1);
                printf("\nPolynomial 2 :\n");
                display(head2);
                break;
            
            case 2:
                sortPoly(head1);
                sortPoly(head2);
                addPoly(head1, head2, result);
                printf("\nResult : ");
                display(result);
                break;

            case 3:
                printf("Enter 1 for poly1 and 2 for poly2: ");
                scanf("%d", &p);
                if (p == 1) {
                    printf("Enter value for variable: ");
                    scanf("%d", &var);
                    res = evalPoly(head1, var);
                    printf("Polynomial 1 has value %d at x = %d",res, var);

                } 
                else if (p == 2) {
                    printf("Enter value for variable: ");
                    scanf("%d", &var);
                    res = evalPoly(head2, var);
                    printf("Polynomial 2 has value %d at x = %d",res, var);
                } 
                else {
                    printf("Invalid polynomial\n");
                }
                break;
                
            case 0:
                break;

            default:
                printf("Invalid choice\n");
                break;
        }

    } while (choice != 0);

    return 0;
}