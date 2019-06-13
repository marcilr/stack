/* 
 * Test driver for Stack ADT
 * Created Mon Jul 29 15:49:19 AKDT 2002
 *   by Raymond E. Marcil
 *
 * This is a quick test driver for the stack ADT.
 * It show the basic usage of the ADT.
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* Function prototypes */
void printInfo(Stack *s);
void pushData(Stack *s, char *data);
void popData(Stack *s);
void searchData(Stack *s, char *data);

/* Functions for use with stack ADT */
void destructor(void *data);
void printer(void *data);
boolean comparator(void *data1, void *data2);

int main(void){
  Stack *stack;
  char  *tmp;

  /* Create a new stack */
  stack = stackCreate();

  printInfo(stack);

  pushData(stack,"cat");
  pushData(stack,"dog");
  pushData(stack,"fish");
  pushData(stack,"horse");
  
  printInfo(stack);

  searchData(stack,"dog");
  searchData(stack,"butterfly");
  searchData(stack,"cat");
  searchData(stack,"minnow");

  popData(stack);
  popData(stack);
  popData(stack);
  popData(stack);

  /* Destroy the stack */
  stackDestroy(stack,&destructor);

  return 0;
}

/*
 * popData()
 * This function tests the pop functionality.
 * 
 * INPUT:    s    Pointer to top of stack.
 * OUTPUT:        Pops top node of stack and prints it.
 */

void popData(Stack *s){
  char *data;

  if (s != NULL){
  	
  data = stackPop(s);
  printf("Popped: %s\n",data);
  
  /* Free up memory */
  if (data != NULL)
    free(data);  
  
  } /* end if */
  
} /* end pop*/

/*
 * pushData()
 * This function allocates and pushes a string
 * onto the stack.
 *
 * INPUT:     *s         Pointer to top of stack.
 *            *data      String to push on stack.
 * RETURNS:   NONE
 */
void pushData(Stack *s, char *data){
  char *tmpPtr;

  tmpPtr =  (char *) malloc(strlen(data)*sizeof(char));
  if (tmpPtr == NULL){
    printf("OUT OF MEMORY!\n");
    exit(1);
  }
  else {
    strcpy(tmpPtr,data);
    stackPush(s,tmpPtr);
  }
}

/*
 * searchData()
 * This function tests the ADT stackSearch function.
 * INPUT:     data     String to search for.
 */
void searchData(Stack *s, char *data){
  char *str=NULL;

  /* Search stack for string */
  str = stackSearch(s,(void *)data,&comparator);

  /* Print results */
  printf("stackSearch: %s %s %s\n",data,
          (str == NULL) ? "FALSE" : "TRUE", str);
}

/*
 * printInfo()
 * This is a quick function that prints information
 * about the stack.
 *
 * INPUT:     s    Pointer to top of stack.
 * RETURNS:        Prints information about the stack.
 */
void printInfo(Stack *s){
  
  printf("\nprintInfo()\n");
  printf("stackEmpty(): %s\n",(stackEmpty(s) == TRUE) ? "TRUE" : "FALSE" );
  printf("stackCount(): %d items on stack\n",stackCount(s));
  printf("stackTop(): %s\n",stackTop(s));
  printf("stackPrint():\n");
  stackPrint(s,&printer);
}

/*
 * destructor()
 * This is a simple destructor for strings 
 * required for use of the stack ADT.
 *
 * INPUT:	data 	Pointer to data to deallocate
 * RETURNS:	NONE
 */	

void destructor(void *data){
	
  if (data != NULL)
  	free(data);
  	
} /* end destructor */


/*
 * printer()
 * This function required by stackPrint() to
 * print the data container.
 *
 * INPUT:    *data     Pointer to data section.
 */

void printer(void *data){

  printf("%s\n",(char *)data);

}

/*
 * comparator()
 * This function accepts two data pointers
 * and returns true if the two match.
 */

boolean comparator(void *data1, void *data2){
  boolean ret = FALSE;

  if (strcmp((char *)data1,(char *)data2)==0)
    ret = TRUE;

  return ret;

} 
