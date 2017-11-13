#pragma once
/*Очередь символов*/

#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct queueItem {
	int data;
	struct queueItem *next;
} QueueItem;

/*Добавление элемента в конец очереди*/
void Enqueue(int value, QueueItem **head, QueueItem **tail);

/*Удаление первого элемента из очереди */
void Dequeue(QueueItem **head, QueueItem **tail);

/*Освобождение памяти занятой очередью*/
void FreeQueue(QueueItem **head, QueueItem **tail);


#endif /*__QUEUE_H__*/
