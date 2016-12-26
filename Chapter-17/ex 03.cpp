#include <iostream>
#include <string>
using namespace std;

void to_lover(char* s) {
	int i = 0;
	while (s[i] != 0)
	{
		if (s[i] >= 65 && s[i] <= 90)  // >= 'A'   <= 'Z'
			s[i] += 32;     // += 'a' - 'A'
		++i;
	}
}

int main()
{
	string str = "HelLo, WOrlD!";
	to_lover(&str[0]);
	cout << str << endl;
}