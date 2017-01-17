#include <iostream>
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


	T get() const { return value; }
	void set(const T& val) { value = val; }
};

template<typename T>
Number<T> operator+(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() + n2.get()); }
template<typename T>
Number<T> operator-(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() - n2.get()); }
template<typename T>
Number<T> operator*(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() * n2.get()); }
template<typename T>
Number<T> operator/(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() / n2.get()); }
template<typename T>
Number<T> operator%(const Number<T>& n1, const Number<T>& n2) { return Number<T>(n1.get() % n2.get()); }

template<typename T>
istream& operator >> (istream& is, Number<T>& obj) { T val; is >> val; obj.set(val); return is; }
template<typename T>
ostream& operator << (ostream& os, Number<T>& obj) { os << obj.get(); return os; }


int main()
{
	Number<int> nd_1;
	Number<int> nd_2;
	cin >> nd_1 >> nd_2;
	cout << nd_1 << '\t' << nd_2 << endl;
	Number<int> nd_3 = nd_1 % nd_2;
	cout << "Result: " << nd_3 << endl;
}