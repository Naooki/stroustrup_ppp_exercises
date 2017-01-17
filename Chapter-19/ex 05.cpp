#include <iostream>
using namespace std;
class Int
{
	int value;

public:
	int get() const { return value; }

	Int() : value(0) {}
	Int(const Int& val) : value(val.value) {} //copy constructor (but what for?) (gratuitous)
	Int(const int& val) : value(val) {}

	Int& operator=(const Int& val) { value = val.value; return *this; } //gratuitous copy assignment

};


istream& operator >> (istream& is, Int obj) { is >> obj.get(); return is; }
ostream& operator << (ostream& os, Int obj) { os << obj.get(); return os; }

Int operator+(Int& v1, Int& v2) { return (v1.get() + v2.get()); }
Int operator-(Int& v1, Int& v2) { return (v1.get() - v2.get()); }
Int operator*(Int& v1, Int& v2) { return (v1.get() * v2.get()); }
Int operator/(Int& v1, Int& v2) { return (v1.get() / v2.get()); }





int main()
{
	Int n1 = 2;
	Int n2 = 3;
	Int n3 = n1 + n2;
	cout << "n1: " << n1 << " n2: " << n2 << " n3: " << n3 << '\n';
}