#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define PLUS 1
#define MINUS -1
//ADT Number - Doubly Linked List
typedef struct node {
	int num;
	struct node *next, *prev;
}node;
typedef struct number {
	int sign, dec;
	node *head, *tail;
}number;

void initNumber(number *a); //Initialize Number ADT
void addDigit(number *a, char ch);  //Add Digit to Right of Number List
void printNumber(number a); //Print Number List
void appendleft(number *a, int no); //Add Digit to Left of Number List
int length(number a); //Length of Number
void remov(number *a, int pos); //Remove Digit from Number List
void zeroRemov(number *a);  //Remove Zeroes from Number

//void destroyNumber(number *a); //Destroy Number ADT

#endif // LIST_H_INCLUDED
