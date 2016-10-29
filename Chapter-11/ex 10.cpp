#include "../../../../libs/std_lib_facilities.h"


vector<string> split(const string& s)
{
	vector<string> result;
	istringstream input{ s };
	for (string sub_str; input >> sub_str;)
		result.push_back(sub_str);
	return result;
}
void print_vector(const vector<string>& str_v)
{
	for (string str : str_v)
		cout << str << endl;
}
int main()
try
{
	cout << "Enter a multi-word string: " << endl;
	string input;
	vector<string> substrings;
	while (getline(cin, input))
	{
		substrings = split(input);
		cout << "Result: " << endl;
		print_vector(substrings);
		cout << "Another try: ";
	}
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "Exception!" << endl;
}
