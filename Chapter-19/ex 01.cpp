#include <vector>
#include <iostream>
#include <string>
using namespace std;


template<typename T> void f(vector<T>& v1, vector<T>& v2)
{
	int min_size = v1.size() > v2.size() ? v2.size() : v1.size();
	for (int i = 0; i < min_size; ++i)
		v1[i] += v2[i];
}

int main()
{
	vector<int> v_int1 = { 1,2,3,4,5,6,7 };
	vector<int> v_int2 = { 10,20,30,40,50 };

	f(v_int1, v_int2);
	cout << "Vector v1: { ";
	for (int i = 0; i < v_int1.size(); ++i)
		cout << v_int1[i] << " ";
	cout << " }\n";


	vector<string> v_str1 = { "ab", "cd", "ef", "gh" };
	vector<string> v_str2 = { "zx", "xc", "cv" };

	f(v_str1, v_str2);
	cout << "Vector v1: { ";
	for (int i = 0; i < v_str1.size(); ++i)
		cout << v_str1[i] << " "; 
	cout << " }\n";
}