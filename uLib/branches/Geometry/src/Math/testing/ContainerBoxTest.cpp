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

  BEGIN_TESTING(Math ContainerBox);

  ContainerBox Cnt;

//  // Local transform:
  Cnt.SetOrigin(Vector3f(-1,-1,-1));
  Cnt.SetSize(Vector3f(2,2,2)); // scaling //
  std::cout << "Container scale is: " << Cnt.GetSize().transpose() << "\n";
  std::cout << "Container scale is: " << Cnt.GetSize().transpose() << "\n";
  TEST0( Vector4f0(Cnt.GetSize().homogeneous() - HVector3f(2,2,2)) );


  ContainerBox Box;

  Box.SetPosition(Vector3f(1,1,1));
  Box.SetSize(Vector3f(2,2,2));
  Box.EulerYZYRotate(Vector3f(0,0,0));
  Vector4f pt = Box.GetLocalPoint(HPoint3f(2,3,2));
  Vector4f wp = Box.GetWorldPoint(pt);
  TEST0( Vector4f0(wp - HPoint3f(2,3,2)) );


////  // Global
//  Cnt.SetPosition(Vector3f(1,1,1));
//  Cnt.EulerYZYRotate(Vector3f(M_PI_2,M_PI_2,0));
//  HPoint3f p = Cnt.GetWorldPoint(1,1,1);
//  //std::cout << p.transpose() << "\n";
//  TEST0( Vector4f0(p - HVector3f(2,1,2)) );
//  p = Cnt.GetWorldPoint(1,2,3);
//  //std::cout << p.transpose() << "\n";
//  TEST0( Vector4f0(p - HVector3f(4,1,3)) );


//  // scaling //



  _fail > 0 ? std::cout << "FAIL\n" : std::cout << "OK!\n";
  END_TESTING;
}


