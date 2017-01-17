#include <vector>
#include <string>
#include <iostream>
using namespace std;
template<typename T> class S
{
public:
	S(T initialiser)
		:val(initialiser) {}
	T& get();
	const T& get() const;
	//void set(const T& newval) { val = newval; }
	S<T>& operator=(const T& obj);
private:
	T val;
};

template<typename T> T& S<T>::get() { return val; }
template<typename T> const T& S<T>::get() const { return val; }
template<typename T> S<T>& S<T>::operator=(const T& obj) { val = obj; return *this; }

template<typename T> istream& read_val(T& v)
{
	cin >> v;
	return cin;
}

template<typename T> istream& operator >> (istream& is, vector<T>& v)
{
	vector<T> buffer;
	char ch;
	is >> ch;
	if (!is) return is;
	if (ch != '{')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	T el;
	while (cin >> el >> ch && ch == ',')
	{
		buffer.push_back(el);
	}
	if(ch!='}')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	buffer.push_back(el);
	v = buffer;
}
template<typename T> ostream& operator << (ostream& os, const vector<T>& v)
{
	os << "{ ";
	for (int i = 0; i < v.size() - 1; ++i)
		os << v[i] << ", ";
	os << v[v.size() - 1] << " }";
	return os;
}


int main()
{
	S<int> s_int(322);
	S<char> s_char('a');
	S<double> s_double(3.22);
	S<string> s_string("abc");
	vector<int> v = { 1,2,3 };
	S<vector<int>> s_vector(v);

	/*cout << "s_int: " << s_int.val << '\n';
	cout << "s_char: " << s_char.val << '\n';
	cout << "s_double: " << s_double.val << '\n';
	cout << "s_string: " << s_string.val << '\n';
	cout << "s_vector: { ";
	for (int i = 0; i < s_vector.val.size(); ++i)
	{
		cout << s_vector.val[i];
		if (i != s_vector.val.size() - 1) cout << ", ";
	}
	cout << " }\n";


	s_int.get() = 1488;
	cout << "s_int: " << s_int.val << '\n';*/


	/*cout << "s_int: " << s_int.get() << '\n';
	cout << "s_char: " << s_char.get() << '\n';
	cout << "s_double: " << s_double.get() << '\n';
	cout << "s_string: " << s_string.get() << '\n';
	cout << "s_vector: { ";
	for (int i = 0; i < s_vector.get().size(); ++i)
	{
		cout << s_vector.get()[i];
		if (i != s_vector.get().size() - 1) cout << ", ";
	}
	cout << " }\n";*/

	/*s_int.set(1488);
	cout << "s_int: " << s_int.get() << '\n';*/
	/*s_int = 1488;
	cout << "s_int: " << s_int.get() << '\n';*/


	/*read_val(s_int.get());
	read_val(s_char.get());
	read_val(s_double.get());
	read_val(s_string.get());
	cout << "s_int: " << s_int.get() << '\n';
	cout << "s_char: " << s_char.get() << '\n';
	cout << "s_double: " << s_double.get() << '\n';
	cout << "s_string: " << s_string.get() << '\n';*/

	vector<int> vi;
	S<vector<int>> s_v_int(vi);
	cin >> s_v_int.get();
	cout << "s_v_int: ";
	cout << s_v_int.get() << '\n';
	
}