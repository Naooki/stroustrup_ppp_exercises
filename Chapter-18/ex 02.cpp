#include <iostream>
using namespace std;

char* my_findx(const char* s, const char* x)
{
	if (s == nullptr || !*s) return nullptr;
	if (x == nullptr || !*x) return const_cast<char*>(s);

	while (*s)
	{
		if (*s == *x)
		{
			const char* ps = s;
			const char* px = x;
			bool is_equal = true;
			while (*px)
			{
				if (*px != *ps)
				{
					is_equal = false;
					break;
				}
				++ps;
				++px;
			}
			if (is_equal) return const_cast<char*>(s); //...
		}
		++s;
	}
	return nullptr;
}

//nice Bewuethr's solution (much shorter...)
char* bewuethr_findx(const char* s, const char* x) //I just got the idea and try to reimplement it
{
	if (s == nullptr || !*s) return nullptr;
	if (x == nullptr || !*x) return const_cast<char*>(s);

	for (int j = 0; *(s+j); ++j) // basically, it just uses fors instead of whiles
	{
		if (*(s+j) == *x)
		{
			bool is_equal = true;
			for (int i = 0; *(x + i); ++i)
			{
				if (!(s + j + i)) return nullptr; //the end of the s
				if (*(s + j + i) != *(x + i))
				{
					is_equal = false;
					break;
				}
			}
			if (is_equal) return const_cast<char*>(s+j);
		}
	}
	return nullptr;
}


int main()
{
	char str[] = "Hello world!";
	char substr[] = "o w";
	char* p = my_findx(str, substr);
	cout << "Result: " << p << endl;
}