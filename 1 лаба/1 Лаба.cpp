#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct stackElement
{
	int data;
	stackElement* prevElement = nullptr;
};

int checkUserInput();
void add_element(stackElement** sp, stackElement** additional);
void addto(stackElement** sp, stackElement* new_element);
stackElement* delete_it(stackElement** sp);
void add_many_elements(stackElement** sp);
void delete_element(stackElement** sp, stackElement** additional);
void show(stackElement** sp);

bool empty(stackElement** sp)
{
	return *sp == nullptr;
}

int main()
{
	stackElement* sp = nullptr;
	stackElement* additional = nullptr;
	int menu = -1;
	while (menu != 0)
	{
		system("cls");
		
		cout <<
			"1. Add" << endl <<
			"2. Add many elements" << endl <<
			"3. Delete" << endl <<
			"4. Show" << endl <<
			"5. Show additional" << endl <<
			"0. Exit" << endl;	

		menu = checkUserInput();

		system("cls");

		switch (menu) 
		{
		case 0:
			return 0;
		case 1:
			add_element(&sp, &additional);
			break;
		case 2:
			add_many_elements(&sp);
			break;
		case 3:
			delete_element(&sp, &additional);
			break;
		case 4:
			show(&sp);
			break;
		case 5:
			show(&additional);
			break;
		default:
			cout << "Wrong input!" << endl;
		}
		system("pause");
	}
}

int checkUserInput()
{
	int result;
	cin >> result;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Input error" << endl;
		system("pause");
		cout << "Try again: ";
		cin >> result;
	}
	return result;
}

void add_element(stackElement** sp, stackElement** additional)
{
	cout <<
		"Do you want to create new element?" << endl <<
		"1. Yes" << endl <<
		"0. No" << endl;
	
	while (true) 
	{
		int choice = checkUserInput();

		if (choice == 1)
		{
			stackElement* pTemp = new stackElement;
			cout << "Enter data: ";
			pTemp->data = checkUserInput();
			addto(sp, pTemp);
			return;
		}
		if (choice == 0)
		{
			if (empty(additional))
				cout << "Additional stack is empty!" << endl;
			else
			{
				stackElement* deleted = delete_it(additional);
				addto(sp, deleted);
			}
			return;
		}

		cout << "Wrong input" << endl;
	}
}

void addto(stackElement** sp, stackElement* new_element) 
{
	if (empty(sp)) 
	{
		*sp = new_element;
	}
	else 
	{
		new_element->prevElement = *sp;
		*sp = new_element;
	}
}

stackElement* delete_it(stackElement** sp)
{
	if (!empty(sp)) 
	{
		stackElement* pTemp = *sp;
		*sp = (*sp)->prevElement;
		pTemp->prevElement = nullptr;
		return pTemp;
	}
	return nullptr;
}

void add_many_elements(stackElement** sp) 
{
	srand(time(0));
	cout << "Enter count: ";
	int count = checkUserInput();

	while (count > 0)
	{
		stackElement* new_element = new stackElement;
		new_element->data = rand();
		addto(sp, new_element);
		count--;
	}
}

void delete_element(stackElement** sp, stackElement** additional) 
{
	cout <<
		"Move to additional stack?" << endl <<
		"1. Yes" << endl <<
		"0. No" << endl;
	while (true) 
	{
		int choice = checkUserInput();

		if (choice == 1)
		{
			stackElement* pTemp = delete_it(sp);
			addto(additional, pTemp);
			return;
		}

		if (choice == 0) 
		{
			delete delete_it(sp);
			return;
		}

		cout << "Wrong input!" << endl;
	}
}

void show(stackElement** sp)
{
	if (empty(sp))
	{
		cout << "Stack is empty!" << endl;
		return;
	}

	stackElement* pCur = *sp;
	while (pCur != nullptr) 
	{
		cout << pCur->data << ' ';
		pCur = pCur->prevElement;
	}
	cout << endl;
}