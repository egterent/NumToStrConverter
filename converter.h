#pragma once

#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "queue.h"

/*—читывание введенного числа в очередь*/
bool NumsToQueue(QueueItem **head1, QueueItem **tail1, QueueItem **head2, QueueItem **tail2);

/*ѕеревод числа в строку*/
void ConvertNumToStr(QueueItem **head1, QueueItem **tail1, QueueItem **head2, QueueItem **tail2);

#endif // !__CONVERTER_H__
