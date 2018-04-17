SUBDIRS = .

include $(top_srcdir)/Common.am
include Vtk.am


library_includedir = $(includedir)/libmutom-${PACKAGE_VERSION}/Vtk
library_include_HEADERS = uLibVtkInterface.h \
                          uLibVtkViewer.h \
                          vtkContainerBox.h \
                          vtkMuonScatter.h \
                          vtkStructuredGrid.h \
                          vtkVoxRaytracerRepresentation.h \
                          vtkVoxImage.h
#                          vtkHLineRepresentation.h \
#			  vtkTriangleMesh.h


_VTK_SOURCES =  uLibVtkInterface.cxx \
                uLibVtkViewer.cpp \
                vtkContainerBox.cpp \
                vtkMuonScatter.cxx \
                vtkStructuredGrid.cpp \
                vtkVoxRaytracerRepresentation.cpp \
                vtkVoxImage.cpp
#vtkTriangleMesh.cpp



noinst_LTLIBRARIES = libconvtk.la
libconvtk_la_SOURCES = ${_VTK_SOURCES}
libconvtk_la_LIBADD = $(AM_LIBS_ALL)


