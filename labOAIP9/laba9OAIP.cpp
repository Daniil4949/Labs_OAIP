#include <iostream>
#include <string>
#include <cmath>

using namespace std;

double a = 4, b = 8, h = 0.1, eps = 0.0000000001;

double F(double);
double FindRoot(double, double, double);

int main()
{
	system("chcp 1251");
	system("cls");
	int n = 0;
	cout << "При параметрах:\na = " + to_string(a) + "\nb = " + to_string(b) + "\nh = " + to_string(h) + "\ne = " + to_string(eps) + "\n\n";
	for (double x = a; x <= b; x += h)
	{
		if (F(x) * F(x + h) < 0)
		{
			n++;
			cout << "x" + to_string(n) + " = " + to_string(FindRoot(x, eps, h)) + "\n";
		}
	}
	if (n == 0) cout << "Корней нет\n";
}

double F(double x)
{
	return sqrt(x) - pow(cos(x), 2) - 2;
}

double FindRoot(double x0, double epsilon, double q)
{
	double x1 = x0 - F(x0) * q / (F(x0) - F(x0 - q));
	while (fabs(x1 - x0) > eps)
	{
		x0 = x1;
		x1 = x1 - F(x1) * q / (F(x1) - F(x1 - q));
	}
	return x0;
}