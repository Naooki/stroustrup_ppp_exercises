#include <string>
#include <iostream>

char* strcopy(const char* p)
{
	int length = 0;
	while (true)
		if (p[length++] == 0) break;
	char* res = new char[length];
	for (int i = 0; i < length; ++i)
		res[i] = p[i];
	return res;
}

int main()
{
	std::string str = "Hello, World!";
	char* p = strcopy(&str[0]);
	std::cout << p << std::endl;  //when print pointer to char, it prints the whole string...

	int i = 123;
	int* pi = &i;
	std::cout << "Int* pi: " << pi << std::endl;
	char ch = 'B';
	char* pch = &ch;
	std::cout << "Char* pch: " << pch << std::endl;  // The result is "B" and then some strange symbols, interesting...
}