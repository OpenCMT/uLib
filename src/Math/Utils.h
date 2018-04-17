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



#ifndef U_UTILS_H
#define U_UTILS_H

#include <math.h>
#include <limits>
#include <float.h>

#define fastSign(x) ((x>0)-(x<0))

namespace uLib {

inline bool isFinite(float x) {
    return (x<=FLT_MAX && x>= -FLT_MAX);
}

inline bool isFinite(double x) {
    return (x<=DBL_MAX && x>= -DBL_MAX);
}

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

}

#endif // UTILS_H
