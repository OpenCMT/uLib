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


#include "ImageSpace.h"

namespace uLib {

//ImageSpace::ImageSpace(const Vector3i size) :
//    StructuredData(size)
//{}


void ImageSpace::SetSpacing(const Vector3f spacing)
{
    ContainerBox::SetSize(spacing);
}

Vector3f ImageSpace::GetSpacing() const
{
    return ContainerBox::GetSize();
}

Vector3i ImageSpace::Find(const Vector4f pt) const
{
    Vector3i out;
    Vector4f p = GetLocalPoint(pt);
    out << (int)floor(p(0)),
           (int)floor(p(1)),
           (int)floor(p(2));
    return out;
}

void ImageSpace::PrintSelf(std::ostream &o)
{
    o << "uLib Structured Grid: \n"
//      << "dim     = " << this->GetDims().transpose() << "\n"
      << "spacing = " << this->GetSpacing().transpose() << "\n";
}


} // uLib


