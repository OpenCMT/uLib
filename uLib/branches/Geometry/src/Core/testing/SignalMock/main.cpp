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




#include <fstream>

#include <boost/signals2/signal.hpp>


#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>


#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/typeof/std/utility.hpp>


#include "Ob.h"
#include "Ob1.h"
#include "Ob2.h"




using namespace uLib;

using namespace SignalMock;;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// main //




class OBT1 : public Ob {
public:

signals:
    void Sig_v();

    void Sig_v(int i);

    void Sig_v(int i, int j);

    int Sig_i(int i, int j);

    int SignalTest(int i,int j);

public slots:
    void Slot() {
        std::cout << "slot v0 called\n";
    }

    void Slot(int i) {
        std::cout << "slot v1i called with i=" << i << "\n";
    }

    void Slot(int i,int j) {
        std::cout << "slot v2i called with i=" << i  << " j=" << j << "\n";
    }

    int SlotAdd(int i,int j) {
        std::cout << "slot i2i called with i=" << i  << " j=" << j << "\n";
        return i+j;
    }
};




// Wrote by moc //
void OBT1::Sig_v() {
    //    SignalBase * sig = this->findSignal((void(OBT1::*)())&OBT1::Sig_v);
    //    typedef SignalMock::Signal<void()>::type SigT;
    //    if(sig) reinterpret_cast<SigT*>(sig)->operator()();
    BOOST_AUTO(sig, this->findSignal2((void(OBT1::*)())&OBT1::Sig_v));
    sig->operator()();
}

void OBT1::Sig_v(int i) {
    SignalBase * sig = this->findSignal((void(OBT1::*)(int))&OBT1::Sig_v);
    typedef SignalMock::Signal<void(int)>::type SigT;
    if(sig) reinterpret_cast<SigT*>(sig)->operator()(i);
}

void OBT1::Sig_v(int i, int j) {
    SignalBase * sig = this->findSignal((void(OBT1::*)(int,int))&OBT1::Sig_v);
    typedef SignalMock::Signal<void(int,int)>::type SigT;
    if(sig) reinterpret_cast<SigT *>(sig)->operator()(i,j);
}

int OBT1::Sig_i(int i, int j)
{
    SignalBase * sig = this->findSignal(&OBT1::Sig_i);
    typedef SignalMock::Signal<int(int,int)>::type SigT;
    if(sig) return *reinterpret_cast<SigT *>(sig)->operator()(i,j);
    else return 0;
}

int OBT1::SignalTest(int i, int j)
{
    SignalBase * sig = this->findSignal(&OBT1::SignalTest);
    typedef SignalMock::Signal<int(int,int)>::type SigT;
    if(sig) return *reinterpret_cast<SigT *>(sig)->operator()(i,j);
    else return 0;
}











int main()
{
    OBT1 o1,o2;

    o1.addSignal(&OBT1::SignalTest, "OBT1::SignalTest");
    o1.addSignal((void(OBT1::*)())&OBT1::Sig_v, "OBT1::Sig_v0");
    o1.addSignal((void(OBT1::*)(int))&OBT1::Sig_v, "OBT1::Sig_v1i");

    Ob::connect(&o1,(void(OBT1::*)())&OBT1::Sig_v,
                &o2,(void(OBT1::*)())&OBT1::Slot);
    Ob::connect(&o1,(void(OBT1::*)(int))&OBT1::Sig_v,
                &o2,(void(OBT1::*)(int))&OBT1::Slot);
    Ob::connect(&o1,&OBT1::SignalTest,&o2,&OBT1::SlotAdd);



    o1.PrintSelf(std::cout);


    // Qt style emit //
    emit o1.Sig_v();
    emit o1.Sig_v(1);
    emit o1.Sig_v(1,2);
    std::cout << "return val2  = " << o1.SignalTest(3,4) << "\n";



    return 0;
}



