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
#include "../Vector.h"

using namespace ltk;

int main() {
    BEGIN_TESTING(Vector - cc);

    typedef ltkVector<int, 4 > ltkInt4;

    ltkInt4 v, w;
    v = 1, 2, 3, 4;
    w = v;

    printf("v -> %d,%d,%d,%d\n", v[0], *(v.getBuffer() + 1), v.at(2), v(3));


    // test assign operator
    TEST1(v == w);
    TEST0(v != w);

    // test accessors
    TEST1(v[0] == 1);
    TEST1(*(v.getBuffer() + 1) == 2);
    TEST1(v.at(2) == 3);
    TEST1(v(3) == 4);

    // setter
    w << 1, 4, 9, 16;
    TEST1(w[0] == 1);
    TEST1(w[1] == 4);
    TEST1(w[2] == 9);
    TEST1(w[3] == 16);

    // math operators
    v *= v;
    w = 1, 4, 9, 16;
    TEST1(v == w);
    v /= v;
    w = 1, 1, 1, 1;
    TEST1(v == w);
    v += v;
    w = 2, 2, 2, 2;
    TEST1(v == w);

    v << 1, 1, -1, 1;
    w << -1, 1, 1, 1;
    TEST0(v * w);
    TEST0(v / w);

    END_TESTING;
}
