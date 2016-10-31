#include "../../../../libs/std_lib_facilities.h"

int main()
try
{
	cout << "Input file name: ";
	string input_file;
	cin >> input_file;

	ifstream ifs{ input_file };
	if (!ifs) error("Can't open input file!");
	ofstream ofs{ "output.txt" };
	if (!ofs) error("Can't open output file!");

	ofs << scientific << setprecision(8);

	int current_row = 1;
	for (double num; ifs >> num;)
	{
		ofs << setw(20) << num << '|';
		if (current_row == 4)
		{
			ofs << endl;
			current_row = 1;
		}
		++current_row;
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