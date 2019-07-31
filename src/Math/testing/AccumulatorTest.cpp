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




#include "Math/Accumulator.h"
#include "testing-prototype.h"

#include <TRandom.h>


//#include <boost/accumulators/framework/accumulator_set.hpp>
//#include <boost/accumulators/statistics/count.hpp>
//#include <boost/accumulators/accumulators.hpp>

using namespace uLib;

int test_ABTrim() {

    Accumulator_ABTrim<float> acc;

    acc.SetABTrim(1,1);

    std::vector<float> v;
    for(float tmpf : {1,5,5,5,300}) v.push_back(tmpf);
    //v << 1,5,5,5,300;

    for(std::vector<float>::iterator itr=v.begin(); itr<v.end(); itr++)
        acc += *itr;

    // TODO missing operator <<
    //std::cout << "Accumulating  Trim(1,1) vector: "
    //          << v << " ... out = " << acc() << "\n";

    return( acc() == 15.0 );

}


int test_Mean() {
    Accumulator_Mean<float> mean;
    TRandom rnd;
    const int c = 10000000;
    std::vector<float> v;
    v.reserve(c);
    for(int i=0;i<c;++i) v.push_back( rnd.Gaus(2000,5) );

    float m = 0;
    for(int i=0;i<c;++i) m += v[i];
    m /= c;
    std::cout << "simple mean: " << m << "\n";

    for(int i=0;i<c;++i) mean(v[i]);
    std::cout << "mean pass: " << mean() << "\n";
    mean.AddPass();
    for(int i=0;i<c;++i) mean(v[i]);
    std::cout << "mean pass: " << mean() << "\n";
    mean.AddPass();
    for(int i=0;i<c;++i) mean(v[i]);
    std::cout << "mean pass: " << mean() << "\n";
    mean.AddPass();
    for(int i=0;i<c;++i) mean(v[i]);
    std::cout << "mean pass: " << mean() << "\n";
    mean.AddPass();
    for(int i=0;i<c;++i) mean(v[i]);
    std::cout << "mean pass: " << mean() << "\n";
    mean.AddPass();
    for(int i=0;i<c;++i) mean(v[i]);
    std::cout << "mean pass: " << mean() << "\n";
    mean.AddPass();
    for(int i=0;i<c;++i) mean(v[i]);
    std::cout << "mean pass: " << mean() << "\n";


}




int main(void) {
    BEGIN_TESTING(Accumulator);

    //TEST1( test_ABTrim() );
    test_Mean();

    END_TESTING;
}
