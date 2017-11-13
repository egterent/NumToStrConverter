#pragma once
/*������� ��������*/

#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct queueItem {
	int data;
	struct queueItem *next;
} QueueItem;

/*���������� �������� � ����� �������*/
void Enqueue(int value, QueueItem **head, QueueItem **tail);

/*�������� ������� �������� �� ������� */
void Dequeue(QueueItem **head, QueueItem **tail);

/*������������ ������ ������� ��������*/
void FreeQueue(QueueItem **head, QueueItem **tail);


#endif /*__QUEUE_H__*/
