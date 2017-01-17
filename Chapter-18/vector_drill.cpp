#include <vector>
#include <iostream>
using namespace std;

vector<int> gv = { 1,2,4,8,16,32,64,128,256,512 };

void f(const vector<int>& v)
{
	cout << "Global vector:\n";
	vector<int> lv(v.size());
	for (int i = 0; i < lv.size(); ++i)
	{
		lv[i] = gv[i];
		cout << lv[i] << ' ';
	}
	cout << "\nArguemnt vector:\n";
	vector<int> lv2 = v;
	for (int i = 0; i < lv2.size(); ++i)
		cout << lv2[i] << ' ';
	cout << '\n';
}

int fact(const int& n)
{
	int result = 1;
	for (int i = 2; i <= n; ++i) result *= i;
	return result;
}

int main()
{
	f(gv);
	cout << "\n\n";
	vector<int> vv = { fact(0), fact(1), fact(2), fact(3), fact(4), fact(5), fact(6), fact(7), fact(8), fact(9) };
	f(vv);
}