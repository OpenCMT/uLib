
include $(top_srcdir)/Common.am

#AM_DEFAULT_SOURCE_EXT = .cpp



TESTS = LtkDebugTest \
	LtkFunctionToStringTest

LDADD = ../../../libmutom-0.1.la
check_PROGRAMS = $(TESTS)


####################################################
# Hybrid c/c++ Ltk Specific tests                  #
####################################################

check_PROGRAMS += Vector-test
Vector_test_SOURCES = Vector.c
TESTS += Vector-test

check_PROGRAMS += Vector-test-cc
Vector_test_cc_SOURCES = Vector-cc.cpp
TESTS += Vector-test-cc

check_PROGRAMS += Object-test
Object_test_SOURCES = Object.c
TESTS += Object-test

check_PROGRAMS += Object-test-cc
Object_test_cc_SOURCES = Object-cc.cpp
TESTS += Object-test-cc

####################################################

AM_COLOR_TESTS = always
