/*
*/ 

#ifndef DEBUG_REP_H
#define DEBUG_REP_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/* this file uses two preprocessor variables to control whether
 * we use nontemplate functions or specializations for string
 * data and to control whether we define versions of debug_rep
 * that handle character pointers.
 *
 * SPECIALIZED is defined, then we define specializations
 *             for string, char*, and const char* and do not
 *             define nontemplate functions taking these types
 *
 * OVERCHAR only matters if SPECIALIZED is not defined.  In this case
 *          if OVERCHAR is defined, we define one nontemplate function
 *          that takes a string; if OVERCHAR is not defined 
 *          we also define nontemplate functions taking char* and
 *          const char*
*/
#ifndef SPECIALIZED
std::string debug_rep(const std::string &s);
#ifndef OVERCHAR
std::string debug_rep(char *p);
std::string debug_rep(const char *cp);
#endif
#endif
// overloaded, not specialized, function templates
template <typename T> std::string debug_rep(const T &t);
template <typename T> std::string debug_rep(T *p);
template <typename T> std::string debug_rep(T b, T e);
template <typename T> std::string debug_rep(const std::vector<T> &v);

// print any type we don't otherwise handle
template <typename T> std::string debug_rep(const T &t)
{
#ifdef DEBUG
	std::cout << "const T&" << "\t";
#endif
	std::ostringstream ret; 
	ret << "debug_const_&T: ";
	ret << t; // uses T's output operator to print a representation of t
	return ret.str();  // return a copy of the string to which ret is bound
}

// print pointers as their pointer value 
// followed by the object to which the pointer points
// NB: this function will not work properly with char*
template <typename T> std::string debug_rep(T *p)
{
#ifdef DEBUG
	std::cout << "T*" << "\t";
#endif
	std::ostringstream ret;
	ret << "debug_*T: " << p;         	// print the pointer's own value
	if (p)
		ret << " " << debug_rep(*p); 		// print the value to which p points
	else
		ret << " null pointer";      		// or indicate that the p is null
	return ret.str(); 						// return a copy of the string to which ret is bound
}

// print strings inside double quotes 
std::string debug_rep(const std::string &s)

{
#ifdef DEBUG
	std::cout << "const string &" << "\t";
#endif
	std::cout << "debug_const string &:";
	return '"' + s + '"';
}


#ifndef OVERCHAR
// convert the character pointers to string and call the string version of debug_rep
std::string debug_rep(char *p) 
{	
	std::cout << "debug_char*:";
	return debug_rep(std::string(p));
}
std::string debug_rep(const char *p) 
{	
	std::cout << "debug_const char*:";
	return debug_rep(std::string(p));
}
#endif

template <typename T> std::string debug_rep(T b, T e)
{
	std::ostringstream ret;
	ret << "debug_T_beg_end: ";
	for (T it = b; it != e; ++it) {
		if (it != b)
			ret << ",";            // put comma before all but the first element
		ret << debug_rep(*it);     // print the element
	}
	return ret.str();
}

template <typename T> std::string debug_rep(const std::vector<T> &v)
{
	std::ostringstream ret;
	ret << "debug_T_vector: [";
	ret << debug_rep(v.begin(), v.end());
	ret << "]";
	return ret.str();
}
#endif
