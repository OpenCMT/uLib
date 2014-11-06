#ifndef U_CORE_PROGRAMMABLEACCESSOR_H
#define U_CORE_PROGRAMMABLEACCESSOR_H

#include <Core/Macros.h>
#include <Core/Types.h>
#include <Core/SmartPointer.h>
#include <Core/Named.h>

#include <Core/Function.h>

#include <boost/any.hpp>

namespace uLib {



namespace detail {





class any_c : public boost::any {
    typedef boost::any any;

public:

    any_c() : any() {}

    template<typename ValueType>
    any_c(const ValueType & value) : any(value) {}

    any_c(const any & other) : any(other) {}

    // this is needed to tait static_cast using any_cast function //
    template <typename _TT>
    operator _TT () const { return boost::any_cast<_TT>(*this); }

};


template <typename D>
class ProgrammableAccessor_Base {
protected:

public:
    virtual D Get(void *) const = 0;
    virtual void Set(void *,const D) const = 0;

    template <typename T>
    T Get(void *ob) const {
        return static_cast<T>(this->Get(ob));
    }

    template <typename T>
    void Set(void *ob, const T data) const {
        this->Set(ob,static_cast<D>(data));
    }

    virtual ~ProgrammableAccessor_Base() {}
};


template<typename D, typename R, typename T>
class functor_by_ref : public ProgrammableAccessor_Base<D>
{
public:
    explicit functor_by_ref(R&(T::*__pf)()) : MFRef(__pf) {}
    D Get(void * ptr) const
    { return static_cast<D>((reinterpret_cast<T *>(ptr)->*MFRef)()); }
    void Set(void * ptr, const D data) const
    { ((reinterpret_cast<T *>(ptr)->*MFRef)()) = static_cast<const R>(data); }
private:
    R&(T::*MFRef)();
};

template<typename D, typename R, typename T>
class functor_by_mfptr_cc : public ProgrammableAccessor_Base<D>
{
    typedef R(T::*GetterType)() const;
    typedef void(T::*SetterType)(const R);
public:
    explicit functor_by_mfptr_cc( GetterType _get, SetterType _set ) :
        GetPtr(_get), SetPtr(_set)  {}
    D Get(void * ptr) const
    { return static_cast<D>((reinterpret_cast<T *>(ptr)->*GetPtr)()); }
    void Set(void * ptr, const D data) const
    { if (SetPtr) (reinterpret_cast<T *>(ptr)->*SetPtr)(static_cast<const R>(data)); }

private:
    GetterType GetPtr;
    SetterType SetPtr;
};

template<typename D, typename R, typename T>
class functor_by_mfptr_vv : public ProgrammableAccessor_Base<D>
{
    typedef R(T::*GetterType)();
    typedef void(T::*SetterType)(R);
public:
    explicit functor_by_mfptr_vv( GetterType _get, SetterType _set ) :
        GetPtr(_get), SetPtr(_set)  {}
    D Get(void * ptr) const
    { return static_cast<D>((reinterpret_cast<T *>(ptr)->*GetPtr)()); }
    void Set(void * ptr, const D data) const
    { if (SetPtr) (reinterpret_cast<T *>(ptr)->*SetPtr)(static_cast<const R>(data)); }

private:
    GetterType GetPtr;
    SetterType SetPtr;
};


template<typename D, typename R, typename T>
class functor_by_member : public ProgrammableAccessor_Base<D>
{
public:
    explicit functor_by_member(R T::*__pf) : MDPtr(__pf) {}
    D Get(void * ptr) const
    { return static_cast<D>(reinterpret_cast<T *>(ptr)->*MDPtr); }
    void Set(void * ptr, const D data) const
    { (reinterpret_cast<T *>(ptr)->*MDPtr) = static_cast<const D>(data); }
private:
    R T::*MDPtr;
};

} // detail



////////////////////////////////////////////////////////////////////////////////
//  Programmable Accessor Factory  /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////





template <typename D >
class ProgrammableAccessor : public Named {
public:

    struct Wrapper {
        Wrapper(const ProgrammableAccessor<D> *ac, void *ob) :
            m_access(ac), m_object(ob)
        { assert(ob != NULL); }

        template <typename T>
        inline T Get() const { return m_access->Get<T>(m_object); }

        template <typename T>
        inline void Set(const T data) const { return m_access->Set<T>(m_object,data); }

        void *m_object;
        const ProgrammableAccessor<D> *m_access;
    };

    ProgrammableAccessor() : Named("no access defined") {}

    template < typename F >
    ProgrammableAccessor(F f) : Named(f)
    { SetAccessFunctions(f); }

    template < typename F1, typename F2 >
    ProgrammableAccessor(F1 f1, F2 f2) : Named(f1) // << FIX
    { SetAccessFunctions(f1,f2); }


    // ----- move to factory //
    template <typename R, typename T>
    inline void SetAccessFunctions(R(T::*_pg)()const, void(T::*_ps)(const R) = NULL)
    {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_mfptr_cc<D,R,T>(_pg,_ps));
        this->SetName(_pg); // << FIX
    }

    template <typename R, typename T>
    inline void SetAccessFunctions(R(T::*_pg)(), void(T::*_ps)(R) = NULL) {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_mfptr_vv<D,R,T>(_pg,_ps));
        this->SetName(_pg); // << FIX
    }

    template <typename R, typename T>
    inline void SetAccessFunctions(R&(T::*_pf)()) {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_ref<D,R,T>(_pf));
        this->SetName(_pf);
    }

    template <typename R, typename T>
    inline void SetAccessFunctions(R T::*_pf) {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_member<D,R,T>(_pf));
        this->SetName(_pf);
    }
    // ------ //

    const Wrapper operator() (void *ob) const { return Wrapper(this,ob); }

    inline D Get(void *ob) const { return m_base->Get(ob); }

    inline void Set(void *ob, const D data) const { m_base->Set(ob,data); }

    template <typename T>
    inline T Get(void *ob) const { return m_base->Get<T>(ob); }

    template <typename T>
    inline void Set(void *ob, const T data) const { return m_base->Set<T>(ob,data); }

private:
    SmartPointer< detail::ProgrammableAccessor_Base<D> > m_base;
};


typedef ProgrammableAccessor<detail::any_c> ProgrammableAccessorAny;


} // uLib



#endif // PROGRAMMABLEACCESSOR_H
