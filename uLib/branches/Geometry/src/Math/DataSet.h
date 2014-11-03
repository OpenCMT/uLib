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

namespace uLib {

class DataSet_Base {
public:
    DataSet_Base() {}

    virtual ~DataSet_Base() {}
    virtual const void * GetPtr(Id_t id) const = 0;
    virtual       void * GetPtr(Id_t id)       = 0;
    virtual size_t Size() const = 0;

private:


};

template <typename T>
class VectorData : public DataSet_Base, public Vector<T> {
public:


protected:
    const void *GetPtr(Id_t id) const { return &this->at(id); }
    void *      GetPtr(Id_t id)       { return &this->at(id); }
};










} // uLib



#endif // DATASET_H
