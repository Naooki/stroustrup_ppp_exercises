#include <iostream>
using namespace std;

char* c_style_cat_dog(const char* s1, const char* s2, const char* separator)
{
	int len = 0; // find total length
	const char* p = s1;
	while (*p) { ++len; ++p; }
	p = separator;
	while (*p) { ++len;	++p; }
	p = s2;
	while (*p) { ++len;	++p; }

	char* res = new char[len + 1];
	char* pp = res;
	while (*s1) { *pp = *s1; ++s1; ++pp; }
	while (*separator) { *pp = *separator; ++separator; ++pp; }
	while (*s2)	{ *pp = *s2; ++s2; ++pp; }
	*pp = 0;
	return res;
}

int main()
{
	char* p = c_style_cat_dog("Hello", "World!", ", ");
	cout << p << endl;
	p = c_style_cat_dog("Niels", "Bohr", ".");
	cout << p << endl;

	delete[] p;
}