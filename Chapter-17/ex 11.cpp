#include <string>
#include <iostream>

using namespace std;

//doubly-linked list (actually I did it while reading the chapter but, okay) Practice makes perfect)
class Link {
public:
	string value;

	Link(string str, Link* prv = nullptr, Link* nxt = nullptr)
		:value(str), prev_link(prv), next_link(nxt) {}
	Link* insert(Link* n);
	Link* add(Link* n);
	Link* erase();

	Link* advance(int n) const;

	Link* find(const string& s);
	const Link* find(const string& s) const;

	
	Link* previous() const { return prev_link; }
	Link* next() const { return next_link; }
private:
	Link* next_link;	//successor
	Link* prev_link;	//predecessor
};

Link* Link::insert(Link* n) {
	if (this == nullptr) return n;
	if (n == nullptr) return this;
	n->next_link = this;
	if (prev_link)
	{
		prev_link->next_link = n;
		n->prev_link = prev_link;
	}
	prev_link = n;
	return n;
}
Link* Link::add(Link* n) {
	if (this == nullptr) return n;
	if (n == nullptr) return this;
	n->prev_link = this;
	if (next_link)
	{
		next_link->prev_link = n;
		n->next_link = next_link;
	}
	next_link = n;
	return n;
}
Link* Link::erase() {
	if (this == nullptr) return nullptr;
	if (next_link) next_link->prev_link = prev_link;
	if (prev_link) prev_link->next_link = next_link;
	return next_link;  // what if next_link would be a nullptr (erased link was the last in a list)?
}
Link* Link::advance(int n) const {  //stroustrup offers us to use const function...
	if (this == nullptr) return nullptr;
	Link* p_new = const_cast<Link*>(this);  //I don't know other way how to implement it with const
	//const Link* p_new = this;				// it would work but in the book this function returns NOT constant pointer
	while (n != 0)
	{
		if (n > 0)
		{
			if (p_new == nullptr) return nullptr;
			p_new = p_new->next_link;
			--n;
		}
		if (n < 0)
		{
			p_new = p_new->prev_link;
			if (p_new == nullptr) return nullptr;
			++n;
		}
	}
	return p_new;
}

Link* Link::find(const string& s) {  //returns nullptr for "not found"
	if (this == nullptr) return nullptr;
	Link* p = this;
	while (p != nullptr)
	{
		if (p->value == s) return p;
		p = p->next_link;
	}
	return nullptr;
}

const Link* Link::find(const string& s) const {
	if (this == nullptr) return nullptr;
	const Link* p = this;
	while (p != nullptr)
	{
		if (p->value == s) return p;
		p = p->next_link;
	}
	return nullptr;
}


void print_all(Link* p) {
	cout << "{ ";
	while (p)
	{
		cout << p->value;
		if (p = p->next()) cout << ", ";
	}
	cout << " }";
}


int main()
{
	Link* norse_gods = new Link("Thor");
	norse_gods = norse_gods->insert(new Link("Odin"));
	norse_gods = norse_gods->insert(new Link("Zeus"));
	norse_gods = norse_gods->insert(new Link("Freya"));

	Link* greek_gods = new Link("Hera");
	greek_gods = greek_gods->insert(new Link("Athena"));
	greek_gods = greek_gods->insert(new Link("Mars"));
	greek_gods = greek_gods->insert(new Link("Poseidon"));

	cout << "Before correction:\n";
	print_all(norse_gods);
	cout << '\n';
	print_all(greek_gods);
	cout << '\n';

	Link* p1 = norse_gods->find("Zeus");
	if (p1)
	{
		if (p1 == norse_gods) norse_gods = norse_gods->next();  //both ponters point to one object, so if we erase one pointer from the list
																// and insert it into anoter list, then using 2nd pointer we will manipulate
																// with second list too. Pointers are "funny"...
		p1->erase();
		greek_gods = greek_gods->insert(p1);
	}

	Link* p2 = greek_gods->find("Mars");
	if (p2) p2->value = "Ares";

	cout << "After correction:\n";
	print_all(norse_gods);
	cout << '\n';
	print_all(greek_gods);
	cout << '\n';
}