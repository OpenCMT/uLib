# SUBDIRS = .

include $(top_srcdir)/Common.am

DISTSOURCES        = vtkviewport.cpp main.cpp
DISTHEADERS_MOC    =
DISTHEADERS_NO_MOC = 
FORMS              = vtkviewport.ui 

FORMHEADERS = $(FORMS:.ui=.h)
MOC_CC = $(FORMS:.ui=.moc.cpp) $(DISTHEADERS_MOC:.h=.moc.cpp)

bin_PROGRAMS    = QTVtkViewport

BUILT_SOURCES = $(FORMHEADERS) $(MOC_CC)
CLEANFILES    = $(BUILT_SOURCES)

EXTRA_DIST                   = $(FORMS)
QTVtkViewport_SOURCES        = $(DISTSOURCES) $(DISTHEADERS_MOC) $(DISTHEADERS_NO_MOC)
nodist_QTVtkViewport_SOURCES = $(MOC_CC)

QTVtkViewport_LDADD = $(top_srcdir)/libmutom.la


.ui.h: $(FORMS)
	$(UIC) -o ui_$@ $<

.ui.hpp: $(FORMS_HPP)
	$(UIC) -o $@ $<

.h.moc.cpp:
	$(MOC) -o $@ $<


SUFFIXES = .h .ui .moc.cpp
