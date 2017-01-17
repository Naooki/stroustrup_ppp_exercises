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

template<typename T>
class Link {
public:
	T value;

	Link(const T& val , Link* prv = nullptr, Link* nxt = nullptr)
		:value(val), prev_link(prv), next_link(nxt) {}

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

template<typename T>
Link<T>* Link<T>::insert(Link<T>* n) {
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

template<typename T>
Link<T>* Link<T>::add(Link<T>* n) {
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
template<typename T>
Link<T>* Link<T>::add_ordered(Link<T>* n) {  //looks bad((
	if (this == nullptr)
	{
		n->next_link = nullptr;
		n->prev_link = nullptr;
		return n;
	}
	if (n == nullptr) return this;
	Link<T>* p = this;
	if (n->value.name < p->value.name)
	{
		while (n->value.name < p->value.name)
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
		while (n->value.name > p->value.name)
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

template<typename T>
Link<T>* Link<T>::erase() {
	if (this == nullptr) return nullptr;
	if (next_link) next_link->prev_link = prev_link;
	if (prev_link) prev_link->next_link = next_link;
	return next_link;
}

template<typename T>
Link<T>* Link<T>::advance(int n) const {
	if (this == nullptr) return nullptr;
	Link<T>* p_new = const_cast<Link<T>*>(this);
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

template<typename T>
Link<T>* Link<T>::find(const string& str) {
	if (this == nullptr) return nullptr;
	Link<T>* p = this;
	while (p != nullptr)
	{
		if (p->value.name == str) return p;
		p = p->next_link;
	}
	return nullptr;
}

template<typename T>
const Link<T>* Link<T>::find(const string& str) const {
	if (this == nullptr) return nullptr;
	const Link<T>* p = this;
	while (p != nullptr)
	{
		if (p->value.name == str) return p;
		p = p->next_link;
	}
	return nullptr;
}

int main()
{
	Link<God>* all_gods = new Link<God>(God("Thor", "Norse", "Pinzgauer", "Hammer"));
	all_gods = all_gods->insert(new Link<God>(God("Odin", "Norse", "Eight-legged horse", "")));
	all_gods = all_gods->insert(new Link<God>(God("Zeus", "Greek", "", "Lightning")));
	all_gods = all_gods->insert(new Link<God>(God("Freia", "Norse", "F-transport", "F-weapon")));
	all_gods = all_gods->insert(new Link<God>(God("Hera", "Greek", "H-transport", "Spear")));
	all_gods = all_gods->insert(new Link<God>(God("Athena", "Greek", "A-transport", "A-weapon")));
	all_gods = all_gods->insert(new Link<God>(God("Mars", "Roman", "M-transport", "M-weapon")));
	all_gods = all_gods->insert(new Link<God>(God("Poseidon", "Greek", "Seahorse", "Trident")));
	all_gods = all_gods->insert(new Link<God>(God("Ares", "Greek", "A-transport", "A-weapon")));
	all_gods = all_gods->insert(new Link<God>(God("Vesuvius", "Roman", "V-transport", "Volcano")));
	all_gods = all_gods->insert(new Link<God>(God("Bacchus", "Roman", "Stretcher", "Wine goblet")));
}