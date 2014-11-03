#ifndef U_CORE_STRING_H
#define U_CORE_STRING_H

#include <string>
#include <sstream>

namespace uLib {

typedef std::string  String;
typedef std::wstring Stringw;

}

template < typename C >
std::basic_string<C> & operator << (std::basic_string<C> &str, const C *c_str) {
    std::basic_stringstream<C> ss(c_str);
    str += ss.str();
    return str;
}

#endif // STRING_H
