#pragma once

#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "queue.h"

/*���������� ���������� ����� � �������*/
bool NumsToQueue(QueueItem **head1, QueueItem **tail1, QueueItem **head2, QueueItem **tail2);

/*������� ����� � ������*/
void ConvertNumToStr(QueueItem **head1, QueueItem **tail1, QueueItem **head2, QueueItem **tail2);

#endif // !__CONVERTER_H__
