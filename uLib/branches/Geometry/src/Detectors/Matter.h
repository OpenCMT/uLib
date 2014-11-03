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



#ifndef MATTER_H
#define MATTER_H

#include "Core/Object.h"

class G4Element;
class G4Material;

namespace uLib {


////////////////////////////////////////////////////////////////////////////////
//// ELEMENT ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Element {
public:

    uLibRefMacro(G4Data,G4Element *)
private:
    G4Element *m_G4Data;
};



////////////////////////////////////////////////////////////////////////////////
//// MATERIAL //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class Material : public Object {
public:

    uLibRefMacro(G4Data,G4Material *)
private:
    G4Material *m_G4Data;
};



}


#endif // MATTER_H
