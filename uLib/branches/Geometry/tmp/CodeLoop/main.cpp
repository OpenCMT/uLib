#include <iostream>


#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkObjectFactory.h>
#include <vtkRenderer.h>

#include <eigen3/Eigen/Dense>

#include "src/ManageFilename.h"
#include "src/Test.h"

int main()
{

    Eigen::Vector2f v2(0,2);

    vtkRenderWindow *window = vtkRenderWindow::New();
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    vtkRenderer *renderer = vtkRenderer::New();


    window->AddRenderer(renderer);
    iren->SetRenderWindow(window);

    std::string filname = "test.vtk";

    //    std::cout << ManageFilename::GetFileName(filname) << "\n";
    TestFilename test("test.vtk");
    test.PrintName();
    test.PrintExtension();

    //iren->Start();
    renderer->Delete();
    window->Delete();
    iren->Delete();
    return 0;
}
