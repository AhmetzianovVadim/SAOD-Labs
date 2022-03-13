/*  
������ ����������� ����� � ����������� �� � ������� ���-������� � ������������ �� ��������� ���-�������
������� ���-������� �� �����
������������ ����������� ����� ������ ������, ��� ��������� � ������� (� ������� ��������������), ��� � �������������: ��������� ��� ����� �������� ���-������� � �������� ���������� ��������������� ������ ������� � �������� ������
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

		cout << "�������� ����� ������ ����:" << endl << "1 - ������� �������" << endl << "2 - �����" << endl << "3 - ��������" << endl << "4 - �����" << endl;
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
			cout << "������� ������ �������: ";
			count = Input();
			while (count <= 1)
			{
				if (count <= 1)
					cout << "������ ������� ������ ���� ������ �������" << endl;
				count = Input();
			}
			Table = Create(count);
			cout <<"������� �������" << endl;
			break;
		case 2:
			if (count != 0)
			{
				cout << "������� �������� �����: ";
				cin >> value;
				int result = Search(value, Table, count);
				if (result != -1)
					cout << "������ = " << result << endl;
				else
					cout << "�� �������" << endl;
			}
			else
				cout << "�������� �������" << endl;
			break;
		case 3:
			if (count != 0)
				Show(Table, count);
			else
				cout << "�������� �������" << endl;
			break;
		case 4:
			return 0;
			break;
		default:
			cout <<  "������" << endl;
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
		cout << "������ �����!" << endl;
		system("pause");
		cout << "���������� ��� ���: ";
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
			cout << endl << "����������� ��������. �������� �����" << endl;
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
