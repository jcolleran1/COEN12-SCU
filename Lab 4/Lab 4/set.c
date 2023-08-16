// Joshua Colleran
// lab 4- "set.c"
// Wedneday 5:15 - 8:00
// This lab part implements a hash table with chaining for a set adt

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#include "set.h"

typedef struct set SET;

struct set {
	int count;
	int length;
	LIST **elts;
	int (*compare)();
	unsigned(*hash)();
};

//return a pointer to a new list using compare as its comparison function, which may be NULL
//Run time: 0(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
	int i;
	int avg = 20;
	SET *sp;
	sp = malloc(sizeof(SET));	
	assert(sp != NULL);
	sp->length = maxElts/avg;
	sp->count = 0;
	sp->hash = hash;
	sp->elts = malloc(sizeof(void*)*sp->length);	
	assert(sp->elts != NULL);
	
	for (i = 0; i < sp->length; i++) {
		sp->elts[i]=createList(sp->compare);
	}
	return sp;
}

//reallocate memory associated with the list pointed to by lp
//Run time: 0(n)
void destroySet(SET *sp) {
	assert(sp!=NULL);
	int i;
	for(i = 0; i < sp->length; i++) {
		destroyList(sp->elts[i]);
	}
	free(sp->elts);
	free(sp);
}

//return the number of items in the list pointed to by lp
//Run time: 0(1)
int numElements(SET *sp) {
	assert(sp!=NULL);
	return sp->count;
}

//adds elements in the list pointed to by lp
//Run time: 0(n)
void addElement(SET *sp, void *elt) {
	assert(sp!=NULL && elt!=NULL);
	int i = (*sp->hash)(elt) % sp->length;
	if (findItem(sp->elts[i],elt)==NULL) {
		addFirst(sp->elts[i],elt);
		sp->count++;
		return;
	} else {
		return;	
	}
}

//if item is present in the list pointed to by lp then remove it; the comparison function must not be NULL
//Run time: 0(n)
void removeElement(SET *sp, void *elt) {
	assert(sp!=NULL && elt!=NULL);
	int i = (*sp->hash)(elt)%sp->length;
	removeItem(sp->elts[i],elt);
	sp->count--;
	return;
}

//if item is present in the list pointed to by lp then return the matching item, otherwise return NULL; the comparison function must not be NULL
//Run time: 0(n)
void *findElement(SET *sp, void *elt) {
	assert(sp!=NULL && elt!=NULL);
	int i = (*sp->hash)(elt)%sp->length;
	return findItem(sp->elts[i],elt);
}

//allocate and return an array of items in the list pointed to by lp
//Run time: 0(n)
void *getElements(SET *sp) {
	assert(sp!=NULL);
	int i,j = 0;
	void **item = malloc(sizeof(void*)*sp->count);
	assert(item != NULL);
	for(i = 0;  i < sp->length; i++) {
		void **cpy = getItems(sp->elts[i]);
		memcpy(item+j, cpy, sizeof(void*)*numItems(sp->elts[i]));
		j+= numItems(sp->elts[i]);
		free(cpy);		
	}
	return item;	
}
