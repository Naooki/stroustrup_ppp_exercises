#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Number
{
	T value;
public:
	Number() :value(T()) {} //default constructor
	Number(const T& obj) :value(obj) {} //init constructor
	Number(const Number& obj) :value(obj.value) {} //copy constructor

	Number& operator=(const Number& obj) { value = obj.value; return *this; } //copy assignment

	Number& operator+=(const Number& obj) { value += obj.value; return *this; }
	Number& operator-=(const Number& obj) { value -= obj.value; return *this; }
	Number& operator*=(const Number& obj) { value *= obj.value; return *this; }
	Number& operator/=(const Number& obj) { value /= obj.value; return *this; }
	Number& operator%=(const Number& obj) { value %= obj.value; return *this; }

	T get() const { return value; }
	void set(const T& val) { value = val; }
};

//template<typename T>
//Number<T> operator+(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() + n2.get()); }
//template<typename T>
//Number<T> operator-(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() - n2.get()); }
//template<typename T>
//Number<T> operator*(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() * n2.get()); }
//template<typename T>
//Number<T> operator/(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() / n2.get()); }
//template<typename T>
//Number<T> operator%(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() % n2.get()); }

template<typename T, typename U>
typename common_type<T, U>::type operator+(const Number<T>& n1, const Number<U>& n2) { return common_type<T, U>::type(n1.get() + n2.get()); }
template<typename T, typename U>
typename common_type<T, U>::type operator-(const Number<T>& n1, const Number<U>& n2) { return common_type<T, U>::type(n1.get() - n2.get()); }
template<typename T, typename U>
typename common_type<T, U>::type operator*(const Number<T>& n1, const Number<U>& n2) { return common_type<T, U>::type(n1.get() * n2.get()); }
template<typename T, typename U>
typename common_type<T, U>::type operator/(const Number<T>& n1, const Number<U>& n2) { return common_type<T, U>::type(n1.get() / n2.get()); }
template<typename T, typename U>
typename common_type<T, U>::type operator%(const Number<T>& n1, const Number<U>& n2) { return common_type<T, U>::type(n1.get() % n2.get()); }



template<typename T>
istream& operator >> (istream& is, Number<T>& obj) { T val; is >> val; obj.set(val); return is; }
template<typename T>
ostream& operator << (ostream& os, Number<T>& obj) { os << obj.get(); return os; }


//Exercise 2 function
template<typename T, typename U>
typename std::common_type<T, U>::type foo(vector<Number<T>> vt, vector<Number<U>> vu)
{
	common_type<T, U>::type sum = 0;
	int min_size = vt.size() > vu.size() ? vu.size() : vt.size();
	for (int i = 0; i < min_size; ++i)
		sum += vt[i] * vu[i];
	return sum;
}

int main()
{
	vector<Number<double>> v2 = { 1.5,2.5,3.5,4.5,5.5,6.5 };
	vector<Number<int>> v1 = { 1,2,3,4,5 };

	Number<double> td(1.1);
	Number<int> ti(1);
	cout << "Multiplication: " << td*ti << " Sum: " << td+ti <<  endl;
	cout << "Foo result: " << foo(v1, v2) << endl; 
}