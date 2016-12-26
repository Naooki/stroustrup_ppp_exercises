#include <iostream>

using namespace std;

int main() {
	int v_int;
	int* p1 = &v_int;
	cout << p1 << endl;

	double v_double;
	double* p2 = &v_double;
	cout << p2 << endl;

	char v_char;
	char* p3 = &v_char;
	cout << p3 << endl;

	bool v_bool;
	bool* p4 = &v_bool;
	cout << p4 << endl;

	cout << "------------\n";
	// 1
	cout << "Output format of a pointer:\n";
	int* pi = new int(0);
	cout << "int* pi is " << pi << "\n";
	cout << "&*pi is " << &*pi << "\n";
	cout << "&pi[1] is " << &pi[1] << "\n";
	delete pi;
}	