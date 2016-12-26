#include <iostream>

using namespace std;

int main()
{
	bool a, b, c;
	bool* pa = &a;
	bool* pb = &b;
	bool* pc = &c;
	cout << "Pointer pa: " << pa << endl;
	cout << "Pointer pb: " << pb << endl;
	cout << "Pointer pc: " << pc << endl;  // stack grows down (toward lower addresses)
	//it reserves 4 bytes for every bool instead of 1 byte...
	cout << "----------------------------------\n";

	bool* pda = new bool;
	bool* pdb = new bool;
	bool* pdc = new bool;
	cout << "Pointer pda: " << pda << endl;
	cout << "Pointer pdb: " << pdb << endl;
	cout << "Pointer pdc: " << pdc << endl;  // stack grows down (toward lower addresses)
	//It seems like it finds any sufficient piece of heap and puts its there(the addresses order is not consistent)

	cout << "----------------------------------\n";

	bool* p_array = new bool[20];
	for (int i = 0; i < 20; ++i)
		cout << "Pointer p_arr[" << i << "] is: " << &p_array[i] << endl; //in array poiters grow up(toward upper addresses)

}