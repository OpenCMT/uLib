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



#ifndef U_CORE_OBJECT_H
#define U_CORE_OBJECT_H

#include <iostream>

// WARNING: COPILE ERROR if this goes after mpl/vector //
//#include "Core/Vector.h"

#include "Core/Types.h"
#include "Core/Debug.h"

#include "Core/Function.h"
#include "Core/Signal.h"

#include "Core/Mpl.h"
#include "Core/Serializable.h"
#include "Core/ObjectProps.h"
#include "Core/Uuid.h"

namespace boost {
namespace archive {
class polymorphic_iarchive;
class polymorphic_oarchive;
} // archive
} // boost


namespace uLib {


class Version {
public:
    static const char *PackageName;
    static const char *VersionNumber;
    static const char *Release;
};






////////////////////////////////////////////////////////////////////////////////
//// OBJECT ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



/**
 * @brief Object class is the object base implementation for uLib Framework.
 */
class Object : public ObjectPropable
{


public:
    //    std::string name;
    //    void PrintName() { std::cout << "Ob name: " << name << "\n"; }

    Object();
    Object(const Object &copy);
    ~Object();

    ////////////////////////////////////////////////////////////////////////////
    // PARAMETERS //

    // FIXX !!!
    virtual void DeepCopy(const Object &copy);


    ////////////////////////////////////////////////////////////////////////////
    // SERIALIZATION //

    template <class ArchiveT> void serialize(ArchiveT &ar, const unsigned int version)    {
                ObjectPropable::serialize(ar,version);
    }
    template <class ArchiveT> void save_override(ArchiveT &ar,const unsigned int version) {}

    void SaveConfig(std::ostream &os, int version = 0);
    void LoadConfig(std::istream &is, int version = 0);

    static void SaveXml(std::ostream &os, Object &ob);
    static void LoadXml(std::istream &is, Object &ob);



    ////////////////////////////////////////////////////////////////////////////
    // SIGNALS //

    // Qt4 style connector //
    static bool connect(const Object *ob1, const char *signal_name, const Object *receiver, const char *slot_name) {
        //        // NOT WORKING YET //
        //        1) find slot pointer from name
        //        SignalBase   *sig = ob1->findSignal(signal_name);
        //        GenericMFPtr *slo = receiver->findSlot(slot_name);
        //        if(sig && slo)
        //            return Object::connect(sig,slo->operator ()(),receiver);
        //        else return false;
    }

    // Qt5 style connector //
    template <typename Func1, typename Func2>
    static bool connect( typename FunctionPointer<Func1>::Object *sender,   Func1 sigf,
                         typename FunctionPointer<Func2>::Object *receiver, Func2 slof)
    {
        SignalBase *sigb = sender->findOrAddSignal(sigf);
        typedef boost::signals2::signal<typename FunctionPointer<Func2>::SignalSignature> SigT;
        ConnectSignal(sigb,slof,receiver);
    }

    template <typename FuncT>
    static inline bool connect(SignalBase *sigb, FuncT slof, Object *receiver) {
        ConnectSignal(sigb,slof,receiver);
    }


    template< typename FuncT >
    inline typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type *
    addSignal(FuncT fun, const char *name) {
        typedef typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type SigT;
        SignalBase *sig = NewSignal(fun);
        addSignalImpl(sig,fun,name);
        return (SigT *)sig;
    }

    template< typename FuncT>
    inline bool addSlot(FuncT fun, const char *name) {
        this->addSlotImpl(GenericMFPtr(fun),name);
    }

    template < typename FuncT >
    inline typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type *
    findSignal(FuncT fptr)
    {
        typedef typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type SigT;
        return (SigT *)findSignalImpl(GenericMFPtr(fptr));
    }

    template < typename FuncT >
    inline typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type *
    findOrAddSignal(FuncT fptr)
    {
        typedef typename Signal<typename FunctionPointer<FuncT>::SignalSignature>::type SigT;
        SignalBase *sig = findSignalImpl(GenericMFPtr(fptr));
        if(!sig) {
            sig = NewSignal(fptr);
            addSignalImpl(sig,fptr,"signal_name_to_be_implemented");
        }
        return (SigT *)sig;
    }


    inline SignalBase *
    findSignal(const char *name) const
    {
        return findSignalImpl(name);
    }

    inline GenericMFPtr *
    findSlot(const char *name) const
    {
        return findSlotImpl(name);
    }


    void PrintSelf(std::ostream &o) const;

    inline const Object& operator = (const Object &copy)
    { this->DeepCopy(copy); return *this; }


private:
    bool addSignalImpl(SignalBase *sig, GenericMFPtr fptr, const char *name);
    bool addSlotImpl(GenericMFPtr fptr, const char *name);
    SignalBase   *findSignalImpl(const GenericMFPtr &fptr) const;
    SignalBase   *findSignalImpl(const char *name) const;
    GenericMFPtr *findSlotImpl(const char *name) const;

    friend class boost::serialization::access;
    friend class ObjectPrivate;
    class ObjectPrivate *d;
};



} // uLib

////////////////////////////////////////////////////////////////////////////////

//std::ostream & operator << (std::ostream &os, uLib::Object &ob);
//std::ostream & operator << (std::ostream &os, uLib::Object *ob);
//std::istream & operator >> (std::istream &is, uLib::Object &ob);


#endif // U_OBJECT_H
