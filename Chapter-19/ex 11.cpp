#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class counted_ptr
{
	T* value;
	int* counter;
public:
	explicit counted_ptr(const T& val);
	counted_ptr(const counted_ptr& cnt_p);
	~counted_ptr();
	
	counted_ptr& operator =(const counted_ptr& cnt_p);
	T operator *() { return *value; }
	T* operator ->() { return value; }
};

template<typename T>
counted_ptr<T>::counted_ptr(const T& val)
	:value(new T), counter(new int)
{
	*value = val;
	*counter = 1;
}
template<typename T>
counted_ptr<T>::counted_ptr(const counted_ptr& cnt_p)
	:value(cnt_p.value), counter(cnt_p.counter)
{
	++*counter;
}
template<typename T>
counted_ptr<T>::~counted_ptr()
{
	--*counter;
	if (*counter == 0)
	{
		delete value;
		delete counter;
		cout << "Pointed value destroyed.\n";
	}
}
template<typename T>
counted_ptr<T>& counted_ptr<T>::operator =(const counted_ptr& cnt_p)
{
	if (this == &cnt_p) return *this; //self-assignment

	--*counter;
	if (*counter == 0)
	{
		delete value;
		delete counter;
	}
	value = cnt_p.value;
	counter = cnt_p.counter;
	++*counter;
	return *this;
}
//--------------------------------------------------------------------------------------------------------

//arg test
template<typename T>
void arg_test(counted_ptr<T>& arg)
{
	counted_ptr<T> lp = arg; //initialisation
	cout << "*lp: " << *lp << '\n';
	lp = counted_ptr<T>(T()); //assignment
	cout << "*lp: " << *lp << '\n';
}

void container_test()
{
	double a = 13.37, b = 3.22;

	vector<counted_ptr<double>> v;
	v.push_back(counted_ptr<double>(a));
	v.push_back(counted_ptr<double>(v[0]));
	v.push_back(counted_ptr<double>(b));
	v.push_back(counted_ptr<double>(a));

}

int main()
{
	double d = 14.88;

	counted_ptr<double> p(d);
	arg_test(p);
	cout << "Done!\n";

	container_test();
	cout << "Done!\n";
}
