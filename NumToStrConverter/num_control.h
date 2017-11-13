#pragma once
/*Ограничение на ввод
символов кроме цифр*/

#ifndef __NUM_CONTROL_H__
#define __NUM_CONTROL_H__

#define DECIMAL_SEPARATOR ','

/*Проверка является ли введенный символ цифрой, если нет *value = NULL*/
void GetNumbers(char *value);

#endif /*__NUM_CONTROL_H__*/

