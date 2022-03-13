/*Реализовать специальные методы сортировки :
     Простейшую карманную с использованием второго массива и без него
     Обобщенную карманную сортировку с повторяющимися ключами и
дополнительными списками
     Поразрядную сортировку
Все методы реализуются как подпрограммы и поэтапно добавляются в
главную программ*/


#include <iostream>

using namespace std;

int check = 0;

struct list
{
	int value;
	list* next = nullptr;
};

int input();
int* Create_Unique(int arr_size);
int* Create(int arr_size);
void Show(int* arr, int arr_size);
void Copy(int* arr, int* copia, int n);
void Karman_With_Arr(int* copied_arr, int arr_size);
void Add_Item(list* pHead, int value);
void Clear(list* pHead);
void ShowKar_Com(list* sort, int arr_sized);
void Karman_Common(int* arr, int arr_sized);
void Karman_Without_Arr(int* copied_arr, int arr_sized);
void Razrad(int* copied_arr, int arr_sized);
int get_Arr_Size();

bool unique = false;

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int* unsort = NULL;
	int* sort = NULL;
	int arr_size = -1;
	int menu_point = -1;
	do
	{
		system("cls");

		cout << 
			"1 - Автоматическое создание массива с неповторяющимися значениями" << endl <<
			"2 - Автоматическое создание массива с повторяющимися значениями" << endl <<
			"3 - Показать исходный массив" << endl <<
			"4 - Карманная сортировка с дополнительным массивом" << endl <<
			"5 - Карманная сортировка без дополнительного массива" << endl <<
			"6 - Обобщенная карманная сортировка" << endl <<
			"7 - Поразрядная сортировка" << endl <<
			"8 - Выход" << endl;

		menu_point = input();
		
		system("cls");

		switch (menu_point)
		{
		case 1:
			if (arr_size > 0)
			{
				unsort = nullptr;
				sort = nullptr;
				delete[] unsort;
				delete[] sort;
			}
			unique = true;
			arr_size = get_Arr_Size();
			unsort = Create_Unique(arr_size);
			sort = new int[arr_size];
			cout << "Массив создан" << endl;
			break;
		case 2:
			if (arr_size > 0)
			{
				unsort = nullptr;
				sort = nullptr;
				delete[] unsort;
				delete[] sort;
			}
			unique = false;
			arr_size = get_Arr_Size();
			unsort = Create(arr_size);
			sort = new int[arr_size];
			cout << "Массив создан" << endl;
			break;
		case 3:
			if (arr_size > 0)
				Show(unsort, arr_size);
			else
				cout << "Массив пуст!" << endl;
			break;
		case 4:
			if (arr_size > 0)
			{
				if (unique)
				{
					Copy(unsort, sort, arr_size);
					Karman_With_Arr(sort, arr_size);
				}
				else
					cout << "Создайте массив с неповторяющимися значениями" << endl;
			}
			else
				cout << "Массив пуст!" << endl;
			break;
		case 5:
			if (arr_size > 0)
			{
				if (unique)
				{
					Copy(unsort, sort, arr_size);
					Karman_Without_Arr(sort, arr_size);
				}
				else
					cout << "Создайте массив с неповторяющимися значениями" << endl;
			}
			else
				cout << "Массив пуст!" << endl;
			break;
		case 6:
			if (arr_size > 0)
			{
				Karman_Common(unsort, arr_size);
			}
			else
				cout << "Массив пуст!" << endl;
			break;
		case 7:
			if (arr_size > 0)
			{
				Copy(unsort, sort, arr_size);
				Razrad(sort, arr_size);
			}
			else
				cout << "Массив пуст!" << endl;
			break;
		case 8:
			return 0;
			break;
		default:
			cout << "Ошибка" << endl;
			break;
		}
		system("pause");
	} while (menu_point != 8);
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

int get_Arr_Size() 
{
	int arr_size = -1;
	while (arr_size < 10 || arr_size > 10000)
	{
		system("cls");
		cout << "Введите размер массива: ";
		arr_size = input();
		if (arr_size < 10 || arr_size > 10000)
		{
			cout << "Размер массива должен быть в диапазоне 10-10000 " << endl;
			system("pause");
		}
	}
	return arr_size;
}

int* Create_Unique(int arr_size)
{
	int r, temp;
	int* arr = new int[arr_size];
	for (int i = 0; i < arr_size; i++)
	{
		arr[i] = i;
	}
	for (int j = 0; j < arr_size; j++)
	{
		r = rand() % arr_size;
		temp = arr[j];
		arr[j] = arr[r];
		arr[r] = temp;
	}
	return arr; 
}

int* Create(int arr_size)
{
	int* arr = new int[arr_size];
	for (int i = 0; i < arr_size; i++)
		arr[i] = rand() % (arr_size/2);
	return arr;
}

void Copy(int* arr, int* copia, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
		copia[i] = arr[i];
}

void Karman_With_Arr(int* arr_copied, int arr_size)
{
	int swaps = 0;
	int* sort = new int[arr_size];
	for (int i = 0; i < arr_size; i++, swaps++)
		sort[arr_copied[i]] = arr_copied[i];
	Show(sort, arr_size);
	cout << "Сравнений не проводилось." << endl
		<< "Количество пересылок: " << swaps << endl;
	sort = nullptr;
	delete[] sort;
}

void Karman_Without_Arr(int* arr_copied, int arr_size)
{
	int swaps = 0, comparison = 0;
	for (int i = 0; i < arr_size; i++)
		while (comparison++ && arr_copied[i] != i )
		{
			int temp = arr_copied[i];
			arr_copied[i] = arr_copied[temp];
			arr_copied[temp] = temp;
			swaps++;
		}
	Show(arr_copied, arr_size);
	cout << "Количество сравнений: " << comparison << endl
		<< "Количество перестановок: " << swaps << endl;
}

void Karman_Common(int* arr, int arr_size)
{
	int max_value = 0;
	if (!unique)
		max_value = arr_size / 2;
	else
		max_value = arr_size;
	list* sort = new list[max_value];
	int swaps = 0;
	for (int i = 0; i < max_value; i++)
		sort[i].next = nullptr;
	for (int i = 0; i < arr_size; i++, swaps++)
		Add_Item(&sort[arr[i]], arr[i]);
	ShowKar_Com(sort, max_value);
	cout << "Количество пересылок: " << swaps << endl;
	for (int i = 0; i < max_value; i++)
		Clear(sort[i].next);
	delete[] sort;
}

void Add_Item(list* pHead, int value)
{
	while (pHead->next != nullptr)
		pHead = pHead->next;
	pHead->next = new list;
	pHead->next->value = value;
	pHead->next->next = nullptr;
}

void ShowKar_Com(list* sort, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
	{
		list* pCurrent = sort[i].next;
		while (pCurrent != NULL)
		{
			cout << pCurrent->value << " ";
			pCurrent = pCurrent->next;
		}
	}
	cout << endl;
}

void Clear(list* pHead)
{
	while (pHead != NULL)
	{
		list* temp = pHead;
		pHead = pHead->next;
		delete temp;
	}
}


void Razrad(int* copied_arr, int arr_size)
{
	int max_value = -1;
	if (unique)
		max_value = arr_size;
	else
		max_value = arr_size / 2;

	list* sort = new list[10];
	int temp = max_value - 1;
	int k = 0;
	int swaps = 0;
	while (temp >= 1)
	{
		k++;
		temp /= 10;
		for (int i = 0; i < 10; i++)
			sort[i].next = nullptr;
		for (int j = 0; j < arr_size; j++)
		{
			int current_div = 1;
			for (int m = 0; m < k; m++, current_div *= 10);
			Add_Item(&sort[((copied_arr[j] % current_div) * 10) / current_div], copied_arr[j]);
			swaps++;
		}
		for (int j = 0, n = 0; n < arr_size; j++)
		{
			list* temp = sort[j].next;
			while (temp != NULL)
			{
				copied_arr[n] = temp->value;
				temp = temp->next;
				n++;
				swaps++;
			}
		}
		for (int j = 0; j < 10; j++)
			Clear(sort[j].next);
	}
	Show(copied_arr, arr_size);
	cout << "Количество пересылок: " << swaps << endl;
	delete[] sort;
}

void Show(int* arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
		cout << arr[i] << " ";
	cout << endl;
}