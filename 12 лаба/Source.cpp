/*поиск вершины с заданным значением ключа с выводом счетчика числа появлений данного ключа
добавление новой вершины в соответствии со значением ее ключа или увеличение счетчика числа появлений
построчный вывод дерева в наглядном виде с помощью обратно симметричного обхода
вывод всех вершин в одну строку по порядку следования ключей с указанием для каждой вершины значения ее счетчика появлений
удаление вершины с заданным значением ключа*/
#include <iostream>
#include <string>

using namespace std;

struct node
{
	node* left = nullptr;
	node* right = nullptr;
	int value = -1;
	int key_count = 1;
};

int input();
int ask_count();
int choice();
void del(node* np);
node* create(node* np, int node_count);
node* search(node* np, int to_search);
void add_recursive(node* np, int new_node);
void back_symmetric(node* np, string side, int level = 0);
void show(node* np, string side, int level);
void add_node_menu(node** np);
void add_non_recursive(node* np, int new_value);
void search_menu(node* tree);
void show_in_line(node* tree);
void delete_menu(node** pRoot);
void delete_node(node** pRoot, node** parent);

int main() 
{
	setlocale(LC_ALL, "Rus");
	node* tree = nullptr;

	int menu_point = -1;

	do
	{
		system("cls");

		cout <<
			"1. Создать дерево" << endl <<
			"2. Добавить вершину" << endl <<
			"3. Поиск" << endl <<
			"4. Показать" << endl <<
			"5. Вывод всех вершин в одну строку по порядку" << endl <<
			"6. Удалить вершину" << endl <<
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
			add_node_menu(&tree);
			break;
		case 3:
			if (tree != nullptr)
				search_menu(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 4:
			if(tree != nullptr)
				back_symmetric(tree, "-RN");
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 5:
			if (tree != nullptr) {
				show_in_line(tree);
				cout << endl;
			}
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 6:
			if (tree != nullptr)
			{
				delete_menu(&tree);
			}
			else
				cout << "Дерево не создано!" << endl;
			break;
		default:
			cout << "Ошибка" << endl;
		}
		system("pause");
	} while (menu_point != 0);
}

void del(node* pCurrent)
{
	if (pCurrent != nullptr)
	{
		del(pCurrent->left);
		del(pCurrent->right);
		pCurrent = nullptr;
	}
	delete pCurrent;
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

int choice()
{
	int result;
	do {
		result = input();
		if (result != 1 && result != 2)
			cout << "Ошибка ввода! Попробуйте еще раз: ";
	} while (result != 1 && result != 2);
	return result;
}

int ask_count()
{
	cout << "Введите количество вершин: ";
	int node_count = input();

	while (node_count <= 0)
	{
		cout << "Ошибка! Попробуйте снова: ";
		node_count = input();
	}
	return node_count;
}

node* create(node* pCurrent, int node_count)
{
	srand(time(0));
	pCurrent = new node;
	pCurrent->value = 1 + rand() % 100;
	for (node_count--; node_count > 0; node_count--)
	{
		int new_node_value = 1 + rand() % 100;
		add_recursive(pCurrent, new_node_value);
	}
	return pCurrent;
}

void add_recursive(node* pCurrent, int new_node_value)
{
	if (pCurrent->value == new_node_value)
		pCurrent->key_count++;
	else if (pCurrent->value > new_node_value)
	{
		if (pCurrent->left == nullptr)
		{
			pCurrent->left = new node;
			pCurrent->left->value = new_node_value;
		}
		else
			add_recursive(pCurrent->left, new_node_value);
	}
	else
	{
		if (pCurrent->right == nullptr)
		{
			pCurrent->right = new node;
			pCurrent->right->value = new_node_value;
		}
		else
			add_recursive(pCurrent->right, new_node_value);
	}
}

void add_node_menu(node** tree)
{
	cout << "Введите значение вершины: ";
	int new_value = input();

	if (*tree == nullptr)
	{
		*tree = new node;
		(*tree)->value = new_value;
	}
	else {
		cout << "Добавить " << endl <<
			"1. рекурсивный метод" << endl <<
			"2. нерекурсивный метод" << endl;
		int add_type = choice();

		if (add_type == 1)
			add_recursive(*tree, new_value);
		else
			add_non_recursive(*tree, new_value);
	}
}

void add_non_recursive(node* np, int new_value)
{
	while (true)
	{
		if (np->value == new_value)
		{
			np->key_count++;
			break;
		}
		else if (np->value > new_value)
		{
			if (np->left == nullptr)
			{
				np->left = new node;
				np->left->value = new_value;
				break;
			}
			else
				np = np->left;
		}
		else
		{
			if (np->right == nullptr)
			{
				np->right = new node;
				np->right->value = new_value;
				break;
			}
			else
				np = np->right;
		}
	}
}

node* search(node* pCurrent, int to_search) 
{
	if (pCurrent != nullptr)
	{
		if (pCurrent->value == to_search)
			return pCurrent;
		else if (to_search < pCurrent->value)
			search(pCurrent->left, to_search);
		else if (to_search > pCurrent->value)
			search(pCurrent->right, to_search);
	}
	else return nullptr;
}

void back_symmetric(node* pCurrent, string side, int level)
{
	if (pCurrent != nullptr)
	{
		back_symmetric(pCurrent->right, "-R", level + 1);
		show(pCurrent, side, level);
		back_symmetric(pCurrent->left, "-L", level + 1);
	}
}

void show(node* pCurrent, string side, int level)
{
	for (int i = 0; i < level; i++) { cout << "    "; }
	cout << pCurrent->value << side <<"(" << pCurrent->key_count << ")" << endl;
}

void search_menu(node* np) 
{
	cout << "Введите ключ вершины для поиска: ";
	int to_search = input();

	node* result = search(np, to_search);
	if (result == nullptr)
		cout << to_search << " не найдено!" << endl;
	else
		cout << to_search << " найдено! Количество: " << result->key_count << "!" << endl;
}

void show_in_line(node* np)
{
	if (np != nullptr)
	{
		show_in_line(np->right);
		cout << np->value << "(" << np->key_count << ") ";
		show_in_line(np->left);
	}
}

void delete_menu(node** pRoot)
{
	cout << "Введите ключ вершины: ";
	node* pCurrent = *pRoot;
	int to_delete = input();
	node* parent = nullptr;
	node* result = search(pCurrent, to_delete);
	if (result == nullptr)
	{
		cout << "Вершина " << to_delete << " не найдена" << endl;
	}
	else
	{
		while (pCurrent->value != to_delete)
		{
			parent = pCurrent;
			if (to_delete < pCurrent->value)
				pCurrent = pCurrent->left;
			else
				pCurrent = pCurrent->right;
		}

		/*if (pCurrent->key_count > 1)
			pCurrent->key_count--;*/

		if (parent == nullptr && (*pRoot)->left == nullptr && (*pRoot)->right == nullptr)
		{
			*pRoot = nullptr;
			delete* pRoot;
		}
		else if (parent == nullptr && ((*pRoot)->left == nullptr || (*pRoot)->right == nullptr)) 
		{
			if ((*pRoot)->left != nullptr)
				*pRoot = (*pRoot)->left;
			else
				*pRoot = (*pRoot)->right;
		}
		else
		{
			delete_node(&pCurrent, &parent);
		}
	}
}

void delete_node(node** pCurrent, node** parent)
{
	if ((*pCurrent)->right == nullptr && (*pCurrent)->left == nullptr)
	{
		if ((*parent)->left == *pCurrent)
			(*parent)->left = nullptr;
		else
			(*parent)->right = nullptr;
		*pCurrent = nullptr;
		delete* pCurrent;
	}
	else if ((*pCurrent)->left != nullptr && (*pCurrent)->right == nullptr)
	{
		if ((*parent)->left == *pCurrent)
			(*parent)->left = (*pCurrent)->left;
		else
			(*parent)->right = (*pCurrent)->left;
		*pCurrent = nullptr;
		delete* pCurrent;
	}
	else if ((*pCurrent)->left == nullptr && (*pCurrent)->right != nullptr)
	{
		if ((*parent)->left == *pCurrent)
			(*parent)->left = (*pCurrent)->right;
		else
			(*parent)->right = (*pCurrent)->right;
		*pCurrent = nullptr;
		delete* pCurrent;
	}
	else
	{
		node* pTemp = (*pCurrent)->right;
		node* pTemp_from = nullptr;
		while (pTemp->left != nullptr)
		{
			pTemp_from = pTemp;
			pTemp = pTemp->left;
		}

		(*pCurrent)->value = pTemp->value;
		(*pCurrent)->key_count = pTemp->key_count;
		if (pTemp == (*pCurrent)->right)
			(*pCurrent)->right = pTemp->right;
		else
			pTemp_from->left = pTemp->right;
		delete pTemp;
	}
}
		
		

