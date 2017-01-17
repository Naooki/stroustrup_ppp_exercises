#include <iostream>
using namespace std;

bool is_palindrome(const char s[], int n)
{
	int first = 0;
	int last = n - 1;
	while (first < last)
	{
		if (s[first] != s[last]) return false;
		++first;
		--last;
	}
	return true;
}

istream& read_word(istream& is, char* buffer, int max_len)
{
	is.width(max_len);
	is >> buffer;
	if (strlen(buffer) == max_len - 1)
	{
		cout << "The string is too long. The length of the input string is only " << max_len - 1 << " characters!\n";
		char ch;
		while (is.get(ch))
		{
			if (ch == '\n') break;
		}
	}
	return is;
}

istream& arbitrarily_long_word(istream& is, char*& buffer)  //I should pass pointer by reference to change it eventually...
{
	int len = 0;
	char ch;
	char* new_buffer;
	while (is.get(ch))
	{
		++len;
		new_buffer = new char[len];
		for (int i = 0; i < len - 1; ++i)
			new_buffer[i] = buffer[i];
		delete[] buffer;
		if (ch == '\n') 
		{ 
			new_buffer[len-1] = 0;
			buffer = new_buffer;
			break; 
		}
		new_buffer[len-1] = ch;
		buffer = new_buffer;
	}
	return is;
}

int main()
{
	//Message is input string is too long
	constexpr int max = 10;
	char s[max];
	while (read_word(cin, s, max) && strcmp(s, "quit"))	//strcmp returns 0 when strings are equal 
	{
		cout << s << " is";
		if (!is_palindrome(s, strlen(s))) cout << " not";
		cout << " a palindrome.\n";
	}
	cin.ignore(5, '\n');
	//Arbitrarily long input strings
	//We definitely need free store array there...
	char* p_str = nullptr;
	while (arbitrarily_long_word(cin, p_str))
	{
		if (!strcmp(p_str, "quit")) break;
		cout << p_str << " is";
		if (!is_palindrome(p_str, strlen(p_str))) cout << " not";
		cout << " a palindrome.\n";
	}
}