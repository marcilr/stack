/* 
 * stack.c
 * Created Mon Jul 29 16:00:51 AKDT 2002
 *   by Raymond E. Marcil
 *
 * This is a very simple generic stack ADT that I developed
 * for use with the JAVA native method.  This stack 
 * will push/pop generic data containers through the 
 * use of void * pointers.  The stack uses a dummy head node 
 * to point to the stack. Pushed nodes are inserted
 * between the dummy head and the first node. 
 * Nothing fancy here.
 *
 * The following functions are supported:
 *   stackCreate()      Create a New stack
 *   stackDestroy()     Destroy the stack
 *   stackEmpty()       Check if the stack is empty
 *   stackTop()         Return pointer to data on top of stack.
 *   stackPush()        Push data onto stack.
 *   stackPop()         Pop data off of stack.
 *   stackPrint()       Print data on the stack.
 *   stackCount()       Return number of nodes in stack.
 *   stackSearch()      Search stack.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/*
 * stackCreate()
 * This function creates the dummy head
 * for the stack. The dummy heads fields
 * are initialized and a pointer to the
 * dummy head is returned.
 *
 * INPUT:     NONE
 * RETURNS:   Pointer to stack.
 */

Stack *stackCreate(void){
     
     Stack *s;

     s = (Stack *) malloc(sizeof(Stack));
     if (s==NULL){
      printf("OUT OF MEMORY!\n");
      exit(1);
     }     

     s->next=NULL;
     s->data=NULL;
     s->count=0;

     return s;
}

/* 
 * StackDestroy()
 * This function destroys the stack and frees all 
 * memory associated with it. This function requires
 * a function pointer to a "destructor."  Which knows
 * how to deallocate the data container given a 
 * pointer.
 *
 * INPUT:     *s               Pointer to stack to destroy
 *            *destructor      Function pointer to destructor
 * RETURNS:   NONE
 */

void stackDestroy(Stack *s, void (*destructor)(void *data)){
  Stack *tmp;

  while (s->next != NULL){

    // Get pointer to head node
    tmp = s->next;

    // Remove head node from stack
    s->next = tmp->next;

    // Free data
    if (tmp->data != NULL)
      destructor(tmp->data);
    
    // Free node
    free(tmp);

    s->count--;
  }

  // Free dummy head
  free(s);
}

/*
 * stackEmpty()
 * This function determines if
 * the stack is empty.
 *
 * INPUT:      s       Pointer to stack
 * RETURNS:    TRUE    Stack is empty
 *             FALSE   Stack is not empty
 */

boolean stackEmpty(Stack *s){

  return( (s->count==0) ? TRUE : FALSE );

}


/* 
 * stackTop()
 * This function returns the data
 * for the top element of the stack.
 *
 * INPUT:      s         Pointer to stack
 * RETURNS:    char *    Pointer to data of top
 *                       node of stack.
 *             NULL      Stack empty or data null.
 */

char *stackTop(Stack *s)
{
  char *data;

  if(stackEmpty(s) == TRUE) {
    data=NULL;
  }
  else {
    data=s->next->data;
  }

  return data;
}

/*
 * stackPush()
 * Push string onto stack.
 *
 * INPUT:   s         Pointer to top of stack
 *          data      Pointer to allocated data to push on stack.
 */

void stackPush(Stack *s, void *data){
  Stack *newObject;

  // Allocate new stack module
  newObject = (Stack *) malloc(sizeof(Stack));
  if (s==NULL){
    printf("OUT OF MEMORY!\n");
    exit(1);
  }
  
  // Save pointer to data  
  newObject->data = data;

  // Insert new object
  newObject->next=s->next;

  // Add new object to stack
  s->next=newObject;

  // Bump up count
  s->count++;

}

/*
 * stackPop()
 * Function to pop data off the stack.
 *
 * INPUT:      s        Pointer to top of stack.
 * RETURNS:    char *   Pointer to data from top element of stack.
 *             NULL     Stack empty or data is null.
 * NOTE:                It is up to the caller to free data!
 */

char * stackPop(Stack *s){
  Stack *tmp;
  char *data=NULL;

  if (s != NULL) {
    if (s->next != NULL){

      data=s->next->data;

      // Save tmp pointer to node we're popping
      tmp = s->next;
      tmp->data=NULL;
      s->next = tmp->next;
      free(tmp);

      // Reduce count by 1
      s->count--;
     
    }

  }
  return data;

}

/*
 * stackPrint()
 * This function prints the entire stack. It requires a 
 * function pointer to a function that actually prints
 * the data in the data container.
 * 
 * INPUT:    s           Pointer to stack
 *           *printer    Function pointer to printer function
 * RETURNS:        Prints the stack to stdout.
 *
 */

void stackPrint(Stack *s, void (*printer)(void *dataPtr)){
  Stack *ptr;

  if (s != NULL){

    /* Get pointer to first real node */
    ptr = s->next;

    /* Walk the list of nodes */
    while (ptr != NULL){
      printer(ptr->data);
      ptr=ptr->next;
    } /* end while */

  } /* end if */

} /* end stackPrint() */

/*
 * stackCount()
 * This function returns the number of
 * nodes in the stack.
 *
 * INPUT:     s      Pointer to top of stack
 * RETURNS           Number of nodes in stack
 */

int stackCount(Stack *s){
  int ret = 0;

  /* Get count */
  if (s != NULL) {
    ret = s->count;
  }

  return ret;
}

/*
 * stackSearch()
 * This function walks the stack for the 
 * specified data node and returns it.
 * A comparator is used to match the node.
 *
 * INPUT:    *s            Pointer to stack
 *           *data         Data to search for
 *           *comparator   Function pointer to comparator
 *
 * RETURNS:  *data         Pointer to data
 *           NULL          No match found.
 */

void *stackSearch(Stack *s, 
                  void *data,
                  boolean (*comparator)(void *data1, void *data2)){ 
  Stack    *ptr;
  void     *ret = NULL;
  boolean  flag = FALSE;

  if (s != NULL){
    ptr = s->next;

    /* Walk the stack */
    while ((ptr != NULL) && (ret==NULL)){
      flag = comparator(data,ptr->data);
      if (flag == TRUE)
	ret = ptr->data;
      ptr=ptr->next;
    }
  }

  return ret;
}
