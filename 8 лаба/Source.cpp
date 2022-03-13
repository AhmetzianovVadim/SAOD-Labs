//������ ������B ����� � �����
#include <iostream>
#include <locale.h>

//������ ������� (��������,������������, ��������������, ���������, � ����������(���))

using namespace std;

struct sublist_element
{
	int value;
	sublist_element* ptr_to_next = nullptr;
	sublist_element* ptr_to_prev = nullptr;
};


struct list_element
{
	int number_list;
	sublist_element* ptr_to_sublist = nullptr;
	list_element* ptr_to_next = nullptr;
	list_element* ptr_to_prev = nullptr;
};

int input();
void add_to_list(list_element* list);
int choice();
list_element* search_list(list_element* list, int item);
void add_to_sublist(list_element* list);
sublist_element* search_sublist(sublist_element* list, int inf);
void del_from_list(list_element* list);
void del_from_sublist(list_element* list);
void show(list_element* list);
void full_search(list_element* list);

bool empty_list(list_element* list)
{
	return list->ptr_to_prev == list && list->ptr_to_next == list;
}

bool empty_sublist(sublist_element* list)
{
	return list->ptr_to_prev == list && list->ptr_to_next == list;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	list_element* list = new list_element;
	list->ptr_to_next = list;
	list->ptr_to_prev = list;

	int menu_point;

	do {
		system("cls");

		cout << "1. �������� � �������� ������" << endl << "2. �������� �� ��������������� ������" << endl << "3. ������� �� ��������� ������" << endl << "4. ������� �� ���������������� ������ " << endl << "5. �����" << endl << "6. ��������" << endl << "0. �����" << endl;
		menu_point = input();

		system("cls");

		switch (menu_point)
		{
		case 0:
			return 0;
		case 1:
			add_to_list(list);
			break;
		case 2:
			add_to_sublist(list);
			break;
		case 3:
			del_from_list(list);
			break;
		case 4:
			del_from_sublist(list);
			break;
		case 5:
			full_search(list);
			break;
		case 6:
			show(list);
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
		cout << "������!" << endl;
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


void add_to_list(list_element* list)
{
	cout << "������� ����� ������ ��� ����������: ";
	int new_list_number = input();

	list_element* new_list_element = new list_element;
	new_list_element->number_list = new_list_number;

	sublist_element* new_sublist = new sublist_element;
	new_list_element->ptr_to_sublist = new_sublist;
	new_sublist->ptr_to_next = new_sublist;
	new_sublist->ptr_to_prev = new_sublist;

	if (empty_list(list))
	{
		list->ptr_to_prev = new_list_element;
		list->ptr_to_next = new_list_element;
		new_list_element->ptr_to_next = list;
		new_list_element->ptr_to_prev = list;
	}
	else
	{
		cout <<
			"��������: " << endl <<
			"  1. ��" << endl <<
			"  2. �����" << endl;
		int add_type = choice();

		system("cls");

		if (add_type == 1)
			cout << "�������� ��: ";
		else
			cout << "�������� �����: ";
		int number_old_list_element = input();

		list_element* old_list_element = search_list(list, number_old_list_element);
		if (old_list_element == nullptr)
		{
			cout << number_old_list_element << " �� ������";
			delete old_list_element;
		}
		else
		{
			if (add_type == 1)
			{
				new_list_element->ptr_to_next = old_list_element;
				new_list_element->ptr_to_prev = old_list_element->ptr_to_prev;
				old_list_element->ptr_to_prev->ptr_to_next = new_list_element;
				old_list_element->ptr_to_prev = new_list_element;
			}

			if (add_type == 2)
			{
				new_list_element->ptr_to_next = old_list_element->ptr_to_next;
				new_list_element->ptr_to_prev = old_list_element;
				old_list_element->ptr_to_next->ptr_to_prev = new_list_element;
				old_list_element->ptr_to_next = new_list_element;
			}
		}
	}
}

list_element* search_list(list_element* list, int item)
{
	if (empty_list(list))
		cout << "������ ����!" << endl;
	else
	{
		list_element* t = list->ptr_to_next;
		do
		{
			if (t->number_list == item)
				return t;
			t = t->ptr_to_next;
		} while (t != list);
	}
	return nullptr;
}

void add_to_sublist(list_element* list)
{
	if (empty_list(list))
		cout << "������� �������� ���� �� ���� �������� ������" << endl;
	else 
	{
		cout << "������� ����� ������: ";
		int number_of_list = input();

		list_element* checked_list = search_list(list, number_of_list);
		if (checked_list == nullptr)
			cout << number_of_list << " �� ������!" << endl;
		else
		{
			sublist_element* sublist = checked_list->ptr_to_sublist;

			cout << "������� �������� ��� ����������: ";
			int new_sublist_value = input();

			sublist_element* new_sublist_element = new sublist_element;
			new_sublist_element->value = new_sublist_value;

			if (empty_sublist(sublist))
			{
				sublist->ptr_to_prev = new_sublist_element;
				sublist->ptr_to_next = new_sublist_element;
				new_sublist_element->ptr_to_next = sublist;
				new_sublist_element->ptr_to_prev = sublist;
			}
			else
			{
				cout <<
					"��������: " << endl <<
					"  1. ��" << endl <<
					"  2. �����" << endl;
				int add_type = choice();

				system("cls");

				if (add_type == 1)
					cout << "�������� ��: ";
				else
					cout << "�������� �����: ";
				int old_sublist_element_value = input();

				sublist_element* old_sublist_element = search_sublist(sublist, old_sublist_element_value);
				if (old_sublist_element == nullptr)
				{
					cout << old_sublist_element_value << " �� ������!";
					delete new_sublist_element;
				}
				else
				{
					if (add_type == 1)
					{
						new_sublist_element->ptr_to_next = old_sublist_element;
						new_sublist_element->ptr_to_prev = old_sublist_element->ptr_to_prev;
						old_sublist_element->ptr_to_prev->ptr_to_next = new_sublist_element;
						old_sublist_element->ptr_to_prev = new_sublist_element;
					}

					if (add_type == 2)
					{
						new_sublist_element->ptr_to_next = old_sublist_element->ptr_to_next;
						new_sublist_element->ptr_to_prev = old_sublist_element;
						old_sublist_element->ptr_to_next->ptr_to_prev = new_sublist_element;
						old_sublist_element->ptr_to_next = new_sublist_element;
					}
				}
			}
		}
	}
}

sublist_element* search_sublist(sublist_element* list, int inf)
{
	if (empty_sublist(list))
		cout << "������ ����!" << endl;
	else
	{
		sublist_element* t = list->ptr_to_next;
		do
		{
			if (t->value == inf)
				return t;
			t = t->ptr_to_next;
		} while (t != list);
	}
	return nullptr;
}

void del_from_list(list_element* list)
{
	if (empty_list(list))
		cout << "������ ����!" << endl;
	else
	{
		cout << "������� ����� ������ ��� ��������: ";
		int number_list_to_delete = input();

		list_element* element_to_delete = search_list(list, number_list_to_delete);
		if (element_to_delete == nullptr)
			cout << number_list_to_delete << " �� ������" << endl;
		else
		{
			sublist_element* sublist = element_to_delete->ptr_to_sublist;

			if (!empty_sublist(sublist)) {
				sublist_element* t = sublist->ptr_to_next;
				do
				{
					sublist_element* next = t->ptr_to_next;
					delete t;
					t = next;
				} while (t != sublist);
			}

			delete element_to_delete->ptr_to_sublist;

			element_to_delete->ptr_to_next->ptr_to_prev = element_to_delete->ptr_to_prev;
			element_to_delete->ptr_to_prev->ptr_to_next = element_to_delete->ptr_to_next;
			
			delete  element_to_delete;
		}
	}
}

void del_from_sublist(list_element* list)
{
	if (empty_list(list))
		cout << "������� �������� ���� �� ���� �������� ������" << endl;
	else
	{
		cout << "������� ����� ������: ";
		int number_list = input();

		list_element* from_list = search_list(list, number_list);
		if (from_list == nullptr)
			cout << number_list << " �� ������" << endl;
		else
		{
			sublist_element* sublist = from_list->ptr_to_sublist;

			if (empty_sublist(sublist))
				cout << "��������������� ������ ����!" << endl;
			else
			{
				cout << "������� �������� ��� ��������: ";
				int value_to_delete = input();

				sublist_element* sublist_element_to_delete = search_sublist(sublist, value_to_delete);
				if (sublist_element_to_delete == nullptr)
					cout << value_to_delete << " �� ������" << endl;
				else
				{
					sublist_element_to_delete->ptr_to_prev->ptr_to_next = sublist_element_to_delete->ptr_to_next;
					sublist_element_to_delete->ptr_to_next->ptr_to_prev = sublist_element_to_delete->ptr_to_prev;
				}
				delete  sublist_element_to_delete;
			}
		}
	}
}

void full_search(list_element* list)
{
	if (list->ptr_to_prev == list && list->ptr_to_next == list)
		cout << "������ ����!" << endl;
	else
	{
		cout << "������� �������� ��� ������: ";
		int to_search = input();

		list_element* t = list->ptr_to_next;
		do
		{
			if (search_sublist(t->ptr_to_sublist, to_search) != nullptr)
			{
				system("cls");
				cout << to_search << " ������" << endl;
				return;
			}
			t = t->ptr_to_next;
		} while (t != list);

		system("cls");
		cout << to_search << " �� ������" << endl;
	}
}

void show(list_element* list)
{
	if (empty_list(list))
		cout << "������ ����!" << endl;
	else
	{
		list_element* t = list->ptr_to_next;
		do
		{
			cout << t->number_list << ": ";

			sublist_element* sublist = t->ptr_to_sublist;

			if (empty_sublist(sublist))
				cout << "�����";
			else
			{
				sublist_element* t1 = sublist->ptr_to_next;
				do
				{
					cout << t1->value << " ";
					t1 = t1->ptr_to_next;
				} while (t1 != sublist);
			}
			cout << endl;
			t = t->ptr_to_next;
		} while (t != list);
	}
}