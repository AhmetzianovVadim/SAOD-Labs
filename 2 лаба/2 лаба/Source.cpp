#include <iostream>

#define QUEUE_SIZE 5

using namespace std;

struct queue
{
	int arr[QUEUE_SIZE];
	int add_count = 0;
	int delete_count = 0;
};

int input();
void add_element(queue* q);
void addition(queue*q, const int value);
void delete_element(queue* q);
void show(queue *q);

bool is_full(queue *q) 
{
	return q->add_count - q->delete_count >= QUEUE_SIZE;
}

bool queue_is_empty(queue* q)
{
	return q->add_count - q->delete_count == 0;
}

int main() 
{
	queue q;

	int choice = -1;

	while (choice != 0)
	{ 
		system("cls");

		cout <<
			"1. Add" << endl <<
			"2. Delete" << endl <<
			"3. Show" << endl <<
			"0. Exit" << endl;

		choice = input();

		system("cls");

		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			add_element(&q);
			break;
		case 2:
			delete_element(&q);
			break;
		case 3:
			show(&q);
			break;
		default:
			cout << "Wrong input" << endl;
		}
		system("pause");
	}
	return 0;
}

int input()
{
	int result;
	cin >> result;
	while (cin.fail()) 
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Input error!" << endl;
		system("pause");
		cout << "Try again: ";
		cin >> result;
	}
	return result;
}

void add_element(queue* q) 
{
	if (is_full(q))
	{
		cout << "Queue is full!" << endl;
	}
	else
	{
		cout << "Enter data: ";
		addition(q, input());
	}
}

void addition(queue* q, const int value) 
{
	if (!is_full(q))
	{
		q->arr[q->add_count % QUEUE_SIZE] = value;
		q->add_count++;
	}
}

void delete_element(queue* q) 
{
	if (!queue_is_empty(q))
	{
		q->delete_count++;
	}
	else
		cout << "Queue is empty!" << endl;
}

void show(queue* q)
{
	if (queue_is_empty(q))
	{
		cout << "Queeue is empty" << endl;
	}
	else 
	{
		for (int i = q-> delete_count; i < q-> add_count; i++)
		{
			cout << q->arr[i % QUEUE_SIZE] << ' ';
		}
		cout << endl;
	}
}