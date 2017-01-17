#include "../../../../libs/std_lib_facilities.h"
using namespace std;

template<typename T, typename U>
struct Pair
{
public:
	Pair(T var_type, U var_val)
		:id(var_type), value(var_val) {}
	T id;
	U value;
};
template<typename T, typename U>
class Symbol_table
{
	vector< Pair<T, U> > table;
public:
	U& get(const T& name); //returns value with given name "name"
	void set(const T& name, const U& val); //set the value named "name" with value "val"
	bool is_declared(const T& name); //returns true if there is a value in table with given name
	void declare(const T& name, const U& val); //adds the (name,val) pair to the table
	void print(ostream& os); //prints table
};
template<typename T, typename U>
U& Symbol_table<T,U>::get(const T& name)
{
	for (Pair<T, U> elem : table)
		if (elem.id == name) return elem.value;
	error("Element hasn't been found: ", name);
}
template<typename T, typename U>
void Symbol_table<T,U>::set(const T& name, const U& val)
{
	for (Pair<T, U> elem : table)
		if (elem.id == name)
		{
			elem.value = val;
			return;
		}
	error("Element hasn't been found: ", name);
}
template<typename T, typename U>
bool Symbol_table<T,U>::is_declared(const T& name)
{
	for (Pair<T, U> elem : table)
		if (elem.id == name) return true;
	return false;
}
template<typename T, typename U>
void Symbol_table<T,U>::declare(const T& name, const U& val)
{
	if (is_declared(name)) error("This name exists already: ", name);
	table.push_back(Pair<T, U>(name, val));
}
template<typename T, typename U>
void Symbol_table<T,U>::print(ostream& os)
{
	for (Pair<T, U> elem : table)
		os << elem.id << " : " << elem.value << '\n';
}


int main()
{
	Symbol_table<string, double> st;
	st.declare("pi", 3.14);
	st.declare("e", 2.71);
	st.print(cout);
}