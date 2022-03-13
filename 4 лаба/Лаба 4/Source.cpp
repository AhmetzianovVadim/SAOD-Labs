//������.�������� ������ �� ������ �������, ����������� ���������� 
#include <iostream>
#include <locale.h>
#include <stdlib.h>

using namespace std;

#define LIST_SIZE 5

struct list_int
{
	int count = 0;
	int list[LIST_SIZE];
	int size = LIST_SIZE;
};

struct list_char 
{
	int count = 0;
	char list[LIST_SIZE][100];
	int size = LIST_SIZE;
};

int input();
void mainLoop(list_int list_i, list_char list_c);
void showInt(list_int* l);
void addInt(list_int* l);
void deletionInt(list_int* l);
int findInt(list_int* l, int to_find);
void showChar(list_char* l);
void addChar(list_char* l);
void deletionChar(list_char* l);
int findChar(list_char* l, char* to_find);
int ChooseTypeOflist();
void if_exit();

int main()
{
	setlocale(LC_ALL, "Rus");
	list_int list_i;
	list_char list_c;
	mainLoop(list_i, list_c);
	return 0;
}

//������� ����
void mainLoop(list_int list_i, list_char list_c)
{
	if_exit();
	int list_type = ChooseTypeOflist();
	//�������� ��� ��������
	int choice = -1;

	while (choice != 0)
	{
		system("cls");

		cout << "1. ��������" << endl << "2. ��������" << endl << "3. �������" << endl << "0. ������� ��� ������" << endl;

		choice = input();

		system("cls");

		switch (choice)
		{
		case 0:
			mainLoop(list_i, list_c);
		case 1:
			if (list_type == 1)
				showInt(&list_i);
			else
				showChar(&list_c);
			break;
		case 2:
			if (list_type == 1)
				addInt(&list_i);
			else
				addChar(&list_c);
			break;
		case 3:
			if (list_type == 1)
				deletionInt(&list_i);
			else
				deletionChar(&list_c);
			break;
		default:
			cout << "������������ ����, ���������� ��� ���" << endl;
				break;
		}
		system("pause");
	}
}

void if_exit() //��������� ����� �� ������������ ����� �� ���������
{
	char e = 'a';
	system("cls");
	cout << "��� ������ ���� ������ ������� ����� ������, ��� ������ ������� q" << endl;
	cin >> e;
	if (e == 'q')
		exit(0);
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

int ChooseTypeOflist() //�������� ��� ������
{

	int list_type = -1;
	while (list_type != 1 && list_type != 2)
	{
		system("cls");
		cout << "1. ������ �����" << endl << "2. ������ ����� " << endl;
		list_type = input();
		if (list_type != 1 && list_type != 2)
		{
			cout << "������������ ����! ���������� ������: " << endl;
			system("pause");
		}
	}
	return list_type;

}

int input() 
{
	int result;
	cin >> result;
	while (cin.fail()) 
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "������ �����!" << endl;
		system("pause");
		cout << "���������� ������: ";
		cin >> result;
	}
	return result;
}

//������� ��� ������ int
void showInt(list_int* l) 
{
	if (l->count == 0)
		cout << "������ ����!" << endl;
	else
	{
		for (int i = 0; i < l->count; i++)
			cout << l->list[i] << " ";
		cout << endl;
	}
}

void addInt(list_int* l)
{
	if (l->count == l->size)
	{
		cout << "������ ��������!" << endl;
	}
	else
	{
		cout << "������� �����, ����� ��������: ";
		int to_add = input();
		bool has_added = false;
		for (int i = 0; i < l->count; i++)  
		{
			if (to_add < l->list[i]) //���������� ������ �� ������� �����, ������� ������ ������������
			{
				for (int j = l->count; j >= i; j--)
					l->list[j] = l->list[j - 1]; //������� ��� �����, ������� ������������ �� ���� ������� ������

				l->list[i] = to_add;
				has_added = true;
				break;
			}
		}

		if (!has_added)
			l->list[l->count] = to_add;

		l->count++;
		cout << to_add << " ��������!" << endl;
	}
}

void deletionInt(list_int* l)
{
	if (l->count == 0)
		cout << "������ ����!" << endl;
	else
	{
		cout << "������� ����� ��� ��������: ";
		int to_delete = input();

		int index = findInt(l, to_delete);
		if (index == -1)
			cout << "����� �� �������!" << endl;
		else
		{
			for (int i = index; i < l->count - 1; i++)
				l->list[i] = l->list[i + 1]; //������� ��� ����� �����, ������� � ����������
			l->count--;
			cout << to_delete << " ������!" << endl;
		}
	}
}

int findInt(list_int* l, int to_find)
{
	for (int i = 0; i < l->count; i++)
	{
		if (l->list[i] == to_find)
			return i;
	}
	return -1;
}

//������� ��� ������ char
void showChar(list_char* l)
{
	if (l->count == 0)
		cout << "������ ����!" << endl;
	else
	{
		for (int i = 0; i < l->count; i++)
			cout << l->list[i] << " ";
		cout << endl;
	}
}


void addChar(list_char* l) 
{
	if (l->count == l->size)
		cout << "������ ��������!" << endl;
	else
	{
		cout << "������� ������, ����� ��������: ";
		char to_add[100];
		cin >> to_add;
		bool has_added = false;

		for (int i = 0; i < l->count; i++)
		{
			if (strcmp(to_add, l->list[i]) < 0)
			{
				for (int j = l->count; j >= i; j--)
					strcpy_s(l->list[j], l->list[j - 1]);
				strcpy_s(l->list[i], to_add);
				has_added = true;
				break;
			}
		}
		if (!has_added)
			strcpy_s(l->list[l->count], to_add);
		l->count++;
		cout << to_add << " ��������!" << endl;
	}
}

void deletionChar(list_char* l)
{
	if (l->count == 0)
		cout << "������ ����!" << endl;
	else
	{
		cout << "������� ������ ��� ��������: ";
		char to_delete[100];
		cin >> to_delete;

		int index = findChar(l, to_delete);
		if (index == -1)
			cout << "������ �� �������!" << endl;
		else
		{
			for (int i = index; i < l->count - 1; i++)
				strcpy_s(l->list[i], l->list[i + 1]);
			l->count--;
			cout << to_delete << " ������!" << endl;
		}
	}
}

int findChar(list_char* l, char* to_find)
{
	for (int i = 0; i < l->count; i++)
	{
		if (strcmp(l->list[i], to_find) == 0)
			return i;
	}
	return -1;
}