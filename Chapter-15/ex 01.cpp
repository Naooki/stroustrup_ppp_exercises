#include "std_lib_facilities.h"

 Iteratively calculates factorial for n.
long long iterative_fac(int n)
{
	return (n > 1) ? n*iterative_fac(n - 1) : 1;
}
 Recursively calculates factorial for n.
long long recursive_fac(int n)
{
	long long res = 1;
	while (n > 1)
	{
		res *= n;
		--n;
	}
	return res;
}

int main()
{
	cout << iterative_fac(20) << endl;
	cout << recursive_fac(20) << endl;
}
