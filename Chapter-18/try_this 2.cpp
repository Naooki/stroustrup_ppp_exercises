#include <iostream>
class My_vector {
	int sz;
	double* elem;
public:
	My_vector(int size, double* p)
		:sz(size), elem(p) {}

	//double operator[](int n) { return elem[n]; }
	double& operator[] (int n) { return elem[n]; }
	const double& operator[] (int n) const { return elem[n]; } //or we can return just double...
};

int main()
{
	double* p = new double[5]{1,2,3,4,5};
	My_vector v(5, p);
	int x = v[4];
	v[2] = x;
}