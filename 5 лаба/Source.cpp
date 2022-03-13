//список с индексами
#include <iostream>
#include <locale.h>

#define SIZE 5

using namespace std;

struct element 
{
	int value;
	int ptr_to_next_element;
};

struct List 
{
	int count = 0;
	int size = SIZE;
	element list[SIZE + 1];
};

int input();
void add(List* l);
int search(List* l, int to_search);
void show(List* l);
void del(List* l);

int main() 
{
	setlocale(LC_ALL, "Rus");
	List l;
	
	l.list[0].ptr_to_next_element = 0;
	for (int i = 1; i < l.size + 1; i++)
		l.list[i].ptr_to_next_element = -1;

	int choice;

	do 
	{
		system("cls");
		cout <<"1. Добавить" << endl << "2. Удалить" << endl << "3. Показать" << endl << "0. Выход" << endl;
		choice = input();

		system("cls");

		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			add(&l);
			break;
		case 2:
			del(&l);
			break;
		case 3:
			show(&l);
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

void add(List* l) 
{
	if (l->count == l->size)
		cout << "Список заполнен!" << endl;
	else
	{
		cout << "Введите число для добавления: ";
		int new_value = input();

		if (l->count == 0)
		{
			l->list[1].ptr_to_next_element = l->list[0].ptr_to_next_element; 
			l->list[0].ptr_to_next_element = 1;
			l->list[1].value = new_value;
			l->count++;
		}
		else
		{
			int next_free_index;
			for (next_free_index = 1; l->list[next_free_index].ptr_to_next_element != -1; next_free_index++);

			int add_type;
			cout << "Добавить: " << endl << "  1. до элемента" << endl << "  2. после элемента" << endl;

			do {
				add_type = input();
				if (add_type != 1 && add_type != 2)
					cout << "Ошибка ввода! Попробуйте: ";
			} while (add_type != 1 && add_type != 2);

			if (add_type == 1)
				cout << "Добавить до: ";
			else
				cout << "Добавить после: ";
			int old_value = input();
			int index_ptr_to_old_value = search(l, old_value);
			if (index_ptr_to_old_value == -1)
				cout << old_value << " элемент не найден!" << endl;
			else
			{
				if (add_type == 2)
				{
					int old_value_index = l->list[index_ptr_to_old_value].ptr_to_next_element;
					l->list[next_free_index].value = new_value;
					l->list[next_free_index].ptr_to_next_element = l->list[old_value_index].ptr_to_next_element;
					l->list[old_value_index].ptr_to_next_element = next_free_index;
					l->count++;
				}
				else 
				{  
					l->list[next_free_index].value = new_value;
					l->list[next_free_index].ptr_to_next_element = l->list[index_ptr_to_old_value].ptr_to_next_element;		
					l->list[index_ptr_to_old_value].ptr_to_next_element = next_free_index;
					l->count++;
				}
			}
		}
	}
}

int search(List* l, int to_search) 
{
	int i = 0;
	do
	{
		if (l->list[i].value == to_search)
		{
			for (int j = 0;; j++)
			{
				if (l->list[j].ptr_to_next_element == i) {
					return j;
				}
			}
		}
		i = l->list[i].ptr_to_next_element;
	} while (i != 0);
	return -1;
}

void del(List* l)
{
	if (l->count == 0)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите элемент для удаления: ";
		int to_delete = input();

		int index_ptr_to_del_value = search(l, to_delete);
		if (index_ptr_to_del_value == -1)
			cout << to_delete << " элемент не найден!" << endl;
		else
		{
			int index_del_value = l->list[index_ptr_to_del_value].ptr_to_next_element;
			int next = l->list[index_del_value].ptr_to_next_element; 
			l->list[index_del_value].ptr_to_next_element = -1; 
			l->list[index_ptr_to_del_value].ptr_to_next_element = next; 
			l->count--;
			cout << to_delete << " удален!" << endl;
		}
	}
}


void show(List* l)
{
	if (l->count == 0)
		cout << "Список пуст!" << endl;
	else
	{
		int i = l->list[0].ptr_to_next_element;
		while (i != 0)
		{
			cout << l->list[i].value << " ";
			i = l->list[i].ptr_to_next_element;
		}
		cout << endl;
	}
}