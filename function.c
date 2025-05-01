
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "list.h"
#include "function.h"

//Equal the digits after decimal point
void decimalEqual(number *a, number *b) {
	int i;
	if(a->dec > b->dec) {
		int diff = a->dec - b->dec;
		for(i = 0; i < diff; i++) {
			addDigit(b, '0');
			b->dec++;
		}
	}
	else if(b->dec > a->dec) {
		int diff = b->dec - a->dec;
		for(i = 0; i < diff; i++) {
			addDigit(a, '0');
			a->dec++;
		}
	}
}

//Equal length of 2 numbers
void lengthEqual(number *a, number *b) {
	int gap;
	gap = length(*a) - length(*b);
	if(gap > 0) {
		int i = 0;
		while(i < gap) {
			appendleft(b, 0);
			i++;
		}
	}
	else if(gap < 0) {
		int i = 0;
		gap = -gap;
		while(i < gap) {
			appendleft(a, 0);
			i++;
		}
	}
}

//Check if Number is Zero or not
int zeroNumber(number a) {
	int i, flag = 0;
	node *p = a.head;
	for(i = 0; i < length(a); i++) {
		if(p->num != 0)
			flag = 1;
		 p = p->next;
	}
	return flag;
}

//copy number a in number b.
void copy(number *a, number *b) {
	int i, no, len;
	char ch;
	len = length(*a);
	node *t1 = a->head;
	for(i = 0; i < len; i++) {
		no = t1->num;
		ch = no + '0';
		addDigit(b, ch);
		t1 = t1->next;
	}
	b->dec = a->dec;
	b->sign = a->sign;
	return;
}

//Function To Compare Equal Length Numbers
int compareEqual(number a, number b) {
	lengthEqual(&a, &b);
	decimalEqual(&a, &b);
	node *p, *q;
	int len;
	int i;
	len = length(a);
	p = a.head;
	q = b.head;
	for(i = 1; i <= len; i++) {
		if(p->num > q->num)
			return 1;
		else if(p->num < q->num)
			return -1;
		p = p->next;
		q = q->next;
	}
	return 0;
}

//Addition Operation
number *add(number *a, number *b) {
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	decimalEqual(a, b);
	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = sub(b, a);
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = sub(a, b);
		}
	}
	else if(a->sign == b->sign) {
		int i, n1, n2, carry = 0, sum;
		int len_a, len_b;
		node *t1 = a->tail;
		node *t2 = b->tail;
		len_a = length(*a);
		len_b = length(*b);
		if(a->sign == MINUS)
			ans->sign = MINUS;
		else
			ans->sign = PLUS;
		if(len_a >= len_b) {
			for(i = 1; i <= len_b; i++) {
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_a - len_b; i++) {
				n1 = t1->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t1 = t1->prev;
			}
		}else {
			for(i = 1; i <= len_a; i++) {
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_b - len_a; i++) {
				n1 = t2->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				appendleft(ans, sum);
				t2 = t2->prev;
			}
		}
		ans->dec = a->dec;
		if(carry != 0)
			appendleft(ans, carry);
	}
	return ans;
}


//Subtraction operation.
number *sub(number *a, number *b) {
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	decimalEqual(a, b);
	lengthEqual(a, b);
	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = add(a, b);
			ans->sign = MINUS;
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = add(a, b);
			ans->sign = PLUS;
		}
	}
	else if(a->sign == b->sign) {
		if(a->sign == MINUS) {
			a->sign = b->sign = PLUS;
			ans = sub(b, a);
		}
		else if(a->sign == PLUS) {
			int n1, n2, diff, borrow = 0, i, len;
			node *t1 = a->tail;
			node *t2 = b->tail;
			len = length(*b);
			if(compareEqual(*a, *b) == 1) {
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n1 = n1 - borrow;
					if(n1 >= n2) {
						diff = n1 - n2;
						borrow = 0;
						appendleft(ans, diff);
					}
					else {
						n1 = n1 + 10;
						diff = n1 - n2;
						borrow = 1;
						appendleft(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else if(compareEqual(*a, *b) == -1) {
				ans->sign = MINUS;
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n2 = n2 - borrow;
					if(n2 >= n1) {
						diff = n2 - n1;
						borrow = 0;
						appendleft(ans, diff);
					}
					else {
						n2 = n2 + 10;
						diff = n2 - n1;
						borrow = 1;
						appendleft(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else {
				if(compareEqual(*a, *b) == 0) {
					appendleft(ans, 0);
				}
			}
		}
	}
	ans->dec = a->dec;
	return ans;
}

//Multiplication Operation.
number *mult(number *a, number *b) {
	number *ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	if((zeroNumber(*a) == 0) || (zeroNumber(*b) == 0)) {
		addDigit(ans, '0');
		return ans;
	}
	int lengthdiff;
	if(a->sign == b->sign) {
		ans->sign = PLUS;
		a->sign = b->sign = PLUS;
	}
	else {
		ans->sign = MINUS;
		a->sign = b->sign = PLUS;
	}
	lengthdiff = length(*a) - length(*b);
	if(lengthdiff < 0) {
		ans = mult(b, a);
		return ans;
	}
	else {
		node *t1, *t2;
		int len_a = length(*a);
		int len_b = length(*b);
		int i, j, n1 = 0, n2 = 0;
		int tempresult[2 * len_a];
		for(i = 0; i < 2 *len_a; i++)
			tempresult[i] = 0;
		int k = 2 * len_a - 1;
		t2 = b->tail;
		for(i = 0; i < len_b; i++) {
			t1 = a->tail;
			int carry1 = 0, carry2 = 0;
			for(j = k - i; j > len_a - 2; j--) {
				if(t1 != NULL && t2 != NULL) {
					n1 = t1->num * t2->num + carry1;
					t1 = t1->prev;
					carry1 = n1 / 10;
					n1 = n1 % 10;
					n2 = tempresult[j] + n1 + carry2;
					carry2 = n2 / 10;
					n2 = n2 % 10;
					tempresult[j] = n2;
				}
				else {
					break;
				}
			}
			tempresult[j] = carry1 + carry2 + tempresult[j];
			len_a--;
			t2 = t2->prev;
		}
		for(i= k; i >= len_a - 1 && i >= 0; i--) {
			appendleft(ans, tempresult[i]);
		}
		ans->dec = a->dec + b->dec;
		return ans;
	}
}

//Division Operation.
number *division(number *m, number *n){
	if(zeroNumber(*n) == 0) {
		printf("Dividing by Zero is not allowed.\n");
		return NULL;
	}
	zeroRemov(m);
	zeroRemov(n);

	int k = m->dec > n->dec ? m->dec : n->dec;
	int i = 0;

	while(i < k) {
		if(m->dec > 0)
			m->dec--;
		else
			addDigit(m, '0');
		if(n->dec > 0)
			n->dec--;
		else
			addDigit(n, '0');
		i++;
	}
	i = 9;
	number *c, *d, *ans, *q, *pro;
	c = (number *)malloc(sizeof(number));
	d = (number *)malloc(sizeof(number));
	ans = (number *)malloc(sizeof(number));
	pro = (number *)malloc(sizeof(number));
	q = (number *)malloc(sizeof(number));

	initNumber(ans);
	initNumber(c);
	initNumber(q);
	initNumber(d);
	if(m->sign == n->sign) {
		q->sign = PLUS;
		m->sign = n->sign = PLUS;
	}
	else {
		q->sign = MINUS;
		m->sign = n->sign = PLUS;
	}
	node *p = m->head;
	char ch = p->num + '0';
	addDigit(d, ch);
	while(q->dec < SCALE){
		while(i >= 0){
			appendleft(c, i);
			pro = mult(n, c);
			ans = sub(d, pro);
			if(ans->sign != MINUS) {
				addDigit(q, i + '0');
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				break;
			}
			else{
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				i--;
			}
		}
		d = ans;
		if(p->next != NULL) {
			p = p->next;
			ch = p->num + '0';
			addDigit(d, ch);
		}
		else{
			q->dec++;
			addDigit(d, '0');
		}
		i = 9;
		node *tmp = c->head;
		free(tmp);
		c->head = c->tail = NULL;
	}
	q->dec--;
	return q;
}

//Modulus Operation
number *modulus(number *a, number *b) {
	if(zeroNumber(*b) == 0) {
		printf("ERROR : Modulo by Zero is not allowed.\n");
		return NULL;
	}
	int tempsign;
	if(a->sign == MINUS) {
		tempsign = MINUS;
		a->sign = b->sign = PLUS;
	}
	else {
		tempsign = PLUS;
		a->sign = b->sign = PLUS;
	}
	decimalEqual(a, b);
	int a_dec = a->dec;
	number *ans = (number *)malloc(sizeof(number));
	number *temp = (number *)malloc(sizeof(number));
	initNumber(ans);
	initNumber(temp);
	temp = division(a, b);
	if(temp->dec != 0) {
		int pos = length(*temp) - 1;
		while(temp->dec != 0) {
			remov(temp, pos);
			temp->dec--;
			pos--;
		}
	}
	temp = mult(temp, b);
	ans = sub(a, temp);
	ans->sign = tempsign;
	ans->dec = a_dec;
	return ans;
}
