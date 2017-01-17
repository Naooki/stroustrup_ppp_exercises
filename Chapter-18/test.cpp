#include <iostream>
using namespace std;
namespace reimplemented
{
	char* strdup(const char* c_str, int n_max) {
		if (!c_str) return nullptr;
		const char* p = c_str;
		int size = 0;
		while (*p++)
		{
			if (size == n_max) break;
			++size;
		}

		char* res = new char[size + 1]; //c-str needs 0
		char* res_index = res;
		for (res_index; res_index < res + size; ++res_index)
		{
			*res_index = *c_str;
			++c_str;
		}
		*res_index = 0;
		return res;
	}
}
int main()
{
	char* fake_c_str_ptr5 = new char[3]{ 'a', 'b', 'c' };
	char* p1 = reimplemented::strdup(fake_c_str_ptr5, 3);
	cout << p1 << endl;
	return 0;
}