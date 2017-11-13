#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <allocators>
#include "converter.h"
#include "num_control.h"
#include "numbers.h"

/*Максимальное количество символов в строковом представлении числа 
с учетом символа конца строки*/
#define MAX_NUM_LENGTH 14 

/*Перевод целого числа в строковое представление*/
void NumToStr(QueueItem *head, char* string, int n, bool HasFraction);

/*Подсчет количества цифр в очереди*/
int NumsCount(QueueItem *head);

/*Индекс в массиве окончаний в зависимости от значения цифры*/
int EndingNumber(int c);

/*Добавление в конец строки числительного 10^3n (тысяча, миллион и т.д.)*/
void AddMilles(int c, int milnum, char *str);

/*Добавление в конец строки слова "целые" с требуемым окончанием*/
void AddQuotient(int c, char *str, bool HasFraction);

/*Добавление в конец строки числительного, определяющего 
знаменатель десятичной дроби (десятых, сотых и т.д.) с требуемым окончанием*/
void AddFractions(int c, char *str, bool HasFraction, int n);

bool NumsToQueue(QueueItem **head1, QueueItem **tail1, QueueItem **head2, QueueItem **tail2)
{
	char c;
	bool HasDecSep = false;

	while ((c = _getch()) != 13) /*Ввод символов пока не нажата клавиша Enter*/
	{
		if (c == 27)             /*Выход, если нажата клавиша Escape*/
			return false;
		if (!HasDecSep)
		{
			if (c == DECIMAL_SEPARATOR) /*Введен разделитель в десятичной дроби*/
			{
				printf("%c", c);
				HasDecSep = true;
			}
			else
			{
				GetNumbers(&c); /*Возвращает только цифры и разделитель*/
				if (c != NULL)
				{
					printf("%c", c);   /*Добавление цифр в очередь*/
					Enqueue(atoi(&c), head1, tail1); /*для целой части числа*/
				}
			}			
		}
		else
		{
			GetNumbers(&c);
			if (c != NULL)
			{
				printf("%c", c);      /*Добавление цифр в очередь*/
				Enqueue(atoi(&c), head2, tail2);  /*для дробной части числа*/
			}
		}
	}
	return true;
}

void ConvertNumToStr(QueueItem **head1, QueueItem **tail1, QueueItem **head2, 
	QueueItem **tail2)
{
	char *string;
	int n1, n2;

	n1 = NumsCount(*head1);
    n2 = NumsCount(*head2);
	while (n1 > 1 && (*head1)->data == 0)
	{
		Dequeue(head1, tail1);
		n1--;
	}
	if ((n1 > 36) || (n2 > 35))
		printf("\nСлишком большое число!");
	else
	{    /*Выделение памяти, достаточной для строкового представления числа*/
		string = (char *)malloc(MAX_NUM_LENGTH * (n1 + n2));
		strcpy(string, "");
		NumToStr(*head1, string, n1, *head2 != NULL);
		AddQuotient((*tail1)->data, string, *head2 != NULL);
		if (*head2 != NULL)
		{
			NumToStr(*head2, string, n2, true);
			AddFractions((*tail2)->data, string, true, n2);
		}
		printf(string);
		free(string);
	}
}

void NumToStr(QueueItem *head, char* string, int n, bool HasFraction)
{
	int m, i, milnum = 0;
	char *str;
	QueueItem *p = head;
	int c;
	bool hasMilles;

	/*Выделение памяти, достаточной для строкового представления числа*/
	str = (char *)malloc(MAX_NUM_LENGTH * n);
	strcpy(str, "");
	i = n - 1;
	hasMilles = false;
	while (p != NULL)
	{
		c = p->data;
		m = i % 3;
		if (c != 0 && i > 2)
			hasMilles = true;
		switch (m)
		{
		case 0: 
			milnum = i / 3; /*Определение степени n для числительных вида 10^3n*/
			/*Определение рода для слов один и два*/
			if ((milnum == 1 || HasFraction) && (c == 1 || c == 2))
				strcat(strcat(str, OneTwoThousand[c]), " "); 
			else
				if (c != 0 || (c == 0 && n == 1))
					strcat(strcat(str, ToTenNames[c]), " ");  /*От 0 до 9*/
			if (hasMilles)
			    AddMilles(c, milnum, str);
			hasMilles = false;
			break;
		case 1:			
			if (c == 1)
			{
				p = p->next;
				i--;
				c = p->data;
				milnum = i / 3;
				strcat(strcat(str, ToTwentyNames[c]), " "); /*От 10 до 19*/
				if (hasMilles)
				    AddMilles(0, milnum, str);
			}
			else
				if (c != 0)  /*Названия десятков*/
				    strcat(strcat(str, DecadesNames[c]), " ");
			break;
		case 2:
			if (c != 0)  /*Названия сотен*/
				strcat(strcat(str, HandredsNames[c]), " ");
			break;
		}
		p = p->next;
		i--;
	}
	strcat(string, str);
	free(str);
}

int NumsCount(QueueItem *head)
{
	int i = 0;
	QueueItem *p = head;

	while (p != NULL)
	{
		i++;
		p = p->next;
	}
	return i;
}

int EndingNumber(int c)
{
	if (c == 1)     /*номер окончания, согласованного с заданной формой*/ 
		return 0;   /*числительного один*/
	else
		if ((c < 5) && (c > 0)) 
			return 1;     /*два, три, четыре*/
		else
			return 2;     /*остальные числа*/
}

void AddMilles(int c, int milnum, char *str)
{
	if (milnum > 0)
	{
		strcat(str, MillesNames[milnum]);
		if (milnum == 1)        /*окончания для тысяч*/
			strcat(strcat(str, ThousandFlexions[EndingNumber(c)]), " "); 
		else            /*окончания для миллион, миллиард и т.д.*/
			strcat(strcat(str, MillesFlexions[EndingNumber(c)])," ");
	}
}

void AddQuotient(int c, char *str, bool HasFraction)
{
	if (HasFraction)   /*есть дробная часть*/
		strcat(strcat(strcat(str, Quot), /*требуемая форма слова целый*/
			ToHandredFractionsFlexions[EndingNumber(c)]), " и ");
}

void AddFractions(int c, char *str, bool HasFraction, int n)
{
	int m;

	if (HasFraction)
	{		
		if (n < 3)
		{
			strcat(str, ToHandredFractionsNames[n]); /*требуемая форма для десятый */
			strcat(str, ToHandredFractionsFlexions[EndingNumber(c)]); /*или сотый*/
		}
		else
		{
			m = n % 3;
			if (m > 0)
				strcat(str, FractionsNames[m]); /*десяти- или сто-*/
			strcat(str, MillesNames[n / 3]);  /*тысяч, миллион и т.д.*/
			strcat(str, FractionsFlexions[EndingNumber(c)]); /*окончание*/
		}
	}
}
