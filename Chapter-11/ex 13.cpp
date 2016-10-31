#include "../../../../libs/std_lib_facilities.h"

int main()
try
{
	string file_name;
	cin >> file_name;
	ifstream ifs{file_name};
	vector<string> buffer;

	
	for (string word; ifs >> word;)
		buffer.push_back(word);


	ofstream ofs{ file_name };
	while (buffer.size() != 0)
	{
		ofs << buffer.back() << endl;
		buffer.pop_back();
	}
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "Exception!" << endl;
}