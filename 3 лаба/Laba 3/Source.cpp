#include <iostream>
#include <ctime>
#include <locale.h>

using namespace std;

struct queue_element
{
	char value;
	queue_element* next = nullptr;
	queue_element* prev = nullptr;
};
struct queue 
{
	queue_element* first = nullptr;
	queue_element* last = nullptr;
};

void addition(queue* q, char value);
void deletion(queue* q);
void show(queue* q);

char get_random_char() 
{
	return rand() % 26 + 65;
}

bool queue_is_empty(queue* q) 
{
	return q->first == nullptr || q->last == nullptr;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	queue q;

	srand(time(nullptr));
	cout << "Генератор случайных чисел обновлен!" << endl;

	char p = 'a';

	while (p != 'q') 
	{
		int r = rand() % 101;
		
		if (r % 2 == 0)
		{
			const int count = rand() % 3 + 1;
			cout << "Добавлено " << count << endl;
			for (int i = 0; i < count; i++)
				addition(&q, get_random_char());
		}
		else  if (!queue_is_empty(&q))
		{
			const int count = rand() % 3 + 1;
			cout << "Удалено " << count << endl;
			for (int i = 0; i < count; i++)
				deletion(&q);
		}
		else
			cout << "Ничего не удалено, ничего не добавлено" << endl;
		show(&q);
		p = getchar();
	}
	return 0;
}

void addition(queue* q, char randomChar) 
{
	queue_element* temp = new queue_element;
	temp->value = randomChar;

	if (queue_is_empty(q))
	{
		q->first = temp;
		q->last = temp;
	}
	else 
	{
		temp->prev = q->last;
		q->last->next = temp;
		q->last = temp;
	}
	
}

void deletion(queue* q)
{
	queue_element* to_delete = q->first;
	if (q->first == q->last)
	{
		q->first = nullptr;
		q->last = nullptr;
	}
	else
	{
		q->first = q->first->next;
		q->first->prev = nullptr;
	}

	delete to_delete;

}

void show(queue* q)
{
	cout << "Статус: ";
	if (queue_is_empty(q)) 
	{
		cout << "Очередь пуста!" << endl;
		return;
	}
	queue_element* temp = q->first;

	while (temp)
	{
		cout << temp->value << " ";
		temp = temp->next;
	}
	cout << endl;
}