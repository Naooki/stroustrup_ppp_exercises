#include <iostream>
#include <sstream>

using namespace std;


int ptr_to_int(void* ptr)
{
	stringstream ss;
	ss << ptr;
	int result;
	ss >> hex >> result;
	return result;
}


int main()
{
	int* p1 = new int(10);
	double* p2 = new double(10.1);
	bool* p3 = new bool(true);
	char* p4 = new char('a');

	cout << "Size of int is:" << ptr_to_int(&p1[1]) - ptr_to_int(&p1[0]) << "   and with sizeof(int): "<< sizeof(int) << endl;
	cout << "Size of double is:" << ptr_to_int(&p2[1]) - ptr_to_int(&p2[0]) << "   and with sizeof(double): " << sizeof(double) << endl;
	cout << "Size of bool is:" << ptr_to_int(&p3[1]) - ptr_to_int(&p3[0]) << "   and with sizeof(bool): " << sizeof(bool) << endl;
	cout << "Size of char is:" << ptr_to_int(&p4[1]) - ptr_to_int(&p4[0]) << "   and with sizeof(char): " << sizeof(char) << endl;
	
	cout << "And sizeof(char*) is: " << sizeof(p4) << endl;
}