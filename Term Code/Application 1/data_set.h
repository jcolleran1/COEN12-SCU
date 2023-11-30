//Joshua Colleran
//Term project application 1: data_set.h
//This file initializes all the functions for data_set.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX 3000


typedef struct student {
        int id;
        int age;
} STUDENT;

typedef struct list {
        int length;
        int count;
        STUDENT student[MAX];
} LIST;



LIST *createDataSet();

void destroyDataSet(LIST *list);

int searchAge(LIST *list, int age);

void insertion(LIST *list, int age, int id, int index);

void deletion(LIST *list, int age);

int maxAgeGap(int max, int min);
