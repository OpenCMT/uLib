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




#include <iostream>

#include <boost/signals2/signal.hpp>


#include "Core/Object.h"
#include "testing-prototype.h"

#define emit




template <typename T, bool copyable = true>
class property
{
    typedef boost::signals2::signal<void(const property<T>& )> signal_t;

public:
    property() : m_changed(new signal_t) {}
    property(const T in) : value(in) , m_changed(new signal_t) {}

    inline operator T const & () const { return value; }
    inline operator T & () { return value; }
    inline T & operator = (const T &i) { value = i; return value; }
    template <typename T2> T2 & operator = (const T2 &i) { T2 &guard = value; }    // Assign exact identical types only.
    inline signal_t & valueChanged() { return *m_changed; }

private:
    T value;
    boost::shared_ptr<signal_t> m_changed;
};


//template <typename T>
//class property <T,false> {
//    typedef boost::signals2::signal<void( T )> signal_t;

//public:
//    property() : m_changed() {}
//    property(const T in) : value(in) , m_changed() {}

//    inline operator T const & () const { return value; }
//    inline operator T & () { valueChanged()(value); return value; }
//    inline T & operator = (const T &i) { value = i; valueChanged()(value); return value; }
//    template <typename T2> T2 & operator = (const T2 &i) { T2 &guard = value; }     // Assign exact identical types only.
//    inline signal_t &valueChanged() { return m_changed; }

//private:
//    property(const property<T> &);
//    property<T> &operator = (const property<T>&);

//    T value;
//    signal_t m_changed;
//};

// test generic void function slot //
void PrintSlot(const property<int> &i) { std::cout << "slot called, new value = " << i << "!\n"; }





int main()
{    


}
