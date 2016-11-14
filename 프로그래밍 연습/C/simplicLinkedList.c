/*
 *	Simplic Linked List Structure
 *	Corder : Yowu (uyu423@gmail.com || http://luckyyowu.tistory.com)
 *	Date : 2016. 04. 15
 *	Development Env.
 *		Ubuntu 15.10 (x64, Linux Kernel 4.2.0)
 *		GNU Compiler Collection 5.2.1
 *		Vi IMproved 7.4, File Encoding UTF-8
 *
 *	아 중간고사 공부 하기 싫당.. 자소설도 쓰기 귀찮당 ㅜㅜ
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
	struct __node *cur;
	struct __node *head;
	struct __node *tail;
} linkedList;

typedef struct __node {	
	int data;
	struct __node *next;
} node;

void createNode(linkedList *L, int tdata) {
	node *newNode = (node *)malloc(sizeof(node));
	newNode->data = tdata;
	newNode->next = NULL;
	if(L->head == NULL && L->tail == NULL)
		L->head = L->tail = newNode;	
	else {
		L->tail->next = newNode;
		L->tail = newNode;
	}

	L->cur = newNode;
}


void deleteLastNode(linkedList *L) {
	node *p = L->head;
	while(p->next->next != NULL) p = p->next;
	p->next = p->next->next;
	L->tail = p;
}

void printNodes(linkedList *L) {
	node *p = L->head;	
	putchar('[');
	while(p != NULL) {
		printf("%d, ", p->data);
		p = p->next;
	}
	putchar(']');
	putchar('\n');
}

int main(void) {
	//linkedList pointer define start
	linkedList *L = (linkedList *)malloc(sizeof(linkedList));
	L->cur = NULL;
	L->head = NULL;
	L->tail = NULL;
	//linkedList pointer define end

	createNode(L, 1);
	createNode(L, 2);
	createNode(L, 3);
	deleteLastNode(L);
	createNode(L, 4);
	createNode(L, 5);
	createNode(L, 6);
	deleteLastNode(L);
	deleteLastNode(L);
	createNode(L, 7);
	printNodes(L);

	return 0;
}
