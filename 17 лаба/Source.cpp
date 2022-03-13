/*����������� ����� ����������� �����������
j = (( h (����) + i ) mod m ) + 1, ��� i = 0, 1, 2, . . . , m-2
���������� ������ ����� � ������� � ��������� ��������� ��� ���� ���������
����� ��������� ����� � ������� � ��������� ��������� ��� ���� ���������
����� �������� ��������� ������� �� �����
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

		cout << "�������� ����� ������ ����:" << endl << "1 - �������� � �������" << endl << "2 - �����" << endl << "3 - ��������" << endl << "4 - �����" << endl;
		menu_point = input();
		system("cls");
		switch (menu_point)
		{
		case 1:
			fCreated = true;
			comparison = 0;
			cout << "������� �������� ����� = ";
			cin >> value;
			if (Search(Table, value, comparison) != -1)
				cout << "������ ���� ��� �������������. ���-�� ��������� = " << comparison << endl;
			else
			{
				comparison = 0;
				if (Add(Table, value, comparison) == 1)
					cout << "���� ��������. ���-�� ��������� = " << comparison << endl;
				else
					cout << "���� �� ��������" << endl;
			}
			break;
		case 2:
			if (fCreated)
			{
				comparison = 0;
				cout << "������� �������� ����� = ";
				cin >> value;
				if (Search(Table, value, comparison) != -1)
					cout << "������ = " << Search(Table, value, comparison) << " ���-�� ��������� = " << comparison << endl;
				else
					cout << "���� �� ������" << endl;
				break;
			}
			else
				cout << "������� �������� � ������� ��������" << endl;
			break;
		case 3:
			if (fCreated)
				Show(Table);
			else 
				cout << "������� �������� � ������� ��������" << endl;
			break;
		case 4:
			return 0;
		default:
			cout << "������" << endl;
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
		cout << "������ �����!" << endl;
		system("pause");
		cout << "���������� ��� ���: ";
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



