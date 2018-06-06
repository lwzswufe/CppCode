#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;
using std::istream; using std::ostream;
#include <string>
using std::string;
#include <cstddef>
using std::size_t;

class Base
{
friend istream& operator>>(istream&, Base&);
friend ostream& operator<<(ostream&, const Base&);
public:
    Base():name("default"), father("null")
            { cout << "Base::Constructor__default->" << endl;}
    Base(string name_):name(name_), father("null") 
            { cout << "Base::Constructor->" << endl;}
    
    ~Base() = default;

    string name;
    const string cls_name{"Base"};
    string get_father() const
    {
        return father;
    }
    int sum(int a, int b, int c, int d){return a+b+c+d;}
    int sum(int a, int b, int c){return a+b+c;}
    int sum(int a, int b){return a+b;}
    
protected:
    string father;
    
private:
    int private_id{0};
};

class A : public Base
{
public:
    A():Base("A")
    {   father = Base::cls_name;
        cout << "A::Constructor__default->" << endl;
    }
    const string cls_name{"A"};
    int sum(int a, int b) {return 2*a+2*b;}
};

class B : public Base       
{
public:
    B():Base("B")
    {   father = Base::cls_name;
        cout << "B::Constructor__default->" << endl;
    }
    const string cls_name{"B"};
};

class C : private Base
{
public:
    C():Base("C")
    {   father = Base::cls_name;
        cout << "C::Constructor__default->" << endl;
    }
    const string cls_name{"C"};
    using Base::sum;
};

void print(const Base& item)
{   
    cout << "name: " << item.name               // calls Quote::isbn
         << "  class:" << item.cls_name
         << "  father: " << item.get_father()
         << endl;
}