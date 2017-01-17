#include <string>
#include <iostream>
using namespace std;

class File_Exc 
{
	string text;
public:
	File_Exc(string description)
		:text(description) {}

	string what() { return "Exception: " + text; }
};

class File_handle
{
	FILE* file;
	string name;

public:
	File_handle(const string& fname, const string& fmode);
	~File_handle();
	FILE* handled_file() { return file; }
};

File_handle::File_handle(const string& fname, const string& fmode)
	:file(nullptr),name(fname)
{
	file = fopen(fname.c_str(), fmode.c_str());
	if (!file) throw File_Exc("File opening problem.");
	cout << "File has been opened!\n";
}
File_handle::~File_handle()
{
	if (fclose(file)) throw File_Exc("File closing problem.");
	cout << "File has been closed!\n";
}

int main()
try
{
	string name = "test.txt";
	File_handle fhandle(name, "w");
	cout << "Enter a line to input into the file:\n";
	string input;
	getline(cin, input);
	fwrite(input.c_str(), sizeof(char), input.size(), fhandle.handled_file());
	return 0;
}
catch (File_Exc e)
{
	cerr << e.what() << endl;
	return 1;
}
catch (...)
{
	cerr << "exception!\n";
	return 2;
}