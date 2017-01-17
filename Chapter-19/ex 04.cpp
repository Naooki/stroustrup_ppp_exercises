#include <iostream>

using namespace std;

template<typename T>
struct Link
{
	T value;
	Link* prev; //predecessor
	Link* succ; //successor
	Link(const T& v, Link* p = nullptr, Link* s = nullptr)
		:value(v), prev(p), succ(s) {}
};

template<typename T>
Link<T>* insert(Link<T>* p, Link<T>* n) //inserts n before p
{
	if (n == nullptr) return p;
	if (p == nullptr) return n;
	if (p->prev) p->prev->succ = n;
	n->prev = p->prev;
	n->succ = p;
	p->prev = n;
	return n;
}


int main()
{
	Link<string>* ng = new Link<string>("Odin");
	ng = insert(ng, new Link<string>("Freya"));
	ng = insert(ng, new Link<string>("Thor"));

}