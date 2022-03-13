#include <iostream>
#include <iomanip>
#include <locale.h>

using namespace std;


struct node
{
	node* left = nullptr;
	node* right = nullptr;
	int value = -1;
};


struct stackElement
{
	int level = -1;
	node* node = nullptr;
	stackElement* prev = nullptr;
};

int input();
int ask_count();
node* create(node* tree, int count);
void del(node* tree);
void forward(node* tree, int level = 0);
void symmetric(node* tree, int level = 0);
void back_symmetric(node* tree, int level = 0);
void symmetric_non_recursive(node* tree);
void push(stackElement** sp, stackElement* elem);
stackElement* pop(stackElement** sp);


int main()
{
	setlocale(LC_ALL, "Rus");
	node* np = nullptr;

	int menu_point;

	do {
		system("cls");

		cout <<
			"1. Создать дерево" << endl <<
			"2. Обход в прямом направлении" << endl <<
			"3. Обход в симметричном направлении" << endl <<
			"4. Обход в обратно-симметричном направлении" << endl <<
			"5. Обход в симметричном направлении нерекурсивно" << endl <<
			"0. Выход" << endl;
		menu_point = input();

		system("cls");

		switch (menu_point)
		{
		case 0:
			return 0;
		case 1:
			if (np != nullptr)
				del(np);
			np = create(np, ask_count());
			break;
		case 2:
			if (np != nullptr)
				forward(np);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 3:
			if (np != nullptr)
				symmetric(np);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 4:
			if (np != nullptr)
				back_symmetric(np);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 5:
			if (np != nullptr)
				symmetric_non_recursive(np);
			else
				cout << "Дерево не создано!" << endl;
			break;
		default:
			cout << "Ошибка ввода!" << endl;
		}

		system("pause");
	} while (menu_point != 0);

	return 0;
}

int input()
{
	int result;
	cin >> result;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Ошибка!" << endl;
		system("pause");
		cout << "Попробуйте заново: ";
		cin >> result;
	}
	return result;
}

int ask_count()
{
	cout << "Введите количество вершин: ";
	int count = input();

	while (count <= 0)
	{
		cout << "Ошибка! Попробуйте заново: ";
		count = input();
	}
	return count;
}

node* create(node* tree, int count)
{
	int Number_of_left, Number_of_right;
	if (count != 0)
	{
		Number_of_left = count / 2;
		Number_of_right = count - Number_of_left - 1;
		tree = new node;
		tree->value = 1 + rand() % 100;
		tree->left = create(tree->left, Number_of_left);
		tree->right = create(tree->right, Number_of_right);
		return tree;
	}
	else
		return nullptr;
}

void show(node* tree, int level)
{
	for (int i = 0; i < level; i++) { cout << "    "; }
	cout << tree->value << endl;
}

void forward(node* tree, int level)
{
	if (tree != nullptr)
	{
		show(tree, level);
		forward(tree->left, level + 1);
		forward(tree->right, level + 1);
	}
}

void symmetric(node* tree, int level)
{
	if (tree != nullptr)
	{
		symmetric(tree->left, level + 1);
		show(tree, level);
		symmetric(tree->right, level + 1);
	}
}

void back_symmetric(node* tree, int level)
{
	if (tree != nullptr)
	{
		back_symmetric(tree->right, level + 1);
		show(tree, level);
		back_symmetric(tree->left, level + 1);
	}
}

void del(node* tree)
{
	if (tree != nullptr)
	{
		del(tree->left);
		del(tree->right);
	}
	delete tree;
}

void symmetric_non_recursive(node* np)
{
	stackElement* sp = nullptr;
	stackElement* stak_element;

	int level = 0;

	while (true) {
		while (np != nullptr)
		{
			stak_element = new stackElement;
			stak_element->level = level++;
			stak_element->node = np;
			push(&sp, stak_element);
			np = np->left;
		}

		stak_element = pop(&sp);

		if (stak_element == nullptr)
			break;
		else {
			level = stak_element->level+1;
			np = stak_element->node;
			
			show(np, level-1);

			np = np->right;
		}
	}
}

void push(stackElement** sp, stackElement* elem)
{
	if (*sp == nullptr)
		*sp = elem;
	else
	{
		elem->prev = *sp;
		*sp = elem;
	}
}

stackElement* pop(stackElement** sp)
{
	if (*sp != nullptr)
	{
		stackElement* to_delete = *sp;
		*sp = (*sp)->prev;
		to_delete->prev = nullptr;
		return to_delete;
	}
	return nullptr;
}