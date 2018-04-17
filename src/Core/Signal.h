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



#ifndef U_CORE_SIGNAL_H
#define U_CORE_SIGNAL_H

#include <boost/typeof/typeof.hpp>

#include <boost/signals2/signal.hpp>
#include <boost/signals2/slot.hpp>
#include <boost/signals2/signal_type.hpp>

#include "Function.h"




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Signals macro //

#define default(vlaue)
#define slots
#define signals /*virtual void init_signals();*/ public
#define emit
#define SLOT(a)     BOOST_STRINGIZE(a)
#define SIGNAL(a)   BOOST_STRINGIZE(a)

#define _ULIB_DETAIL_SIGNAL_EMIT(_name,...)                       \
        static BOOST_AUTO(sig,this->findOrAddSignal(&_name));     \
        sig->operator()(__VA_ARGS__);

/**
 * Utility macro to implement signal emission implementa una delle seguenti:
 *
 * // metodo standard con cast //
 * SignalBase * sig = this->findSignal((void (Ob1::*)(void))&Ob1::V0);
 * typedef Signal<void()>::type SigT;
 * if(sig) reinterpret_cast<SigT*>(sig)->operator()();
 *
 * // cast automatico //
 * static BOOST_AUTO(sig,this->findOrAddSignal(&Ob1::V0));
 *   sig->operator()();
*/
#define ULIB_SIGNAL_EMIT(_name,...) _ULIB_DETAIL_SIGNAL_EMIT(_name,__VA_ARGS__)


namespace uLib {


// A boost::signal wrapper structure ///////////////////////////////////////////

// TODO ...

typedef boost::signals2::signal_base SignalBase;

template <typename T>
struct Signal {
    typedef boost::signals2::signal<T> type;
};



////////////////////////////////////////////////////////////////////////////////


namespace detail {


template <typename FuncT, int arity>
struct ConnectSignal {};

template <typename FuncT>
struct ConnectSignal< FuncT, 0 > {
    static void connect(SignalBase *sigb, FuncT slof, typename FunctionPointer<FuncT>::Object *receiver) {
        typedef typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type SigT;
        reinterpret_cast<SigT*>(sigb)->connect(slof);
    }
};

template <typename FuncT>
struct ConnectSignal< FuncT, 1 > {
    static void connect(SignalBase *sigb, FuncT slof, typename FunctionPointer<FuncT>::Object *receiver) {
        typedef typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type SigT;
        reinterpret_cast<SigT*>(sigb)->connect(boost::bind(slof,receiver));
    }
};

template <typename FuncT>
struct ConnectSignal< FuncT, 2 > {
    static void connect(SignalBase *sigb, FuncT slof, typename FunctionPointer<FuncT>::Object *receiver) {
        typedef typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type SigT;
        reinterpret_cast<SigT*>(sigb)->connect(boost::bind(slof,receiver,_1));
    }
};

template <typename FuncT>
struct ConnectSignal< FuncT, 3 > {
    static void connect(SignalBase *sigb, FuncT slof,  typename FunctionPointer<FuncT>::Object *receiver) {
        typedef typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type SigT;
        reinterpret_cast<SigT*>(sigb)->connect(boost::bind(slof,receiver,_1,_2));
    }
};

template <typename FuncT>
struct ConnectSignal< FuncT, 4 > {
    static void connect(SignalBase *sigb, FuncT slof,  typename FunctionPointer<FuncT>::Object *receiver) {
        typedef typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type SigT;
        reinterpret_cast<SigT*>(sigb)->connect(boost::bind(slof,receiver,_1,_2,_3));
    }
};

template <typename FuncT>
struct ConnectSignal< FuncT, 5 > {
    static void connect(SignalBase *sigb, FuncT slof,  typename FunctionPointer<FuncT>::Object *receiver) {
        typedef typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type SigT;
        reinterpret_cast<SigT*>(sigb)->connect(boost::bind(slof,receiver,_1,_2,_3,_4));
    }
};


} // detail



template <typename FuncT>
SignalBase *NewSignal(FuncT f) {
    // seems to work wow !
    return new Signal<void()>::type;
}

template <typename FuncT>
void ConnectSignal(SignalBase *sigb, FuncT slof, typename FunctionPointer<FuncT>::Object *receiver)
{
    detail::ConnectSignal< FuncT, FunctionPointer<FuncT>::arity >::connect(sigb,slof,receiver);
}




} // uLib

#endif // SIGNAL_H
