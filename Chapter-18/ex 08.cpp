//is palindrome(using a backward copy)
#include <iostream>
#include <string>
using namespace std;

bool is_palindrome(const string& str)
{
	string copy = "";
	for (int i = str.length() - 1; i >= 0; --i)
		copy.push_back(str[i]);
	return copy == str;

}
bool is_palindrome(const char str[], int n)
{
	int first = 0;
	int last = n - 1;
	char* copy = new char[n+1];
	copy[n] = 0;
	int index = 0;
	for (int i = last; i >= first; --i)
	{
		copy[index] = str[i];
		++index;
	}
	for (int i = first; i <= last; ++i)
		if (str[i] != copy[i]) 
		{
			delete[] copy; 
			return false;
		}
	delete[] copy;
	return true;
}

bool is_palindrome(const char* first, const char* last)
{
	int len = 0;
	const char* ptr = first;
	while (ptr <= last) {	++len; ++ptr; }
	char* copy = new char[len];
	ptr = last;
	char* copy_ptr = copy;
	while (ptr >= first) { *copy_ptr = *ptr; ++copy_ptr; --ptr; }
	copy_ptr = copy;
	for (first; first <= last; ++first)
	{
		if (*first != *copy_ptr) { delete[] copy; return false; }
		++copy_ptr;
	}
	delete[] copy;
	return true;
}


int main() {
	cout << "Using string:\n";
	string str = "babcb";
	cout << "String: " << str << " palindrome. -> " << is_palindrome(str) << endl;

	cout << "Using array:\n";
	char arr_str[] = "babab";
	cout << "String: " << str << " palindrome. -> " << is_palindrome(arr_str, 5) << endl;

	cout << "Using pointers:\n";
	char ptrs_str[] = { 'b','a','b','c','b' };
	cout << "String: " << str << " palindrome. -> " << is_palindrome(&ptrs_str[0], &ptrs_str[4]) << endl;
}