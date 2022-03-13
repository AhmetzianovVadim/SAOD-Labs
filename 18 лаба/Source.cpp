/*
��������� ������ ��������� ��������� ��������:
���������� ������ ����� � ������� � ��������� ��������� ��� ����
���������
����� ��������� ����� � ������� � ��������� ��������� ��� ����
���������
����� �������� ��������� ������� �� �����
�������� ��������� ����� �� ������
 
 
*/


#include <iostream>

using namespace std;

const int M = 10;

struct list_element
{
	string key;
	list_element* next;
};

struct list
{
	string value;
	list_element* head_element;
};

list l[M];

int Hash(string value);
list_element* GetItem(int index, int& comparison);
int Add(string value);
int Search(string to_search, int& comparison);
void Show();
int Del(string key);
int input();

int main()
{
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < M; i++)
	{
		l[i].value.clear();
		l[i].head_element = new list_element;
		l[i].head_element->next = nullptr;
	}
	string value;
	int comparison;
	int menu_point;
	bool fCreated = false;
	do
	{
		system("cls");

		cout << ("�������� ����� ������ ����:") << endl <<
		"1 - ��������" << endl <<
		"2 - ������" << endl <<
		"3 - ��������" << endl <<
		"4 - �������" << endl <<
		"5 - �����" << endl;

		menu_point = input();
		system("cls");

		switch (menu_point)

		{
		case 1:
			fCreated = true;
			cout <<"������� ���� = ";
			cin >> value;
			comparison = 0;
			if (Search(value, comparison) != 0)
				cout << "���� ��� �����������, ��������� = " << comparison << endl;
			else
			{
				comparison = Add(value);
				cout << "���� ��������. C�������� = " << comparison << endl;
			}
			break;
		case 2:
			if (fCreated)
			{
				cout << "������� ���� = ";
				cin >> value;
				comparison = 0;
				if (Search(value, comparison) != 0)
					cout << "�������, ��������� = " << comparison << endl;
				else
					cout << "�� �������" << endl;
			}
			else
				cout << "������� �������� �������� � ���-�������" << endl;
			break;
		case 3:
			if (fCreated)
				Show();
			else 
				cout << "������� �������� �������� � ���-�������" << endl;
			break;
		case 4:
			if (fCreated)
			{
				cout << "������� ���� = ";
				cin >> value;
				if (Del(value) == 1)
					cout << "�������" << endl;
				else
					cout << "�� �������" << endl;
			}
			else 
				cout << "������� �������� �������� � ���-�������" << endl;
			break;
		case 5:
			return 0;
		default:
			cout << "������" << endl;
			break;
		}
		system("pause");
	} while (menu_point != 5);
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
		cout << "���������� ��� ���: ";
		cin >> result;
	}
	return result;
}

int Hash(string value)
{
	int sum = 0;
	for (int i = 0; i < value.size(); i++)
		sum += value[i];
	return sum % M;
}

list_element* GetItem(int hash_index, int& comparison)
{
	list_element* CurrentItem = l[hash_index].head_element;
	while (++comparison && CurrentItem->next != nullptr)
		CurrentItem = CurrentItem->next;
	return CurrentItem;
}

int Add(string value)
{
	int count = 0;
	int hash = Hash(value);
	if (++count && l[hash].value.empty())
		l[hash].value = value;
	else
	{
		cout << endl << "�������� ����������� ��������" << endl;
		list_element* CurrentItem = GetItem(hash, count);
		list_element* tmp = new list_element;
		tmp->key = value;
		tmp->next = nullptr;
		CurrentItem->next = tmp;
		CurrentItem = tmp;
	}
	return count;
}

int Search(string to_search, int& comparison)
{
	int flag = 0;
	int hash = Hash(to_search);
	if (++comparison && l[hash].value == to_search)
		flag = 1;
	else
	{
		list_element* temp = l[hash].head_element->next;
		while (++comparison && temp != nullptr)
		{
			if (temp->key == to_search)
			{
				flag = 1;
				break;
			}
			temp = temp->next;
		}
	}
	if (flag)
		return 1;
	else
		return 0;
}

void Show()
{
	for (int i = 0; i < M; i++)
	{
		cout << "Table[" << i << "] = " << l[i].value << " : ";
		list_element* temp = l[i].head_element->next;
		while (temp != nullptr)
		{
			cout << temp->key << " ";
			temp = temp->next;
		}
		cout << endl;
	}
}

int Del(string value)
{
	int flag = 0;
	int hash = Hash(value);
	if (l[hash].value == value)
	{
		if (l[hash].head_element->next == nullptr)
		{
			flag = 1;
			l[hash].value = "";
		}
		else
		{
			l[hash].value = l[hash].head_element->next->key;
			list_element* tmp = l[hash].head_element->next;
			l[hash].head_element->next = tmp->next;
			flag = 1;
			delete tmp;
		}
	}
	else
	{
		list_element* prev = l[hash].head_element;
		list_element* tmp = l[hash].head_element->next;
		while (tmp != NULL)
		{
			if (tmp->key == value)
			{
				prev->next = tmp->next;
				delete tmp;
				flag = 1;
				break;
			}
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
	}
	return flag;
}

