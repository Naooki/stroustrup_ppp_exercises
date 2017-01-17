#include <cstdlib>
#include <initializer_list>
#include <iostream>
using namespace std;


template<typename T> class Allocator
{
public:
	T* allocate(int n);
	void deallocate(T* p);
	void construct(T* p, const T& el);
	void destroy(T* p);
};

template<typename T>
T* Allocator<T>::allocate(int n)
{
	return static_cast<T*>(malloc(n * sizeof(T))); //static cast is needed cause malloc returns void*
}

template<typename T>
void Allocator<T>::deallocate(T* p)
{
	free(p);
}
template<typename T>
void Allocator<T>::construct(T* p, const T& el)
{
	new (p) T(el); //placement new
}
template<typename T>
void Allocator<T>::destroy(T* p)
{
	p->~T(); //explicit destructor call
}

struct Out_of_range {};
template<typename T, typename A = Allocator<T>> class vector
{
private:
	A alloc;
	T* elem;
	int sz;
	int space;
public:
	//constructors
	vector()
		:elem(nullptr), sz(0), space(0) {}
	vector(int n);
	vector(initializer_list<T> lst); //init_list constructor
	vector(const vector& v); //copy constructor
	vector(const vector&& v); //moving constructor

	vector& operator=(const vector& v); //copy assignment
	vector& operator=(vector&& v); //moving assignment
	~vector();

	//access
	T& at(int n);
	const T& at(int n) const;
	T& operator[](int n);
	const T& operator[](int n) const;
	
	//common operations
	void push_back(const T& val);
	void resize(int newsize, T def = T()); //we inintialise all elements of a vector while resising
	void reserve(int newalloc);

	int size() { return sz; }
};

template<typename T, typename A>
vector<T, A>::vector(int n)
	:sz(n), space(n), elem(alloc.allocate(n))
{
	for (int i = 0; i < n; ++i)
		alloc.construct(&elem[i], T());
}
template<typename T, typename A>
vector<T, A>::vector(initializer_list<T> lst)
	:sz(lst.size()), space(lst.size()), elem(alloc.allocate(lst.size()))
{
	copy(lst.begin(), lst.end(), elem);
}
template<typename T, typename A>
vector<T, A>::vector(const vector<T,A>& v)
	:elem(alloc.allocate(v.sz)), sz(v.sz), space(v.sz)
{
	for (int i = 0; i < v.sz; ++i)
		alloc.construct(&elem[i], v.elem[i]);
}
template<typename T, typename A>
vector<T, A>::vector(const vector&& v)
	: elem(v.elem), sz(v.sz), space(v.sz)
{
	v.sz = 0;
	v.space = 0;
	v.elem = nullptr;
}
template<typename T, typename A>
vector<T, A>::~vector()
{
	for (int i = 0; i < sz; ++i)
		alloc.destroy(&elem[i]);
	alloc.deallocate(elem);
}


template<typename T, typename A>
vector<T, A>& vector<T,A>::operator=(const vector<T, A>& v)
{
	if (this == &v) return *this; //self-assignment
	if (this->space >= v.sz)
	{
		for (int i = 0; i < sz; ++i)
			alloc.destroy(&this->elem[i]);
		for (int i = 0; i < v.sz; ++i)
			alloc.construct(&this->elem[i], v.elem[i]);
		this->sz = v.sz;
		return *this;
	}
	T* newspace = alloc.allocate(v.sz);
	for (int i = 0; i < v.sz; ++i)
		alloc.construct(&newspace[i], v.elem[i]);
	for (int i = 0; i < this->sz; ++i)
		alloc.destroy(&this->elem[i]);
	alloc.deallocate(this->elem);
	this->elem = newspace;
	this->space = this->sz = v.sz;
	return *this;
}
template<typename T, typename A>
vector<T, A>& vector<T,A>::operator=(vector<T, A>&& v)
{
	for (int i = 0; i < this->sz; ++i) //free old memory
		alloc.destroy(&this->elem[i]);
	alloc.deallocate(this->elem);

	this->elem = v.elem;
	this->sz = v.sz;
	this->space = v.space;
	v.elem = nullptr;
	v.sz = v.space = 0;
	return *this;
}

template<typename T, typename A>
void vector<T, A>::reserve(int newalloc)
{
	if (newalloc <= space) return;
	T* newelem = alloc.allocate(newalloc); //okay, according to struousdtrup this variant of reserve is potencially unsafe cause in case of generation of
	//an exception while copying this would lead to a memory leak(its better to use vector_base from the book cause in this case the allocated memory would be deallocated - RAII)
	for (int i = 0; i < sz; ++i)
	{
		alloc.construct(&newelem[i], elem[i]); //because some types don't support assignment to a not initialised variable
		alloc.destroy(&elem[i]);
	}
	alloc.deallocate(elem);
	elem = newelem;
	space = newalloc;
}

template<typename T, typename A> 
T& vector<T, A>::at(int n)
{
	if (n < 0 || n >= sz) throw Out_of_range();
	return elem[n];
}
template<typename T, typename A>
const T& vector<T, A>::at(int n) const
{
	if (n < 0 || n >= sz) throw Out_of_range();
	return elem[n];
}

template<typename T, typename A>
T& vector<T, A>::operator[](int n)
{
	return elem[n];
}
template<typename T, typename A>
const T& vector<T, A>::operator[](int n) const
{
	return elem[n];
}

template<typename T, typename A>
void vector<T, A>::push_back(const T& val)
{
	if (space == 0) reserve(8);
	if (sz == space) reserve(2 * space);
	alloc.construct(&elem[sz], val);
	++sz;
}

template<typename T, typename A>
void vector<T, A>::resize(int newsize, T def = T())
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i)
		alloc.construct(&elem[i], def);
	for (int i = newsize; i < sz; ++i)
		alloc.destroy(&elem[i]);  //in case if new size is smaller then the old one we should destroy unnecessary elements
	sz = newsize;
}


int main()
{
	vector<int> vi = {1,2,3,4,5,6}; //initialization lost constructor

	for (int i = 0; i < vi.size(); ++i)
		cout << vi[i] << endl;
	cout << "---------------------------------\n";
	vector<int> vi_cpy = vi; //coppy constructor
	for (int i = 0; i < vi.size(); ++i)
		cout << vi[i] << endl;
	cout << "---------------------------------\n";
	vector<int> v_empty; //default constructor
	v_empty.push_back(1);
	v_empty.push_back(1);
	v_empty.push_back(1);
	for (int i = 0; i < v_empty.size(); ++i)
		cout << v_empty[i] << endl;
	cout << "---------------------------------\n";
	vector<int> v_def(5); //constructor (int n)
	for (int i = 0; i < v_def.size(); ++i)
		cout << v_def[i] << endl;
	cout << "---------------------------------\n";
	v_def = vi; //copy assignment
	for (int i = 0; i < v_def.size(); ++i)
		cout << v_def[i] << endl;
	cout << "---------------------------------\n";
	v_def = vector<int>{1,4,8,8,1,3,3,7}; //moving assignment
	for (int i = 0; i < v_def.size(); ++i)
		cout << v_def[i] << endl;
	cout << "---------------------------------\n";
	vector<int>v_movinit = vector<int>{ 1,3,3,7,1,3,3,7 }; //moving initialization
	for (int i = 0; i < v_movinit.size(); ++i)
		cout << v_movinit[i] << endl;

}