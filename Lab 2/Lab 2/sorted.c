//Lab2 part 2
//Joshua Colleran
//April 23th, 2023
//This lab with count the words in a file and will let the user know if the file is non existant or cannot be opened
#include <assert.h>
#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct set {
//      Initializing struct (Time 0(1))
	int max;
	int count;
	char **string;
} SET;

static int search (SET *sp, char *elt, bool *found) {
//	Will binary search through **string to find the needed elements (Time: 0(log n)
	int i;	
	int high = sp->count-1;
	int low = 0;
	int mid = 0;
	while (high >= low) {
		mid = (low + high)/2;
		if (strcmp(sp->string[mid], elt) > 0) {
			high = mid-1;
		} else if (strcmp(sp->string[mid], elt) < 0) {
			low = mid + 1;
		} else {
			*found = true;
			return mid;
		}
	}
	*found = false;
	return low;
}	

SET *createSet(int maxElts) {
//      return a pointer to a new set with a maximum capacity of maxElts (Time: 0(1))
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
//	deallocate memory associated with the set pointed to by sp (Time: 0(n))
	int i;
	for (i=0; i < sp->count; i++) {
		free(sp->string[i]);
	}
	free(sp->string);
	free(sp);
}

int numElements(SET *sp) {
//	returns the number of elements in the set pointed to by sp (Time: 0(1))
	assert(sp != NULL);
	return sp->count;
}

void addElement(SET *sp, char *elt) {
//	add elt to the set pointed to by sp (Time: 0(n))
//	has search
	bool found = true;
	int amount = search(sp, elt, &found);
	assert(p != NULL && elt != NULL);
	if(found == false) {
		int i;
		for(i = sp->count; i > amount; i--) {
			sp->string[i] = sp->string[i-1];
		}
		sp -> string[amount] = strdup(elt);
        	sp->count += 1;
	} else {
			return;
    	}

}	

void removeElement(SET *sp, char *elt) {
//	remove elt from the set pointed to by sp (Time: 0(n))
//	has search
	bool found;
	int i;
	int num = search(sp, elt, &found);
	if (found == false) {
		return;
	} else {
		free(sp->string[num]);
		for(i = num; i < sp->count-1; i++) {
			sp->string[num] = sp->string[i+1];
		}
	}
	sp->count -= 1;
} 

char *findElement(SET *sp, char *elt) {
//	if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL (Time: 0log(n))
//	has search
	bool found = false;
	search(sp, elt, &found);
	if (found == true) {
		return elt;
	} else {
		return NULL;
	}
	
}

char **getElements(SET *sp) {
//	allocate and return an array of elements in the set pointed to by sp (Time: 0(1))
    	char **dest =  malloc(sizeof(char*)*sp->count);
    	memcpy(dest, sp->string, sizeof(char*)*sp->count);
    	return dest;
}

