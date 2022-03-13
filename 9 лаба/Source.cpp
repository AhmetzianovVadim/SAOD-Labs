//ИСД
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
node* create(node* pCurrent, int count);
int ask_count();
void del(node* pCurrent);
void forward(node* pCurrent, int level = 0);
void symmetric(node* pCurrent, int level = 0);
void back_symmetric(node* pCurrent, int level = 0);
void show(node *pCurrent, int level);

int main()
{
	setlocale(LC_ALL, "Rus");
	node* tree = nullptr;

	int menu_point;

	do {
		system("cls");

		cout <<
			"1. Создать дерево" << endl <<
			"2. Обход в прямом направлении" << endl <<
			"3. Обход в симметричном направлении" << endl <<
			"4. Обход в обратно-симметричном направлении" << endl <<
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
			if (tree != nullptr)
				forward(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 3:
			if (tree != nullptr)
				symmetric(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 4:
			if (tree != nullptr)
				back_symmetric(tree);
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
	node* temp_node;
	int Number_of_left, Number_of_right;
	if (count != 0)
	{
		Number_of_left = count / 2;
		Number_of_right = count - Number_of_left - 1;
		temp_node = new node;
		temp_node->value = 1 + rand() % 100;
		temp_node->left = create(temp_node->left, Number_of_left);
		temp_node->right = create(temp_node->right, Number_of_right);
		tree = temp_node;
		return temp_node;
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


