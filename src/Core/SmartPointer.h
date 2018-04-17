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



#ifndef U_CORE_SMARTPOINTER_H
#define U_CORE_SMARTPOINTER_H


namespace uLib {

template <typename T>
class SmartPointer {
    typedef T element_type;
public:

    explicit
    SmartPointer(T* ptr = NULL) : m_counter(0) {
        if(!ptr) ptr = new T;
        if (ptr) m_counter = new ReferenceCounter(ptr);
    }

    // TakeReference //
    SmartPointer(T &ref) : m_counter(new ReferenceCounter(&ref,0)) { }

    SmartPointer(const SmartPointer& copy) throw () {
        acquire(copy.m_counter);
    }

    SmartPointer(SmartPointer * copy) throw () {
        acquire(copy->m_counter);
    }

    virtual ~SmartPointer()  {  release();  }

    SmartPointer & operator=(const SmartPointer& copy) {
        if (this != &copy)
        {
            release();
            acquire(copy.m_counter);
        }
        return *this;
    }

    T & operator*() const throw () {  return *m_counter->ptr; }
    T * operator->() const throw () {  return m_counter->ptr; }

    T * get() const throw () {
        return m_counter ? m_counter->ptr : 0; }
    bool unique() const throw () {
        return (m_counter ? m_counter->count == 1 : true);  }


  private:

    struct ReferenceCounter
    {
      ReferenceCounter(T* ptr = 0, unsigned c = 1) : ptr(ptr), count(c) { }
      T*       ptr;
      unsigned count;
    } * m_counter;

    // increment the count
    void acquire(ReferenceCounter* c) throw ()
    {
        m_counter = c;
        if (c && c->count>0) ++c->count;
    }

    // decrement the count, delete if it is 0
    void release() {
        if (m_counter) {
            if (--m_counter->count == 0) {
                delete m_counter->ptr;
            }
            if (m_counter->count <= 0) {
                delete m_counter;
                m_counter = NULL;
            }
        }
    }

};



}

#endif // SMARTPOINTER_H
