#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

struct Node
{
	Node* left = NULL;
	Node* right = NULL;
	string info;
	int key;
};

void Task(Node*, vector<int>&, int = 0);
void Add(Node*&, int, string);
void DeleteNode(Node*&);
void DeleteTree(Node*&);
void ShowTree(Node*, int = 0);
void Traversal_1(Node*);
void Traversal_2(Node*);
void GetNodes(Node*, vector<Node*>&);
void BubbleSort(vector<Node*>&);
Node* Balance(Node*&, vector<Node*>&, int = -1, int = 0);
Node*& GetNodeByKey(Node*&, int);
Node*& GetMaxNode(Node*&, Node*** = NULL);
int main()
{
	system("chcp 1251>nul");
	Node* root = NULL;
	bool fact = true;
	while (fact == true)
	{
		int key;
		string name;
		Node* keyNode;
		vector<Node*> nodes;
		cout << "Если хотите создать дерево, то нажмите 1" << endl;
		cout << "Если хотите выполнить задание, то нажмите 2" << endl;
		cout << "Если хотите добавить значение в дерево, то нажмите 3" << endl;
		cout << "Если хотите удалить информацию из дерева, то нажмите 4" << endl;
		cout << "Если хотите просмотреть информацию из дерева, то нажмите 5" << endl;
		cout << "Если хотите осуществить поиск в дереве по заданному ключу, то нажмите 6" << endl;
		cout << "Если хотите сбалансировать дерево, то нажмите 7" << endl;
		cout << "Если хотите распечатать, то нажмите 8" << endl;
		cout << "Если хотите завершить программу, то нажмите 9" << endl;
		int n;
		cin >> n;
		switch (n)
		{
		case 1:
		{
			DeleteTree(root);
			int size, key = -1, nameRange = 8, keyRange;
			cout << "Введите размер: " << endl;
			cin >> size;
			keyRange = size;
			cout << "\n";
			for (int i = 0; i < size; i++)
			{
				cout << "Введите ключ " << i + 1 << " добавляемого элемента: " << endl;
				cin >> key;
				cout << "Введите информацию "<< i + 1 <<" добавляемого элемента: " << endl;
				string name = "";
				cin >> name;
				cout << name << ": " << key << "\n";
				Add(root, key, name);
			}
			break;
		}
		case 2:
		{
			vector<int> nodeCount;
			Task(root, nodeCount);
			for (int i = 0; i < (int)nodeCount.size(); i++)
			{
				cout << "Уровень " << i + 1 << ": " << nodeCount[i] << "\n";
			}
			break;
		}
		case 3:
			cout << "Введите ключ: " << endl;
			cin >> key;
			while (GetNodeByKey(root, key)) 
			{
				cout << "Введите другой ключ: " << endl;
				cin >> key;
			}
			cout << "Введите имя: ";
			cin>>name;
			Add(root, key, name);
			break;
		case 4:
			cout << "Введите ключ: " << endl;
			cin >> key;
			DeleteNode(GetNodeByKey(root, key));
			break;
		case 5:
			ShowTree(root);
			break;
		case 6:
			cout << "Введите ключ: " << endl;
			cin >> key;
			keyNode = GetNodeByKey(root, key);
			if (keyNode)
			{
				cout << "Имя: " << keyNode->info << "\n";
			}
			else
			{
				cout << "Элемент не найден\n";
			}
			break;
		case 7:
			GetNodes(root, nodes);
			BubbleSort(nodes);
			Balance(root, nodes);
			break;
		case 8:
			cout << "Если хотите распечатать прямым обходом, то нажмите 1" << endl;
			cout << "Если хотите распечатать обратным обходом, то нажмите 2" << endl;
			cout << "Если хотите распечатать в порядке возрастания ключа, то нажмите 3" << endl;
			int choise;
			cin >> choise;
			switch (choise)
			{
			case 1:
				Traversal_1(root);
				break;
			case 2:
				Traversal_2(root);
				break;
			case 3:
				GetNodes(root, nodes);
				BubbleSort(nodes);
				for (int i =0;i< nodes.size();++i)
				{
					cout << nodes[i]->info << " ";
				}
				break;
			}
			cout << "\n";
			break;
		case 9:
			fact = false;
		}
		cout << "\n";
	}
}

void Task(Node* p, vector<int>& nodeCount, int level)
{
	if (!p)
	{
		return;
	}
	if (nodeCount.size() <= level)
	{
		nodeCount.push_back(1);
	}
	else
	{
		nodeCount[level]++;
	}
	Task(p->left, nodeCount, level + 1);
	Task(p->right, nodeCount, level + 1);
}

void Add(Node*& root, int key, string info)
{
	Node** p = &root;
	while (*p)
	{
		if (key < (*p)->key)
		{
			p = &(*p)->left;
		}
		else if (key > (*p)->key)
		{
			p = &(*p)->right;
		}
	}
	Node* newNode = new Node;
	newNode->key = key;
	newNode->info = info;
	*p = newNode;
}


void DeleteNode(Node*& target)
{
	if (!target) return;
	Node* tempPtr = NULL;
	if ((target->left && !target->right) || (!target->left && target->right))
	{
		if (target->left)
		{
			tempPtr = target->left;
		}
		else
		{
			tempPtr = target->right;
		}
		
	}
	else if (target->left && target->right)
	{
		Node** prevPtr = NULL;
		tempPtr = GetMaxNode(target->left, &prevPtr);
		if (!prevPtr)
		{
			tempPtr->right = target->right;
		}
		else
		{
			if (tempPtr->left)
			{
				(*prevPtr)->right = tempPtr->left;
			}
			else (*prevPtr)->right = NULL;
			tempPtr->right = target->right;
			tempPtr->left = target->left;
		}
	}
	else
	{
		target = NULL;
	}
	delete target;
	target = tempPtr;
}

void DeleteTree(Node*& root)
{
	while (root) DeleteNode(root);
}

void ShowTree(Node* p, int level)
{
	string str;
	if (!p)
	{
		return;
	}
	ShowTree(p->right, level + 1);
	for (int i = 0; i < level; i++) str = str + "   ";
	cout << str <<p->info << "\n";
	ShowTree(p->left, level + 1);
}

void Traversal_1(Node* p)
{
	if (!p) return;
	cout << p->info << " ";
	Traversal_1(p->left);
	Traversal_1(p->right);
}

void Traversal_2(Node* p)
{
	if (!p) return;
	Traversal_2(p->left);
	Traversal_2(p->right);
	cout << p->info << " ";
}

void GetNodes(Node* p, vector<Node*>& nodes)
{
	if (!p)
	{
		return;
	}
	nodes.push_back(p);
	GetNodes(p->left, nodes);
	GetNodes(p->right, nodes);
}

void BubbleSort(vector<Node*>& nodes)
{
	int n = nodes.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (nodes[i]->key > nodes[j]->key)
			{
				Node* temp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = temp;
			}
		}
	}
}

Node* Balance(Node*& root, vector<Node*>& nodes, int k, int n)
{
	if (k == -1)
	{
		k = nodes.size();
		root = nodes[k / 2];
	}
	if (n == k)
	{
		return NULL;
	}
	int m = (n + k) / 2;
	nodes[m]->left = Balance(root, nodes, m, n);
	nodes[m]->right = Balance(root, nodes, k, m + 1);
	return nodes[m];
}

Node*& GetNodeByKey(Node*& root, int key)
{
	Node** p = &root;
	while (*p)
	{
		if ((*p)->key > key) p = &(*p)->left;
		else if ((*p)->key < key) p = &(*p)->right;
		else return *p;
	}
	return *p;
}

Node*& GetMaxNode(Node*& root, Node*** prev)
{
	Node** p = &root;
	while ((*p)->right)
	{
		if (prev) *prev = p;
		p = &(*p)->right;
	}
	return *p;
}