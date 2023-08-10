//Joshua Colleran
//May 31, 2023
//Lab5: This part of the lab will take a text file and read through it, it will then use hufman coding
//to compress the file and output the amount of bits in each letter and the total bits needed

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"
#include "pack.h"
#include <ctype.h>

typedef struct node NODE;

int counts[257];
NODE * nodes[257];

//Creates a node for the priority queue
//Big O: 0(1)
static NODE *mkNode(int count, NODE *left_node, NODE *right_node) {

	NODE *new_node = malloc(sizeof(NODE));
	assert(new_node != NULL);
	new_node->count = count;
	new_node->parent = NULL;
	if(left_node != NULL) {
		left_node->parent = new_node;
	}

	if(right_node != NULL) {
		right_node->parent = new_node;
	}

	return new_node;
}

//This function compares the two node pointers
//Big O: 0(1)
static int compare(NODE *t1, NODE *t2) {
	assert(t1 != NULL && t2 != NULL);
	return (t1->count < t2->count) ? -1 : (t1->count > t2->count);
}

//This function will return the depth
//Big O: 0(1)
static int depth(NODE *np) {
	assert(np != NULL);
	if(np->parent == NULL) {
		return 0;
	}
	return depth(np->parent) + 1;
}

//This function will read the binary file
//Big O: O(n)
static void readFile(char *fName) {
	FILE *fp = fopen(fName, "rb");
	int i;
	if(fp == NULL) {
		return;
	}
	while((i = getc(fp)) != EOF) {
		counts[i]++;
	}
	fclose(fp);
	return;
}

//This main function reads the file, creates the priority queue, and then after it will use the huffman code to print out the bits
//Big O: O(n)
int main(int argc, char *argv[]) {
	int i,j;
	if(argc != 3) {
		return 0;
	}
	readFile(argv[1]);	
	PQ *pq = createQueue(compare);

	for(i=0; i<256; i++) {
		if(counts[i] > 0) {
			nodes[i] = mkNode(counts[i], NULL, NULL);
			addEntry(pq, nodes[i]);
		}	
	}
	nodes[256] = mkNode(0, NULL, NULL);
	addEntry(pq, nodes[256]);	

	while(numEntries(pq) > 1) {
		NODE *left_node = removeEntry(pq);
		NODE *right_node = removeEntry(pq);
		addEntry(pq, mkNode(left_node->count + right_node->count, left_node, right_node));
	}
	
	for(j = 0; j < 257; j++) {
		if(nodes[j] != NULL) {
			if(isprint(j)) {
				printf(" '%c' ", j);
			} else {
				printf("%03o", j);
			}
		printf(": %d x %d bits = %d bits \n", counts[j], depth(nodes[j]), counts[j] * depth(nodes[j]));					
		}	
	}
	pack(argv[1], argv[2], nodes);
	destroyQueue(pq);
	return 0;	
}
