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



#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <vtkSmartPointer.h>

#include <vtkPolyDataReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkOBJReader.h>
#include <vtkSTLReader.h>

#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

#include "Vtk/vtkTriangleMesh.h"


namespace uLib {


class vtkTriangleMeshPimpl {
public:
    vtkTriangleMeshPimpl(vtkTriangleMesh::Content &content) :
        m_content(content),
        m_Poly(vtkPolyData::New()),
        m_Actor(vtkActor::New())
    {
        vtkSmartPointer<vtkPolyDataMapper> mapper =
                vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(m_Poly->GetProducerPort());
        m_Actor->SetMapper(mapper);
    }

    ~vtkTriangleMeshPimpl() {
        m_Poly->Delete();
        m_Actor->Delete();
    }


    void vtk2uLib_update();
    void uLib2vtk_update();

    // members //
    TriangleMesh &m_content;
    vtkPolyData  *m_Poly;
    vtkActor     *m_Actor;
};


void vtkTriangleMeshPimpl::vtk2uLib_update()
{
    // Assumes that Polys are Triangles !!! //
    vtkIdType number_of_points = m_Poly->GetNumberOfPoints();
    vtkIdType number_of_triangles = m_Poly->GetNumberOfPolys();

    std::cout << "//////\n" <<
                 "number of points = " << number_of_points << "\n" <<
                 "muiber of polys  = " << number_of_triangles << "\n" <<
                 "//////\n";





    m_content.Points().resize(number_of_points);    
    for (int i=0; i<number_of_points; ++i)
    {
        double *point = m_Poly->GetPoint(i);
        m_content.Points()[i](0) = point[0];
        m_content.Points()[i](1) = point[1];
        m_content.Points()[i](2) = point[2];
//        std::cout << "pt" << i << " = " << m_content.Points()[i].transpose() << "\n";
    }

    m_content.Triangles().resize(number_of_triangles);
    m_Poly->GetPolys()->InitTraversal();
    vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
    for (int i=0; i<number_of_triangles; ++i)
    {
        m_Poly->GetPolys()->GetNextCell(idList);
        m_content.Triangles()[i](0) = idList->GetId(0);
        m_content.Triangles()[i](1) = idList->GetId(1);
        m_content.Triangles()[i](2) = idList->GetId(2);
    }
    m_Poly->Update();
    m_Actor->GetMapper()->Update();
}

void vtkTriangleMeshPimpl::uLib2vtk_update()
{
    vtkIdType number_of_points = m_content.Points().size();
    vtkIdType number_of_triangles = m_content.Triangles().size();

    vtkSmartPointer<vtkPoints> points
      = vtkSmartPointer<vtkPoints>::New();
    points->SetNumberOfPoints(number_of_points);
    for (vtkIdType i = 0; i < number_of_points; i++)
      {
      double x, y, z;
      x = m_content.Points().at(i)(0);
      y = m_content.Points().at(i)(1);
      z = m_content.Points().at(i)(2);
      points->SetPoint(i, x, y, z);
      }

    vtkSmartPointer<vtkCellArray> polys
      = vtkSmartPointer<vtkCellArray>::New();
    for (vtkIdType i = 0; i < number_of_triangles; i++)
      {
      vtkIdType a, b, c;
      a = m_content.Triangles().at(i)(0);
      b = m_content.Triangles().at(i)(1);
      c = m_content.Triangles().at(i)(2);
      polys->InsertNextCell(3);
      polys->InsertCellPoint(a);
      polys->InsertCellPoint(b);
      polys->InsertCellPoint(c);
      }

    m_Poly->SetPoints(points);
    m_Poly->SetPolys(polys);
    m_Poly->Update();
    m_Actor->GetMapper()->Update();
}


// -------------------------------------------------------------------------- //





vtkTriangleMesh::vtkTriangleMesh(vtkTriangleMesh::Content &content) :
    d(new vtkTriangleMeshPimpl(content))
{}

vtkTriangleMesh::~vtkTriangleMesh()
{
    delete d;
}

void vtkTriangleMesh::ReadFromFile(const char *filename)
{
    vtkSmartPointer<vtkPolyDataReader> reader =
            vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(filename);
    reader->Update();
    d->m_Poly->DeepCopy(reader->GetOutput());
    d->vtk2uLib_update();
}

void vtkTriangleMesh::ReadFromXMLFile(const char *filename)
{
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
            vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(filename);
    reader->Update();
    d->m_Poly->DeepCopy(reader->GetOutput());
    d->vtk2uLib_update();
}

void vtkTriangleMesh::ReadFromObjFile(const char *filename)
{
    vtkSmartPointer<vtkOBJReader> reader =
            vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(filename);
    reader->Update();
    d->m_Poly->DeepCopy(reader->GetOutput());
    d->vtk2uLib_update();
}

void vtkTriangleMesh::ReadFromStlFile(const char *filename)
{
    vtkSmartPointer<vtkSTLReader> reader =
            vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(filename);
    reader->Update();
    d->m_Poly->DeepCopy(reader->GetOutput());
    d->vtk2uLib_update();
}

vtkProp *vtkTriangleMesh::GetProp()
{
    return d->m_Actor;
}

vtkPolyData *vtkTriangleMesh::GetPolyData() const
{
    return d->m_Poly;
}

void vtkTriangleMesh::Update()
{
    d->uLib2vtk_update();
}

}
