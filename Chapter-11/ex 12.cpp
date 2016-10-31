/*
Okay, so here I have a bug: in input like "ab/n  cd" some 1 character just goes nowhere...

Here is a discussion about an issue:
http://www.cplusplus.com/forum/general/120661/
*/


#include "../../../../libs/std_lib_facilities.h"

int main()
try
{
	cout << "Input file name: ";
	string file_name;
	cin >> file_name;
	fstream fs{ file_name };
	char ch_begin;
	char ch_end;
	int length = 0;
	string line;
	for (char ch; fs.get(ch);)
		++length;
	fs.clear();

	for (int i = 0; i<length/2; ++i)
	{
		fs.seekg(i, ios::beg);
		fs.get(ch_begin);
		fs.seekg(-i-1, ios::end);
		fs.get(ch_end);
		fs.seekp(i, ios::beg);
		fs << ch_end;
		fs.seekp(-i-1, ios::end);
		fs << ch_begin;

		fs.seekg(i, ios::beg);
	}
	cout << "Done!" << endl;
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "Exception!" << endl;
}
