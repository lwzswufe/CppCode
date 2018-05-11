#include <string>
#include <iostream>

class Screen 
{
public:
    typedef std::string::size_type pos;
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)
	Screen() = default;  // needed because Screen has another constructor
#else
	Screen(): cursor(0), height(0), width(0) { }
#endif
	// cursor initialized to 0 by its in-class initializer
    Screen(pos ht, pos wd, char c): height(ht), width(wd), 
	                                contents(ht * wd, c) { }

    Screen(pos ht = 0, pos wd = 0): 
       cursor(0), height(ht), width(wd), contents(ht * wd, '.') { }
    char get() const                        // get the character at the cursor
	    { return contents[cursor]; }        // implicitly inline
    inline char get(pos ht, pos wd) const;  // explicitly inline
	Screen &clear(char = bkground);
private:
	static const char bkground = ' ';
public:
    Screen &move(pos r, pos c);      // 因为返回类型是*this  Screen& 表示返回类型是Screen的引用
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen get_copy() {return *this;}               // 没有& 返回的是复制体 
	// other members as before
    // display overloaded on whether the object is const or not
    Screen &display(std::ostream &os)               // 根据对象是否是const 重载
                  {   os << "non-const\n";
                      do_display(os); 
                      return *this; 
                  }
    const Screen &display(std::ostream &os) const   // const重载
                  {   os << "const\n";
                      do_display(os); 
                      return *this; 
                  }
private:
     // function to do the work of displaying a Screen
    void do_display(std::ostream &os) const;

private:
#ifdef IN_CLASS_INITS
    pos cursor = 0;
    pos height = 0, width = 0;
#else
    pos cursor;
    pos height, width;
#endif
    std::string contents;
};

Screen &Screen::clear(char c) 
{
	contents = std::string(height*width, c);
	return *this;
}

inline                              // we can specify inline on the definition
Screen &Screen::move(pos r, pos c)  // 将指针移动到
{
    pos row = r * width;            // compute the row location
    cursor = row + c;               // move cursor to the column within that row
    return *this;                   // return this object as an lvalue
}

char Screen::get(pos r, pos c) const // declared as inline in the class
{                                   // 显示某个位置的字符
    pos row = r * width;            // compute row location
    return contents[row + c];       // return character at the given column
}

inline Screen &Screen::set(char c) 
{ 
    contents[cursor] = c;           // set the new value at the current cursor location
    return *this;                   // return this object as an lvalue
}
inline Screen &Screen::set(pos r, pos col, char ch)
{
	contents[r*width + col] = ch;   // set specified location to given value
	return *this;                   // return this object as an lvalue
}

inline void Screen::do_display(std::ostream &os) const 
{
    // os << contents;
    int i = 0;
    for (int h=0; h<height; h++)
    {
        for (int w=0; w<width; w++)
        {   
            os << contents[i];
            i++;
        }
        os << "\n";
    }

}