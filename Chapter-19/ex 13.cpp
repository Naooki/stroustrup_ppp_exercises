#include <string>
#include <iostream>
using namespace std;

class Tracer
{
	string str;
public:
	Tracer(const string& s) :str(s) { cout << "Constructor: " << s << '\n'; }
	~Tracer() { cout << "Destructor: " << str << '\n'; }
	Tracer(const Tracer& t) :str(t.str) { cout << "Copy constructor: " << t.str << '\n'; }
	Tracer& operator=(const Tracer& t) { str = t.str; cout << "Copy assignment: " << t.str << '\n'; return *this; }
};

Tracer foo(Tracer obj)
{
	Tracer t = obj;
	return t;
}

Tracer global("global");

int main()
{
	{ Tracer t("t"); }  //local - constructed and instantly destroyed
	Tracer tt("tt");
	Tracer tt1 = foo(tt);
	Tracer* pt = new Tracer("free store tracer");
	tt1 = *pt;
	delete pt;
}