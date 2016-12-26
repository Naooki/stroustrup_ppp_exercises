#include <iostream>
#include <vector>
using namespace std;

void print_array10(ostream& os, int* a) {
	for (int i = 0; i < 10; ++i)
		os << a[i] << ' ';
}
void print_array(ostream& os, int* a, int n) {
	for (int i = 0; i < n; ++i)
		os << a[i] << ' ';
}
void print_vector(ostream& os, vector<int>& v) {
	for (int el : v)
		os << el << ' ';
}

int main() {
	int* parray = new int[10];
	cout << "Array: " << endl;
	for (int i = 0; i < 10; ++i)
		cout << parray[i] << endl;
	cout << "-----------------" << endl;
	delete[] parray;

	int* pinitarray10 = new int[10] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
	print_array10(cout, pinitarray10);
	cout << "\n-----------------" << endl;
	delete[] pinitarray10;

	int* pinitarray11 = new int[11] { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109,110 };
	print_array10(cout, pinitarray11);
	cout << pinitarray11[10];
	cout << "\n-----------------" << endl;
	delete[] pinitarray11;


	int* pinitarray20 = new int[20]{ 100, 101, 102, 103, 104, 105, 106, 107, 108, 109
									,110, 111, 112, 113, 114, 115, 116, 117, 118, 119 };
	print_array(cout, pinitarray20, 20);
	cout << "\n-----------------" << endl;
	delete[] pinitarray20;

	vector<int> v10(10);
	print_vector(cout, v10);
	cout << "\n-----------------" << endl;

	vector<int> v11(11);
	print_vector(cout, v11);
	cout << "\n-----------------" << endl;
	
	vector<int> v20(20);
	print_vector(cout, v20);
	cout << "\n-----------------" << endl;


	cout << "\n\n\n Part 2: \n";  //part 2 of the drill

	int* p1 = new int(7);
	cout << "Pointer p1 is:" << p1 << "   Value it points to:" << *p1 << endl;
	cout << "\n-----------------" << endl;

	
	int* p2 = new int[7] {1, 2, 4, 8, 16, 32, 64};
	cout << "Array p2: pointer:" << p2 << endl;
	for(int i = 0; i < 7; ++i)
		cout << "Pointer is:" << &p2[i] << "   Value it points to:" << p2[i] << endl;  // every step +4 in address (4 bytes, I guess)
	cout << "\n-----------------" << endl;

	int* p3 = p2;   // so yeah, p3 now points at the exactly same address in heap, and because of the same type(int) we can 
					// get elements of the array just my by 4 bytes in address(sizeof(int));
	cout << "Array p3: pointer:" << p3 << endl;
	for (int i = 0; i < 7; ++i)
		cout << "Pointer is:" << &p3[i] << "   Value it points to:" << p3[i] << endl;
	cout << "\n-----------------" << endl;


	p2 = p1;
	cout << "Array p2: pointer:" << p2 << endl;  //we have only this value(7) at address it points to. It's not an array...
	for (int i = 0; i < 7; ++i)
		cout << "Pointer is:" << &p2[i] << "   Value it points to:" << p2[i] << endl;  
	cout << "\n-----------------" << endl;


	p2 = p3;
	cout << "Array p2: pointer:" << p2 << endl;  // p3 was initialised at first with pointer p2, which was an array at that point,
												 // so now we just restore the inital value of p2...
	for (int i = 0; i < 7; ++i)
		cout << "Pointer is:" << &p2[i] << "   Value it points to:" << p2[i] << endl;
	cout << "\n-----------------" << endl;

	
	
	cout << "Array p1: pointer:" << p1 << endl; // print p1 also...
	for (int i = 0; i < 7; ++i)
		cout << "Pointer is:" << &p1[i] << "   Value it points to:" << p1[i] << endl;
	cout << "\n-----------------" << endl;

	delete p1;
	delete[] p2;


	p1 = new int[10]{ 1,2,4,8,16,32,64,128,256,512 };
	p2 = new int[10];
	for (int i = 0; i < 10; ++i)
	{
		p2[i] = p1[i];
		cout << p2[i] << ' ';
	}
	cout << "\n-----------------" << endl;


	vector<int> v1{ 1,2,4,8,16,32,64,128,256,512 };
	vector<int> v2(10);
	for (int i = 0; i < 10; ++i)
	{
		v2[i] = v1[i];
		cout << v2[i] << ' ';
	}
	cout << "\n-----------------" << endl;

}