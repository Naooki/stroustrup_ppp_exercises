#include <cstdlib>
#include <initializer_list>
using namespace std;

namespace naook {
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




	struct Out_of_range {}; //exceptions

	template<typename T, typename A>
	struct Vec_rep
	{
		A alloc;
		T* elem;
		int sz;
		int space;
	};

	template<typename T, typename A = Allocator<T>> class vector
	{
	private:
		Vec_rep<T,A> *rep;
	public:
		//constructors
		vector() : rep(new Vec_rep<T, A>) { rep->elem = nullptr; rep->sz = 0; rep->space = 0; }
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

		int size() { return rep->sz; }
	};

	template<typename T, typename A>
	vector<T, A>::vector(int n) //now its correct, other constructors need to be done in the same way...
		: rep(new Vec_rep<T,A>)
	{
		rep->sz = n;
		rep->space = n;
		rep->elem = rep->alloc.allocate(n);
		for (int i = 0; i < n; ++i)
			rep->alloc.construct(&rep->elem[i], T());
	}
	template<typename T, typename A>
	vector<T, A>::vector(initializer_list<T> lst)
		: rep(new Vec_rep<T,A>),rep->sz(lst.size()), rep->space(lst.size()), rep->elem(rep->alloc.allocate(lst.size()))
	{
		copy(lst.begin(), lst.end(), rep->elem);
	}
	template<typename T, typename A>
	vector<T, A>::vector(const vector<T, A>& v)
		: rep(new Vec_rep<T,A>), rep->elem(rep->alloc.allocate(v.rep->sz)), rep->sz(v.rep->sz), rep->space(v.rep->sz)
	{
		for (int i = 0; i < v.rep->sz; ++i)
			rep->alloc.construct(&rep->elem[i], v.rep->elem[i]);
	}
	template<typename T, typename A>
	vector<T, A>::vector(const vector&& v)
		: rep(new Vec_rep<T,A>), rep->elem(v.rep->elem), rep->sz(v.rep->sz), rep->space(v.rep->sz)
	{
		v.rep->sz = 0;
		v.rep->space = 0;
		v.rep->elem = nullptr;
	}
	template<typename T, typename A>
	vector<T, A>::~vector()
	{
		for (int i = 0; i < rep->sz; ++i)
			rep->alloc.destroy(&rep->elem[i]);
		rep->alloc.deallocate(rep->elem);
		delete rep;
	}


	template<typename T, typename A>
	vector<T, A>& vector<T, A>::operator=(const vector<T, A>& v)
	{
		if (this == &v) return *this; //self-assignment
		if (this->rep->space >= v.rep->sz)
		{
			for (int i = 0; i < rep->sz; ++i)
				rep->alloc.destroy(&this->rep->elem[i]);
			for (int i = 0; i < v.rep->sz; ++i)
				rep->alloc.construct(&this->rep->elem[i], v.rep->elem[i]);
			this->rep->sz = v.rep->sz;
			return *this;
		}
		T* newspace = rep->alloc.allocate(v.rep->sz);
		for (int i = 0; i < v.rep->sz; ++i)
			rep->alloc.construct(&newspace[i], v.rep->elem[i]);
		for (int i = 0; i < this->rep->sz; ++i)
			rep->alloc.destroy(&this->rep->elem[i]);
		rep->alloc.deallocate(this->rep->elem);
		this->rep->elem = newspace;
		this->rep->space = this->rep->sz = v.rep->sz;
		return *this;
	}
	template<typename T, typename A>
	vector<T, A>& vector<T, A>::operator=(vector<T, A>&& v)
	{
		for (int i = 0; i < this->rep->sz; ++i) //free old memory
			rep->alloc.destroy(&this->rep->elem[i]);
		rep->alloc.deallocate(this->rep->elem);

		this->rep->elem = v.rep->elem;
		this->rep->sz = v.rep->sz;
		this->rep->space = v.rep->space;
		v.rep->elem = nullptr;
		v.rep->sz = v.rep->space = 0;
		return *this;
	}

	template<typename T, typename A>
	void vector<T, A>::reserve(int newalloc)
	{
		if (newalloc <= rep->space) return;
		T* newelem = rep->alloc.allocate(newalloc); //okay, according to struousdtrup this variant of reserve is potencially unsafe cause in case of generation of
											   //an exception while copying this would lead to a memory leak(its better to use vector_base from the book cause in this case the allocated memory would be deallocated - RAII)
		for (int i = 0; i < rep->sz; ++i)
		{
			rep->alloc.construct(&newelem[i], rep->elem[i]); //because some types don't support assignment to a not initialised variable
			rep->alloc.destroy(&rep->elem[i]);
		}
		rep->alloc.deallocate(rep->elem);
		rep->elem = newelem;
		rep->space = newalloc;
	}

	template<typename T, typename A>
	T& vector<T, A>::at(int n)
	{
		if (n < 0 || n >= rep->sz) throw Out_of_range();
		return rep->elem[n];
	}
	template<typename T, typename A>
	const T& vector<T, A>::at(int n) const
	{
		if (n < 0 || n >= rep->sz) throw Out_of_range();
		return rep->elem[n];
	}

	template<typename T, typename A>
	T& vector<T, A>::operator[](int n)
	{
		return rep->elem[n];
	}
	template<typename T, typename A>
	const T& vector<T, A>::operator[](int n) const
	{
		return rep->elem[n];
	}

	template<typename T, typename A>
	void vector<T, A>::push_back(const T& val)
	{
		if (rep->space == 0) reserve(8);
		if (rep->sz == rep->space) reserve(2 * rep->space);
		rep->alloc.construct(&rep->elem[sz], val);
		++rep->sz;
	}

	template<typename T, typename A>
	void vector<T, A>::resize(int newsize, T def = T())
	{
		reserve(newsize);
		for (int i = rep->sz; i < newsize; ++i)
			rep->alloc.construct(&rep->elem[i], def);
		for (int i = newsize; i < rep->sz; ++i)
			rep->alloc.destroy(&rep->elem[i]);  //in case if new size is smaller then the old one we should destroy unnecessary elements
		rep->sz = newsize;
	}
}