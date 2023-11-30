//Joshua Colleran 
//Term project application 2: college.c
//This file contains the main functions that calls the rest of the functions from data_set.c
#include "data_set.h"
//The main function will create a data set with random  IDs and age
//It will then generate a random ID to search for and then delete all the students with that age
//Then it will free the data set
int main(void) {	
	LIST *list = createDataSet();  
    	assert(list != NULL);
    	srand(time(NULL));
    	int i, randAge, randId, randNext, min, max;
    	min = max = randAge = (rand() % 13)+18;    
    	randId = (rand()%2)+1;                
    	insertion(list, randAge, randId, 0);        
    	printf("Age %d Id %d\n", randAge, randId);
    	for(i = 1; i < 1000; i++) {         
        	randAge = (rand() % 13)+18;    
        	randNext = list->student[i-1].id+((rand()%2)+1);
        	if(randAge > max) {                                 
        		max = randAge;
        	}
        	if(randAge < min) {      
        		min = randAge;
        	}
        	insertion(list, randAge, randNext, i);   
        	printf("Age %d Id %d\n", randAge, randNext);    
	} 
	randAge = (rand() % 13)+18;
	searchID(list, randId);
	deletion(list, randAge);
	destroyDataSet(list);
}
