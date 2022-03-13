#include <iostream>
using namespace std;

int* arr = nullptr;
int count = 0;
void create_arr();

int input();
void show(int* arr);
void bubble_sort();
int* copy_arr();
void insertion_sort();
void selection_sort();

int main() 
{
	setlocale(LC_ALL, "Russian");
	int menu_point = -1;
	do
	{
		system("cls");

		cout <<
			"1. ������� ������" << endl <<
			"2. �������� ����������������� ������" << endl <<
			"3. ����� �������� (������)" << endl <<
			"4. ����� �������" << endl <<
			"5. ����� ������" << endl <<
			"0. �����" << endl;

		menu_point = input();

		system("cls");

		if (arr == nullptr && menu_point != 1 && menu_point != 0)
		{
			cout << "������" << endl;
			system("pause");
			continue;
		}
		switch (menu_point)
		{
		case 1:
			create_arr();
			break;
		case 2:
			show(arr);
			break;
		case 3:
			bubble_sort();
			break;
		case 4:
			insertion_sort();
			break;
		case 5:
			selection_sort();
			break;
		case 0:
			if (arr != nullptr) delete[] arr;
			return 0;
			break;
		default:
			cout << "������� ������� �������" << endl;
			break;
		}
		system("pause");
	} 
	while (menu_point != 0);
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

void create_arr() 
{
	do 
	{	
		system("cls");
		cout << "������� ������ �������: ";
		::count = input();
		if (::count < 0 || ::count > 10000)
		{
			cout << "������ ������� ������ ���� � ��������� �� 1 �� 10000" << endl;
			system("pause");
		}
	} while (::count < 0 || ::count > 10000);
	if (arr != nullptr)
		delete[] arr;
	arr = new int[::count];
	srand(time(0));
	for (int i = 0; i < ::count; i++)
	{
		arr[i] = rand() % 1000;
	}
	show(arr);
}

void show(int* arr)
{
	for (int i = 0; i < ::count; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void bubble_sort() //����� ��������(������)
{
	int comparison = 0, swaps = 0, temp;
	int* copied_arr = copy_arr();
	for (int i = 0; i < ::count; i++)
	{
		for (int j = ::count - 1; j > i; j--) 
		{
			comparison++;
			if (copied_arr[j] < copied_arr[j-1]) 
			{
				temp = copied_arr[j];
				copied_arr[j] = copied_arr[j - 1];
				copied_arr[j - 1] = temp;
				swaps++;
			}
		}
	}
	
	show(copied_arr);
	cout << "���������� ��������� - " << comparison << endl;
	cout << "���������� ������������ - " << swaps << endl;
	delete[] copied_arr;
}

int* copy_arr() 
{
	int* pCopy = new int[::count];
	for (int i = 0; i < ::count; i++)
		pCopy[i] = arr[i];
	return pCopy;
}

void insertion_sort() //����� �������
{
	int swaps = 0, comparison = 0, temp = 0, j = 0;
	int* copied_arr = copy_arr();
	for (int i = 0; i < ::count - 1; i++) {
		j = i + 1;
		while (j > 0) {
			comparison++;
			if ((copied_arr[j] < copied_arr[j - 1])) 
			{
				temp = copied_arr[j];
				copied_arr[j] = copied_arr[j - 1];
				copied_arr[j - 1] = temp;
				swaps++;
				j--;
			}
			else break;
		}
	}
	show(copied_arr);
	cout << "���������� ��������� - " << comparison << endl;
	cout << "���������� ������������ - " << swaps << endl;
	delete[] copied_arr;
}

void selection_sort() //����� ������
{
	int swaps = 0, comparison = 0, temp, min_index;
	int* copied_arr = copy_arr();
	for (int i = 0; i < ::count - 1; i++) {
		min_index = i;
		for (int j = i + 1; j < ::count; j++) {
			comparison++;
			if (copied_arr[min_index] > copied_arr[j]) {
				min_index = j;
			}
		}
		if (min_index != i) {
			temp = copied_arr[i];
			copied_arr[i] = copied_arr[min_index];
			copied_arr[min_index] = temp;
			swaps++;
		}
	}
	show(copied_arr);
	cout << "���������� ��������� - " << comparison << endl;
	cout << "���������� ������������ - " << swaps << endl;
	delete[] copied_arr;
}