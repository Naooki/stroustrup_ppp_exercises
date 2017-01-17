#include <vector>
#include <iostream>
//#include <type_traits> //???
using namespace std;

template<typename T, typename U>
typename std::common_type<T,U>::type foo(vector<T> vt, vector<U> vu)
{
	//double sum = 0;
	typename std::common_type<T, U>::type sum = 0; //I've come across this solution on Bewuethr's github... Looks cool, but I've no idea how it works yet :D
	int min_size = vt.size() > vu.size() ? vu.size() : vt.size();
	for (int i = 0; i < min_size; ++i)
		sum += vt[i] * vu[i];
	return sum;
}

int main()
try
{
	vector<int> v1 = { 2,3,4 };
	vector<double> v2 = { 2.0, 3.0, 4.0 };
	cout << "Result: " << foo(v1, v2) << '\n';
	return 0;
}
catch (exception& e)
{
	cerr << "Exception: " << e.what() << endl;
	return 1;
}
catch (...)
{
	cerr << "Exception!" << endl;
	return 2;
}
