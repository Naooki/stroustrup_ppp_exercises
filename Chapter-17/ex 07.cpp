#include <iostream>
using namespace std;


char* push_back(char* p, char ch) {
	int i = 0;
	while (p[i]) ++i;
	char* p_new = new char[i+2];
	for (int j = 0; p[j]; ++j)
	{
		p_new[j] = p[j];
	}
	p_new[i] = ch;
	p_new[i + 1] = 0;
	delete[] p;
	return p_new;
}

int main()
{
	char* p_ch = new char[1]{0};
	char ch;
	while (cin >> ch)
	{
		if (ch == '!') break;
		p_ch = push_back(p_ch,ch);
		cout << "Array is: " << p_ch << endl;
	}
}