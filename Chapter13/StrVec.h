

#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;
#include <memory>
using std::allocator;
#include <utility>
#include <algorithm>
#include <string>
using std::string;
using std::pair;
using std::size_t;
// vec<string>版 
class StrVec 
{
public:
    StrVec(); 
    StrVec(const string*, const string*);

	StrVec(const StrVec&);            	// 拷贝构造函数 copy constructor
	StrVec &operator=(const StrVec&); 	// 赋值函数 copy assignment
                                        // && 右值引用 只能绑定到即将销毁的对象上
	StrVec(StrVec&&);                   // 右值引用 构造 move constructor
	StrVec &operator=(StrVec&&);        // 右值引用 移动 move assignment

    ~StrVec();                          // 析构函数

    void push_back(const string&);  	// copy the element
    void push_back(string&&);       	// move the element

										// add elements
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }

										// iterator interface
	string *begin() const { return elements; }
	string *end() const { return first_free; }
                                        // 随机访问
	string& operator[](size_t n) { return elements[n]; }
private:
	// static allocator<string> alloc; 	// 分配内存
	allocator<string> alloc;
    string *elements;   				// pointer to the first element in the array
    string *first_free; 				// pointer to the first free element in the array
    string *cap;  
    pair<string*, string*> alloc_n_copy(const string*, const string*);

	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    									// used by the copy constructor, assignment operator, and destructor
	void free();             			// destroy the elements and free the space
    void reallocate();       			// get more space and copy the existing elements
};

inline 
StrVec::StrVec()
:elements(nullptr), first_free(nullptr), cap(nullptr)
{   
    cout << "默认构造函数" << endl;
}

inline
StrVec::StrVec(const StrVec &s)
{
	cout << "拷贝构造函数_引用" << endl;
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first; 
	first_free = cap = newdata.second;
}

inline
StrVec::StrVec(const string *b, const string* e)
{
	cout << "拷贝构造函数_指针" << endl;
	auto newdata = alloc_n_copy(b, e);
	elements = newdata.first;
	first_free = cap = newdata.second;
}

inline
StrVec &StrVec::operator=(const StrVec &rhs)
{
	cout << "赋值_左值引用" << endl;
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

inline
StrVec::StrVec(StrVec &&s) 
  : elements(s.elements), first_free(s.first_free), cap(s.cap)
{   
    cout << "拷贝构造函数_右值引用" << endl;
	s.elements = s.first_free = s.cap = nullptr;
}

inline
StrVec &StrVec::operator=(StrVec &&rhs)
{   cout << "赋值函数_右值引用" << endl;
	if (this != &rhs)                   // 判定自拷贝
	{
		free();                   		// free existing elements 
		elements = rhs.elements;  		// take over resources from rhs
		first_free = rhs.first_free;
		cap = rhs.cap;
										// leave rhs in a destructible state
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

inline
StrVec::~StrVec()
{	
	cout << "析构函数" << endl;
	free(); 
}

inline
void StrVec::free()
{
    cout << "  释放内存  ";
	if (elements) 
	{
    									// destroy the old elements in reverse order
		for (auto p = first_free; p != elements; /* empty */)
			alloc.destroy(--p);  		// 对p指向的对象执行析构函数
		alloc.deallocate(elements, cap - elements);
	}
}

inline
void StrVec::reallocate()
{
    									// we'll allocate space for twice as many elements as the current size
    cout << "扩容 旧大小: " << size();
    auto newcapacity = size() ? 2 * size() : 1;
    
										// allocate new memory
	auto newdata = alloc.allocate(newcapacity);
										// 从旧内存拷贝数据到新内存
	auto dest = newdata;  				// points to the next free position in the new array
    auto elem = elements; 				// points to the next element in the old array
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++)); 
    									// 在内存上依次构建对象--> 旧内存的对象
    									// update our data structure to point to the new elements
	free();   							// free the old space once we've moved the elements
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
	cout << " 扩容后:" << size() << " 占用： " << capacity() << endl;
}

inline
pair<string*, string*> 
StrVec::alloc_n_copy(const string *b, const string *e)
{
										// allocate space to hold as many elements as are in the range
	auto data = alloc.allocate(e - b); 	//分配内存
										// initialize and return a pair constructed from data and
										// the value returned by uninitialized_copy
	return make_pair(data, uninitialized_copy(b, e, data));
}

inline
void StrVec::push_back(string &&s) 
{	
	cout << "右值引用成员函数" << endl;
    chk_n_alloc(); // reallocates the StrVec if necessary
	alloc.construct(first_free++, std::move(s));
}

inline
void StrVec::push_back(const string& s)
{	
	cout << "左值引用成员函数" << endl;
    chk_n_alloc(); // ensure that there is room for another element
    alloc.construct(first_free++, s);  
}