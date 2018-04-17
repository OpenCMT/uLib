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

#ifndef ROOTHITRAW_H
#define ROOTHITRAW_H

#include <Rtypes.h>

namespace ROOT {
namespace Mutom {



class Hit32 {
public:
    Int_t   code;
    Float_t drift;
};

class Hit64 {
public:
    Long_t   code;
    Double_t drift;
};



class HitRaw
{
public:
//    virtual Int_t Flags() {}
//    virtual Int_t Chm()   const {}
//    virtual Int_t Rob()   const {}
//    virtual Int_t Tdc()   const {}
//    virtual Int_t Ch()    const {}
    virtual void  SetFlags  (Int_t flags) = 0;
    virtual void  SetChamber(Int_t cmb) = 0;
    virtual void  SetChannel(Int_t Rob, Int_t Tdc, Int_t Ch) = 0;
//    virtual float operator() (  ) {}
protected:
    virtual ~HitRaw() {}
};



} // Mutom
} // ROOT

#endif // ROOTHITRAW_H
