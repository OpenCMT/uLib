/*//////////////////////////////////////////////////////////////////////////////
// CMT Cosmic Muon Tomography project //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  Copyright (c) 2014, Universita' degli Studi di Padova, INFN sez. di Padova
  All rights reserved

  Authors: Andrea Rigoni Garola < andrea.rigoni@pd.infn.it >

  ------------------------------------------------------------------
  This library is free software;  you  can  redistribute  it  and/or
  modify it  under the  terms  of  the  GNU  Lesser  General  Public
  License as published  by  the  Free  Software  Foundation;  either
  version 3.0 of the License, or (at your option) any later version.

  This library is  distributed in  the hope that it will  be useful,
  but  WITHOUT ANY WARRANTY;  without  even  the implied warranty of
  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of  the GNU Lesser General  Public
  License along with this library.

//////////////////////////////////////////////////////////////////////////////*/



#ifndef U_CORE_STRINGREADER_H
#define U_CORE_STRINGREADER_H

#include <istream>
#include <algorithm>

#include "Core/Vector.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>


// RIPENSARE COMPLETAMENTE !!!

namespace uLib {

struct StringReader {

    std::istream & m_is;

    StringReader(std::istream &is) : m_is(is) {}

    void ReadString(const char *str) {
        //        // clean compared string //
        //        char chars[] = " \t\n";
        //        for (unsigned int i = 0; i < strlen(chars); ++i)
        //        { cmps.erase (std::remove(str.begin(), str.end(), chars[i]), str.end()); }

        // SISTEMARE !!!

        int  pos = 0;
        char c;
        while( pos < strlen(str) ) {
            while( IsEscape(str[pos])) pos++;
            if ( pos >= strlen(str) ) break;
            while( IsEscape(c = m_is.get()) );
            if (c == str[pos] ) pos++;
            else pos = 0;
        }        
    }

    static inline bool IsEscape(char c){
        const char *escapes = " \r\n\t";
        for ( int i = 0 ; i < 4 ; ++i) {
            if(c == escapes[i]) return true;
        }
        return false;
    }

};

template <typename T>
inline StringReader & operator >> (StringReader &isr, T &t) {
    isr.m_is >> t;
    return isr;
}

inline StringReader & operator >> (StringReader &isr, const char *str) {
    isr.ReadString(str);
    return isr;
}



} // uLib


#endif // STRINGREADER_H
