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



#ifndef U_CORE_FUNCTION_H
#define U_CORE_FUNCTION_H

#include <typeinfo>

#include <boost/type_traits.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_arity.hpp>
//#include <boost/typeof/std/utility.hpp>


namespace uLib {









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






////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Function pointers //

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




//////// generic mfp container object  /////////////////////////////////////////

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

} // uLib




#endif // FUNCTION_H
