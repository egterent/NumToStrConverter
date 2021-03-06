#pragma once

#ifndef __NUMBERS_H__
#define __NUMBERS_H__

#include <stdlib.h> 

/*������ � ��������� ������������*/

/*�� ���� �� ������*/
char ToTenNames[10][7] = { "����","����","���","���",
"������", "����", "�����", "����", "������", "������" };

/*�� ����������� �� ������������*/
char ToTwentyNames[10][14] = {"������",  "�����������", "����������",
"����������", "������������", "����������", "�����������",
"����������", "������������", "������������" };

/*������� ��� ��� ��������� � ��������*/
char OneTwoThousand[3][5] = { "", "����", "���"};

/*�������*/
char DecadesNames[10][12] = { "", "������","��������",
"��������", "�����", "���������", "����������",
"���������", "�����������", "���������" };

/*�����*/
char HandredsNames[10][10] = { "", "���", 
"������", "������", "���������", "�������", 
"��������", "�������", "���������", "���������" };

/*������ ����� � �������� ������� ���� (���� 10^3n)*/
char MillesNames[12][12] = { "", "�����", "�������",
"��������", "��������", "�����������", "�����������", "�����������",
"����������", "���������", "���������", "���������" };

/*��������� ��� ����� � �������� ������� ���� */
char MillesFlexions[3][3] = { "", "�", "��" };

/*��������� ��� �����*/
char ThousandFlexions[3][2] = { "�", "�", "" };

/*��������� ��� ������� � ����� ����� � ��������������� �����*/
char ToHandredFractionsFlexions[3][3] = { "��", "��", "��" };

/*��������� ��� ����� �� �������� � ����*/
char FractionsFlexions[3][4] = { "���", "���", "���" };

char FractionsNames[3][7] = {"", "������", "���" };

char ToHandredFractionsNames[3][6] = { "", "�����", "���" };

char Quot[] = "���"; /*������ ��������������� �����*/

#endif /*__NUMBERS_H__*/