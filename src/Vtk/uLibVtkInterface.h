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



#ifndef ULIBVTKINTERFACE_H
#define ULIBVTKINTERFACE_H



#include <ostream>
#include <iomanip>

#include <Core/Object.h>



// vtk classes forward declaration //
class vtkProp;
class vtkPolyData;
class vtkPropCollection;
class vtkRenderer;
class vtkRendererCollection;


namespace uLib {
namespace Vtk {



//template <class T>
//class Tie {

//public:
//    typedef T Content;


//};



class Puppet : public Object
{
    uLibTypeMacro(Puppet, Object)
public:
    Puppet();
    ~Puppet();

    virtual vtkProp * GetProp();

    virtual vtkPropCollection * GetProps();

    void ConnectRenderer(vtkRenderer *renderer);

    void DisconnectRenderer(vtkRenderer *renderer);

    void ConnectViewer(class Viewer *viewer);

    void DisonnectViewer(class Viewer *viewer);

    vtkRendererCollection * GetRenderers() const;


    virtual void PrintSelf(std::ostream &o) const;

    virtual void ConnectInteractor(class vtkRenderWindowInteractor *interactor) { (void)interactor; }

protected:

    void SetProp(vtkProp *prop);

    void RemoveProp(vtkProp *prop);

private:
    friend class PuppetData;
    class PuppetData *d;
};




class Polydata {
public:

    virtual vtkPolyData * GetPolyData() const { return NULL; }

    virtual void SaveToFile(const char *vtk_file);

    virtual void SaveToXMLFile(const char *vtp_file);

protected:
    virtual ~Polydata() {}
};


} // vtk
} // uLib



#endif // ULIBVTKINTERFACE_H
