//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList


typedef struct _queue
{
	LinkedList ll;
} Queue;  // You should not change the definition of Queue

///////////////////////// function prototypes ////////////////////////////////////

void removeOddValues(Queue *q)
{
	ListNode *cur, *nxt;
	cur = q->ll.head;
	int idx = 0;
	while (cur != NULL)
	{
		nxt = cur->next;
		if (cur->item % 2 == 1)
			removeNode(&(q->ll), idx--);
			
		cur = nxt;
		idx++;
	}
}