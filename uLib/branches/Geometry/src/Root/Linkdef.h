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



#ifndef U_ROOT_LINKDEF_H
#define U_ROOT_LINKDEF_H

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;

#pragma link C++ class TestTObject+;

using namespace ROOT::Mutom;

#pragma link C++ class ROOT::Math::Cartesian2D<int>+;
#pragma link C++ class ROOT::Math::Cartesian2D<float>+;
#pragma link C++ class ROOT::Math::Cartesian2D<double>+;

#pragma link C++ class ROOT::Math::Cartesian3D<int>+;
#pragma link C++ class ROOT::Math::Cartesian3D<float>+;
#pragma link C++ class ROOT::Math::Cartesian3D<double>+;

#pragma link C++ class Vector2i+;
#pragma link C++ class Vector2f+;
#pragma link C++ class Vector2d+;

#pragma link C++ class Vector3i+;
#pragma link C++ class Vector3f+;
#pragma link C++ class Vector3d+;

#pragma link C++ typedef Matrix3i;
#pragma link C++ typedef Matrix3f;
#pragma link C++ typedef Matrix3d;

#pragma link C++ class Line3f+;
#pragma link C++ class Line3d+;

#pragma link C++ class MuonScatter+;
#pragma link C++ function MuonScatter::p_mean() const;

// #pragma link C++ class DetectorChamber+;

#pragma link C++ class HitRaw+;
#pragma link C++ function HitRaw::Chm() const;
#pragma link C++ function HitRaw::Rob() const;
#pragma link C++ function HitRaw::Tdc() const;
#pragma link C++ function HitRaw::Ch() const;


#endif // __CINT__

#endif // LINKDEF_H
