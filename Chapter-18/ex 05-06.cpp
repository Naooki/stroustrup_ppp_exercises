#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string cat_dog(const string& s1, const string& s2, const string& separator) { 
	//... rly?
	stringstream ss;
	ss << s1 << separator << s2;
	return ss.str();
}

int main() {  //sizeof(string) == 28 byte, btw...
	cout << "Result:\n" << cat_dog("Hello", "World!", ", ") << endl;
}