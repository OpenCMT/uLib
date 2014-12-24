#ifndef U_CORE_PROGRAMMABLEACCESSOR_H
#define U_CORE_PROGRAMMABLEACCESSOR_H

#include <boost/type_traits.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include <Core/Macros.h>
#include <Core/Types.h>
#include <Core/SmartPointer.h>
#include <Core/Named.h>

#include <Core/Function.h>

#include <boost/any.hpp>

namespace uLib {



namespace detail {


template <typename T>
struct is_iterator {
    template <typename U>
    static char test(typename U::iterator_category* x);

    template <typename U>
    static long test(U* x);

    static const bool value = sizeof(test<T>(nullptr)) == 1;

};


template <typename D>
class ProgrammableAccessor_Base {
public:
    virtual D Get(void *) const = 0;
    virtual void Set(void *,const D) const = 0;
    virtual ~ProgrammableAccessor_Base() {}
};


template<typename D, typename R, class T1>
class functor_by_static_acc : public ProgrammableAccessor_Base<D>
{
    typedef R(*GeT)(const T1 *);
    typedef void(*SeT)(T1 *,R);
public:
    explicit functor_by_static_acc(GeT _get, SeT _set  = NULL) :
        GetPtr(_get), SetPtr(_set) {}

    D Get(void * ptr) const
    { return static_cast<D>((*GetPtr)(reinterpret_cast<const T1 *>(ptr))); }

    void Set(void * ptr, const D data) const
    { if (SetPtr) (*SetPtr)(reinterpret_cast<T1 *>(ptr),static_cast<const R>(data)); }

private:
    GeT GetPtr;
    SeT SetPtr;
};

template<typename D, typename R, class T1>
class functor_by_static_acc_ref : public ProgrammableAccessor_Base<D>
{
    typedef R(*GeT)(const T1 &);
    typedef void(*SeT)(T1 &,R);
public:
    explicit functor_by_static_acc_ref(GeT _get, SeT _set  = NULL) :
        GetPtr(_get), SetPtr(_set) {}

    D Get(void * ptr) const
    { return static_cast<D>((*GetPtr)(reinterpret_cast<const T1 &>(ptr))); }

    void Set(void * ptr, const D data) const
    { if (SetPtr) (*SetPtr)(reinterpret_cast<T1 &>(ptr),static_cast<const R>(data)); }

private:
    GeT GetPtr;
    SeT SetPtr;
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
    typedef R(T::*GeT)() const;
    typedef void(T::*SeT)(const R);
public:
    explicit functor_by_mfptr_cc( GeT _get, SeT _set ) :
        GetPtr(_get), SetPtr(_set)  {}

    D Get(void * ptr) const
    { return static_cast<D>((reinterpret_cast<T *>(ptr)->*GetPtr)()); }

    void Set(void * ptr, const D data) const
    { if (SetPtr) (reinterpret_cast<T *>(ptr)->*SetPtr)(static_cast<const R>(data)); }

private:
    GeT GetPtr;
    SeT SetPtr;
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
    template < R T::*_pf >
    class StaticWrapper {
        static D Get(void *ptr) { return static_cast<D>(reinterpret_cast<T *>(ptr)->*_pf); }
        static void Set(void *ptr, const D data) { (reinterpret_cast<T *>(ptr)->*_pf) = static_cast<const D>(data); }
    };
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


    ProgrammableAccessor() : Named("") {}

    ProgrammableAccessor(const char *name) : Named(name) {}

    template < typename F >
    ProgrammableAccessor(const char *name, F f) : Named(name)
    { SetAccessFunctions(f); }

    template < typename F1, typename F2 >
    ProgrammableAccessor(const char *name, F1 f1, F2 f2) : Named(name)
    { SetAccessFunctions(f1,f2); }

    template < typename F >
    ProgrammableAccessor(F f) : Named(f)
    { SetAccessFunctions(f); }

    template < typename F1, typename F2 >
    ProgrammableAccessor(F1 f1, F2 f2) : Named(f1) // << FIX
    { SetAccessFunctions(f1,f2); }


    // ----- factory functions //
    template <typename R, typename T1>
    inline void SetAccessFunctions(R(*_pg)(const T1 *), void(*_ps)(T1*,R) = NULL) {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_static_acc<D,R,T1>(_pg,_ps));
    }

    template <typename R, typename T1>
    inline void SetAccessFunctions(R(*_pg)(const T1&), void(*_ps)(T1&,R) = NULL) {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_static_acc_ref<D,R,T1>(_pg,_ps));
    }

    template <typename R, typename T>
    inline void SetAccessFunctions(R(T::*_pg)()const, void(T::*_ps)(const R) = NULL)
    {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_mfptr_cc<D,R,T>(_pg,_ps));
    }

    template <typename R, typename T>
    inline void SetAccessFunctions(R(T::*_pg)(), void(T::*_ps)(R) = NULL) {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_mfptr_vv<D,R,T>(_pg,_ps));
    }

    template <typename R, typename T>
    inline void SetAccessFunctions(R&(T::*_pf)()) {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_ref<D,R,T>(_pf));
    }

    template <typename R, typename T>
    inline void SetAccessFunctions(R T::*_pf) {
        m_base = SmartPointer< detail::ProgrammableAccessor_Base<D> >(new detail::functor_by_member<D,R,T>(_pf));
    }
    // ------ //

/*
    //    struct Wrapper {
    //        Wrapper(const ProgrammableAccessor<D> *ac, void *ob) :
    //            m_access(ac), m_object(ob)
    //        { assert(ob != NULL); }

    //        template <typename T>
    //        inline T Get() const { return static_cast<T>(m_access->Get(m_object)); }

    //        template <typename T>
    //        inline void Set(const T data) const { return m_access->Set(m_object,static_cast<T>(data)); }

    //        void *m_object;
    //        const ProgrammableAccessor<D> *m_access;
    //    };
    //    const Wrapper operator() (void *ob) const { return Wrapper(this,ob); }
*/

    inline D Get(void *ob) const { return m_base->Get(ob); }

    inline void Set(void *ob, const D data) const { m_base->Set(ob,data); }

    template <typename T>
    inline T Get(void *ob) const
    { return static_cast<T>(m_base->Get(ob)); }

    template <typename T>
    inline void Set(void *ob, const T data) const
    { return m_base->Set(ob,static_cast<T>(data)); }

    template <typename T>
    inline D Get(const T &ob,
                 typename boost::disable_if< detail::is_iterator<T> >::type *d1 = 0,
                 typename boost::disable_if< boost::is_pointer<T> >::type *d2 = 0 ) const
    { return m_base->Get((void*)(&ob)); } // FIX << add "void * const" to Getters

    template <typename T>
    inline void Set(T &ob, const D data,
                    typename boost::disable_if< detail::is_iterator<T> >::type *d1 = 0,
                    typename boost::disable_if< boost::is_pointer<T> >::type *d2 = 0) const
    { return m_base->Set(&ob,data); }

    template <typename It>
    inline D Get(const It &it,
                 typename boost::enable_if< detail::is_iterator<It> >::type *d1 = 0,
                 typename boost::disable_if< boost::is_pointer<It> >::type *d2 = 0) const
    { return m_base->Get(it.base()); }

    template <typename It>
    inline void Set(const It &it, const D data,
                    typename boost::enable_if< detail::is_iterator<It> >::type *d1 = 0,
                    typename boost::disable_if< boost::is_pointer<It> >::type *d2 = 0) const
    { return m_base->Set(it.base(),data); }


private:
    SmartPointer< detail::ProgrammableAccessor_Base<D> > m_base;
};



} // uLib



#endif // PROGRAMMABLEACCESSOR_H
