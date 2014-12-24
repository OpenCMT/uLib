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

#ifndef U_MATH_DATASET_H
#define U_MATH_DATASET_H

#include <Core/Macros.h>
#include <Core/Vector.h>

#include <Core/Function.h>

#include "Math/Dense.h"
#include "Math/StructuredData.h"

#include <Core/ClassCompound.h>
#include <Core/ProgrammableAccessor.h>

#include <vtkInformation.h>


namespace uLib {




class AbstractArray {
public:
    //    virtual const void * GetDataPointer(Id_t id) const = 0;
    virtual       void * GetDataPointer(Id_t id) = 0;
    virtual ~AbstractArray() {}
};



template < typename T >
class DataAttributes {
public:
    DataAttributes() : m_Active(NULL) {}

    template < typename F >
    void AddAttribute(const char *name, F f) {
        ProgrammableAccessor<T> pa(name);
        pa.SetAccessFunctions(f);
        m_Accessors.push_back(pa);
        m_Active = &m_Accessors.back();
    }

    template < typename F1, typename F2 >
    void AddAttribute(const char *name, F1 f1, F2 f2) {
        ProgrammableAccessor<T> pa(name);
        pa.SetAccessFunctions(f1,f2);
        m_Accessors.push_back(pa);
        m_Active = &m_Accessors.back();
    }

    ProgrammableAccessor<T> * GetAttribute(const char *name) /*const*/ {
        foreach (ProgrammableAccessor<T> &el, m_Accessors) {
            if(el.GetName() == name)
                return &el;
        }
        return NULL;
    }

    void SetActive(const char *name) {
        m_Active = this->GetAttribute(name);
    }
    uLibGetMacro(Active,ProgrammableAccessor<T> *)
    uLibRefMacro(Accessors, Vector< ProgrammableAccessor<T> >);
private:
    Vector< ProgrammableAccessor<T> > m_Accessors;
    ProgrammableAccessor<T>   *m_Active;
};



class DataSet : public AbstractArray {
public:
    DataSet() {}
    virtual ~DataSet() {}

    template < typename F >
    inline void AddScalarAccess(const char *name, F f) { Scalars().AddAttribute(name,f); }

    template < typename F1, typename F2 >
    inline void AddScalarAccess(const char *name, F1 f1, F2 f2) { Scalars().AddAttribute(name,f1,f2); }

    double GetScalar(int id) {
        ProgrammableAccessor<double> *acc = Scalars().GetActive();
        if (acc) return acc->Get(this->GetDataPointer(id));
    }

    double GetScalar(const char *name, int id) {
        ProgrammableAccessor<double> *acc = Scalars().GetAttribute(name);
        if (acc) return acc->Get(this->GetDataPointer(id));
    }

    void SetScalar(int id, double val) {
        ProgrammableAccessor<double> *acc = Scalars().GetActive();
        if (acc) acc->Set(this->GetDataPointer(id),val);
    }

    void SetScalar(const char *name, int id, double val) {
        ProgrammableAccessor<double> *acc = Scalars().GetAttribute(name);
        if (acc) acc->Set(this->GetDataPointer(id),val);
    }

    inline void SetActiveScalars(const char *name) { Scalars().SetActive(name); }
    inline ProgrammableAccessor<double> * GetActiveScalars() { return Scalars().GetActive(); }


    uLibRefMacro(Scalars,DataAttributes< double   >);
    uLibRefMacro(Vectors,DataAttributes< Vector3d >);
private:
    DataAttributes< double   > m_Scalars;
    DataAttributes< Vector3d > m_Vectors; // da finire ... //
};




// TO BE MOVED OR REMOVED ...
template <
        typename T,
        class ScalarAccess
        >
class DataVectorCompound :
        public DataSet,
        public ClassCompound< ScalarAccess >
{
    typedef DataVectorCompound<T,ScalarAccess> ThisClass;
    typedef ClassCompound< ScalarAccess > Compound;
    typedef T DataType;

public:
    DataVectorCompound() {}

    template < class Other >
    DataVectorCompound(const Other &cp) :
        Compound(cp),
        m_Data(cp.Data())
    {}

    const void * GetDataPointer(Id_t id) const { return (const void *)&m_Data.at(id); }
    void * GetDataPointer(Id_t id) { return (void *)&m_Data.at(id); }

    inline DataType & operator [] (Id_t id) { return m_Data.operator [](id); }
    inline const DataType & operator [] (Id_t id) const { return m_Data.operator [](id); }

    inline void SetSize(const size_t size) { m_Data.resize(size); }
    inline const size_t GetSize() const { return m_Data.size(); }

    uLibRefMacro(Data,Vector<DataType>)
    uLibConstRefMacro(Data,Vector<T>)
private:
    Vector<DataType> m_Data;
};





} // uLib



#endif // DATASET_H
