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

#include "Core/Archives.h"
#include "Core/String.h"

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
  BEGIN_TESTING(uLib Math);

  //////////////////////////////////////////////////////////////////////////////
  ///////////////// VECTOR TESTING /////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  std::cout << "Testing Vectors\n";

  { // ROW COLUMN ACCESSOR ORDER TEST //
      Matrix2i test;
      test << 1,2,3,4;
      std::cout << "print row column test ";
      std::cout <<  test(0,0) << " " <<
                    test(0,1) << " " <<
                    test(1,0) << " " <<
                    test(1,1) << " " << "\n";

      TEST1( test(0,1) == 2 && test(1,0) == 3 );
  }


  {
      Vector3i test(0,0,0);
      ++test(1);
      std::cout << "increment of single dim inside vector: " << test.transpose() << "\n";
      TEST1( test == Vector3i(0,1,0) );
  }

  {
      Matrix4f mat;
      mat <<  1,0,0,0,
              0,1,0,0,
              0,0,1,0,
              0,0,0,1;

      std::cout << "determinant" << mat.determinant() << "\n";
  }


  {
      //      Vector3f v(1,2,3);
      //      std::string str("2 3 5");
      //      std::istringstream istr(str);
      //      uLib::Archive::hrt_iarchive hi(istr);
      //      hi >> v;
      //      uLib::Archive::hrt_oarchive ho(std::cout);
      //      ho << v;
  }

  {
      // VECTOR STRING INTERACTION //
      Vector3f v;
      std::string str("2 3 5");
      str >> v;
      std::string sstr;
      sstr << v << "\n";
      std::cout << sstr;
  }


  END_TESTING;
}


