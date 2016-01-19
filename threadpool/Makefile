#=======================================================================
# Name        : Makefile
# Author      : Rubens Gomes
# Copyright   : Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
# Description : GNU Makefile to build threadpool
#=======================================================================
.PHONY: all clean clobber default depend dir 

.SUFFIXES:
.SUFFIXES: .cpp .o

.DEFAULT_GOAL = default

CXX = g++
RM = rm 
SHELL = /bin/sh

# boost must be installed in following path
BOOSTDIR = /usr/local/boost_1_60_0

# file to place all the makedepend depencies
MAKEDEPFILE = Make.dep

# folder to place all built files
BUILDDIR = build

# preprocessor macro definitions
DEFS = \
  -DBOOST_THREAD_POSIX \
  -DBOOST_THREAD_USE_LIB

# C header files search path
CINCLUDES = \
  -I/usr/lib/gcc/i686-pc-cygwin/4.9.3/include

# C++ header files search path
CXXINCLUDES = \
  -I/usr/lib/gcc/i686-pc-cygwin/4.9.3/include/c++ \
  -I/lib/gcc/i686-pc-cygwin/4.9.3/include/c++/i686-pc-cygwin

# preprocessor header files search paths
INCLUDES = \
  -I. \
  -I$(CXXSRCDIR) \
  -I$(BOOSTDIR) \
  $(CINCLUDES) \
  $(CXXINCLUDES)

# compiling flags
CXXFLAGS = -g -c -Wall -Wextra -pedantic -std=c++11  \
  $(DEFS) $(INCLUDES) 

# linking flags
LDFLAGS = -static

# linking libs search paths
LIB_DIRS = \
  -L/usr/local/boost_1_60_0/stage/lib

# linking libs to search
LIBS = \
  -lboost_thread \
  -lboost_system \
  -lboost_log \
  -lboost_log_setup \
  -lboost_date_time \
  -lboost_filesystem \
  -lrt

# C++ project source code folder
CXXSRCDIR = src
CXXSRCS = $(wildcard $(CXXSRCDIR)/*.cpp) 

# project test source code folder
TESTDIR = test
TESTSRCS = $(wildcard $(TESTDIR)/*.cpp) 

# all the sources
SRCS = $(CXXSRCS) $(TESTSRCS)

# all the .o object files
OBJS = \
  $(patsubst $(CXXSRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(CXXSRCS)) \
  $(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TESTSRCS))

# the target main application
TARGET = $(BUILDDIR)/test

# compiling objects .o files
$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) $< -o $@ 

# linking to create target
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(LIB_DIRS) -o $(TARGET) $(OBJS) $(LIBS)

# target to create the build folder
dir:
	mkdir -p $(BUILDDIR)

# makes minimum necessary
default: dir $(TARGET) 

# makes everything
all: clobber depend default

# cleans only the minimum
clean:
	$(RM) -f $(OBJS) $(TARGET)

# cleas all
clobber: clean
	$(RM) -fr $(BUILDDIR)

# the makedepend target
depend: 
	makedepend -f$(MAKEDEPFILE) -- $(CXXFLAGS) -- $(SRCS)

include ./$(MAKEDEPFILE)
# DO NOT DELETE
