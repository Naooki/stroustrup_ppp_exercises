#include "../../../../libs/std_lib_facilities.h"


bool is_whitespace(const char& ch, const string& w)
{
	if (ch == ' ') return true;
	for (char c : w)
		if (ch == c) return true;
	return false;
}
vector<string> split(const string& s, const string& w)
{
	vector<string> result;
	istringstream input{ s };
	stringstream output;
	for (char ch; input.get(ch);)
	{
		if (!is_whitespace(ch,w)) output << ch;
		else output << ' ';
	}
	for (string word; output >> word;)
		result.push_back(word);
	return result;
}
void print_vector(const vector<string>& str_v)
{
	for (string str : str_v)
		cout << str << endl;
}
int main()
{
	cout << "Input string with whitespaces: ";
	string whitespaces;
	cin >> whitespaces;
	cout << "Input multi-word string: ";
	string input_str;
	vector<string> result_vector;
	while (getline(cin, input_str))
	{
		result_vector = split(input_str, whitespaces);
		cout << "Result: " << endl;
		print_vector(result_vector);
		cout << "Input another string: ";
	}
}