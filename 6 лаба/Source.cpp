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

		cout << "1. Добавить" << endl << "2. Удалить" << endl << "3. Показать основной список" << endl << "4. Показать дополнительный список" << endl << "0. Выход" << endl;
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
			cout << "Ошибка ввода!" << endl;
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
		cout << "Неправильный ввод!" << endl;
		system("pause");
		cout << "Попробуйте еще раз: ";
		cin >> result;
	}
	return result;
}

void add()
{
	cout << "Введите число для добавления: ";
	int new_value = input();

	element* new_element = new element;
	new_element->value = new_value;

	if (list->ptr_to_next == nullptr)
		list->ptr_to_next = new_element;
	else
	{
		int add_type;
		cout <<
			"Добавить: " << endl <<
			"  1. до" << endl <<
			"  2. после" << endl;
		do {
			add_type = input();
			if (add_type != 1 && add_type != 2)
				cout << "Ошибка ввода! Попробуйте снова: ";
		} while (add_type != 1 && add_type != 2);

		if (add_type == 1)
			cout << "Добавить до: ";
		else
			cout << "Добавить после: ";
		int old_value = input();

		element* pre_old_element = search(old_value);
		if (pre_old_element == nullptr)
		{ 
			cout << old_value << " элемент не найден!";
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
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите число для удаления: ";
		int to_delete = input();

		element* ptr_to_pre_del = search(to_delete);
		if (ptr_to_pre_del == nullptr)
			cout << to_delete << " элемент не найден!" << endl;
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
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Основной список: ";
		for (element* t = list->ptr_to_next; t != nullptr; t = t->ptr_to_next)
			cout << t->value << " ";
		cout << endl;
	}
}


void show_additional()
{
	if (additional->ptr_to_next == nullptr)
		cout << "Дополнительный список пуст!" << endl;
	else
	{
		cout << "Дополнительный список: ";
		for (element* t = additional->ptr_to_next; t != nullptr; t = t->ptr_to_next)
			cout << t->value << " ";
		cout << endl;
	}
}