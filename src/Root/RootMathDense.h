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



#ifndef ROOTMATHDENSE_H
#define ROOTMATHDENSE_H

#include <Root/TestTObject.h>

#include <Math/Vector3D.h>
#include <Math/Vector2D.h>

#include <Math/MatrixRepresentationsStatic.h>

namespace ROOT {
namespace Mutom {

typedef ROOT::Math::Cartesian2D<int>    Vector2i;
typedef ROOT::Math::Cartesian2D<float>  Vector2f;
typedef ROOT::Math::Cartesian2D<double> Vector2d;

typedef ROOT::Math::Cartesian3D<int>    Vector3i;
typedef ROOT::Math::Cartesian3D<float>  Vector3f;
typedef ROOT::Math::Cartesian3D<double> Vector3d;

typedef ROOT::Math::MatRepStd<int   ,3> Matrix3i;
typedef ROOT::Math::MatRepStd<float ,3> Matrix3f;
typedef ROOT::Math::MatRepStd<double,3> Matrix3d;


template <typename T>
struct Line3D
{
    ROOT::Math::Cartesian3D<T> origin,direction;
};


typedef Line3D<float> Line3f;
typedef Line3D<double> Line3d;



} // Mutom
} // ROOT

#endif // ROOTMATHDENSE_H
