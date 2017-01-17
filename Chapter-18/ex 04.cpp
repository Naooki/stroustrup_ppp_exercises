//test things
#include <iostream>
using namespace std;

namespace c_str_ns
{
	char* strdup(const char* c_str) {
		if (!c_str) return nullptr;
		const char* p = c_str;
		int size = 0;
		while (*p++) ++size;

		char* res = new char[size + 1]; //c-str needs 0
		char* res_index = res;
		for (res_index; res_index < res + size + 1; ++res_index)
		{
			*res_index = *c_str;
			++c_str;
		}
		return res;
	}

	//nice Bewuethr's solution (much shorter...)
	char* findx(const char* s, const char* x) //I just got the idea and try to reimplement it
	{
		if (s == nullptr || !*s) return nullptr;
		if (x == nullptr || !*x) return const_cast<char*>(s);

		for (int j = 0; *(s + j); ++j) // basically, it just uses fors instead of whiles
		{
			if (*(s + j) == *x)
			{
				bool is_equal = true;
				for (int i = 0; *(x + i); ++i)
				{
					if (!(s + j + i)) return nullptr; //the end of the s
					if (*(s + j + i) != *(x + i))
					{
						is_equal = false;
						break;
					}
				}
				if (is_equal) return const_cast<char*>(s + j);
			}
		}
		return nullptr;
	}

	int strcmp(const char* a, const char* b)
	{
		while (true)
		{
			if (*a < *b) return 1;
			else if (*a > *b) return -1;
			if (*a == 0 || *b == 0) break;
			++a;
			++b;
		}
		return 0;
	}
}

int main()
{
	cout << "--------- strdup() ---------\n";
	cout << "Strings on the stack:\n";
	char fake_c_str[] = { 'a', 'b', 'c' };
	char real_c_str[] = { 'a', 'b', 'c', 0 };
	char* p = c_str_ns::strdup(fake_c_str);
	cout << p << endl;
	delete[] p;
	p = c_str_ns::strdup(real_c_str);
	cout << p << endl;
	delete[] p;
	cout << "Strings on the heap(free store):\n";
	char* fake_c_str_ptr = new char[3]{ 'a', 'b', 'c' };
	char* real_c_str_ptr = new char[4] { 'a', 'b', 'c', 0 };
	p = c_str_ns::strdup(fake_c_str_ptr);
	cout << p << endl;
	delete[] p;
	p = c_str_ns::strdup(real_c_str_ptr);
	cout << p << endl;
	delete[] p;
	delete[] fake_c_str_ptr;
	delete[] real_c_str_ptr;
	cout << "--------- --------- ---------\n\n\n";

	/*											//this code doesn't work, no wonder actually
	cout << "--------- findx() ---------\n";
	cout << "Strings on the stack:\n";
	char fake_c_str1[] = { 'a', 'b', 'c' };
	char fake_c_str2[] = { 'b', 'c' };
	char* pp = c_str_ns::findx(fake_c_str1, fake_c_str2);
	cout << pp << endl;
	cout << "Strings on the heap(free store):\n";
	char* fake_c_str_ptr1 = new char[3]{ 'a', 'b', 'c' };
	char* fake_c_str_ptr2 = new char[3]{ 'b', 'c' };
	pp = c_str_ns::findx(fake_c_str_ptr1, fake_c_str_ptr2);
	cout << pp << endl;
	delete[] fake_c_str_ptr1;
	delete[] fake_c_str_ptr2;
	cout << "--------- --------- ---------\n";
	*/

	cout << "--------- strcmp() ---------\n";
	cout << "Strings on the stack:\n";
	char fake_c_str3[] = { 'a', 'b', 'c', 'd' };
	char fake_c_str4[] = { 'a', 'b', 'c', 'd' };
	cout << c_str_ns::strcmp(fake_c_str3, fake_c_str4) << endl;
	cout << "Strings on the heap(free store):\n";
	char* fake_c_str_ptr3 = new char[4]{ 'a', 'b', 'c', 'd' };
	char* fake_c_str_ptr4 = new char[4]{ 'a', 'b', 'c', 'd' };
	cout << c_str_ns::strcmp(fake_c_str_ptr3, fake_c_str_ptr4) << endl;  // in case when strings are the same results are wrong
	delete[] fake_c_str_ptr3;
	delete[] fake_c_str_ptr4;
	cout << "--------- --------- ---------\n\n\n";
}