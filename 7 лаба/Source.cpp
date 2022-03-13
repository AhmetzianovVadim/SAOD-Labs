//�B������B����bI� ������ ����� � �������� B ������ � �������� �����B������
#include <iostream>
#include <locale.h>

using namespace std;

struct element
{
	int value;
	element* ptr_to_prev;
	element* ptr_to_next;
};

element* list = new element;

int input();
int choice();
element* search(int item, bool step = false);
element* search_back(int item, bool step = false);
void add();
void del();
void search_menu();
void show();

int main()
{
	setlocale(LC_ALL, "Rus");
	
	list->ptr_to_prev = list;
	list->ptr_to_next = list;

	int menu_point;

	do {
		system("cls");

		cout << "1. ��������" << endl << "2. �������" << endl << "3. �����" << endl << "4. ��������" << endl << "0. �����" << endl;

		menu_point = input();

		system("cls");

		switch (menu_point)
		{
		case 0:
			return 0;
		case 1:
			add();
			break;
		case 2:
			del();
			break;
		case 3:
			search_menu();
			break;
		case 4:
			show();
			break;
		default:
			cout << "������ �����!" << endl;
		}

		system("pause");
	} while (menu_point != 0);

	return 0;
}

int input()
{
	int result;
	cin >> result;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "������ �����!" << endl;
		system("pause");
		cout << "���������� �����: ";
		cin >> result;
	}
	return result;
}

int choice()
{
	int result;
	do {
		result = input();
		if (result != 1 && result != 2)
			cout << "������ �����! ���������� �����: ";
	} while (result != 1 && result != 2);
	return result;
}

void add()
{
	cout << "������� �������� ��� ����������: ";
	int new_value = input();

	element* new_element = new element;
	new_element->value = new_value;

	if (list->ptr_to_prev == list && list->ptr_to_next == list)
	{
		list->ptr_to_prev = new_element;
		list->ptr_to_next = new_element;
		new_element->ptr_to_next = list;
		new_element->ptr_to_prev = list;
	}
	else
	{
		cout << "��������: " << endl << "  1. ��" << endl << "  2. �����" << endl;
		int add_type = choice();

		system("cls");

		if (add_type == 1)
			cout << "�������� ��: ";
		else
			cout << "�������� �����: ";
		int old_value = input();

		element* old_element = search(old_value);
		if (old_element == nullptr)
		{
			cout << old_value << " �� ������!";
			delete new_element;
		}
		else
		{
			if (add_type == 1)  
			{
				new_element->ptr_to_next = old_element;
				new_element->ptr_to_prev = old_element->ptr_to_prev;
				old_element->ptr_to_prev->ptr_to_next = new_element;
				old_element->ptr_to_prev = new_element;
			}

			if (add_type == 2) 
			{
				new_element->ptr_to_next = old_element->ptr_to_next;
				new_element->ptr_to_prev = old_element;
				old_element->ptr_to_next->ptr_to_prev = new_element;
				old_element->ptr_to_next = new_element;
			}
		}
	}
}

element* search(int old_value, bool step)
{
	if (list->ptr_to_prev == list && list->ptr_to_next == list)
		cout << "������ ����!" << endl;
	else
	{
		int i = 0;
		element* el = list->ptr_to_next;
		do
		{
			if (el->value == old_value) {
				if (step)
					cout << i << " ���" << endl;
				return el;
			}
			el = el->ptr_to_next;
			i++;
		} while (el != list);
	}
	return nullptr;
}

element* search_back(int item, bool step)
{
	if (list->ptr_to_prev == list && list->ptr_to_next == list)
		cout << "������ ����!" << endl;
	else
	{
		int i = 0;
		element* t = list->ptr_to_prev;
		do
		{
			if (t->value == item) {
				if (step)
					cout << i << " ���" << endl;
				return t;
			}
			t = t->ptr_to_prev;
			i++;
		} while (t != list);
	}
	return nullptr;
}

void del()
{
	if (list->ptr_to_prev == list && list->ptr_to_next == list)
		cout << "������ ����!" << endl;
	else
	{
		cout << "������� �������� ��� ��������: ";
		int to_delete = input();

		element* elem_delete = search(to_delete);
		if (elem_delete == nullptr)
			cout << to_delete << " �� ������!" << endl;
		else
		{
			elem_delete->ptr_to_prev->ptr_to_next = elem_delete->ptr_to_next;
			elem_delete->ptr_to_next->ptr_to_prev = elem_delete->ptr_to_prev;
		}
		delete  elem_delete;
	}
}
void search_menu()
{
	if (list->ptr_to_prev == list && list->ptr_to_next == list)
		cout << "������ ����!" << endl;
	else 
	{
		cout <<
			"�����: " << endl <<
			"  1. ������" << endl <<
			"  2. ��������" << endl;
		int search_type = choice();

		system("cls");

		cout << "������� ������� ��� ������: ";
		int to_search = input();

		element* elem;
		if (search_type == 1)
			elem = search(to_search, true);
		else
			elem = search_back(to_search, true);

		if (elem == nullptr)
			cout << to_search << " �� ������" << endl;
		else
			cout << to_search << " ������" << endl;
	}
}


void show()
{
	if (list->ptr_to_prev == list && list->ptr_to_next == list)
		cout << "������ ����!" << endl;
	else {
		cout <<
			"��������: " << endl <<
			"  1. � ������ �����������" << endl <<
			"  2. � �������� �����������" << endl;
		int show_type = choice();

		system("cls");

		if (show_type == 2)
		{
			cout << "������: ";
			element* t = list->ptr_to_prev;
			do
			{
				cout << t->value << " ";
				t = t->ptr_to_prev;
			} while (t != list);
			cout << endl;
		}
		else {
			cout << "������: ";
			element* t = list->ptr_to_next;
			do
			{
				cout << t->value << " ";
				t = t->ptr_to_next;
			} while (t != list);
			cout << endl;
		}
	}
}