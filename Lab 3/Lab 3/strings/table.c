//Joshua Colleran
//Lab 3
//March 6th, 2023
// The functions manipulate the elements by adding, removing, and searching through them

//The included libraries and the defined terms
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"
# include <stdbool.h>
# include <assert.h>
# define EMPTY 0
# define FULL 1
# define DELETED 2

//Defines the struct "set"
typedef struct set {
    int count;
    int length;
    void **data;
    char *flags;
}SET;
static int search(SET *sp, char *elt, bool *found);	

//This creates the ADT set with the size of maxElts and allocates the memory for the ADT
//BigO:n 0(n)
SET *createSet(int maxElts) { 
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	sp->flags = malloc(sizeof(char*)*maxElts);
	assert(sp->flags != NULL);

	int i;
        sp->count = 0;
        sp->length = maxElts;
	for(i = 0; i < sp->length; i++){
		sp->flags[i] = EMPTY;
	}
	return sp;		
}

// This function frees the memory allocated for the elements in the createSet function
// BigO: 0(1)
void destroySet(SET *sp) {
	assert(sp != NULL);
	int i;
	for(i = 0; i < sp->count; i++) {
		if(sp->flags[i] == FULL){
			free(sp->data[i]);
		}		
	}
	free(sp->flags);
	free(sp->data);
	free(sp);
}

//This function will return the number of elements in the set
//BigO: O(1)
int numElements(SET *sp) {
	assert(sp != NULL);
	return sp -> count;
}

// The add element function ensures that there are no duplicate elements that are added to the set.
// It also increments count and marks the index it was added at as FULL
// BigO: O(n)
void addElement(SET *sp, char *elt) {
        assert(sp != NULL && elt != NULL);
        bool found;
        int i = search(sp, elt, &found);
        if(found == true) {
                return;
        } else {
		assert(sp->count < sp->length);
		sp->data[i] = strdup(elt);
		sp -> flags[i] = FULL;
		sp -> count++;
	}
	return;
}

//This will set the flag of the hash table to deleted at index "i" if the specfic element is found in the set
//It will also free the pointer at the index and take the count down
//BigO: O(n)
void removeElement(SET *sp, char *elt) {
	assert(sp != NULL && elt != NULL);
	bool found;
	int i =	search(sp, elt, &found);
	if(found) {
		free(sp->data[i]);
		sp->flags[i] = DELETED;
		sp->count--;
	}			
	return;
}

//Searches for the element pointed at by elt, and indexes the element and returns true if found otherwise returns NULL
//BigO: O(n)
char *findElement(SET *sp, char *elt) {
	assert(sp != NULL && elt != NULL);
        bool found;
        int i = search(sp, elt, &found);
	return found ? sp->data[i] : NULL;
}

//This function will create memory for the copu of each element in the sorted set. It will also return the copy of the set making sure there is no duplicates.
//BigO: O(n)
char **getElements(SET *sp) {
	assert(sp != NULL);
        int i, j;
	char **copy = malloc(sizeof(char*)*sp->count);
	assert(copy!= NULL);
	j = 0;
	for(i = 0; i < sp->length; i++){
		if(sp->flags[i] == FULL){
			copy[j++] = sp-> data[i];	
		}	
	}
	return copy;
}

//Hash function that has the purpose of finding an open index
//uses linear probing to avoid collision
//BigO: O(n)
unsigned strhash(char *s) {
	unsigned hash = 0;
	while(*s != '\0'){
		hash = 31 * hash + *s ++;
	}
	return hash;
}

//This function will search through the hash table and use linear probing to avoid collisions
//This will use different logic if the index is marked from the DEFINED FULL EMPTY AND DELETED
//Overall it will find thee right spot to insert into the set
//BigO: O(n)
int search(SET *sp, char *elt, bool *found) {
	assert(sp != NULL);
    	assert(elt != NULL);
	int pos, i;
	int f = -1;
	int hash = strhash(elt) % sp -> length;
	for (i = 0; i < sp->length; i++) {
		pos = (hash + i) % sp -> length;
		if(sp->flags[pos] == FULL) {
            		if(strcmp(elt, sp->data[pos]) == 0){
                 		*found = true;
                 		return (pos);
            		}
        	} else if (sp->flags[pos] == EMPTY) {
			*found = false;
			if (f!= -1) {
				return f;
			}
			return pos; 
		} else if (sp->flags[pos] == DELETED) {
			if (f == -1) {
				f = pos;
			}
		}
	}
	*found = false;
	return f;
}
	
