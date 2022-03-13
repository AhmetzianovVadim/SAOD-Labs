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
			"1. Создать массив" << endl <<
			"2. Показать неотсортированный массив" << endl <<
			"3. Метод пузырька (обмена)" << endl <<
			"4. Метод вставок" << endl <<
			"5. Метод выбора" << endl <<
			"0. Выход" << endl;

		menu_point = input();

		system("cls");

		if (arr == nullptr && menu_point != 1 && menu_point != 0)
		{
			cout << "Ошибка" << endl;
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
			cout << "Команда введена неверно" << endl;
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
		cout << "Ошибка ввода!" << endl;
		system("pause");
		cout << "Попробуйте еще раз: ";
		cin >> result;
	}
	return result;
}

void create_arr() 
{
	do 
	{	
		system("cls");
		cout << "Введите размер массива: ";
		::count = input();
		if (::count < 0 || ::count > 10000)
		{
			cout << "Размер массива должен быть в диапазоне от 1 до 10000" << endl;
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

void bubble_sort() //метод пузырька(обмена)
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
	cout << "Количество сравнений - " << comparison << endl;
	cout << "Количество перестановок - " << swaps << endl;
	delete[] copied_arr;
}

int* copy_arr() 
{
	int* pCopy = new int[::count];
	for (int i = 0; i < ::count; i++)
		pCopy[i] = arr[i];
	return pCopy;
}

void insertion_sort() //метод вставки
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
	cout << "Количество сравнений - " << comparison << endl;
	cout << "Количество перестановок - " << swaps << endl;
	delete[] copied_arr;
}

void selection_sort() //метод выбора
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
	cout << "Количество сравнений - " << comparison << endl;
	cout << "Количество перестановок - " << swaps << endl;
	delete[] copied_arr;
}