#include "../../../../libs/std_lib_facilities.h"


enum class CharType { isspace, isalpha, isdigit, isxdigit, isupper, islower, isalnum, iscntrl, ispunct, isprint, isgraph };

int main()
{
	cout << "Input file name: ";
	string file_name;
	cin >> file_name;

	ifstream ifs{ file_name };
	
	vector<int> nums(11);
	for (char ch; ifs.get(ch);)
	{
		if (isspace(ch)) ++nums[int(CharType::isspace)];
		if (isalpha(ch)) ++nums[int(CharType::isalpha)];
		if (isdigit(ch)) ++nums[int(CharType::isdigit)];
		if (isxdigit(ch)) ++nums[int(CharType::isxdigit)];
		if (isupper(ch)) ++nums[int(CharType::isupper)];
		if (islower(ch)) ++nums[int(CharType::islower)];
		if (isalnum(ch)) ++nums[int(CharType::isalnum)];
		if (iscntrl(ch)) ++nums[int(CharType::iscntrl)];
		if (ispunct(ch)) ++nums[int(CharType::ispunct)];
		if (isprint(ch)) ++nums[int(CharType::isprint)];
		if (isgraph(ch)) ++nums[int(CharType::isgraph)];
	}
	cout << "The number of isspace chars: " << nums[0] << endl;
	cout << "The number of isalpha chars: " << nums[1] << endl;
	cout << "The number of isdigit chars: " << nums[2] << endl;
	cout << "The number of isxdigit chars: " << nums[3] << endl;
	cout << "The number of isupper chars: " << nums[4] << endl;
	cout << "The number of islower chars: " << nums[5] << endl;
	cout << "The number of isalnum chars: " << nums[6] << endl;
	cout << "The number of iscntrl chars: " << nums[7] << endl;
	cout << "The number of ispunct chars: " << nums[8] << endl;
	cout << "The number of isprint chars: " << nums[9] << endl;
	cout << "The number of isgraph chars: " << nums[10] << endl;
}