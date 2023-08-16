//Lab2
//Joshua Colleran
//April 23th, 2023
//This lab will search through text files using arrays and binary search
#include <assert.h>
#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct set {
//      defining struct (Time: O(1))
	int max;
	int count;
	char **string;
} SET;

static int search (SET *sp, char *elt) {
//	search throgh **string and return location (Time: Olog(n))
	int i;
	for(i = 0; i < sp->count; i++) {
		if(strcmp(elt, sp->string[i]) == 0)
			return i;
		}
		return -1;
	}

SET *createSet(int maxElts) {
//      return a pointer to a new set with a maximum capacity of maxElts (Time: O(1))
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->string =  malloc(sizeof(char*)*maxElts);
        sp->count = 0;
        sp->max = maxElts;
	assert(sp->string != NULL);
	return sp;	
}

void destroySet(SET *sp) {
//	deallocate memory associated with the set pointed to by sp (Time: O(n))
	int i;
	for (i=0; i < sp->count; i++) {
		free(sp->string[i]);
	}
	free(sp->string);
	free(sp);
}

int numElements(SET *sp) {
//	return the number of elements in the set pointed to by sp (Time: O(1))
	assert(sp != NULL);
	return sp->count;
}

void addElement(SET *sp, char *elt) {
//	add elt to the set pointed to by sp (Time: O(n))
//	has search
	if (search(sp, elt) == -1) {
        	assert(sp->count < sp->max);
		sp -> string[sp->count] = strdup(elt);
        	sp->count += 1;
		return;
    	}
    	return;	

}	

void removeElement(SET *sp, char *elt) {
//	remove elt from the set pointed to by sp (Time: O(n))
//	has search
	int num = search(sp, elt);
	if (num == -1) {
		return;
	}
	free(sp->string[num]);
	sp->string[num] = sp->string[sp->count-1];
	sp->count -= 1;
} 

char *findElement(SET *sp, char *elt) {
//	if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL (Time: O(log n))
//	has search
	int current = search(sp, elt);
	if (current != -1) {
		return sp->string[current];
	} else {
		return NULL;
	}
	
}

char **getElements(SET *sp) {
//	allocate and return an array of elements in the set pointed to by sp (Time: O(1))
    	char **dest =  malloc(sizeof(char*)*sp->count);
    	memcpy(dest, sp->string, sizeof(char*)*sp->count);
    	return dest;
}

