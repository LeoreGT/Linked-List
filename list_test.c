#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "LinkedListItr.h"
#include "list_functions.h"

void DestroyElement(void* _item);
int P1 (void * _element, void* _context);
int Less (void* _a, void* _b);

void List_CreateTest();
void List_DestroyTest();
void List_PushHeadTest();
void List_PushTailTest();
void List_PopHeadTest();
void List_PopTailTest();
void List_SizeTest();

int main()
{
	List* ptr;
	void* x,*y,*z,*a,*b,*c,*d;

	List_CreateTest();
	List_DestroyTest();
	List_PushHeadTest();
	List_PushTailTest();
	List_PopHeadTest();
	List_PopTailTest();
	List_SizeTest();


	y = malloc(sizeof(int));
	*(int*)y = 4;
	x = malloc(sizeof(int));
	*(int*)x = 30;
	a = malloc(sizeof(int));
	*(int*)a = 3;
	b = malloc(sizeof(int));
	*(int*)b = 5;
	c = malloc(sizeof(int));
	*(int*)c = 20;
	d = malloc(sizeof(int));
	*(int*)d = 20;

	ptr = List_Create();
	List_PushHead(ptr,a);
	List_PushHead(ptr,b);
	List_PushHead(ptr,c);
	List_PushHead(ptr,d);
	List_PushHead(ptr,x);
	List_PushHead(ptr,d);


	ListPrint(ptr);
	z = ListItr_FindFirst(ListItr_Begin(ptr),ListItr_End(ptr),P1,y);
	printf("first Node-------------------->\n");
	if( ListItr_Equals(z,ListItr_End(ptr)))
	{
		printf("NO SUCH NODE\n");
	}else
	{
		NodePrint(z);
	}
	free(y);
	ListItr_Sort(ListItr_Begin(ptr),ListItr_End(ptr),Less);
/*	ListPrint(ptr);*/

	ListItr_Splice(ListItr_Begin(ptr),ListItr_Next(ListItr_Begin(ptr)),ListItr_Prev(ListItr_End(ptr)));
/*	ListPrint(ptr);*/
/*	puts("AFTERRR---------------------------->");*/

	List_Destroy(&ptr,DestroyElement);

	return 0;
}


void List_CreateTest()
{
	List* ptr = List_Create();
	if( NULL != ptr)
	{
		printf("\nTest 1 : CreateList - PASS\n");
	}else
	{
		printf("\nTest 1 : CreateList - FAIL\n");
	}
}


void List_DestroyTest()
{
	List* ptr;
	void* x;

	x = malloc(sizeof(int));
	*(int*)x = 3;

	/* Test 2 :  */
	ptr = List_Create();
	List_PushHead(ptr,x);
	List_Destroy(&ptr,DestroyElement);
	printf("\nTest 2 : DestroyList - PASS\n");


	/* Test 3 : Double free */
	ptr = List_Create();
	List_Destroy(&ptr,DestroyElement);
	List_Destroy(&ptr,DestroyElement);
	printf("Test 3 : DestroyList , Double free - PASS\n");


	/* Test 4 : ptr= NULL */
	List_Destroy(NULL,DestroyElement);
	printf("Test 4 : DestroyList , ptr=NULL - PASS\n");

}

void List_PushHeadTest()
{
	List* ptr = NULL;
	int res;
	void* x;
	/***** ListPushHead *****/

	/* Test 5 : valid input  */
	ptr = List_Create();
	x = malloc(sizeof(int));
	*(int*)x=3;
	res = List_PushHead(ptr,x);
	List_PopHead(ptr,&x);

	if( 3 == *(int*)x && 0 == List_Size(ptr) &&  LIST_SUCCESS == res )
	{
		printf("\nTest 5 : ListPushHead , valid input - PASS\n");
	}else
	{
		printf("\nTest 5 : ListPushHead , valid input - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);
	free(x);

	/* Test 6 : ptr = NULL  */
	ptr = List_Create();
	x = malloc(sizeof(int));
	*(int*)x = 3;
	res = List_PushHead(NULL,x);
	if( 0 == List_Size(ptr) &&  LIST_UNINITIALIZED_ERROR == res)
	{
		printf("Test 6 : ListPushHead , ptr = NULL - PASS\n");
	}
  else
	{
		printf("Test 6 : ListPushHead , ptr = NULL - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);
	free(x);
}

void List_PushTailTest()
{
	List* ptr = NULL;
	int res;
	void* x;
	/* Test 7 : valid input  */
	ptr = List_Create();
	x = malloc(sizeof(int));
	*(int*)x = 3;
	res = List_PushTail(ptr,x);
	List_PopTail(ptr,&x);
	if( 3 == *(int*)x && 0 == List_Size(ptr) &&  LIST_SUCCESS == res )
	{
		printf("\nTest 7 : ListPushTail , valid input - PASS\n");
	}else
	{
		printf("\nTest 7 : ListPushTail , valid input - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);
	free(x);

	/* Test 8 : ptr = NULL  */
	ptr = List_Create();
	x = malloc(sizeof(int));
	*(int*)x = 3;
	res = List_PushTail(NULL,x);
	if( 0 == List_Size(ptr) &&  LIST_UNINITIALIZED_ERROR == res)
	{
		printf("Test 8 : ListPushTail , ptr = NULL - PASS\n");
	}
  else
	{
		printf("Test 8 : ListPushTail , ptr = NULL - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);
	free(x);
}

void List_PopHeadTest()
{
	List* ptr = NULL;
	int res;
	void* x;

	/* Test 9 : Empty list  */
	ptr = List_Create();
	res = List_PopHead(ptr,&x);
	if( 0 == List_Size(ptr) && LIST_UNDERFLOW_ERROR == res)
	{
		printf("\nTest 9 : ListPopHead , Empty list - PASS\n");
	}else
	{
		printf("\nTest 9 : ListPopHead , Empty list - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);

	/* Test 10 : ptr = NULL  */
	res = List_PopHead(NULL ,&x);
	if( 0 == List_Size(ptr) && LIST_UNINITIALIZED_ERROR == res)
	{
		printf("Test 10 : ListPopHead , ptr = NULL - PASS\n");
	}else
	{
		printf("Test 10 : ListPopHead , ptr = NULL - FAIL\n");
	}

	/* Test 11 : data = NULL  */
	ptr = List_Create();
	res = List_PopHead(ptr ,NULL);
	if( 0 == List_Size(ptr) && LIST_UNINITIALIZED_ERROR == res)
	{
		printf("Test 11 : ListPopHead , data = NULL - PASS\n");
	}else
	{
		printf("Test 11 : ListPopHead , data = NULL - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);

	/* Test 12 : valid input  */
	ptr = List_Create();
	x = malloc(sizeof(int));
	*(int*)x = 3;
	res = List_PushHead(ptr,x);
	res = List_PopHead(ptr ,&x);
	if( 0 == List_Size(ptr) && 3 == *(int*)x && LIST_SUCCESS == res)
	{
		printf("Test 12 : ListPopHead , valid input - PASS\n");
	}else
	{
		printf("Test 12 : ListPopHead , valid input - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);
}

void List_PopTailTest()
{
	List* ptr = NULL;
	int res;
	void* x;

	x = malloc(sizeof(int));
	*(int*)x = 3;

	ptr = List_Create();
	res = List_PopTail(ptr,&x);
	if( 0 == List_Size(ptr) && LIST_UNDERFLOW_ERROR == res)
	{
		printf("\nTest 13 : ListPopTail , Empty list - PASS\n");
	}
  else
	{
		printf("\nTest 13 : ListPopTail , Empty list - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);


	res = List_PopTail(NULL ,&x);
	if( 0 == List_Size(ptr) && LIST_UNINITIALIZED_ERROR == res)
	{
		printf("Test 14 : ListPopTail , ptr = NULL - PASS\n");
	}else
	{
		printf("Test 14 : ListPopTail , ptr = NULL - FAIL\n");
	}


	ptr = List_Create();
	res = List_PopTail(ptr ,NULL);
	if( 0 == List_Size(ptr) && LIST_UNINITIALIZED_ERROR == res)
	{
		printf("Test 15 : ListPopTail , data = NULL - PASS\n");
	}else
	{
		printf("Test 15 : ListPopTail , data = NULL - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);
	free(x);

	ptr = List_Create();
	x=malloc(sizeof(int));
	*(int*)x=3;
	res = List_PushTail(ptr,x);
	res = List_PopTail(ptr ,&x);
	if( 0 == List_Size(ptr) && 3 == *(int*)x && LIST_SUCCESS == res)
	{
		printf("Test 16 : ListPopTail , valid input - PASS\n");
	}else
	{
		printf("Test 16 : ListPopTail , valid input - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);
	free(x);

}

void List_SizeTest()
{
	List* ptr=NULL;
	int num;
	void* x;

	ptr = List_Create();
	num= List_Size(ptr);
	if( 0 == num)
	{
		printf("\nTest 17 : ListSize , Empty list - PASS\n");
	}else
	{
		printf("\nTest 17 : ListSize , Empty list - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);


	num= List_Size(ptr);
	if( 0 == num)
	{
		printf("Test 18 : ListSize , ptr = NULL - PASS\n");
	}else
	{
		printf("Test 18 : ListSize , ptr = NULL - FAIL\n");
	}

	ptr = List_Create();
	x=malloc(sizeof(int));
	*(int*)x=3;
	List_PushTail(ptr,x);
	num= List_Size(ptr);
	if( 1 == num)
	{
		printf("Test 19 : ListSize , valid input - PASS\n");
	}else
	{
		printf("Test 19 : ListSize , valid input - FAIL\n");
	}
	List_Destroy(&ptr,DestroyElement);

}

void DestroyElement(void* _item)
{
	if(NULL == _item)
	{
		return;
	}
	free(_item);
}


int P1 (void * _element, void* _context)
{
	if( NULL == _element || NULL == _context)
	{
		return 0;
	}

	if(*(int*)_element < *(int*)_context)
	{
		return 1;
	}
		return 0;
}

int Less (void* _a, void* _b)
{
	if( NULL == _a || NULL == _b)
	{
		return 0;
	}

	if(*(int*) _a <= *(int*)_b)
	{
		return 1;
	}
		return 0;
}





