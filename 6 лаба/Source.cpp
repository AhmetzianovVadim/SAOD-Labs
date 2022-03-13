//additional list
#include <iostream>
#include <locale.h>

using namespace std;

struct element 
{
	int value;
	element* ptr_to_next = nullptr;
};

element* list = new element;
element* additional = new element;

int input();
element* search(int data);
void show();
void show_additional();
void add();
void push_additional(element* n);
void del();

int main()
{
	setlocale(LC_ALL, "Rus");
	int choice;

	do {
		system("cls");

		cout << "1. ��������" << endl << "2. �������" << endl << "3. �������� �������� ������" << endl << "4. �������� �������������� ������" << endl << "0. �����" << endl;
		choice = input();

		system("cls");

		switch (choice)
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
			show();
			break;
		case 4:
			show_additional();
			break;
		default:
			cout << "������ �����!" << endl;
		}

		system("pause");
	} while (choice != 0);

	return 0;
}

int input()
{
	int result;
	cin >> result;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "������������ ����!" << endl;
		system("pause");
		cout << "���������� ��� ���: ";
		cin >> result;
	}
	return result;
}

void add()
{
	cout << "������� ����� ��� ����������: ";
	int new_value = input();

	element* new_element = new element;
	new_element->value = new_value;

	if (list->ptr_to_next == nullptr)
		list->ptr_to_next = new_element;
	else
	{
		int add_type;
		cout <<
			"��������: " << endl <<
			"  1. ��" << endl <<
			"  2. �����" << endl;
		do {
			add_type = input();
			if (add_type != 1 && add_type != 2)
				cout << "������ �����! ���������� �����: ";
		} while (add_type != 1 && add_type != 2);

		if (add_type == 1)
			cout << "�������� ��: ";
		else
			cout << "�������� �����: ";
		int old_value = input();

		element* pre_old_element = search(old_value);
		if (pre_old_element == nullptr)
		{ 
			cout << old_value << " ������� �� ������!";
			delete new_element;
		}
		else
		{
			if (add_type == 2)
			{
				element* old_element = pre_old_element->ptr_to_next;
				new_element->ptr_to_next = old_element->ptr_to_next;
				old_element->ptr_to_next = new_element;
			}
			else
			{
				new_element->ptr_to_next = pre_old_element->ptr_to_next;
				pre_old_element->ptr_to_next = new_element;
			}
		}

	}
}

element* search(int data)
{
	for (element* t = list; t != nullptr; t = t->ptr_to_next)
		if (t->ptr_to_next != nullptr && t->ptr_to_next->value == data)
			return t;
	return nullptr;
}

void del()
{
	if (list->ptr_to_next == nullptr)
		cout << "������ ����!" << endl;
	else
	{
		cout << "������� ����� ��� ��������: ";
		int to_delete = input();

		element* ptr_to_pre_del = search(to_delete);
		if (ptr_to_pre_del == nullptr)
			cout << to_delete << " ������� �� ������!" << endl;
		else
		{
			element* t_d = ptr_to_pre_del->ptr_to_next;
			ptr_to_pre_del->ptr_to_next = t_d->ptr_to_next;
			push_additional(t_d);
		}
	}
}

void push_additional(element* n)
{
	n->ptr_to_next = additional->ptr_to_next;
	additional->ptr_to_next = n;
}

void show()
{
	if (list->ptr_to_next == nullptr)
		cout << "������ ����!" << endl;
	else
	{
		cout << "�������� ������: ";
		for (element* t = list->ptr_to_next; t != nullptr; t = t->ptr_to_next)
			cout << t->value << " ";
		cout << endl;
	}
}


void show_additional()
{
	if (additional->ptr_to_next == nullptr)
		cout << "�������������� ������ ����!" << endl;
	else
	{
		cout << "�������������� ������: ";
		for (element* t = additional->ptr_to_next; t != nullptr; t = t->ptr_to_next)
			cout << t->value << " ";
		cout << endl;
	}
}