// Joshua Colleran
// lab 4- "list.c"
// wedneday 5:15 - 8:00
// This lab creats a linked list ADT with the variouse functions of add, remove, or get an element in the linked list


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"


typedef struct list LIST;	
typedef struct node NODE;

struct list {
	int count;
	NODE *head;
	int(*compare)();
};

struct node { 
	void *data;
	struct node *next;
	struct node *prev;
};

//return a pointer to a new list using compare as its comparison function, which may be NULL
//Run time: 0(1)
LIST *createList(int (*compare)()) {
	LIST *lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count = 0;
	lp->head = malloc(sizeof(NODE));
	assert(lp-> head != NULL);
	lp->compare =  compare;
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
		
}

//reallocate memory associated with the list pointed to by lp
//Run time: 0(1)
extern void destroyList(LIST *lp) {
	assert(lp != NULL);
	NODE *del = lp->head->next;
	NODE *prev;
	while(del != lp->head)
	{
		prev = del->prev;
		free(del);
		del = prev;
	}
	free(del);
	free(lp);

}

//return the number of items in the list pointed to by lp
//Run time: 0(1)
extern int numItems(LIST *lp) {
	assert(lp != NULL);
	return lp->count;
}

//add item as the first item in the list pointed to by lp
//Run time: 0(1)
extern void addFirst(LIST *lp, void *item) {
	assert(lp != NULL && item != NULL);
	NODE *old = lp->head->next;
	NODE *new = malloc(sizeof(NODE));
	assert(lp != NULL && item != NULL && new != NULL);
	new->data = item;
	new->prev = lp->head;
	new->next = old;
	old->prev = new;
	lp->head->next = new;
	lp->count++;
	return;
}

//add item as the last item in the list pointed to by lp
//Run time: 0(1)
extern void addLast(LIST *lp, void *item) {
	NODE *temp = malloc(sizeof(NODE));
        assert(lp != NULL && item != NULL);
	temp->data = item;
	lp->head->prev->next = temp;
	temp->next = lp->head;
	temp->prev = lp->head->prev;
	lp->head->prev = temp;
	lp->count++;
	return;

}

//remove and return the first item in the list pointed to by lp ; the list must not be empty
//Run time: 0(1)
extern void *removeFirst(LIST *lp) {
	assert(lp != NULL && lp->count > 0);
	NODE *temp = lp->head->next;
	void *cpy = temp->data;
	lp->head->next = temp->next;
	temp->next->prev = lp->head;
	free(temp);
	lp->count--;
	return cpy;

}

//remove and return the last item in the list pointed to by lp ; the list must not be empty
//Run time: 0(1)
extern void *removeLast(LIST *lp) {
	assert(lp != NULL && lp->count > 0);
	NODE *temp = lp->head->prev;
	void *cpy = temp->data;
	lp->head->prev = temp->prev;
	temp->prev->next = lp->head;
	free(temp);
	lp->count--;
	return cpy;
}

//return, but do not remove, the first item in the list pointed to by lp ; the list must not be empty
//Run time: 0(1)
extern void *getFirst(LIST *lp) {
	assert(lp != NULL && lp->count != 0);
	return lp->head->next->data;

}

//return, but do not remove, the last item in the list pointed to by lp ; the list must not be empty
//Run time: 0(1)
extern void *getLast(LIST *lp) {
	assert(lp != NULL && lp->count != 0);
	return lp->head->prev->data;
}

//if item is present in the list pointed to by lp then remove it; the comparison function must not be NULL
//Run time: 0(n)
void removeItem(LIST *lp, void *item) {
	assert(lp != NULL);
	if(lp->count > 0) {
		NODE *temp = lp->head->next;
		while (temp != lp->head) {
			if((*lp->compare)(temp->data, item) == 0) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(temp);
				lp->count--;
				break;
			} else {
				temp = temp->next;
			}
		}
	}
	return;

}

//if item is present in the list pointed to by lp then return the matching item, otherwise return NULL; the comparison function must not be NULL
//Run time: 0(n)
void *findItem(LIST *lp, void *item) {
	assert(lp != NULL);
	NODE *temp = lp->head->next;
	int i;
	for(i = 0; i < lp->count; i++)
	{
		if(lp->compare(item, temp->data) == 0)
		{
			return temp->data;
		}
		temp = temp->next;
	}
	return NULL;

}

//allocate and return an array of items in the list pointed to by lp
//Run time: 0(n)
void *getItems(LIST *lp) {
	assert(lp != NULL);
	void **item = malloc(sizeof(void*)*lp->count);
	assert(item != NULL);
	NODE *temp = lp->head->next;
	int i;
	for(i=0; i<lp->count; i++) {
		item[i] = temp->data;
		temp = temp->next;
	}
	return item;

}

