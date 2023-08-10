//Joshua Colleran
//May 31, 2023
//Lab5: An implementation of different functions for a queue structure that is defined in the pqueue struct

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

#define IL 10     //intial lenth
#define parent(x) (((x)-1)/2)
#define lc(x) (((x)*2)+1)
#define rc(x) (((x)*2)+2)

struct pqueue {
	int count; /* number of entries in array*/
	int length; /* length of allocated array */
	void **data; /* allocated array of entries */
	int (*compare)(); /* comparison function */
};

//return a pointer to a new priority queue using compare as its comparison function
//Big O: O(1)
PQ *createQueue(int (*compare)()) {
	PQ *pq = malloc(sizeof(PQ));
        assert(compare != NULL);
        pq->compare = compare;
	pq->count = 0;
	pq->length = IL;
	pq->data = malloc(sizeof(void*) *pq->length);
        assert(pq->data != NULL);
	return pq;
}

//deallocate memory associated with the priority queue pointed to by pq
//Big O: O(n)
void destroyQueue(PQ *pq) {
	assert(pq != NULL);	
	free(pq -> data);
	free(pq);
	return;
}

//return the number of entries in the priority queue pointed to by pq
//Big O: O(1)
int numEntries(PQ *pq) {
	assert(pq != NULL);
	return pq -> count;
}

//add entry to the priority queue pointed to by pq
//Big O: O(logn)
void addEntry(PQ *pq, void *entry) {
	assert(pq != NULL && entry != NULL);
	int pos;
	if(pq->count == pq->length) {
		pq->length = pq->length * 2;
		pq->data = realloc(pq->data, sizeof(void *) * pq->length);
		assert(pq->data != NULL);
	}
	pos = pq -> count ++;
	while(pos > 0 && pq->compare(entry, pq->data[parent(pos)]) < 0) {
		pq->data[pos] = pq->data[parent(pos)];
		pos = parent(pos);

	}
	pq->data[pos] = entry;

}

//remove and return the smallest entry from the priority queue pointed to by pq
//Big O: O(logn)
void *removeEntry(PQ *pq) {
	assert(pq != NULL);
	int i = 0;
	int child = 0;
	void *min = pq -> data[0];
	pq->data[i]= pq->data[--pq->count];
	
	while(lc(i) < pq->count){
		if(rc(i) < pq->count) {
			if(pq->compare(pq->data[lc(i)], pq->data[rc(i)]) < 0) {
				child = lc(i);
			} else {
				child = rc(i);
			}
		} else {
			child = lc(i);		
		}

		if(pq->compare(pq->data[child], pq->data[i]) < 0) {
			void *temp = pq->data[child];
			pq->data[child] = pq->data[i];
			pq->data[i] = temp;
			i = child; 
		} else {
			break;
		}
	}
	return min;	
}

