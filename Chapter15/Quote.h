#include <memory>
#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;
using std::istream; using std::ostream;
#include <string>
using std::string;
#include <cstddef>
using std::size_t;
#include <utility> 
using std::pair; using std::make_pair;
#include <algorithm>
using std::min;
// Item sold at an undiscounted price
// derived classes will define various discount strategies
class Quote 
{
friend istream& operator>>(istream&, Quote&);
friend ostream& operator<<(ostream&, const Quote&);
public:

	Quote(): price(0.0) 
            { cout << "Quote::Constructor__default->" << endl;}

    Quote(const string &book, double sales_price):
                     bookNo(book), price(sales_price)
         { cout << "Quote::Constructor->" << endl;}

    //virtual ~Quote() { }        // dynamic binding for the destructor

    string isbn() const 
    { return bookNo; }

    // returns the total sales price for the specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(size_t n) const 
    { cout << "Quote::net_price->" << endl;
      return n * price; 
    }

	                                    // virtual function to return a dynamically allocated copy of itself
    virtual Quote* clone() const 
    { return new Quote(*this); }
protected:
	double price;
private:
    string bookNo;                      // ISBN number of this item
};

///////////////////////////////////////////////////////////////////////
class Disc_quote : public Quote                 // 继承Quote public继承无法访问基类私有属性
{
public:
    // other members as before

    Disc_quote(): quantity(0), discount(0.0)
                {cout << "Disc_quote::Constructor_default->" << endl;}
                                                // 覆盖父类方法 由于无法访问父类私有属性 实际上不可用

    Disc_quote(const string& book, double price,
              size_t qty, double disc):
                 Quote(book, price),            // 继承父类方法
                 quantity(qty), discount(disc)
                 {cout << "Disc_quote::Constructor->" << endl;}

    double net_price(size_t) const = 0;         // 定义为纯虚函数
                                                // 含有纯虚函数的类是抽象基类
    pair<size_t, double> discount_policy() const
    { return make_pair(quantity, discount); }
protected:

    size_t quantity;                            // purchase size for the discount to apply
    double discount;                            // fractional discount to apply
};

// the discount kicks in when a specified number of copies of the same book are sold
// the discount is expressed as a fraction used to reduce the normal price

class Bulk_quote : public Disc_quote 
{                                               // Bulk_quote inherits from Quote
public:

	Bulk_quote()  
                {cout << "Bulk_quote::Constructor_default->" << endl;}

    Bulk_quote(const string& book, double p, 
	           size_t qty, double disc) :
               Disc_quote(book, p, qty, disc)   // 继承父类方法
               { cout << "Bulk_quote::Constructor->" << endl;}       

    // overrides the base version in order to implement the bulk purchase discount policy
    double net_price(size_t) const override;    // 重载虚函数

    Bulk_quote* clone() const 
    {
        cout << "Bulk_quote::clone->" << endl;
        return new Bulk_quote(*this);
    }

};

// discount (a fraction off list) for only a specified number of copies, 
// additional copies sold at standard price
class Lim_quote : public Disc_quote 
{
public:
    Lim_quote(const string& book = "", 
              double sales_price = 0.0,
              size_t qty = 0, double disc_rate = 0.0):
              Disc_quote(book, sales_price, qty, disc_rate) 
            { cout << "Lim_quote::Constructor->" << endl;}

    // overrides base version so as to implement limited discount policy
    double net_price(size_t) const;

    Lim_quote* clone() const { return new Lim_quote(*this); }
};

double print_total(ostream& os, const Quote& item, size_t n)
{
	// depending on the type of the object bound to the item parameter
	// calls either Quote::net_price or Bulk_quote::net_price
	double ret = item.net_price(n); 
    os << "ISBN: " << item.isbn()               // calls Quote::isbn
       << " # sold: " << n << " total due: " << ret << endl;
 	return ret;
}

inline
double Bulk_quote::net_price(size_t cnt) const
{   
    cout << "Bulk_quote::net_price->" << endl;
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

inline
double Lim_quote::net_price(size_t cnt) const
{   cout << "Lim_quote::net_price->" << endl;
    size_t discounted = min(cnt, quantity);
    size_t undiscounted = cnt - discounted;
    return discounted * (1 - discount) * price 
           + undiscounted * price;
}