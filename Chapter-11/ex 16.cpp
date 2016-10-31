#include "../../../../libs/std_lib_facilities.h"

int main()
try
{
	vector<int> nums;

	cout << "Input file name: ";
	string input_file;
	cin >> input_file;
	
	ifstream ifs{ input_file };
	if (!ifs) error("Unable to open input file!");

	for (int num; ifs >> num;)
		nums.push_back(num);
	sort(nums);

	int repeats = 1;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (i == 0 || nums[i] != nums[i - 1])
		{
			if (repeats > 1) cout << ' ' << repeats;
			cout << endl;
			repeats = 1;
			cout << nums[i];
		}
		else ++repeats;
	}
	if (repeats > 1) cout << ' ' << repeats << endl;
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "Exception!" << endl;
}