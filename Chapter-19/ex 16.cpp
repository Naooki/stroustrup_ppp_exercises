#include "my_small_size_vector.h"
#include "iostream"
using namespace naook;

int main()
{
	vector<int> v(10);
	cout << "Vector v(10):\n";
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << '\n';
	cout << "v(10) size: " << sizeof(v) << '\n';
	cout << "--------------------------------------------------\n";
	vector<vector<vector<int>>> v3;
	cout << "v3 size: " << sizeof(v3) << '\n';

}