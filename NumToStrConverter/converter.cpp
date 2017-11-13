#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <allocators>
#include "converter.h"
#include "num_control.h"
#include "numbers.h"

/*������������ ���������� �������� � ��������� ������������� ����� 
� ������ ������� ����� ������*/
#define MAX_NUM_LENGTH 14 

/*������� ������ ����� � ��������� �������������*/
void NumToStr(QueueItem *head, char* string, int n, bool HasFraction);

/*������� ���������� ���� � �������*/
int NumsCount(QueueItem *head);

/*������ � ������� ��������� � ����������� �� �������� �����*/
int EndingNumber(int c);

/*���������� � ����� ������ ������������� 10^3n (������, ������� � �.�.)*/
void AddMilles(int c, int milnum, char *str);

/*���������� � ����� ������ ����� "�����" � ��������� ����������*/
void AddQuotient(int c, char *str, bool HasFraction);

/*���������� � ����� ������ �������������, ������������� 
����������� ���������� ����� (�������, ����� � �.�.) � ��������� ����������*/
void AddFractions(int c, char *str, bool HasFraction, int n);

bool NumsToQueue(QueueItem **head1, QueueItem **tail1, QueueItem **head2, QueueItem **tail2)
{
	char c;
	bool HasDecSep = false;

	while ((c = _getch()) != 13) /*���� �������� ���� �� ������ ������� Enter*/
	{
		if (c == 27)             /*�����, ���� ������ ������� Escape*/
			return false;
		if (!HasDecSep)
		{
			if (c == DECIMAL_SEPARATOR) /*������ ����������� � ���������� �����*/
			{
				printf("%c", c);
				HasDecSep = true;
			}
			else
			{
				GetNumbers(&c); /*���������� ������ ����� � �����������*/
				if (c != NULL)
				{
					printf("%c", c);   /*���������� ���� � �������*/
					Enqueue(atoi(&c), head1, tail1); /*��� ����� ����� �����*/
				}
			}			
		}
		else
		{
			GetNumbers(&c);
			if (c != NULL)
			{
				printf("%c", c);      /*���������� ���� � �������*/
				Enqueue(atoi(&c), head2, tail2);  /*��� ������� ����� �����*/
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
		printf("\n������� ������� �����!");
	else
	{    /*��������� ������, ����������� ��� ���������� ������������� �����*/
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

	/*��������� ������, ����������� ��� ���������� ������������� �����*/
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
			milnum = i / 3; /*����������� ������� n ��� ������������ ���� 10^3n*/
			/*����������� ���� ��� ���� ���� � ���*/
			if ((milnum == 1 || HasFraction) && (c == 1 || c == 2))
				strcat(strcat(str, OneTwoThousand[c]), " "); 
			else
				if (c != 0 || (c == 0 && n == 1))
					strcat(strcat(str, ToTenNames[c]), " ");  /*�� 0 �� 9*/
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
				strcat(strcat(str, ToTwentyNames[c]), " "); /*�� 10 �� 19*/
				if (hasMilles)
				    AddMilles(0, milnum, str);
			}
			else
				if (c != 0)  /*�������� ��������*/
				    strcat(strcat(str, DecadesNames[c]), " ");
			break;
		case 2:
			if (c != 0)  /*�������� �����*/
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
	if (c == 1)     /*����� ���������, �������������� � �������� ������*/ 
		return 0;   /*������������� ����*/
	else
		if ((c < 5) && (c > 0)) 
			return 1;     /*���, ���, ������*/
		else
			return 2;     /*��������� �����*/
}

void AddMilles(int c, int milnum, char *str)
{
	if (milnum > 0)
	{
		strcat(str, MillesNames[milnum]);
		if (milnum == 1)        /*��������� ��� �����*/
			strcat(strcat(str, ThousandFlexions[EndingNumber(c)]), " "); 
		else            /*��������� ��� �������, �������� � �.�.*/
			strcat(strcat(str, MillesFlexions[EndingNumber(c)])," ");
	}
}

void AddQuotient(int c, char *str, bool HasFraction)
{
	if (HasFraction)   /*���� ������� �����*/
		strcat(strcat(strcat(str, Quot), /*��������� ����� ����� �����*/
			ToHandredFractionsFlexions[EndingNumber(c)]), " � ");
}

void AddFractions(int c, char *str, bool HasFraction, int n)
{
	int m;

	if (HasFraction)
	{		
		if (n < 3)
		{
			strcat(str, ToHandredFractionsNames[n]); /*��������� ����� ��� ������� */
			strcat(str, ToHandredFractionsFlexions[EndingNumber(c)]); /*��� �����*/
		}
		else
		{
			m = n % 3;
			if (m > 0)
				strcat(str, FractionsNames[m]); /*������- ��� ���-*/
			strcat(str, MillesNames[n / 3]);  /*�����, ������� � �.�.*/
			strcat(str, FractionsFlexions[EndingNumber(c)]); /*���������*/
		}
	}
}
