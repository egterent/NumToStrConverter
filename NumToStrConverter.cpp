// NumToStrConverter.cpp: определяет точку входа для консольного приложения.
// Программа для перевода целых и дробных чисел в их строковое представление 
// в соответствии с правилами русского языка

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include "converter.h"


int main()
{
	setlocale(LC_ALL, "Rus");
	QueueItem *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL;
	bool quitting = false;
	char choice;
	
	printf("Для ввода нового числа нажмите любую клавишу. Для выхода нажмите Escape");
	printf("\nВведите число. Для отмены ввода нажмите Escape.");
	while (!quitting)
	{
		printf("\n\nЧисло: ");
		if (NumsToQueue(&head1, &tail1, &head2, &tail2))
		{
			printf("\n\nВы ввели: ");
			ConvertNumToStr(&head1, &tail1, &head2, &tail2);
		}
		else
			printf("\n\nВвод числа отменен!");
		if ((choice = _getch()) == 27)
			quitting = true;
		FreeQueue(&head1, &tail1);
		FreeQueue(&head2, &tail2);
	}
	return 0;
}


