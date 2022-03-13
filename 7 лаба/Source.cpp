//дBунапраBленнbIй список поиск и просмотр B прямом и обратном напраBлениях
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

		cout << "1. Добавить" << endl << "2. Удалить" << endl << "3. Поиск" << endl << "4. Показать" << endl << "0. Выход" << endl;

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
			cout << "Ошибка ввода!" << endl;
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
		cout << "Ошибка ввода!" << endl;
		system("pause");
		cout << "Попробуйте снова: ";
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
			cout << "Ошибка ввода! Попробуйте снова: ";
	} while (result != 1 && result != 2);
	return result;
}

void add()
{
	cout << "Введите значение для добавления: ";
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
		cout << "Добавить: " << endl << "  1. До" << endl << "  2. После" << endl;
		int add_type = choice();

		system("cls");

		if (add_type == 1)
			cout << "Добавить до: ";
		else
			cout << "Добавить после: ";
		int old_value = input();

		element* old_element = search(old_value);
		if (old_element == nullptr)
		{
			cout << old_value << " не найден!";
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
		cout << "Список пуст!" << endl;
	else
	{
		int i = 0;
		element* el = list->ptr_to_next;
		do
		{
			if (el->value == old_value) {
				if (step)
					cout << i << " шаг" << endl;
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
		cout << "Список пуст!" << endl;
	else
	{
		int i = 0;
		element* t = list->ptr_to_prev;
		do
		{
			if (t->value == item) {
				if (step)
					cout << i << " шаг" << endl;
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
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите значение для удаления: ";
		int to_delete = input();

		element* elem_delete = search(to_delete);
		if (elem_delete == nullptr)
			cout << to_delete << " не найден!" << endl;
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
		cout << "Список пуст!" << endl;
	else 
	{
		cout <<
			"Поиск: " << endl <<
			"  1. прямой" << endl <<
			"  2. обратный" << endl;
		int search_type = choice();

		system("cls");

		cout << "Введите элемент для поиска: ";
		int to_search = input();

		element* elem;
		if (search_type == 1)
			elem = search(to_search, true);
		else
			elem = search_back(to_search, true);

		if (elem == nullptr)
			cout << to_search << " не найден" << endl;
		else
			cout << to_search << " найден" << endl;
	}
}


void show()
{
	if (list->ptr_to_prev == list && list->ptr_to_next == list)
		cout << "Список пуст!" << endl;
	else {
		cout <<
			"Показать: " << endl <<
			"  1. в прямом направлении" << endl <<
			"  2. в обратном направлении" << endl;
		int show_type = choice();

		system("cls");

		if (show_type == 2)
		{
			cout << "Список: ";
			element* t = list->ptr_to_prev;
			do
			{
				cout << t->value << " ";
				t = t->ptr_to_prev;
			} while (t != list);
			cout << endl;
		}
		else {
			cout << "Список: ";
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