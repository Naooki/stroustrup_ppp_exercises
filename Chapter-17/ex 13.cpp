#include <string>
#include <iostream>

using namespace std;


struct God {
	God(string n, string m, string v, string w)
		:name(n), mythology(m), vehicle(v), weapon(w) {}
	string name;
	string mythology;
	string vehicle;
	string weapon;
};

class Link {
public:
	God god;

	Link(string god_name, string god_mythology, string god_vehicle, string god_weapon, Link* prv = nullptr, Link* nxt = nullptr)
		:god(god_name, god_mythology, god_vehicle, god_weapon),
		 prev_link(prv), next_link(nxt) {}

	Link* insert(Link* n);
	Link* add(Link* n);
	Link* add_ordered(Link* n);

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
	if (this == nullptr)
	{
		n->prev_link = nullptr;
		n->next_link = nullptr;
		return n;
	}
	if (n == nullptr) return this;
	n->next_link = this;
	if (prev_link)
	{
		prev_link->next_link = n;
	}
	n->prev_link = prev_link; //!!!!!!!!!!!!!!!
	prev_link = n;
	return n;
}
Link* Link::add(Link* n) {
	if (this == nullptr)
	{
		n->prev_link = nullptr;
		n->next_link = nullptr;
		return n;
	}
	if (n == nullptr) return this;
	n->prev_link = this;
	if (next_link)
	{
		next_link->prev_link = n;
	}
	n->next_link = next_link; // ITS OBLIGATORY, n->next_link should get next_link EVEN IF ITS NULLPTR,
							  // cause if n initialy had any nead_next, we should change it! 
	next_link = n;
	return n;
}
//add in correct orded; Moves to the very first link in a list;
Link* Link::add_ordered(Link* n) {  //looks bad((
	if (this == nullptr)
	{
		n->next_link = nullptr;
		n->prev_link = nullptr;
		return n;
	}
	if (n == nullptr) return this;
	Link* p = this;
	if (n->god.name < p->god.name)
	{
		while (n->god.name < p->god.name)
		{
			if (p->prev_link == nullptr)
			{
				p->insert(n);
				return n;
			}
			p = p->prev_link;
		}
		p->add(n);
		while (p->prev_link != nullptr) p = p->prev_link;
		return p;
	}
	else
	{
		while (n->god.name > p->god.name)
		{
			if (p->next_link == nullptr)
			{
				p->add(n);
				while (p->prev_link != nullptr) p = p->prev_link;
				return p;
			}
			p = p->next_link;
		}
		p->insert(n);
		while (p->prev_link != nullptr) p = p->prev_link;
		return p;
	}
}
Link* Link::erase() {
	if (this == nullptr) return nullptr;
	if (next_link) next_link->prev_link = prev_link;
	if (prev_link) prev_link->next_link = next_link;
	return next_link; 
}
Link* Link::advance(int n) const {  
	if (this == nullptr) return nullptr;
	Link* p_new = const_cast<Link*>(this);  
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

Link* Link::find(const string& s) {  
	if (this == nullptr) return nullptr;
	Link* p = this;
	while (p != nullptr)
	{
		if (p->god.name == s) return p;
		p = p->next_link;
	}
	return nullptr;
}

const Link* Link::find(const string& s) const {
	if (this == nullptr) return nullptr;
	const Link* p = this;
	while (p != nullptr)
	{
		if (p->god.name == s) return p;
		p = p->next_link;
	}
	return nullptr;
}


void print_all(Link* p) {
	cout << "[ ";
	while (p)
	{
		cout << "God{\"" << p->god.name << "\", \"" << p->god.mythology
			<< "\", \"" << p->god.vehicle << "\", \"" << p->god.weapon << "\"}";
		if (p = p->next()) cout << ",\n  ";
	}
	cout << " ]";
}

Link* gods_to_myth(Link* from, string myth, Link* to) {	//Searches gods by myth and move them
	while (from->previous() != nullptr) from = from->previous();  // go to the beginning of a list
	while (from != nullptr)
	{
		if (from->god.mythology == myth)
		{
			Link* buff = from->next();
			from->erase();							//we need to erase the link from the list at first...
			to = to->add_ordered(from);
			from = buff;
		}
		else from = from->next();
	}
	return to;
}



int main()
{
	Link* all_gods = new Link("Thor", "Norse", "Pinzgauer", "Hammer");
	all_gods = all_gods->insert(new Link("Odin", "Norse", "Eight-legged horse", ""));
	all_gods = all_gods->insert(new Link("Zeus", "Greek", "", "Lightning"));
	all_gods = all_gods->insert(new Link("Freia", "Norse", "F-transport", "F-weapon"));
	all_gods = all_gods->insert(new Link("Hera", "Greek", "H-transport", "Spear"));
	all_gods = all_gods->insert(new Link("Athena", "Greek", "A-transport", "A-weapon"));
	all_gods = all_gods->insert(new Link("Mars", "Roman", "M-transport", "M-weapon"));
	all_gods = all_gods->insert(new Link("Poseidon", "Greek", "Seahorse", "Trident"));
	all_gods = all_gods->insert(new Link("Ares", "Greek", "A-transport", "A-weapon"));
	all_gods = all_gods->insert(new Link("Vesuvius", "Roman", "V-transport", "Volcano"));
	all_gods = all_gods->insert(new Link("Bacchus", "Roman", "Stretcher", "Wine goblet"));
	print_all(all_gods);

	cout << "\n--------------------------------------------------------\n";


	Link* norse_gods = nullptr;
	norse_gods = gods_to_myth(all_gods, "Norse", norse_gods);
	Link* greek_gods = nullptr;
	greek_gods = gods_to_myth(all_gods, "Greek", greek_gods);
	Link* roman_gods = nullptr;
	roman_gods = gods_to_myth(all_gods, "Roman", roman_gods);
	cout << "\nNorse gods:\n";
	print_all(norse_gods);
	cout << "\nGreek gods:\n";
	print_all(greek_gods);
	cout << "\nRoman gods:\n";
	print_all(roman_gods);

	all_gods = nullptr; //cuase it still points to "Bacchus" which is now in the beginning of "roman_gods"
	
	cout << "\n\nWhat left in the all_gods: \n";
	print_all(all_gods);
	cout << "\n";
}