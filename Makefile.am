AUTOMAKE_OPTIONS = foreign

INCLUDES = \
	-I$(includedir) \
	-I$(OFFLINE_MAIN)/include \
	-I$(ROOTSYS)/include

lib_LTLIBRARIES = \
  libPrecisionTest.la

noinst_HEADERS = \
  PrecisionTest.h \
  LDComplex.h \
  PrecisionTestLinkDef.h

libPrecisionTest_la_SOURCES = \
  PrecisionTest.C \
  PrecisionTestFunctions.C \
  PrecisionTestOffsets.C \
  PrecisionTestOffsetsRBR.C \
  PrecisionTestSpecialEventCuts.C \
  LDComplex.cxx \
  PrecisionTest_Dict.C

libPrecisionTest_la_LIBADD = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib \
  -lSubsysReco \
  -lTOAD

# Rule for generating CINT dictionaries from class headers.
PrecisionTest_Dict.C: \
  PrecisionTest.h \
  PrecisionTestLinkDef.h
	rootcint -f $@ -c $(DEFAULT_INCLUDES) $(INCLUDES) $^

clean-local:
	rm -f *Dict*
