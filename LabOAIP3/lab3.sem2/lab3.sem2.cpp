#include<iostream>
#include<cmath>
#include<stack>
using namespace std;
int A(int m, int n) {
	if (m == 0) {
		return n + 1;
	}
	else if (m > 0 && n == 0) {
		return A(m - 1, 1);
	}
	return A(m - 1, A(m, n - 1));
}
int main() {
	system("chcp 1251>nul");
	int n;
	int m;
	int result = 0;
	cout << "Введите значение m:" << endl;
	cin >> m;
	cout << "Введите значение n:" << endl;
	cin >> n;
	cout << "Значение функции Аккермана: " << endl;
	cout<<A(m,n)<<endl;
	
	return 0;
}