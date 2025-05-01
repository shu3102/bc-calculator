#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "list.h"

// Operand Stack to Store Number List Operands and Result of Operation
typedef struct inode {
	number *a;
	struct inode *p;
}inode;
typedef inode *istack; //Operand Stack Pointer
void iinit(istack *s);
void ipush(istack *s, number *a);
number *ipop(istack *s);
int iisempty(istack *s);


// Operator Stack to Store Character Operators
typedef struct cnode {
	char a;
	struct cnode *p;
}cnode;
typedef cnode *cstack;  //Operator Stack Pointer
void cinit(cstack *s);
void cpush(cstack *s, char t);
char cpop(cstack *s);
int cisempty(cstack *s);
char ctop(cstack *s);

#endif // STACK_H_INCLUDED
