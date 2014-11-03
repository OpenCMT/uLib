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



#include "Ob.h"
#include "Ob1.h"
#include "Ob2.h"


using namespace uLib;



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// main //

class SignalBase {
public:
    virtual void call() = 0;
};

template <typename T>
struct Signal : public boost::noncopyable, SignalBase
{
    typedef T PtrSignature;
    virtual void call() {}
};

template <typename Ret, class Obj>
struct Signal<Ret(Obj::*)()> : public boost::noncopyable, SignalBase
{
    typedef boost::function_traits< Ret() >        SignatureTraits;

    typedef boost::signals2::signal<Ret()>         SignalType;
    typedef typename SignalType::slot_function_type    SlotFunctionType;
    typedef typename SignalType::result_type           ResultType;
    typedef boost::signals2::connection                ConnectionType;

    Signal() : m_signal() {};
    virtual ~Signal() {};

    void call() { m_signal(); }

    SignalType & signal() { return m_signal; }

protected:
    SignalType m_signal;
};


template <typename Ret, class Obj, typename Arg>
struct Signal<Ret(Obj::*)(Arg)> : public boost::noncopyable, SignalBase
{
    typedef boost::function_traits< Ret(Arg) >        SignatureTraits;

    typedef boost::signals2::signal<Ret(Arg)>         SignalType;
    typedef typename SignalType::slot_function_type    SlotFunctionType;
    typedef typename SignalType::result_type           ResultType;
    typedef boost::signals2::connection                ConnectionType;

    Signal() : m_signal() {};
    virtual ~Signal() {};

    void call() { m_signal(0); }

    SignalType & signal() { return m_signal; }

protected:
    SignalType m_signal;
};



template < typename T >
static SignalBase * BuildSig(typename FunctionTypes<T>::Object *obj, T f) {
    Signal<T> *s = new Signal<T>;
    typename FunctionTypes<T>::Object::TS ts = {
        static_cast<SignalBase *>(s),
        reinterpret_cast<void *>(f)
    };
    obj->v.push_back(ts);
    return static_cast<SignalBase *>(s);
}

template < typename T >
static SignalBase * FindSignal(typename FunctionTypes<T>::Object *obj, T f) {
    void *ptr = reinterpret_cast<void *>(f);
    for (int i=0; i<obj->v.size(); ++i)
        if(obj->v[i].ptr == ptr) return obj->v[i].sig;
    return NULL;
}

template < typename T1, typename T2 >
static bool Connect(typename FunctionTypes<T1>::Object *sender, T1 signal,
                    typename FunctionTypes<T2>::Object *receiver, T2 slot)
{
    SignalBase *s = FindSignal(sender,signal);
    if(!s) return false;
    static_cast< Signal<T1> * >(s)->signal().connect(boost::bind(slot,receiver));
    return true;
}




class Test : public Ob {
public:

    struct TS{
        SignalBase *sig;
        void       *ptr;
    };

    Vector<TS> v;


    Test() {
        BuildSig(this, &Test::TestSignal);
        BuildSig(this, &Test::TestSignal1);
//        BuildSig(this, &Test::TestSignal2);
    }

signals:

    void TestSignal();
    void TestSignal1(int);
    void TestSignal2(int,int);

public slots:

    void PrintHello() { std::cout << "Hello!\n"; }

};



// moc it //
void Test::TestSignal(){
//    static SignalBase *signal = BuildSig(this, &Test::TestSignal);
    static SignalBase *signal = FindSignal(this,&Test::TestSignal);
    signal->call();
    //    signal->call();
}

void Test::TestSignal1(int)
{
    static SignalBase *signal = FindSignal(this,&Test::TestSignal1);
    signal->call();
}

void Test::TestSignal2(int,int)
{
//    static SignalBase *signal = FindSignal(this,&Test::TestSignal2);
//    signal->call();
}


int main()
{

    ////////////////////////////////////////////////////
    // signalling tests


    Test test;

//    test.addSignal(&Test::TestSignal,"TestSignal()");

//    Test::connect(&test,&Test::TestSignal,&test,&Test::PrintHello);


    Connect(&test,&Test::TestSignal,&test,&Test::PrintHello);

    emit test.TestSignal();

    return 0;
}


