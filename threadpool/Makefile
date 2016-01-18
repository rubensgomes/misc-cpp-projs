#=======================================================================
# Name        : Makefile
# Author      : Rubens Gomes
# Copyright   : Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
# Description : GNU Makefile to build threadpool
#=======================================================================
.PHONY: default all depend clean clobber install test

.SUFFIXES:
.SUFFIXES: .cpp .o

CXX = g++
RM = rm -f
SHELL = /bin/sh

CXXFLAGS = -std=c++11 -g -Wall -Wextra  -pedantic $(INCLUDES)

# boost must be installed in following path
BOOSTDIR = /usr/local/boost_1_60_0

BUILDDIR = build
SRCDIR = src
TESTDIR = test

INCLUDES = \
  -I. \
  -I$(SRCDIR) \
  -I$(BOOSTDIR)

LIBS =

SRCS = \
  $(wildcard $(SRCDIR)/*.cpp) \
  $(wildcard $(TESTDIR)/*.cpp)

OBJS = \
  $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS)) \
  $(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TESTSRCS))

TARGET = $(BUILDDIR)/test

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS) 

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all: dir $(TARGET)

dir:
	mkdir -p $(BUILDDIR)

clean:
	$(RM) $(OBJS) $(TARGET)

distclean: clean
	$(RM) *~ ./.depend

depend: .depend

.depend: $(SRCS) $(TESTSRCS)
	$(CXX) $(CXXFLAGS) -MM $^ >>./.depend;

include ./.depend
