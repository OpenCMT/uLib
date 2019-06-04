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



#ifndef U_CORE_DEBUG_H
#define U_CORE_DEBUG_H



//#include "ltk/ltkdebug.h"
#include "Macros.h"
#include "Types.h"
#include "Mpl.h"
#include "Vector.h"

#include <boost/any.hpp>
#include <TObject.h>

namespace uLib {


namespace detail {

struct DebugAdapterInterface {
    virtual ~DebugAdapterInterface() {}

    virtual void operator()(char val)            {}
    virtual void operator()(unsigned char val)   {}
    virtual void operator()(short val)           {}
    virtual void operator()(unsigned short val)  {}
    virtual void operator()(int val)             {}
    virtual void operator()(unsigned int val)    {}
    virtual void operator()(long val)            {}
    virtual void operator()(unsigned long val)   {}

    virtual void operator()(float val)           {}
    virtual void operator()(double val)          {}

    virtual void operator()(std::string val)     {}
};


struct DebugAdapter {
    struct AnyCastAdapterBase {
        virtual ~AnyCastAdapterBase(){}
        virtual void operator()(SmartPointer<DebugAdapterInterface> &ad, boost::any &val) {}
    };

    template < typename T >
    struct AnyCastAdapter : AnyCastAdapterBase {
        void operator()(SmartPointer<DebugAdapterInterface> &ad, boost::any &val) { ad->operator()(boost::any_cast<T>(val)); }
    };

    struct DItem {
        DItem(){}
        template <typename T> DItem(std::string str, T &t) :
            m_adapter(new AnyCastAdapter<T>()),
            m_name(str),
            m_value(t) { }

        SmartPointer<AnyCastAdapterBase> m_adapter;
        std::string         m_name;
        boost::any          m_value;
    };

};


} // detail



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// text ADAPTER

class DebugAdapterText : public detail::DebugAdapterInterface {
    std::ostream &m_out;
public:
    DebugAdapterText(std::ostream &o) : m_out(o) {}
    void operator()(int val) { m_out << "debug: " << val << "\n"; }
    void operator()(std::string val) { m_out << "debug: " << val << "\n"; }
};





class Debug {
    typedef detail::DebugAdapterInterface AdapterInterface;
    typedef SmartPointer<detail::DebugAdapterInterface> Adapter;
    typedef detail::DebugAdapter::DItem DItem;
public:

    template <typename T> void operator() (std::string str, T &t) { m_v.push_back(DItem(str,t)); }

    void AddAdapter(AdapterInterface &ad) { m_a.push_back(Adapter(ad)); }

    void Update() {
        foreach(Adapter &ad, m_a) {
            foreach(DItem &item, m_v) {
                item.m_adapter->operator()(ad, item.m_value);
            }
        }
    }

private:
    Vector<DItem>     m_v;
    Vector<Adapter>   m_a;
};






} // uLib







#endif // DEBUG_H
