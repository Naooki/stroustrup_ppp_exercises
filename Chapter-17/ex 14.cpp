#include <iostream>
#include <string>
using namespace std;

struct God {
	God(string n, string m, string v, string w)
		:name(n), mythology(m), vehicle(v), weapon(w) {}
	string name;
	string mythology;
	string vehicle;
	string weapon;
};


class Singly_Linked_List;
//singly-linked list
class Link {
public:
	Link(string god_name, string god_mythology, string god_vehicle, string god_weapon, Link* nxt = nullptr)
		:god(god_name, god_mythology, god_vehicle, god_weapon),
		 next_link(nxt) {}

	//Adds Link before cuorrent. Returns its pointer.
	Link* insert(Singly_Linked_List& l, Link* n);
	//Adds Link after current. Returns its pointer.
	Link* add(Link* n);
	//Adds Link in it's correct lexicographical position. Returns its pointer.
	Link* add_ordered(Singly_Linked_List& l, Link* n);
	//Removes current link from the list. Returns the next link;
	Link* erase(Singly_Linked_List& l);
	//Moves by n links. (-n to move left)
	Link* advance(Singly_Linked_List& l, int n);
	//Finds Link with name s. Returns it.
	Link* find(Singly_Linked_List& l, const string& s);
	//Finds Link with name s. Returns constant link.
	const Link* find(Singly_Linked_List& l, const string& s) const;

	Link* next() const { return next_link; }
	/*Link* previous(Singly_Linked_List& l) const
	{
		Link* p = l.first_link;
		if (p == this) return nullptr;
		while (p->next_link != this) p = p->next_link;
		return p;
	}*/

	God god;
private:
	Link* next_link;	//successor
};

class Singly_Linked_List {  //just contains the pointer of the first link of a list
public:
	Singly_Linked_List()
		:first_link(nullptr) {}
	Singly_Linked_List(Link* first)
		:first_link(first) {}
	
	Link* first_link;
};
Link* Link::insert(Singly_Linked_List& l, Link* n) { //We can't get the previous link, so we have to use pointer to the first list element to find previous;
	if (this == nullptr)
	{
		n->next_link = nullptr;
		return n;
	}
	if (n == nullptr) return this;
	Link* prev = l.first_link;
	if (prev == this)
	{
		n->next_link = l.first_link;
		l.first_link = n;
		return n;
	}
	while (prev->next_link != this) prev = prev->next_link; //because we have to find prev every time from the very beginning, the complexity of insert is O(n)
	n->next_link = this;
	prev->next_link = n;
	return n;
}
Link* Link::add(Link* n) {
	if (this == nullptr)
	{
		n->next_link = nullptr;
		return n;
	}
	if (n == nullptr) return this;
	n->next_link = this->next_link;
	this->next_link = n;
	return n;
}
Link* Link::add_ordered(Singly_Linked_List& l, Link* n) {
	if (this == nullptr)
	{
		n->next_link = nullptr;
		return n;
	}
	if (n == nullptr) return this;
	Link* p = l.first_link;
	while (p != nullptr)
	{
		if (n->god.name < p->god.name)
		{
			return p->insert(l, n);
		}
		p = p->next_link;
	}
}
Link* Link::erase(Singly_Linked_List& l)
{
	if (this == nullptr) return nullptr;
	Link* prev = l.first_link;
	if (prev == this)
	{
		l.first_link = nullptr;
		return nullptr;
	}
	while (prev->next_link != this) prev = prev->next_link;
	prev->next_link = this->next_link;
	return next_link;
}
Link* Link::advance(Singly_Linked_List& l, int n)
{
	if (this == nullptr) return nullptr;
	int index = 0;
	Link* p = l.first_link;
	while (p != this)
	{
		p = p->next_link;
		++index;
	}
	index += n;
	p = l.first_link;
	for (int i = 0; i < index; ++i)
	{
		p = p->next_link;
		if (p == nullptr) return nullptr;
	}
	return p;
}
Link* Link::find(Singly_Linked_List& l, const string& s)
{
	if (this == nullptr) return nullptr;
	Link* p = l.first_link;
	while (p->god.name != s)
	{
		p = p->next_link;
		if (p == nullptr) return nullptr;;
	}
	return p;
}
const Link* Link::find(Singly_Linked_List& l, const string& s) const
{
	if (this == nullptr) return nullptr;
	const Link* p = l.first_link;
	while (p->god.name != s)
	{
		p = p->next_link;
		if (p == nullptr) return nullptr;;
	}
	return p;
}

void print(Link* p)
{
	cout << "{ ";
	while (p != nullptr)
	{
		cout << '\"' << p->god.name << '\"';
		p = p->next();
		if (p != nullptr) cout << ", ";
	}
	cout << " }";
}

int main() {
	Link* norse_gods = new Link("Thor", "Norse", "", "");
	Singly_Linked_List norse_list(norse_gods);
	norse_gods = norse_gods->insert(norse_list, new Link("Odin", "Norse", "", ""));
	norse_gods = norse_gods->insert(norse_list, new Link("Zeus", "Greek", "", ""));
	norse_gods = norse_gods->insert(norse_list, new Link("Freya", "Norse", "", ""));

	Link* greek_gods = new Link("Hera", "Greek", "", "");
	Singly_Linked_List greek_list(greek_gods);
	greek_gods = greek_gods->insert(greek_list, new Link("Athena", "Greek", "", ""));
	greek_gods = greek_gods->insert(greek_list, new Link("Mars", "Greek", "", ""));
	greek_gods = greek_gods->insert(greek_list, new Link("Poseidon", "Greek", "", ""));


	cout << "Before correction:\n";
	print(norse_gods);
	cout << '\n';
	print(greek_gods);
	cout << '\n';
	cout << "-------------------------------------------------------\n";
	Link* zeus = norse_gods->find(norse_list, "Zeus");
	if (zeus != nullptr)
	{
		zeus->erase(norse_list);
		greek_gods = greek_gods->insert(greek_list, zeus);
	}
	Link* mars = greek_gods->find(greek_list, "Mars");
	if (mars != nullptr) mars->god.name = "Ares";
	cout << "After correction:\n";
	print(norse_gods);
	cout << '\n';
	print(greek_gods);
	cout << '\n';
}