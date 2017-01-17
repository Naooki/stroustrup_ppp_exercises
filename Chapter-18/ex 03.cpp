#include <iostream>
using namespace std;
int strcmp(const char* a, const char* b)
{
	while(true)
	{
		if (*a < *b) return 1;
		else if (*a > *b) return -1;
		if (*a == 0 || *b == 0) break;
		++a;
		++b;
	}
	return 0;
}

int main()
{
	char str1[] = "";
	char str2[] = "Hello wo";
	cout << "Compare strings: " << strcmp(str1, str2) << endl;
}