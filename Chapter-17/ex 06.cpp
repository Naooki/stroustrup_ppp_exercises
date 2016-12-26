#include <iostream>

using namespace std;

int main()
{
	int i = 0;
	while (true)
	{
		cout << ++i << "MB used... \n";
		double* p = new double[131072];   
		*p = i;
		// Okay, so when I run this program it used 1894Mb of memory and then just thrown std::bad_alloc exception.
		// But the sulution platform of the project os x86, thus, as far as I'm concerned, it can use only 4096Mb for a single process.
		// I set up the x64 solution platform and ran the program :) After that my laptop just stopped for a minute.

		// So it seems like it new operator can devour pretty much all available memory)
	}
}