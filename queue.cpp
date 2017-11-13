/*־קונוהü סטלגמכמג*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "queue.h"

void Enqueue(int value, QueueItem **head, QueueItem **tail)
{
	QueueItem *p;

	p = (QueueItem *)malloc(sizeof(QueueItem));
	p->data = value;
	p->next = NULL;
	if (*head == NULL)
	{
		*head = p;
	}
	else
	{
		(*tail)->next = p;
	}
	*tail = p;
}

void Dequeue(QueueItem **head, QueueItem **tail)
{
	QueueItem *p = *head;

	if (head != NULL)
	{
		*head = (*head)->next;
		if (*head == NULL)
			*tail = NULL;
		free(p);
	}
}


void FreeQueue(QueueItem **head, QueueItem **tail)
{
	while (*head != NULL)
		Dequeue(head, tail);
}