//Joshua Colleran
//Term project application 2
//data_set.c
//June 7th, 2023
//This folder contains all of the functions that are called from main to complete the program

#include "data_set.h"

//This function will create the data set by making a list of the size of the max number of students 
//BigO: O(1)
LIST *createDataSet() {
	LIST *list = malloc(sizeof(LIST));
	assert(list != NULL);
	list->count = 0;
	list->length = MAX;
	STUDENT *student = malloc(sizeof(STUDENT));
	assert(list->student != NULL);
	return list;
}

//This function will free the data in the list
//BigO: O(1)
void destroyDataSet(LIST *list) {
	assert(list != NULL);
	free(list);
	return;
}

//This function will search the list for a certain ID and return the student with that age along with their student ID
//BigO: O(n)
int searchID(LIST *list, int id) {
	assert(list != NULL);
	int flag = 0;
	int i;
	printf("Checking if there is a student of id %d\n", id);    
	for(i = 0; i < list->length; i++) { 
        	if(list->student[i].id == id) {
			printf("There is a student with ID %d at age %d\n", list->student[i].id, list->student[i].age);
			flag = 1;
		}
		
	}
	if (flag==0) {
		printf("There are no students of id %d.\n", id);
		return 0;
	} else {
		return id;
	}
}

//This function will set the age and id to students at each index
//BigO: O(1)
void insertion(LIST *list, int age, int id, int index) {
	assert(list != NULL);
	list->student[index].age = age;
	list->student[index].id = id;
	list->count++;
	return;
}

//This function will find all of the students with a certain age and delete them from the system. 
//BigO: O(n)
void deletion(LIST *list, int age) {
	assert(list != NULL);
	int i;
	for(i = 0; i < list->length; i++) {
		if(list->student[i].age == age) {
			printf("Student with Age %d and ID %d deleted.\n", list->student[i].age, list->student[i].id);
			list->student[i].age = '\0';
			list->student[i].id = '\0';
			list->count--;
		}
	}
	return;
}
