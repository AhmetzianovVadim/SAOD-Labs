#include <iostream>
using namespace std;

void create_arr();
int input();
void show(int* arr);
void bubble_sort();
int* copy_arr();
void insertion_sort();
void selection_sort();
void shell_sort();
void sito(int* copied_arr, int k, int i);
int* pyramidal_sort(int* copied_arr);
int* steps_arr(int count);
int* quick_sort(int* arr, int left, int right);
int* arr = nullptr;
int size = 0;
int quick_sort_swaps = 0;
int quick_sort_comparison = 0;
int pyramidal_comparison = 0;
int pyramidal_swaps = 0;

int main()
{
	setlocale(LC_ALL, "Russian");
	int menu_point = -1;
	int* copied_arr = nullptr;
	do
	{
		system("cls");

		cout <<
			"1. ������� ������" << endl <<
			"2. �������� ����������������� ������" << endl <<
			"3. ����� �������� (������)" << endl <<
			"4. ����� �������" << endl <<
			"5. ����� ������" << endl <<
			"6. ����� �����" << endl <<
			"7. ����� ������� ����������" << endl <<
			"8. ������������� ����������" << endl <<
			"0. �����" << endl;

		menu_point = input();

		system("cls");

		if (arr == nullptr && menu_point != 1 && menu_point != 0)
		{
			cout << "������ �� ������" << endl;
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
		case 6:
			shell_sort();
			break;
		case 7:
			copied_arr = copy_arr();
			show(quick_sort(copied_arr, 0, ::size-1));
			cout << "���������� ��������� - " << quick_sort_comparison << endl;
			cout << "���������� ������������ - " << quick_sort_swaps << endl;
			quick_sort_swaps = 0;
			quick_sort_comparison = 0;
			copied_arr = nullptr;
			delete[] copied_arr;
			break;
		case 8:
			copied_arr = copy_arr();
			show(pyramidal_sort(copied_arr));
			cout << "���������� ��������� - " << pyramidal_comparison << endl;
			cout << "���������� ������������ - " << pyramidal_swaps << endl;
			pyramidal_comparison = 0;
			pyramidal_swaps = 0;
			copied_arr = nullptr;
			delete[] copied_arr;
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
	} while (menu_point != 0);
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
		::size = input();
		if (::size < 2 || ::size > 100000)
		{
			cout << "������ ������� ������ ���� � ��������� �� 2 �� 10000" << endl;
			system("pause");
		}
	} while (::size < 2 || ::size > 100000);
	if (arr != nullptr)
		delete[] arr;
	arr = new int[::size];
	srand(time(0));
	for (int i = 0; i < ::size; i++)
	{
		arr[i] = rand() % 1000;
	}
	show(arr);
}

void show(int* arr)
{
	for (int i = 0; i < ::size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void bubble_sort() //����� ��������(������)
{
	int comparison = 0, swaps = 0, temp;
	int* copied_arr = copy_arr();
	for (int i = 0; i < ::size; i++)
	{
		for (int j = ::size - 1; j > i; j--)
		{
			comparison++;
			if (copied_arr[j] < copied_arr[j - 1])
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
	copied_arr = nullptr;
	delete[] copied_arr;
}

int* copy_arr()
{
	int* pCopy = new int[::size];
	for (int i = 0; i < ::size; i++)
		pCopy[i] = arr[i];
	return pCopy;
}

void selection_sort() //����� ������
{
	int swaps = 0, comparison = 0, temp, min_index;
	int* copied_arr = copy_arr();
	for (int i = 0; i < ::size - 1; i++) {
		min_index = i;
		for (int j = i + 1; j < ::size; j++) {
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
	copied_arr = nullptr;
	delete[] copied_arr;
}

void insertion_sort() //����� �������
{
	int swaps = 0, comparison = 0, temp = 0, j = 0;
	int* copied_arr = copy_arr();
	for (int i = 0; i < ::size - 1; i++) {
		j = i + 1;
		while (j > 0) {
			comparison++;
			if ((copied_arr[j] < copied_arr[j - 1])) {
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
	copied_arr = nullptr;
	delete[] copied_arr;
}

void shell_sort()
{
	int step_width = 0, swaps = 0, comparison = 0;
	int* copied_arr = copy_arr(); 
	int steps_widths_number = (log(::size) / log(2));
	int* steps_widths_arr = steps_arr(steps_widths_number);
	for (int i = steps_widths_number; i > 0; i--)
	{
		step_width = steps_widths_arr[i-1];
		for (int second = step_width; second < ::size; second++)
		{
			int first = second - step_width;
			while (first > -1) 
			{
				comparison++;
				if (copied_arr[first+step_width] < copied_arr[first])
				{
					int temp = copied_arr[first];
					copied_arr[first] = copied_arr[first + step_width];
					copied_arr[first + step_width] = temp;
					swaps++;
					first -= step_width;
				}
				else break;

			}
		}
	}
	show(copied_arr);
	cout << "���������� ��������� - " << comparison << endl;
	cout << "���������� ������������ - " << swaps << endl;
	copied_arr = nullptr;
	delete[] copied_arr;
	steps_widths_arr = nullptr;
	delete[] steps_widths_arr;
}

int* steps_arr(int count)
{
	int* arr = new int[count];
	arr[0] = 1;

	for (int i = 1; i < count; i++) 
	{
		arr[i] = pow(2, i) + 1;
	}
	return arr;
}

int* quick_sort(int* copied_arr, int left, int right)
{
	int i = left;
	int j = right;
	int sred = arr[(left + right) / 2];
	while (i <= j)
	{
		while (arr[i] < sred) { i++; quick_sort_comparison++; };
		while (arr[j] > sred) { j--; quick_sort_comparison++; };
		quick_sort_comparison += 3;
		if (i <= j)
		{
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			quick_sort_swaps++;
			i++;
			j--;
		}
		else break;
	}
	quick_sort_comparison++;
	if (left < j)
		quick_sort(arr, left, j);
	quick_sort_comparison++;
	if (i < right)
		quick_sort(arr, i, right);
	return arr;
}

int* pyramidal_sort(int* copied_arr) 
{
	int left = ::size / 2;
	int right = ::size - 1;
	int temp;
	pyramidal_comparison++;
	while (left > 0) 
	{
		pyramidal_comparison++;
		left--;
		sito(copied_arr, left, right);
	}
	pyramidal_comparison++;
	while (right > 0) 
	{
		pyramidal_comparison++;
		pyramidal_swaps++;
		temp = copied_arr[0];
		copied_arr[0] = copied_arr[right];
		copied_arr[right] = temp;
		right--;
		sito(copied_arr, left, right);
	}
	return copied_arr;
}

void sito(int* copied_arr, int left, int right)
{
	int first = left;
	int second = 2 * first;
	int x = copied_arr[first];
	pyramidal_comparison++;
	if (second < right && copied_arr[second + 1] < copied_arr[second]) second++;
	pyramidal_comparison++;
	while (second < right && copied_arr[second] < x ) 
	{
		pyramidal_comparison++;
		copied_arr[first] = copied_arr[second];
		first = second;
		second = 2 * second;
		pyramidal_comparison++;
		if (second < right && copied_arr[second + 1] < copied_arr[second]) second++;
	}
	pyramidal_swaps++;
	copied_arr[first] = x;
}

