include $(top_srcdir)/Common.am

library_includedir = $(includedir)/libmutom-${PACKAGE_VERSION}/Detectors
library_include_HEADERS = 	DetectorChamber.h 	\
				ExperimentFitEvent.h 	\
				GeantEvent.h  		\
				HitMC.h 		\
				MuonScatter.h 		\
				MuonEvent.h             \
   				MuonError.h		\
				ChamberHitEvent.h 	\
				Hit.h 			\
				LinearFit.h		\
				Solid.h			\
				Matter.h		\
				Scene.h	

_DETECTORS_SOURCES = \
                Solid.cpp \
                Scene.cpp

noinst_LTLIBRARIES = libmutomdetectors.la
libmutomdetectors_la_SOURCES = ${_DETECTORS_SOURCES}


