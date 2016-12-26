#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str;
	char ch;
	while (cin >> ch && ch != '!')
	{
		str.push_back(ch);    //Mmm... Rly?
		cout << str << endl;
	}
}