/*Реализовать метод внутреннего хеширования
j = (( h (ключ) + i ) mod m ) + 1, где i = 0, 1, 2, . . . , m-2
добавление нового ключа в таблицу с подсчетом сделанных при этом сравнений
поиск заданного ключа в таблице с подсчетом сделанных при этом сравнений
вывод текущего состояния таблицы на экран
*/
#include <iostream>
using namespace std;

const int M = 10;

int input();
int Hash(string key, int j);
int Add(string* Table, string key, int& comparison);
int Search(string* Table, string key, int& comparison);
void Show(string* Table);

int main()
{
	bool fCreated = false;
	setlocale(LC_ALL, "Russian");
	string Table[M];
	for (int i = 0; i < M; i++)
		Table[i].clear();
	string value;
	int comparison;
	int menu_point;
	do
	{
		system("cls");

		cout << "Выберите номер пункта меню:" << endl << "1 - Добавить в таблицу" << endl << "2 - Поиск" << endl << "3 - Показать" << endl << "4 - Выход" << endl;
		menu_point = input();
		system("cls");
		switch (menu_point)
		{
		case 1:
			fCreated = true;
			comparison = 0;
			cout << "Введите значение ключа = ";
			cin >> value;
			if (Search(Table, value, comparison) != -1)
				cout << "Данный ключ уже использовался. Кол-во сравнений = " << comparison << endl;
			else
			{
				comparison = 0;
				if (Add(Table, value, comparison) == 1)
					cout << "Ключ добавлен. Кол-во сравнений = " << comparison << endl;
				else
					cout << "Ключ не добавлен" << endl;
			}
			break;
		case 2:
			if (fCreated)
			{
				comparison = 0;
				cout << "Введите значение ключа = ";
				cin >> value;
				if (Search(Table, value, comparison) != -1)
					cout << "Индекс = " << Search(Table, value, comparison) << " Кол-во сравнений = " << comparison << endl;
				else
					cout << "Ключ не найден" << endl;
				break;
			}
			else
				cout << "Сначала добавьте в таблицу элементы" << endl;
			break;
		case 3:
			if (fCreated)
				Show(Table);
			else 
				cout << "Сначала добавьте в таблицу элементы" << endl;
			break;
		case 4:
			return 0;
		default:
			cout << "Ошибка" << endl;
			break;
		}
		system("pause");
	} while (menu_point != 4);
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
		cout << "Попробуйте еще раз: ";
		cin >> result;
	}
	return result;
}


int Add(string* Table, string key, int& comparison)
{
	int flag = 0;
	int hash;
	for (int i = 0; i < M; i++)
	{
		hash = Hash(key, i);
		comparison++;
		if (Table[hash].empty())
		{
			Table[hash] = key;
			flag = 1;
			break;
		}
	}
	if (flag == 1)
		return 1;
	else
		return 0;
}

int Search(string* Table, string key, int& comparison)
{
	bool flag = false;
	int hash;
	for (int i = 0; i < M; i++)
	{
		hash = Hash(key, i);
		comparison++;
		if (Table[hash] == key)
		{
			flag = true;
			break;
		}
	}
	if (flag)
		return hash;
	else
		return -1;
}

int Hash(string key, int j)
{
	int sum = j;
	for (int i = 0; i < key.size(); i++)
		sum += (int)key[i];
	return sum % M;
}


void Show(string* Table)
{
	for (int i = 0; i < M; i++)
		cout << "Table[" << i << "] = " << Table[i] << endl;
}



