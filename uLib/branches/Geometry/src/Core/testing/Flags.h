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



#ifndef U_CORE_FLAGS_H
#define U_CORE_FLAGS_H

namespace uLib {

template<typename T> class Flags
{
    T i;
public:
    typedef T EnumT;

    inline Flags(const Flags &f) : i(f.i) {}
    inline Flags() : i((T)0) {}
    inline Flags(T f) : i(f) {}

    inline Flags &operator=(const Flags &f) { i = f.i; return *this;   }
    inline Flags &operator&=(T mask)          { i &= mask; return *this; }

    inline Flags &operator|=(const Flags f) { i |= f.i; return *this; }
    inline Flags &operator|=(const T f)     { i |= f;   return *this; }
    inline Flags &operator^=(const Flags f) { i ^= f.i; return *this; }
    inline Flags &operator^=(const T f)     { i ^= f;   return *this; }

    inline Flags operator|(const Flags f) const { return Flags(i | f.i); }
    inline Flags operator|(const T f)     const { return Flags(i | f);   }
    inline Flags operator^(const Flags f) const { return Flags(i ^ f.i); }
    inline Flags operator^(const T f)     const { return Flags(i ^ f);   }
    inline Flags operator&(const Flags f) const { return Flags(i & f.i); }
    inline Flags operator&(const T f)     const { return Flags(i & f);   }
    inline Flags operator~()            const { return Flags(~i);      }

    inline bool operator !()   const { return !i; }
    inline bool testFlag(const T f) const
    { return (i & f) == f && (f != 0 || i == f ); }
    //    inline bool operator==(const T f) const { return i==f; }

    inline T operator()()     { return i; }
    inline operator T() const { return i; }
};


typedef Flags<unsigned short> Flags2B;
typedef Flags<unsigned int>   Flags4B;
typedef Flags<unsigned long>  Flags8B;

} // uLib


#endif // FLAGS_H
