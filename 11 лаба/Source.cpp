/*поиск вершины с заданным значением информационной части
добавление левого или правого потомка для заданной вершины
построчный вывод дерева с помощью основных правил обхода
уничтожение всего дерева*/
#include <iostream>
#include <locale.h>
using namespace std;


struct node
{
	node* left = nullptr;
	node* right = nullptr;
	int value = -1;
};

int input();
int ask_count();
void show(node* tree, int level);
node* create(node* tree, int count); 
node* search(node* tree, int to_search);
void del(node* tree);
void add_node(node** tree);
int check();
void search_node(node* tree);
void forward(node* tree, int level = 0);
void symmetric(node* tree, int level = 0);
void back_symmetric(node* tree, int level = 0);

int main()
{
	setlocale(LC_ALL, "Rus");
	node* tree = nullptr;

	int menu_point;

	do {
		system("cls");

		cout <<
			"1. Создать дерево" << endl <<
			"2. Добавить вершину" << endl <<
			"3. Поиск" << endl <<
			"4. Обход в прямом направлении" << endl <<
			"5. Обход в симметричном направлении" << endl <<
			"6. Обход в обратно-симметричном направлении" << endl <<
			"7. Удалить дерево" << endl <<
			"0. Выход" << endl;
		menu_point = input();

		system("cls");

		switch (menu_point)
		{
		case 0:
			return 0;
		case 1:
			if (tree != nullptr)
				del(tree);
			tree = create(tree, ask_count());
			break;
		case 2:
			add_node(&tree);
			break;
		case 3:
			if (tree != nullptr)
				search_node(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 4:
			if (tree != nullptr)
				forward(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 5:
			if (tree != nullptr)
				symmetric(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 6:
			if (tree != nullptr)
				back_symmetric(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 7:
			if (tree != nullptr) {
				del(tree);
				tree = nullptr;
			}
			else
				cout << "Дерево не создано!" << endl;
			break;
		default:
			cout << "Ошибка" << endl;
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
		cout << "Попробуйте снова: ";
		cin >> result;
	}
	return result;
}

int check()
{
	int result;
	do {
		result = input();
		if (result != 1 && result != 2)
			cout << "Ошибка! Попробуйте снова: ";
	} while (result != 1 && result != 2);
	return result;
}

int ask_count()
{
	cout << "Введите количество вершин: ";
	int count = input();

	while (count <= 0)
	{
		cout << "Ошибка! Попробуйте снова: ";
		count = input();
	}
	return count;
}

node* create(node* pCurrent, int count)
{
	int Number_of_left, Number_of_right;
	if (count != 0)
	{
		Number_of_left = count / 2;
		Number_of_right = count - Number_of_left - 1;
		pCurrent = new node;
		pCurrent->value = 1 + rand() % 100;
		pCurrent->left = create(pCurrent->left, Number_of_left);
		pCurrent->right = create(pCurrent->right, Number_of_right);
		return pCurrent;
	}
	else
		return nullptr;
}

void add_node(node** tree)
{
	node* new_node;
	if (*tree == nullptr)
	{
		*tree = new node;
		new_node = *tree;
	}
	else
	{
		cout << "Введите вершину после которой необхоимо добавить новую вершину: ";
		int to_search = input();

		node* old_node = search(*tree, to_search);
		if (old_node == nullptr)
		{
			cout << to_search << " не найдено!" << endl;
			return;
		}
		else
		{
			if (old_node->left == nullptr && old_node->right == nullptr)
			{
				cout << "Добавить:" << endl <<
					"1. влево" << endl <<
					"2. вправо" << endl;
				int type = check();

				if (type == 1)
				{
					old_node->right = new node;
					new_node = old_node->right;
				}
				else
				{
					old_node->left = new node;
					new_node = old_node->left;
				}
			}
			else if (old_node->left != nullptr && old_node->right == nullptr)
			{
				old_node->right = new node;
				new_node = old_node->right;
			}
			else if (old_node->right != nullptr && old_node->left == nullptr)
			{
				old_node->left = new node;
				new_node = old_node->left;
			}
			else
			{
				cout << "Добавление невозможно!" << endl;
				return;
			}
		}
	}

	cout << "Введите число, которое нужно добавить: ";
	new_node->value = input();
	cout << new_node->value << " добавлено!" << endl;
}

void search_node(node* tree)
{
	cout << "Введите вершину для поиска: ";
	int to_search = input();

	node* result = search(tree, to_search);
	if (result == nullptr)
		cout << to_search << " не найдено!" << endl;
	else
		cout << to_search << " найдено!" << endl;
}

node* search(node* pCurrent, int to_search)
{
	if (pCurrent->value == to_search)
		return pCurrent;

	if (pCurrent->left != nullptr) {
		node* result = search(pCurrent->left, to_search);
		if (result != nullptr)
			return result;
	}

	if (pCurrent->right != nullptr) {
		node* result = search(pCurrent->right, to_search);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

void show(node* pCurrent, int level)
{
	for (int i = 0; i < level; i++) { cout << "    "; }
	cout << pCurrent->value << endl;
}

void forward(node* pCurrent, int level)
{
	if (pCurrent != nullptr)
	{
		show(pCurrent, level);
		forward(pCurrent->left, level + 1);
		forward(pCurrent->right, level + 1);
	}
}

void symmetric(node* pCurrent, int level)
{
	if (pCurrent != nullptr)
	{
		symmetric(pCurrent->left, level + 1);
		show(pCurrent, level);
		symmetric(pCurrent->right, level + 1);
	}
}

void back_symmetric(node* pCurrent, int level)
{
	if (pCurrent != nullptr)
	{
		back_symmetric(pCurrent->right, level + 1);
		show(pCurrent, level);
		back_symmetric(pCurrent->left, level + 1);
	}
}

void del(node* pCurrent)
{
	if (pCurrent != nullptr)
	{
		del(pCurrent->left);
		del(pCurrent->right);
	}
	delete pCurrent;
}