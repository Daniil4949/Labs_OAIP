#include<iostream>
#include <string>
#include <ctime>

using namespace std;

struct ListElement
{
	int value;
	ListElement* next = NULL;
	ListElement* prev = NULL;
};

struct List
{
	ListElement* begin = NULL;
	ListElement* end = NULL;
};

void AddToBegin(List*, int);
void AddToEnd(List*, int);
void Delete(ListElement*, List*);
void DeleteList(List*);
void ShowFromBegin(List*);
void ShowFromEnd(List*);

int main()
{
	system("chcp 1251>nul");
	List* list = new List;
	srand(time(NULL));
	int size, value, sizeRange = 5;
	bool fact = true;
	while (fact == true)
	{
		cout << "Если хотите создать список, то нажмите 1" << endl;
		cout << "Если хотите выполнить задание, то нажмите 2" << endl;
		cout << "Если хотите добавить в начало, то нажмите 3" << endl;
		cout << "Если хотите добавить в конец, то нажмите 4" << endl;
		cout << "Если хотите просмотреть с начала, то нажмите 5" << endl;
		cout << "Если хотите просмотреть с конца, то нажмите 6" << endl;
		cout << "Если хотите завершить программу, то нажмите 7" << endl;
		int n;
		cin >> n;
		switch (n)
		{
		case 1:
		{
			DeleteList(list);
			cout << "Если хотите создать список со случайными элементами(значением до 20), то нажмите 1" << endl;
			cout << "Если хотите самостоятельно заполнить список, то нажмите 2" << endl;
			int choise;
			cin >> choise;
			if (choise == 1)
			{
				size = rand() % 11;
				cout << "Размер списка: " << size << "\n\n";
				for (int i = 0; i < size; i++)
				{
					value = rand() % 21;
					cout << value << " ";
					cout << endl;
					AddToBegin(list, value);
				}
			}
			else if (choise == 2)
			{
				cout << "Введите размер списка: " << endl;
				cin >> size;
				cout << "\n";
				for (int i = 0; i < size; i++)
				{
					cin >> value;
					AddToBegin(list, value);
				}
			}
			ShowFromBegin(list);
			break;
		}
		case 2:
		{
			AddToEnd(list, 0);
			for (ListElement* tempPointer = list->begin->next; tempPointer; tempPointer = tempPointer->next)
			{
				if (abs(tempPointer->prev->value % 10) == 5)
				{
					Delete(tempPointer->prev, list);
				}
			}
			Delete(list->end, list);
			break;
		}
		case 3:
			cout << "Введите значение элемента: " << endl;
			cin >> value;
			AddToBegin(list, value);
			break;
		case 4:
			cout << "Введите значение элемента: " << endl;
			cin >> value;
			AddToEnd(list, value);
			break;
		case 5:
			ShowFromBegin(list);
			break;
		case 6:
			ShowFromEnd(list);
			break;
		case 7:
			fact = false;
		}
		cout << "\n";
	}
}

void AddToBegin(List* list, int value)
{
	ListElement* newElement = new ListElement;
	newElement->next = list->begin;
	newElement->value = value;
	if (list->begin) list->begin->prev = newElement;
	if (!list->end) list->end = newElement;
	list->begin = newElement;
}

void AddToEnd(List* list, int value)
{
	ListElement* newElement = new ListElement;
	newElement->prev = list->end;
	newElement->value = value;
	if (list->end) list->end->next = newElement;
	if (!list->begin) list->begin = newElement;
	list->end = newElement;
}

void Delete(ListElement* element, List* list)
{
	if (element == list->begin && element == list->end)
	{
		list->begin = list->end = NULL;
	}
	else if (element == list->begin)
	{
		list->begin = element->next;
		list->begin->prev = NULL;
	}
	else if (element == list->end)
	{
		list->end = element->prev;
		list->end->next = NULL;
	}
	else
	{
		element->next->prev = element->prev;
		element->prev->next = element->next;
	}
	delete element;
}

void DeleteList(List* list)
{
	while (list->begin) Delete(list->begin, list);
}

void ShowFromBegin(List* list)
{
	ListElement* tempPointer = list->begin;
	cout<<"Список: " << endl;
	for (; tempPointer;  tempPointer = tempPointer->next)
	{
		cout << tempPointer->value << " ";
	}
}

void ShowFromEnd(List* list)
{
	ListElement* tempPointer = list->end;
	cout << "Список: " << endl;
	for (; tempPointer;  tempPointer = tempPointer->prev)
	{
		cout  << tempPointer->value << " ";
	}
}
