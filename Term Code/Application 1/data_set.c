//Joshua Colleran
//Term project application 1
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

//This function will search the list for a certain age and return all of the students with that age along with their student ID
//BigO: O(n)
int searchAge(LIST *list, int age) {
	assert(list != NULL);
	int flag = 0;
	int i;
	printf("Checking if there is a student of age %d\n", age);    
	for(i = 0; i < list->length; i++) { 
        	if(list->student[i].age == age) {
			printf("There is a student with Age %d and ID %d\n", list->student[i].age, list->student[i].id);
			flag = 1;
		}
		
	}
	if (flag==0) {
		printf("There are no students of age %d.\n", age);
		return 0;
	} else {
		return age;
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

//This function will return the age gap of the max and min age
//BigO: O(1)
int maxAgeGap(int max, int min) {
	return max-min;
}

