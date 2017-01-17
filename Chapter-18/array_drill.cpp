#include <iostream>
using namespace std;

int ga[] = { 1,2,4,8,16,32,64,128,256,512 };

void f(int arr[], int len)
{
	int la[10];
	cout << "Local array: ";
	for (int i = 0; i < 10; ++i)
	{
		la[i] = ga[i];
		cout << la[i] << ' ';
	}
	cout << '\n';
	int* p = new int[len];
	cout << "Free store array: ";
	for (int i = 0; i < len; ++i)
	{
		p[i] = arr[i];
		cout << p[i] << ' ';
	}
	cout << '\n';
	delete[] p;
}

int fact(const int& n)
{
	int res = 1;
	for (int i = 1; i <= n; ++i) res *= i;
	return res;
}

int main()
{
	int aa[10] = { fact(0),fact(1),fact(2),fact(3),fact(4),fact(5),fact(6),fact(7),fact(8),fact(9) };
	f(ga, 10);
	cout << "\n\n";
	f(aa, 10);
}