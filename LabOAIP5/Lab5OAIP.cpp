#include <iostream>
#include <string>
#include <ctime>
#include<stack>;
using namespace std;
struct Stack
{
	Stack* next;
	int value;
};

void Add(Stack*&, int);
void Delete(Stack*&);
void DeleteStack(Stack*&);
void Show(Stack*);
void SortValue(Stack*);
void SortAddress(Stack*&);

int main()
{
	system("chcp 1251>nul");
	srand(time(NULL));
	Stack* stack = NULL;
	Stack* stack1 = NULL;
	Stack* stack2 = NULL;
	int size, value = 5;
	bool fact = true;
	while (fact == true)
	{
		cout << "Если хотите создать стек, то нажмите 1" << endl;
		cout << "Если хотите выполнить задание, то нажмите 2" << endl;
		cout << "Если хотите добавить элемент, то нажмите 3" << endl;
		cout << "Если хотите удалить все элементы стека, то нажмите 4" << endl;
		cout << "Если хотите отсортировать стек, то нажмите 5" << endl;
		cout << "Если хотите завершить программу, то нажмите 6" << endl;
		int n;
		cin >> n;
		switch (n)
		{
		case 1:
			DeleteStack(stack);
			cout << "Создать стек cо cлучайными числами(до 20) - 0" << "\n";
			cout << "Создать стек c определенными значениями - 1" << "\n";
			int choise;
			cin >> choise;
			if (choise == 0)
			{
				size = rand() % 11;
				cout << "Размер стека: " << size << "\n\n";
				for (int i = 0; i < size; i++)
				{
					value = rand() % 21;
					cout << value << " ";
					Add(stack, value);
				}
			}
			else if (choise == 1)
			{
				cout << "Введите размер стека: " << endl;
				int size;
				cin >> size;
				cout << "\n";
				for (int i = 0; i < size; i++)
				{
					cout << "Введите " << i + 1 << " элемент стека: " << endl;
					cin >> value;
					Add(stack, value);
				}
			}
			//cout << "\nИтоговый вид:\n\n";
			break;
		case 2:
		{
			Stack* stack1 = NULL;
			Stack* stack2 = NULL;
			for (Stack* tempPointer = stack; tempPointer; tempPointer = tempPointer->next)
			{
				if (tempPointer->value > 0)
				{
					Add(stack1, tempPointer->value);
				}
				if (tempPointer->value < 0)
				{
					Add(stack2, tempPointer->value);
				}
				else
				{
					continue;
				}
			}
			/*for (Stack** tempPointer = &stack; *tempPointer; tempPointer = &(*tempPointer)->next)
			{
				if ((*tempPointer)->value > 0 || (*tempPointer)->value < 0)
				{
					Delete(*tempPointer);
				}
			}*/
			Stack** tempPointer = &stack;
			while (*tempPointer)
			{
				if ((*tempPointer)->value > 0 || (*tempPointer)->value < 0)
				{
					Delete(*tempPointer);
				}
				else
				{
					tempPointer = &(*tempPointer)->next;
				}
			}
			Show(stack);
			Show(stack1);
			Show(stack2);

			//Stack** tempPointer = &stack;
			//while (*tempPointer)
			//{
			//	if ((*tempPointer)->value > 0)
			//	{
			//		//int temp1 = (*tempPointer)->value;
			//		Add(stack1, (*tempPointer)->value);
			//		Delete(*tempPointer);
			//	}
			//	else if ((*tempPointer)->value  < 0)
			//	{
			//		Add(stack2, (*tempPointer)->value);
			//		Delete(*tempPointer);
			//	
			//	}
			//	else if ((*tempPointer)->value == 0)
			//	{
			//		continue;
			//	}
			//	
			//	
			//		tempPointer = &(*tempPointer)->next;
			//	
			//}
			//Show(stack);
			//Show(stack1);
			//Show(stack2);
		/*	Show(stack1);
			cout << endl;
			Show(stack2);
			cout << endl;*/
			//Stack** tempPointer = &stack;
			/*for (Stack** tempPointer = &stack; *tempPointer != NULL; tempPointer = tempPointer->next)
			{

			}*/
			/*while (*tempPointer)
			{
				if (abs((*tempPointer)->value % 10) == 5)
				{
					Delete(*tempPointer);
				}
				else
				{
					tempPointer = &(*tempPointer)->next;
				}
			}*/
			break;
		}
		case 3:
			cout << "Введите значение элемента: " << endl;
			int value;
			cin >> value;
			Add(stack, value);
			cout << "\n";
			break;
		case 4:
			DeleteStack(stack);
			break;

		case 5:
			SortValue(stack);
			break;
		case 6:
			fact = false;
		}

		//Show(stack);
		cout << "\n";
	}
}

void Add(Stack*& top, int value)
{
	Stack* newElement = new Stack;
	newElement->next = top;
	newElement->value = value;
	top = newElement;
}

void Delete(Stack*& top)
{
	if (!top) return;
	Stack* tempPointer = top->next;
	delete top;
	top = tempPointer;
}

void DeleteStack(Stack*& top)
{
	while (top) Delete(top);
}

void Show(Stack* top)
{
	Stack* tempPointer = top;
	cout << "Элементы стека: " << endl;
	for (; tempPointer; tempPointer = tempPointer->next)
	{
		cout << tempPointer->value << " ";
	}
	cout << endl;
}

void SortValue(Stack* top)
{
	for (Stack* tempPointer = top; tempPointer; tempPointer = tempPointer->next)
	{
		for (Stack* nextTempPointer = tempPointer->next; nextTempPointer; nextTempPointer = nextTempPointer->next)
		{
			if (tempPointer->value > nextTempPointer->value)
			{
				int tempValue = tempPointer->value;
				tempPointer->value = nextTempPointer->value;
				nextTempPointer->value = tempValue;
			}
		}
	}
}
void SortAddress(Stack*& top)
{
	Add(top, 0);
	for (Stack* tempPointer = top; tempPointer; tempPointer = tempPointer->next)
	{
		for (Stack* nextTempPointer = tempPointer->next; nextTempPointer; nextTempPointer = nextTempPointer->next)
		{
			if (nextTempPointer->next && tempPointer->next->value > nextTempPointer->next->value)
			{
				Stack* tempElement = nextTempPointer->next;
				nextTempPointer->next = tempElement->next;
				tempElement->next = tempPointer->next;
				tempPointer->next = tempElement;
				nextTempPointer = tempPointer;
			}
		}
	}
	Delete(top);
}
