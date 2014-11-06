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

#ifndef U_MATH_IMAGEDATA_H
#define U_MATH_IMAGEDATA_H


#include <Math/ImageSpace.h>
#include <Math/ImageMap.h>

#include <Math/DataSet.h>
#include <Math/StructuredData.h>

namespace uLib {

class ImageData : public ImageSpace, public ImageMap {

public:
    ImageData() : ImageMap(Vector3i::Zero()) {}
    ImageData(const Vector3i &size) : ImageMap(size) {}

    void SetSize(const Vector3f v);

    Vector3f GetSize() const;

    bool IsInsideBounds(const Vector4f pt) const;

    virtual void * GetDataPointer(const Id_t id) const = 0;

    virtual float GetValue(const Vector3i id) const = 0;
    virtual float GetValue(const int id) const = 0;
    virtual void SetValue(const Vector3i id, float value) = 0;
    virtual void SetValue(const int id, float value) = 0;

    virtual void SetDims(const Vector3i &size) = 0;

    void ExportToVtk(const char *file, bool density_type = 0);
    void ExportToVtkXml(const char *file, bool density_type = 0);
    int ImportFromVtk(const char *file);
};




class DataVectorImage : public ImageData {
public:

    inline void * GetDataPointer(const Id_t id) const {
        return m_Data->GetDataPointer(id);
    }

    float GetValue(const Vector3i id) const { return m_Scalars.Get<float>(GetDataPointer(Map(id))); }
    float GetValue(const int id) const { return m_Scalars.Get<float>(GetDataPointer(id)); }
    void SetValue(const Vector3i id, float value) { m_Scalars.Set<float>(GetDataPointer(Map(id)),value); }
    void SetValue(const int id, float value) { m_Scalars.Set<float>(GetDataPointer(id),value); }

    void SetDims(const Vector3i &size) {
        ImageMap::SetDims(size);
        m_Data->SetSize(size.prod());
    }

    uLibRefMacro(Data,SmartPointer<AbstractArray>)
    uLibRefMacro(Scalars,ProgrammableAccessor<double>)
private:
    SmartPointer<AbstractArray> m_Data;
    ProgrammableAccessor<double> m_Scalars;
};








} // uLib

#endif // IMAGEDATA_H
