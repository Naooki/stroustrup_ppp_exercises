//static memory, stack, free storage(heap) memory allocation
#include <iostream>
using namespace std;

//static sotrage (global variables)
int a = 0;
int b = 0;
int c = 0;

void f() { //function loads in the function call stack, so...
	int a = 0;
	int b = 0;
	int c = 0;

	int* pa = &a;
	int* pb = &b;
	int* pc = &c;
	cout << "Stack variables addresses: a: " << pa << " b: " << pb << " c: " << pc << endl;
	//addresses are separated (the substraction (pc-pb) gives 12, not 4)
	if (pc > pb) cout << "Stack grows upwards.\n"; 
	else cout << "Stack grows downwards.\n"; //this one is correct...
	cout << "\n\n\n";
}

int main() {
	//static storage test;
	int* pa = &a;
	int* pb = &b;
	int* pc = &c;
	cout << "Static variables addresses: a: " << pa << " b: " << pb << " c: " << pc << endl;
	if (pc > pb) cout << "Static storage grows upwards.\n"; //this one is correct...
	else cout << "Static storage grows downwards.\n";
	cout << "\n\n\n";

	f(); //stack test;


	//free storage(heap)
	int* h_pa = new int(0);
	int* h_pb = new int(0);
	int* h_pc = new int(0);

	cout << "Static variables addresses: h_pa: " << h_pa << " h_pb: " << h_pb << " h_pc: " << h_pc << endl;
	cout << "It seems that allocator just finds suitable place with enough space. Cause sometimes pb can be > then pa but < then pc...";
	cout << "\n\n\n";

	//and array(free store)
	int* arr_hp = new int[3];
	cout << "Static variables addresses: arr_hp[1]: " << &arr_hp[0] << " arr_hp[1]: " << &arr_hp[1] << " arr_hp[2]: " << &arr_hp[2] << endl;
	if (pc > pb) cout << "Arrays on free store grows upwards.\n"; //this one is correct...
	else cout << "Static storage grows downwards.\n";
	cout << "\n\n\n";



}