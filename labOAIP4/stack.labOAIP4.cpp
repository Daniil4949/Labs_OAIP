#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

struct Table
{
	string name;
	string phoneNumber;
	string cityPhoneNumber;
	string date;
	int time;
	int code;
	int	tariff;
};

struct City
{
	string name;
	int code;
	int time;
	int sum;
};

void ChangeTableInfo(Table&);
void ShowTableInfo(Table);
void ShowTablesInfo(Table[], int);
void ShowCityInfo(City);
void ShowCitiesInfo(City[], int);
void SelectionSort(City[], int, int City::* = &City::time);
void QuickSort(City[], int, int, int City::* = &City::time);
int LinearSearch(City[], int, int, int City::* = &City::time);
int BinarySearch(City[], int, int, int, int City::* = &City::time);

int main()
{
	system("chcp 1251>nul");
	bool fact = true;
	while (fact == true)
	{
		int n, input, result;
		Table* tables;
		City* cities;
		int key;
		cout << "Если хотите прочесть файл, то нажмите 1" << endl;
		cout << "Если хотите записать новый файл, то намжите 2" << endl;
		int choise;
		cin >> choise;
		ifstream fin("Structures.txt", ios::binary);
		fin.seekg(0, ios::end);
		if ((int)fin.tellg() > 0 && choise == 1)
		{
			n = (int)fin.tellg() / sizeof(Table);
			fin.seekg(0, ios::beg);
			tables = new Table[n]{};
			fin.read((char*)tables, sizeof(*tables) * n);
			fin.close();
			ShowTablesInfo(tables, n);
			while (1)
			{
				cout << "Если хотите изменить файл, то нажмите 1 " << endl;
				cout << "В противном случае нажмите 0" << endl;
				int choise3;
				cin >> choise3;
				if (choise3 == 1)
				{
					cout << "Какой номер (от 1)?" << endl;
					int input;
					cin >> input;
					cout << "\n";
					ChangeTableInfo(tables[input - 1]);
					ShowTablesInfo(tables, n);
				}
				else break;
			}
		}
		else
		{
			cout << "Введите количество записей: " << endl;
			cin >> n;
			cout << "\n";
			tables = new Table[n]{};
			for (int i = 0; i < n; i++) ChangeTableInfo(tables[i]);
		}
		ofstream fout("Structures.txt", ios::binary);
		fout.write((char*)tables, sizeof(*tables) * n);
		fout.close();
		cities = new City[n]{};
		int c = 0;
		for (int i = 0; i < n; i++)
		{
			int contained = -1;
			for (int j = 0; j < c; j++) if (tables[i].code == cities[j].code) contained = j;
			if (contained == -1)
			{
				cities[c].name = tables[i].name;
				cities[c].code = tables[i].code;
				cities[c].time = tables[i].time;
				cities[c].sum = tables[i].tariff * tables[i].time;
				c++;
			}
			else
			{
				cities[contained].time += tables[i].time;
				cities[contained].sum += tables[i].tariff * tables[i].time;
			}
		}
		cout << "Города:"<<endl;
		ShowCitiesInfo(cities, c);
		cout << "Если хотите выполнить задание, то нажмите 1" << endl;
		cout << "Если хотите выполнить сортировку прямым выбором, то намжите 2" << endl;
		cout << "Если хотите выполнить быструю сортировку, то нажмите 3" << endl;
		cout << "Если хотите выполнить линейный поиск, то намжите 4" << endl;
		cout << "Если хотите волнить двоичный поиск, то нажмите 5" << endl;
		cout << "Если хотите завершить программу, то нажмите 6" << endl;

		int n1;
		cin >> n1;
		switch (n1)
		{
		case 1:
			ShowCitiesInfo(cities, c);
			break;
		case 2:
			SelectionSort(cities, c);
			ShowCitiesInfo(cities, c);
			break;
		case 3:
			QuickSort(cities, 0, c - 1);
			ShowCitiesInfo(cities, c);
			break;
		case 4:
			cout << "Введите нужное общее время разговоров: " << endl;
			cin >> key;
			cout << "\n";
			result = LinearSearch(cities, c, key);
			if (result >= 0) ShowCityInfo(cities[result]);
			else cout << "Элемент не найден\n\n";
			break;
		case 5:
			cout << "Массив будет отсортирован." << endl;
			QuickSort(cities, 0, c - 1);
			ShowCitiesInfo(cities, c);
			cout << "Введите нужное общее время разговоров: " << endl;
			cin >> key;
			result = BinarySearch(cities, 0, c, key);
			if (result >= 0) ShowCityInfo(cities[result]);
			else cout << "Элемент не найден\n\n";
			break;
		case 6:
			fact = false;
		}
	}
}
void ChangeTableInfo(Table& table)
{
	cout << "Введите дату разговора: " << endl;
	cin >> table.date;
	cout << "Введите код города: " << endl;
	cin >> table.code;
	cout << "Введите название города: " << endl;
	cin >> table.name;
	cout << "Введите время разговора: " << endl;
	cin >> table.time;
	cout << "Введите тариф: " << endl;
	cin >> table.tariff;
	cout << "Введите номер телефона в этом городе: " << endl;
	cin >> table.cityPhoneNumber;
	cout << "Введите номер телефона абонента: " << endl;
	cin >> table.phoneNumber;
	cout << "\n";
}

void ShowTableInfo(Table table)
{
	cout << "\n";
	cout << "Дата разговора: " << table.date<<"\n";
	cout << "Код города: " << table.code << "\n";
	cout << "Название города: " << table.name << "\n";
	cout << "Время разговора: " << table.time << "\n";
	cout << "Тариф: " << table.tariff << "\n";
	cout << "Номер телефона в этом городе: " << table.cityPhoneNumber << "\n";
	cout << "Номер телефона абонента: " << table.cityPhoneNumber << "\n\n";
}

void ShowTablesInfo(Table tables[], int n)
{
	for (int i = 0; i < n; i++) ShowTableInfo(tables[i]);
}

void ShowCityInfo(City city)
{
	cout << "Название города: " << city.name << "\n";
	cout << "Код города: " << city.code << "\n";
	cout << "Общее время разговоров: " << city.time << "\n";
	cout << "Сумма: " << city.sum << "\n\n";
}

void ShowCitiesInfo(City cities[], int n)
{
	for (int i = 0; i < n; i++) ShowCityInfo(cities[i]);
}

void SelectionSort(City array[], int n, int City::* keyPtr)
{
	for (int i = 0; i < n - 1; i++)
	{
		int m = i;
		for (int j = i + 1; j < n; j++) if (array[i].*keyPtr < array[j].*keyPtr) m = j;
		if (m == i) continue;
		City temp = array[i];
		array[i] = array[m];
		array[m] = temp;
	}
}


void QuickSort(City array[], int begin, int end, int City::* keyPtr)
{
	int left = begin, right = end, middle = (left + right) / 2;
	do
	{
		while (array[left].*keyPtr < array[middle].*keyPtr) left++;
		while (array[right].*keyPtr > array[middle].*keyPtr) right--;
		if (left <= right)
		{
			City temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			left++;
			right--;
		}
	} while (left <= right);
	if (begin < right) QuickSort(array, begin, right, keyPtr);
	if (left < end) QuickSort(array, left, end, keyPtr);
}

int LinearSearch(City array[], int n, int key, int City::* keyPtr)
{
	int result = -1;
	for (int i = 0; i < n; i++) if (array[i].*keyPtr == key) result = i;
	return result;
}

int BinarySearch(City array[], int left, int right, int key, int City::* keyPtr)
{
	if (left > right) return -1;
	int middle = (left + right) / 2;
	if (array[middle].*keyPtr > key) return BinarySearch(array, left, middle - 1, key, keyPtr);
	if (array[middle].*keyPtr < key) return BinarySearch(array, middle + 1, right, key, keyPtr);
	return middle;
}
