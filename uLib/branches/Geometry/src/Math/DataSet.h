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
#include <Core/ProgrammableAccessor.h>

#include <vtkInformation.h>


namespace uLib {


class AbstractArray {
public:
    virtual void * GetDataPointer(Id_t id) const = 0;
    virtual void  SetSize(const size_t size) = 0;
    virtual const size_t GetSize() const = 0;
    virtual ~AbstractArray() {}
};


class DataSetAttributes {
public:

    template < typename GeT, typename SeT >
    inline void SetScalars(GeT get, SeT set) {
        m_Scalars.SetAccessFunctions(get,set);
    }

private:
    ProgrammableAccessor<double> m_Scalars;
};




template < typename T >
class DataVector : public AbstractArray {
public:
    void * GetDataPointer(Id_t id) const { return (void *)&m_Data.at(id); }

    inline void SetSize(const size_t size) { m_Data.resize(size); }
    inline const size_t GetSize() const { return m_Data.size(); }

    uLibRefMacro(Data,Vector<T>)
    uLibRefMacro(Attributes,DataSetAttributes)
private:
    DataSetAttributes m_Attributes;
    Vector<T> m_Data;
};





//class DataSet {
//public:

//    virtual Vector3d     GetPoint(const Id_t) const = 0;
//    virtual Vector<Id_t> GetCell(const Id_t)  const = 0;

//private:
//};




} // uLib



#endif // DATASET_H
