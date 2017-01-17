//redesign and reimplement
#include <iostream>
using namespace std;

namespace reimplemented  //I think this code is HORRIBLE(as well as the code in main() - I'm too lazy to split it in nice functions :D)
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

	char* findx(const char* s, int s_max_len, const char* x, int x_max_len) {
		if (s == nullptr || *s == 0) return nullptr;
		if (x == nullptr || *x == 0) return const_cast<char*>(s);

		bool are_equal;
		for (int i = 0; i < s_max_len && *(s+i) != 0; ++i)
		{
			if (*(s+i) == *x)
			{
				are_equal = true;
				for (int j = 0; j < x_max_len && *(x+j) != 0; ++j)
				{
					if (i + j > s_max_len) return nullptr;
					if (*(s + i + j) != *(x + j))
					{
						are_equal = false;
						break;
					}
				}
				if (are_equal) return const_cast<char*>(s+i);
			}
		}
		return nullptr;
	}

	int strcmp(const char* a, int max_a_len, const char* b, int max_b_len)
	{
		if (a == nullptr) return -1;
		if (b == nullptr) return 1;
		int min = max_a_len < max_b_len ? max_a_len : max_b_len;
		for (int i = 0; i < min; ++i)
		{
			if (*a == 0 && *b == 0) return 0;
			if (*a > *b) return -1;
			if (*a < *b) return 1;
			++a;
			++b;
		}
		if (max_a_len > max_b_len) return -1;
		else if (max_a_len < max_b_len) return 1;
		else return 0;

	}
}

int main()
{
	cout << "--------- reimplemented strdup() ---------\n";
	cout << "Strings on the stack:\n";
	char fake_c_str1[] = { 'a', 'b', 'c' };
	char real_c_str1[] = { 'a', 'b', 'c', 0 };
	char* p1 = reimplemented::strdup(fake_c_str1, 3);
	cout << p1 << endl;
	delete[] p1;
	p1 = reimplemented::strdup(real_c_str1, 4);
	cout << p1 << endl;
	delete[] p1;
	cout << "Strings on the heap(free store):\n";
	char* fake_c_str_ptr1 = new char[3]{ 'a', 'b', 'c' };
	char* real_c_str_ptr1 = new char[4]{ 'a', 'b', 'c', 0 };
	p1 = reimplemented::strdup(fake_c_str_ptr1, 3);
	cout << p1 << '\n';
	delete[] p1;
	p1 = reimplemented::strdup(real_c_str_ptr1, 4);
	cout << p1 << endl; //interesting thing: I forgot to put indexes 5 and 6 to the following destructors, they erased same pointers twice.
						//But program crushed right after "cout << p1" line.
	delete[] p1;
	delete[] fake_c_str_ptr1;
	delete[] real_c_str_ptr1;
	cout << "--------- --------- ---------\n\n\n";



	cout << "--------- reimplemented findx() ---------\n";
	cout << "Strings on the stack:\n";
	char fake_c_str2[] = { 'a', 'b', 'c' };
	char fake_sub[] = { 'b', 'c' };
	char real_c_str2[] = { 'a', 'b', 'c', 0 };
	char real_sub[] = { 'b', 'c', 0 };

	char* p2 = reimplemented::findx(fake_c_str2, 3, fake_sub, 2); // this function correctly finds necessary pointer,
	//but because parameter strings can end up not with 0, returning pointer do nothing with it. It seems logical to me...
	cout << p2 << endl;
	p2 = reimplemented::findx(real_c_str2, 4, real_sub, 3);
	cout << p2 << endl;
	cout << "Strings on the heap(free store):\n";
	char* fake_c_str_ptr2 = new char[3]{ 'a', 'b', 'c' };
	char* fake_sub_ptr = new char[2]{ 'b', 'c' };
	char* real_c_str_ptr2 = new char[4]{ 'a', 'b', 'c', 0 };
	char* real_sub_ptr = new char[3]{ 'b', 'c', 0 };

	p2 = reimplemented::findx(fake_c_str_ptr2, 3, fake_sub_ptr, 2);
	cout << p2 << '\n';
	p2 = reimplemented::findx(real_c_str_ptr2, 4, real_sub_ptr, 3);
	cout << p2 << endl; 
	delete[] fake_c_str_ptr2;
	delete[] fake_sub_ptr;
	delete[] real_c_str_ptr2;
	delete[] real_sub_ptr;
	cout << "--------- --------- ---------\n\n\n";



	cout << "--------- reimplemented strcmp() ---------\n";
	cout << "Strings on the stack:\n";
	char fake1_c_str3[] = { 'a', 'b', 'c' };
	char fake2_c_str3[] = { 'a', 'b', 'c' };
	char real1_c_str3[] = { 'a', 'b', 'c', 0 };
	char real2_c_str3[] = { 'a', 'b', 'c', 0 };

	int res3 = reimplemented::strcmp(fake1_c_str3, 3, fake2_c_str3, 3);
	cout << res3 << endl;
	res3 = reimplemented::strcmp(real1_c_str3, 4, real2_c_str3, 4);
	cout << res3 << endl;
	cout << "Strings on the heap(free store):\n";
	char* fake1_c_str_ptr3 = new char[3]{ 'a', 'b', 'c' };
	char* fake2_c_str_ptr3 = new char[3]{ 'a', 'b', 'c' };
	char* real1_c_str_ptr3 = new char[4]{ 'a', 'b', 'c', 0 };
	char* real2_c_str_ptr3 = new char[4]{ 'a', 'b', 'c', 0 };

	res3 = reimplemented::strcmp(fake1_c_str_ptr3, 3, fake2_c_str_ptr3, 3);
	cout << res3 << endl;
	res3 = reimplemented::strcmp(real1_c_str_ptr3, 4, real2_c_str_ptr3, 4);
	cout << res3 << endl;
	delete[] fake1_c_str_ptr3;
	delete[] fake2_c_str_ptr3;
	delete[] real1_c_str_ptr3;
	delete[] real2_c_str_ptr3;
	cout << "--------- --------- ---------\n\n\n";


}