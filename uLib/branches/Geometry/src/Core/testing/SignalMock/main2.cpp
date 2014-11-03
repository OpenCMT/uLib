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

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/signals2/signal.hpp>

#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/typeof/std/utility.hpp>


#include "Ob.h"
#include "Ob1.h"
#include "Ob2.h"


using namespace uLib;



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// main //




class Test : public Ob{
public:

signals:
    void PrintSng() { }
    void PrintSng2(int i);
    void PrintSng3(int i, char c);
};

// written by moc //
void Test::PrintSng2(int i)
{
    std::cout << "[Emit signal: PrintSgn2(" << i <<")]\n";
    typedef void(Test::* FPtr)(int);
    FPtr fptr = &Test::PrintSng2;
    typedef Signal<FunctionTypes<FPtr>::arity, typename FunctionTypes<FPtr>::Signature > SType;
    SignalBase *s = this->findSignal(fptr);
    static_cast<SType *>(s)->m_signal(*this,i);
}

// written by moc //
void Test::PrintSng3(int i,char c)
{
}




class TestSlot: public Ob {
public:
    TestSlot(const char *name) : m_name(name) {}

public slots:
    void PrintInt(int i) {
        std::cout << "SLOT [" << m_name << "]>> TestSlot::PrintInt(" << i << ")\n";
    }

private:
    std::string m_name;
};


void freeFunction0() {}

void freeFunction1(int i) {}

template <typename FuncT>
void printSignature(FuncT f){

    typedef typename boost::function_types::function_type<FuncT>::type Signature;
    typedef boost::mpl::if_< boost::mpl::bool_<boost::is_member_function_pointer<FuncT>::value > , typename boost::function_traits< Signature >::arg1_type, void > Object;

    std::cout << "***Function Signature ***\n"
              << " type_name   : " << typeid(typename boost::function_types::function_type<FuncT>::type).name() << "\n"
                 //              << " object type : " << typeid(typename boost::function_traits< typename boost::function_types::function_type<FuncT>::type >::arg1_type).name() << "\n"
              << " object type : " << typeid(Object).name() << "\n"
              << " is memfn    : " << (boost::is_member_function_pointer<FuncT>::value == true) <<  "\n"
              << " n aguments  : " << boost::function_types::function_arity<FuncT>::value << "\n\n";
}






int main()
{

    Test t1;
    TestSlot t2("slotOb1"),t3("slotOb2");

    // in moc we add signals
    t1.addSignal(&Test::PrintSng2,"Test::PrintSng2(int)");
    t1.addSignal(&Test::PrintSng3,"Test::PrintSng3(int,char)");


    SignalBase * signal = t1.findSignal(&Test::PrintSng2);
    if(signal)
        std::cout << "signal found" << "\n";



    Ob::connect(&t1, &Test::PrintSng2,
                &t2, &TestSlot::PrintInt);
    Ob::connect(&t1, &Test::PrintSng2,
                &t3, &TestSlot::PrintInt);

    emit t1.PrintSng2(5552368);

    //    SignalBase *s = NewSignal(&Test::PrintSng2);


//    printSignature(&freeFunction0);
    printSignature(&freeFunction1);
    printSignature(&Test::PrintSng2);








    return 0;

}



