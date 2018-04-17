


#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include "Math/Dense.h"

#include "Math/ContainerBox.h"
#include "Detectors/MuonScatter.h"
#include "Vtk/vtkMuonScatter.h"
#include "Vtk/vtkContainerBox.h"

int main()
{

    uLib::MuonScatter event;
    event.LineIn().origin << 0,0,0,1;
    event.LineIn().direction << 1,1,1,0;
    event.LineOut().origin << 5,5,5,1;
    event.LineOut().direction << -1,-1,-1,0;

    uLib::Vtk::vtkMuonScatter ms(event);

    uLib::ContainerBox box;
    box.SetPosition(uLib::Vector3f(0,2,0));
    box.SetOrigin(uLib::Vector3f(-1,-0.5,-1));
    box.SetSize  (uLib::Vector3f(2,-1,2));



    uLib::Vtk::vtkContainerBox vtkbox(box);



    return 0;
}
