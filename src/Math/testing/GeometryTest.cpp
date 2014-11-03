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



#include "testing-prototype.h"
#include "Math/Dense.h"
#include "Math/VectorSpace.h"
#include "Math/Geometry.h"
#include "Math/ContainerBox.h"

#include <iostream>
#include <math.h>

using namespace uLib;

int Vector4f0(Vector4f c)
{
  c(3) = 0;
  if ( fabs(c(0)) < 0.001 && fabs(c(1)) < 0.001 && fabs(c(2)) < 0.001 )
    return 0;
  else
    return 1;
}


int main()
{
  BEGIN_TESTING(Math Geometry);

  //////////////////////////////////////////////////////////////////////////////
  ///////////////// GEOMETRY TESTING ///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  Geometry Geo;

  Geo.SetPosition(Vector3f(1,1,1));
  Geo.EulerYZYRotate(Vector3f(0,0,0));
  Vector4f pt = Geo.GetLocalPoint(HPoint3f(2,3,2));
  Vector4f wp = Geo.GetWorldPoint(pt);
  TEST0( Vector4f0(wp - HPoint3f(2,3,2)) );

  Geo.Scale(Vector3f(2,2,2));
  wp = Geo.GetWorldPoint(HPoint3f(1,1,1));
  TEST0( Vector4f0(wp - HPoint3f(3,3,3)) );
  Geo.Scale(Vector3f( .5 , .5 , .5 ));


  Geo.EulerYZYRotate(Vector3f(M_PI_2,0,0));
  wp = Geo.GetWorldPoint(HPoint3f(1,1,1));
  TEST0( Vector4f0(wp - HPoint3f(2,2,0)) );

  Geo.EulerYZYRotate(Vector3f(0,M_PI_2,0));
  wp = Geo.GetWorldPoint(HPoint3f(1,1,1));
  TEST0( Vector4f0(wp - HPoint3f(2,2,2)) );

  Geo.EulerYZYRotate(Vector3f(0,0,M_PI_2));
  wp = Geo.GetWorldPoint(HPoint3f(1,1,1));
  //  std::cout << "Geometry matrix\n" << Geo.GetTransform() << "\n";
  //  std::cout << "World 1,1,1 coords\n" << wp << "\n";
  TEST0( Vector4f0(wp - HPoint3f(0,2,2)) );

  // TESTING FLIP AXES //

  Geo.SetPosition(Vector3f(0,0,0));
  Geo.EulerYZYRotate(Vector3f(-M_PI_2,-M_PI_2,-M_PI_2)); // reset previous
  Geo.EulerYZYRotate(Vector3f(M_PI_2,0,0));              // PI_2 along X
  Geo.FlipAxes(0,2); // flip  X-Z
  Vector4f p = Geo.GetWorldPoint(Vector3f(1,0,0).homogeneous());
  TEST0( Vector4f0(p - HVector3f(1,0,0)) ); // after flip and rotation X->X


  _fail > 0 ? std::cout << "FAIL\n" : std::cout << "OK!\n";
  END_TESTING;
}


