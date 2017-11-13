// NumToStrConverter.cpp: ���������� ����� ����� ��� ����������� ����������.
// ��������� ��� �������� ����� � ������� ����� � �� ��������� ������������� 
// � ������������ � ��������� �������� �����

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
	
	printf("��� ����� ������ ����� ������� ����� �������. ��� ������ ������� Escape");
	printf("\n������� �����. ��� ������ ����� ������� Escape.");
	while (!quitting)
	{
		printf("\n\n�����: ");
		if (NumsToQueue(&head1, &tail1, &head2, &tail2))
		{
			printf("\n\n�� �����: ");
			ConvertNumToStr(&head1, &tail1, &head2, &tail2);
		}
		else
			printf("\n\n���� ����� �������!");
		if ((choice = _getch()) == 27)
			quitting = true;
		FreeQueue(&head1, &tail1);
		FreeQueue(&head2, &tail2);
	}
	return 0;
}


