#include <iostream>
#include <string>

using namespace std;

char* findx(const char* s, const char* x)
{
	int i = 0;
	while (s[i] != 0)
	{
		if (s[i] == x[0])
		{
			int j = 0;
			while (x[j] == s[i + j] || x[j] == 0)
			{
				if (x[j] == 0) return const_cast<char*>(&s[i]);   //lol... (in the exrercise function returns char*,
																  // but we can return const char* to avoid using const_cast)
				++j;
			}
		}
		++i;
	}
	return nullptr;
}

int main()
{
	string str = "Practice makes perfect!";
	string substr = " mak";
	char* p = findx(&str[0], &substr[0]);
	if (p == nullptr) cout << "Not found!" << endl;
	else cout << p << endl;
}