/*
*/ 

#ifndef VEC_H
#define VEC_H

#include <algorithm>
#include <memory>
#include <utility>

// 模板类
// simplified-implementation of memory allocation strategy for a vector-like class
template <typename T>
class Vec 
{
public:
    Vec(): elements(nullptr), first_free(nullptr), cap(nullptr) { }
	Vec(const Vec&);                 	// copy constructor
	Vec &operator=(const Vec&);      	// copy assignment
	Vec(Vec&&) throw();             	// move constructor
	Vec &operator=(Vec&&) throw();  	// move assignment
	~Vec() throw();                 	// destructor

										// add elements
    void push_back(const T&);
    void push_back(T&&);
	
										// size and capacity 容量与大小
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }

										// element access 随机访问
    T& operator[](size_t n) { return elements[n]; }
    const T& operator[](size_t n) const { return elements[n]; }

										// iterator interface 迭代器
	T *begin() const { return elements; }
	T *end() const { return first_free; }
    
private:
    static std::allocator<T> alloc; 	// allocates the elements
										// used by functions that add elements to the Vec
	void chk_n_alloc() { if (first_free == cap) reallocate(); }

    									// utilities used by copy constructor, assignment operator, and destructor
	std::pair<T*, T*> 
	  alloc_n_copy(const T*, const T*);
	void free();
    void reallocate(); 					// get more space and copy existing elements

    T* elements;   						// pointer to first element in the array
    T* first_free; 						// pointer to first free element in the array
    T* cap;        						// pointer to one past the end of the array

};


//definition for the static data member 
template <typename T> std::allocator<T> Vec<T>::alloc;  

template <typename T>
inline
Vec<T>::~Vec() throw() { free(); }		// 析构函数


template <typename T>
inline
std::pair<T*, T*> 						// 复制
Vec<T>::alloc_n_copy(const T *b, const T *e) 
{
	auto data = alloc.allocate(e - b);
	return std::make_pair(data, uninitialized_copy(b, e, data));
}

template <typename T>
inline
Vec<T>::Vec(Vec &&s) throw() : 
										// 移动构造
	elements(s.elements), first_free(s.first_free), cap(s.cap)
{
	// leave s in a state in which it is safe to run the destructor
	s.elements = s.first_free = s.cap = nullptr;
}

template <typename T>
inline
Vec<T>::Vec(const Vec &s)
{
										// 拷贝构造
	auto newdata = alloc_n_copy(s.begin(), s.end()); 
	elements = newdata.first; 
	first_free = cap = newdata.second;
}

template <typename T>
inline
void Vec<T>::free()
{
    // destroy the old elements in reverse order
	for (auto p = first_free; p != elements; /* empty */)
		alloc.destroy(--p);  // destroy elements in reverse order
    
    // deallocate cannot be called on a 0 pointer
	if (elements)
		alloc.deallocate(elements, cap - elements);
}

template <typename T>
inline
Vec<T> &Vec<T>::operator=(Vec &&rhs) throw()
{
	// direct test for self-assignment
	if (this != &rhs)
		free();  // free existing elements if appropriate

	elements = rhs.elements;  // take over resources from rhs
	first_free = rhs.first_free;
	cap = rhs.cap;

	// leave rhs in a destructible state
	rhs.elements = rhs.first_free = rhs.cap = nullptr;

	return *this;
}

template <typename T>
inline
Vec<T> &Vec<T>::operator=(const Vec &rhs)
{
	// call copy to allocate exactly as many elements as in rhs
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

template <typename T>
inline
void Vec<T>::reallocate()
{
    // we'll allocate space for twice as many elements as current size
    auto newcapacity = size() ? 2 * size() : 2;

	// allocate new space
	auto first = alloc.allocate(newcapacity);
	auto dest = first;
	auto elem = elements;

	// move the elements
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();  // free the old space once we've moved the elements

    // update our data structure point to the new elements
    elements = first;
    first_free = dest;
    cap = elements + newcapacity;
}

template <typename T>
inline
void Vec<T>::push_back(const T& s)
{
    chk_n_alloc(); // reallocates the Vec if necessary
    // construct a copy s in the element to which first_free points
    alloc.construct(first_free++, s);  
}

template <typename T>
inline
void Vec<T>::push_back(T&& s) 
{
    chk_n_alloc(); 						// reallocates the Vec if necessary 扩容
	alloc.construct(first_free++, std::move(s));
}

#endif