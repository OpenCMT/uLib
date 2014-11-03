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





#ifndef OB_H
#define OB_H

#include <fstream>
#include <ostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/signals2/signal.hpp>
#include <boost/type_traits.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/typeof/std/utility.hpp>


#include <Core/Object.h>

#include "testing-prototype.h"






#include "Core/Vector.h"

#include "boost/typeof/typeof.hpp"
#include <boost/serialization/binary_object.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/name_generator.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>


#include <boost/serialization/extended_type_info_typeid.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Mock of serializable object system //

#define default(vlaue)
#define slots
#define signals public
#define emit
# define SLOT(a)     a
# define SIGNAL(a)   a





namespace uLib {

namespace SignalMock {




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Function pointers //



////////////////////////////////////////////////////////////////////////////////
// type synthesize ( please read: boost implementation synthesize.hpp )       //
////////////////////////////////////////////////////////////////////////////////
// TODO: change this to boost implementation //
// return a reference to function ... as the boost signal signature wants

template <typename FuncT>
struct FunctionTypes {};

template <typename R, class O>
struct FunctionTypes< R(O::*)() > {
    typedef R  ref();
    typedef R (ptr)();
    typedef O  obj;
};

template <typename R, class O, typename T0>
struct FunctionTypes< R(O::*)(T0) > {
    typedef R  ref(T0);
    typedef R (ptr)(T0);
    typedef O  obj;
};

template <typename R, class O, typename T0, typename T1>
struct FunctionTypes< R(O::*)(T0,T1) > {
    typedef R  ref(T0,T1);
    typedef R (ptr)(T0,T1);
    typedef O  obj;
};

template <typename R, class O, typename T0, typename T1, typename T2>
struct FunctionTypes< R(O::*)(T0,T1,T2) > {
    typedef R  ref(T0,T1,T2);
    typedef R (ptr)(T0,T1,T2);
    typedef O  obj;
};







template<typename Func>
struct FunctionPointer {
    typedef typename boost::function_types::function_type<Func>::type Signature;
    typedef typename FunctionTypes<Func>::ref SignalSignature;
    enum {
        arity = boost::function_types::function_arity<Func>::value,
        ismfp = boost::is_member_function_pointer<Func>::value
    };

    typedef boost::mpl::bool_< ismfp >                            HasObjectType;
    typedef typename FunctionTypes<Func>::obj                     Object;
    typedef boost::function_traits< Signature >                   Traits;

    virtual void PrintSelf( std::ostream &o ) {
        o << "[fp: " << typeid(Signature).name()
          << " arity: " << arity << "]\n"; }
};




//////// generic function holder ///////////////////////////////////////////////

class GenericMFPtr {
    typedef void (GenericMFPtr::*_MFPtrStub_t)();
public:

    typedef _MFPtrStub_t Type;

    GenericMFPtr() {}

    template <typename T>
    GenericMFPtr(T in) {
        m_ptr = reinterpret_cast<_MFPtrStub_t>(in);
    }

    template <typename T>
    inline bool operator == (T in) {
        return m_ptr == reinterpret_cast<_MFPtrStub_t>(in);
    }

    inline bool operator == (const GenericMFPtr &in) {
        return m_ptr == in.m_ptr;
    }

    Type operator()() { return m_ptr; }

    _MFPtrStub_t m_ptr;
private:
};







// A boost::signal wrapper structure ///////////////////////////////////////////

// TODO ...

typedef boost::signals2::signal_base SignalBase;

template <typename T>
struct Signal {
    typedef boost::signals2::signal<T> type;
};

template <typename FuncT>
SignalBase *NewSignal(FuncT f) {
    // seems to work !
    return new Signal<void()>::type;
}


////////////////////////////////////////////////////////////////////////////////


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





////////////////////////////////////////////////////////////////////////////////
//// OB  ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Ob {

public:

    Ob();

    // Qt4 style connector //
    static bool connect(const Ob *ob1, const char *signal, const Ob *receiver, const char *slot) {
        // 1) find slot pointer from name
        // 2) find a way to do connection with no type
        // TODO: finire
    }

    // Qt5 style connector //
    template <typename Func1, typename Func2>
    static bool connect( typename FunctionPointer<Func1>::Object *sender,   Func1 sigf,
                         typename FunctionPointer<Func2>::Object *receiver, Func2 slof)
    {
        SignalBase *sigb = sender->findSignal(sigf);
        typedef boost::signals2::signal<typename FunctionPointer<Func2>::SignalSignature> SigT;
        ConnectSignal<Func2,FunctionPointer<Func2>::arity>::connect(sigb,slof,receiver);
    }

    template <typename FuncT>
    static inline bool connect(SignalBase *sigb, FuncT slof, Ob *receiver) {
        ConnectSignal<FuncT,FunctionPointer<FuncT>::arity>::connect(sigb,slof,receiver);
    }


    template< typename FuncT >
    inline bool addSignal(FuncT fun, const char *name) {
        SignalBase *sig = NewSignal(fun);
        addSignalImpl(sig,fun,name);
    }


    template < typename FuncT >
    inline SignalBase *findSignal(FuncT fptr)
    {
        return findSignalImpl(GenericMFPtr(fptr));
    }

    template < typename FuncT >
    inline boost::signals2::signal< typename FunctionPointer<FuncT>::SignalSignature> *findSignal2(FuncT fptr)
    {
        return (boost::signals2::signal<typename FunctionPointer<FuncT>::SignalSignature> *)findSignalImpl(GenericMFPtr(fptr));
    }

    void PrintSelf(std::ostream &o) const;

private:    

    bool addSignalImpl(SignalBase *sig, GenericMFPtr fptr, const char *name);

    SignalBase *findSignalImpl(const GenericMFPtr &fptr);


    friend class ObPrivate;
    class ObPrivate *d;
};







} // SignalMock

}

////////////////////////////////////////////////////////////////////////////////






#endif
