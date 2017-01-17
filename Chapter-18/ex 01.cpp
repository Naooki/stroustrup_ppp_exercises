#include <iostream>
using namespace std;
namespace ex_01
{
	char* strdup(const char* c_str) {
		if (!c_str) return nullptr;
		const char* p = c_str;
		int size = 0;
		while (*p++) ++size;

		char* res = new char[size + 1]; //c-str needs 0
		char* res_index = res;
		for (res_index;  res_index < res + size + 1; ++res_index)
		{
			*res_index = *c_str;
			++c_str;
		}
		return res;
	}
}
int main() {
	char my_c_str[] = "zxc";
	char* p = ex_01::strdup(my_c_str);
	cout << "Result is: " << p << endl;
	delete[] p; //end of the program, actually. But okay, why not.
}