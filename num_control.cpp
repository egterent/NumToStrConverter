/*Ограничение на ввод
символов кроме цифр*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "num_control.h"

/*Проверка является ли введенный символ цифрой: 
возвращает true, если цифра, и false, если нет*/
bool IsNumber(char value);

char numArray[10] = { '0', '1', '2', '3', '4',
'5', '6', '7', '8', '9' };

bool IsNumber(char value)
{
	bool isNumber = false;
	int i;

	for (i = 0; i < 10; i++)
	{
		if (value == numArray[i])
		{
			isNumber = true;
			break;
		}
	}
	return isNumber;
}

void GetNumbers(char *value)
{
	if (!IsNumber(*value))
		*value = NULL;
}
