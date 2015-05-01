/*
 *	ProjectName	: MaxHeap Example C language
 *	Corder 		: YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
 *	Organiz.	: Catholic Univ. of Korea
 *	Major		: Computer Science (Minor : Infomation System Eng)
 *	DateTime	: 2015.5.1 13:08
 *	Develop OS	: Kubuntu (Ubuntu KDE) 15.04 (Kernel 3.19.0-15-generic)
 *	PorgramLang	: C (Library Model : POSIX)
 *	TextEditor	: VIM - Vi IMproved (7.x ver)
 *	Encording	: UTF-8 (Linux Basic)
 *	Compiler	: GCC 4.9.2
 */

#include <stdio.h>
#define HEAP_MAXSIZE 100

typedef enum { false, true } bool;
int heap[HEAP_MAXSIZE];
int numOfData = 0;

bool heapFull() {
        return (numOfData == HEAP_MAXSIZE ? true : false);
}

bool heapEmpty() {
        return (numOfData < 0 ? true : false);
}
                                                                                             
void push(int data) {                                                                        
        int pos = ++numOfData;                                                               
        if(heapFull()) {                                                                     
                printf("Heap Array Full.\n");                                                
                return;
        }
        while(1) {
                if(pos != 1 && heap[pos/2] < data) {
                        heap[pos] = heap[pos/2];
                        pos = pos/2;
                }
                else {
                        heap[pos] = data;
                        break;
                }
        }
}

int pop() {
        int data = heap[1];
        int cur = 1;
        int child = 2;
        int lastData = heap[numOfData--];
        if(heapEmpty()) {
                printf("Heap Array Empty.\n");
                return -1;
        }
        while(1) {
                if(child > numOfData) {
                        heap[cur] = lastData;
                        break;
                }
                else {
                        if(child + 1 <= numOfData && heap[child + 1] > heap[child]) {
                                child++;
                        }
                        if(lastData < heap[child]) {
                                heap[cur] = heap[child];
                                cur = child;
                                child = cur * 2;
                        }
                        else {
                                heap[cur] = lastData;
                                break;
                        }
                }
        }
        return data;
}

int main() {
        int i, data;
        for(i=0; i<10; i++) {
                scanf("%d", &data);
                push(data);
        }
        for(i=1; i<=10; i++) {
                printf("[%d] pop value : %d\n", i, pop());
        }
}
