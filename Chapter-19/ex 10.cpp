#include "my_vector.h"
#include <iostream>


template<typename T> class unique_ptr
{
	T* ptr;
public:
	unique_ptr(T* p)
		:ptr(p) {}
	T operator *() const { return *ptr; }
	T* operator ->() const { return ptr; }
	T* release()
	{
		T* temp = ptr;
		ptr = nullptr;
		return temp;
	}

	~unique_ptr() { delete ptr; } //delete calls destructors...
};

//------------------------------------------------------------------------------

// demonstrates how only destructor of object held by auto_pntr is called
naook::vector<int>* f()
{
	naook::vector<int>* p1 = new naook::vector<int>();          // destructor never called
	unique_ptr<naook::vector<int>> p2(new naook::vector<int>()); // destructor called when out of scope
	unique_ptr<naook::vector<int>> p3(new naook::vector<int>(5)); // released from auto_pntr
	return p3.release();
}

//------------------------------------------------------------------------------

// shows how auto_pntr destroys its object when an exception is thrown
class Oops {};
void f2()
{
	naook::vector<int>* p1 = new naook::vector<int>();
	unique_ptr<naook::vector<int>> p2(new naook::vector<int>());
	throw Oops();    // calls destructor of p2
	delete p1;              // never gets called
}

//------------------------------------------------------------------------------

int main()
try {
	naook::vector<int>* p = f();
	cout << "Dereference: " << (*p)[0] << "\n";
	cout << "Pointer access (size()): " << p->size() << "\n";
	delete p;

	f2();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
}
catch (...) {
	cerr << "exception\n";
}