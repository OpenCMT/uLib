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



#ifndef U_VTKVOXIMAGE_H
#define U_VTKVOXIMAGE_H

#include <Core/Object.h>
#include <Math/VoxImage.h>

#include "uLibVtkInterface.h"


class vtkImageData;

namespace uLib {
namespace Vtk {

class vtkVoxImage : public Puppet {
    uLibTypeMacro(vtkVoxImage,Puppet)
public:    
    properties()
    {
        float writer_factor;
    };

public:
    typedef Abstract::VoxImage Content;

    vtkVoxImage(Content &content);

    ~vtkVoxImage();

    vtkImageData * GetImageData();

    void SaveToXMLFile(const char *fname);

    void ReadFromVKTFile(const char *fname);

    void ReadFromXMLFile(const char *fname);

    void setShadingPreset(int blendType = 2);

    void Update();

protected:
    void InstallPipe();

private:
    class vtkVoxImagePimpl *d;
};


inline void vtkVoxImage::init_properties()
{
    $_init();
    $$.writer_factor = 1.E6;
}


} // vtk
} // uLib


#endif // VTKVOXIMAGE_H
