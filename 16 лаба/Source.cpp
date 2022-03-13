/*  
ввести подобранные ключи и расположить их в ячейках хеш-таблицы в соответствии со значением хеш-функции
вывести хеш-таблицу на экран
организовать циклический поиск разных ключей, как имеющихся в таблице (с выводом местоположения), так и отсутствующих: вычислить для ключа значение хеш-функции и сравнить содержимое соответствующей ячейки таблицы с исходным ключом
*/
#include <iostream>

using namespace std;

int Hash(string key, int n);
int Input();
string* Create(int n);
int Search(string key, string* Table, int n);
void Show(string* Table, int n);

int main()
{
	setlocale(LC_ALL, "Russian");
	string* Table = nullptr;
	string value;
	int count = 0;
	int menu_choice;
	do
	{
		system("cls");

		cout << "Выберите номер пункта меню:" << endl << "1 - Создать таблицу" << endl << "2 - Поиск" << endl << "3 - Показать" << endl << "4 - Выход" << endl;
		menu_choice = Input();
		system("cls");
		switch (menu_choice)
		{
		case 1:
			if (Table != nullptr)
			{
				Table = nullptr;
				delete[] Table;
			}
			cout << "Введите размер таблицы: ";
			count = Input();
			while (count <= 1)
			{
				if (count <= 1)
					cout << "Размер таблицы должен быть больше единицы" << endl;
				count = Input();
			}
			Table = Create(count);
			cout <<"Таблица создана" << endl;
			break;
		case 2:
			if (count != 0)
			{
				cout << "Введите значение ключа: ";
				cin >> value;
				int result = Search(value, Table, count);
				if (result != -1)
					cout << "Индекс = " << result << endl;
				else
					cout << "Не найдено" << endl;
			}
			else
				cout << "Создайте таблицу" << endl;
			break;
		case 3:
			if (count != 0)
				Show(Table, count);
			else
				cout << "Создайте таблицу" << endl;
			break;
		case 4:
			return 0;
			break;
		default:
			cout <<  "Ошибка" << endl;
			break;
		}
		system("pause");
	} while (menu_choice != 4);
}

int Input()
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

string* Create(int count)
{
	string* Table = new string[count];
	int i = 0;
	while (i < count)
	{
		string key;
		cout << endl << "key = ";
		cin >> key;
		int hash = Hash(key, count);
		if (Table[hash].empty())
			Table[hash] = key;
		else
		{
			cout << endl << "Конфликтная ситуация. Замените слово" << endl;
			continue;
		}
		i++;
	}
	return Table;
}

int Hash(string value, int count)
{
	int sum = 0;
	for (int i = 0; i < value.size(); i++)
		sum += value[i];
	return sum % count;
}

int Search(string value, string* Table, int count)
{
	int hash = Hash(value, count);
	if (Table[hash] == value)
		return hash;
	else
		return -1;
}

void Show(string* Table, int count)
{
	for (int i = 0; i < count; i++)
		cout << "Table[" << i << "] = " << Table[i] << endl;
}
