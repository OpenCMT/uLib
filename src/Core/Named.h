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

#ifndef U_CORE_NAMED_H
#define U_CORE_NAMED_H

#include <Core/Types.h>
#include <Core/String.h>

namespace uLib {

class Named {
public:
    Named() {}
    Named(const String &string) : m_name(string) {}
    Named(const char *name) : m_name(name) {}

    // default generic behaviour //
    template < typename T >
    Named(T t) : m_name(typeid(t).name()) {}

    const String GetName() const { return m_name; }

    void SetName(const String name) { m_name = name; }

    template < typename T >
    void SetName(T t) { m_name = typeid(t).name(); }

private:
    String m_name;
};


} // uLib





#endif // NAMED_H
