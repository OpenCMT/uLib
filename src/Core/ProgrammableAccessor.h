#ifndef U_CORE_PROGRAMMABLEACCESSOR_H
#define U_CORE_PROGRAMMABLEACCESSOR_H

#include <Core/Macros.h>
#include <Core/Types.h>
#include <Core/SmartPointer.h>

namespace uLib {



namespace detail {

template <typename R>
class ProgrammableAccessor_Base {
public:
    virtual R Get(void *) const = 0;
    virtual void Set(void *,const R) const = 0;

    template <typename T>
    T Get(void *ob) const {
        return static_cast<T>(this->Get(ob));
    }

    template <typename T>
    void Set(void *ob, const T data) const {
        this->Set(ob,static_cast<R>(data));
    }

    virtual ~ProgrammableAccessor_Base() {}
};


template<typename R, typename T>
class functor_by_ref : public ProgrammableAccessor_Base<R>
{
public:
    explicit functor_by_ref(R&(T::*__pf)()) : MFRef(__pf) {}
    R Get(void * ptr) const
    { return static_cast<R>((reinterpret_cast<T *>(ptr)->*MFRef)()); }
    void Set(void * ptr, const R data) const
    { ((reinterpret_cast<T *>(ptr)->*MFRef)()) = data; }
private:
    R&(T::*MFRef)();
};

template<typename R, typename T>
class functor_by_mfptr_cc : public ProgrammableAccessor_Base<R>
{
    typedef R(T::*GetterType)() const;
    typedef void(T::*SetterType)(const R);
public:
    explicit functor_by_mfptr_cc( GetterType _get, SetterType _set ) :
        GetPtr(_get), SetPtr(_set)  {}
    R Get(void * ptr) const
    { return static_cast<R>((reinterpret_cast<T *>(ptr)->*GetPtr)()); }
    void Set(void * ptr, const R data) const
    { if (SetPtr) (reinterpret_cast<T *>(ptr)->*SetPtr)(data); }

private:
    GetterType GetPtr;
    SetterType SetPtr;
};

template<typename R, typename T>
class functor_by_mfptr_vv : public ProgrammableAccessor_Base<R>
{
    typedef R(T::*GetterType)();
    typedef void(T::*SetterType)(R);
public:
    explicit functor_by_mfptr_vv( GetterType _get, SetterType _set ) :
        GetPtr(_get), SetPtr(_set)  {}
    R Get(void * ptr) const
    { return static_cast<R>((reinterpret_cast<T *>(ptr)->*GetPtr)()); }
    void Set(void * ptr, const R data) const
    { if (SetPtr) (reinterpret_cast<T *>(ptr)->*SetPtr)(data); }

private:
    GetterType GetPtr;
    SetterType SetPtr;
};


template<typename R, typename T>
class functor_by_member : public ProgrammableAccessor_Base<R>
{
public:
    explicit functor_by_member(R T::*__pf) : MDPtr(__pf) {}
    R Get(void * ptr) const
    { return static_cast<R>(reinterpret_cast<T *>(ptr)->*MDPtr); }
    void Set(void * ptr, const R data) const
    { (reinterpret_cast<T *>(ptr)->*MDPtr) = data; }
private:
    R T::*MDPtr;
};

} // detail



////////////////////////////////////////////////////////////////////////////////
//  Programmable Accessor Factory  /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template <typename R>
class ProgrammableAccessor {
public:
    template <typename T>
    ProgrammableAccessor(R(T::*_pg)()const, void(T::*_ps)(const R) = NULL) :
        m_base(new detail::functor_by_mfptr_cc<R,T>(_pg,_ps)) {}

    template <typename T>
    ProgrammableAccessor(R(T::*_pg)(), void(T::*_ps)(R) = NULL) :
        m_base(new detail::functor_by_mfptr_vv<R,T>(_pg,_ps)) {}

    template <typename T>
    ProgrammableAccessor(R&(T::*_pf)()) :
        m_base(new detail::functor_by_ref<R,T>(_pf)) {}

    template <typename T>
    ProgrammableAccessor(R T::*_pf) :
        m_base(new detail::functor_by_member<R,T>(_pf)) {}

    template <typename OtherR>
    inline OtherR Get(void *ob) const { return m_base->Get<OtherR>(ob); }

    template <typename OtherR>
    inline void Set(void *ob, const OtherR data) const { return m_base->Set<OtherR>(ob,data); }

private:
    SmartPointer< detail::ProgrammableAccessor_Base<R> > m_base;
};


} // uLib



#endif // PROGRAMMABLEACCESSOR_H
