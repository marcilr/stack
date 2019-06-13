/*
 * stack.h
 * 
 * Created Tue Jul 30 09:15:02 AKDT 2002
 *  By Raymond E. Marcil
 *
 * Header file for simple stack ADT.
 *
 * Public functions:
 *   stackCreate()      Create a New stack
 *   stackDestroy()     Destroy the stack
 *   stackEmpty()       Check if the stack is empty
 *   stackTop()         Return pointer to data on top of stack.
 *   stackPush()        Push data onto stack.
 *   stackPop()         Pop data off of stack.
 *   stackPrint()       Print data on the stack.
 *   stackCount()       Return number of nodes in stack. 
 *   stackSearch()      Search stack for specified data.
 */


/* Stack node definition */
typedef struct Stack
{
  void *data;
  struct Stack *next;
  int count;
} Stack;

/* Boolean, used by stackEmpty function */ 
typedef enum boolean {FALSE, TRUE} boolean;

/* ================ Public Functon Prototypes ================= */
/* ================ Public Functon Prototypes ================= */ 

Stack   *stackCreate(void);
void     stackDestroy(Stack *s, void (*destructor)(void *data));
boolean  stackEmpty(Stack *s);
char    *stackTop(Stack *s);
void     stackPush(Stack *s, void *data);
char    *stackPop(Stack *s);
void     stackPrint(Stack *s, void (*printer)(void *dataPtr));
int      stackCount(Stack *s);
void     *stackSearch(Stack *s, void *data,
                      boolean (*comparator)(void *data1, void *data2));

