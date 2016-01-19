#=======================================================================
# Name        : Makefile
# Author      : Rubens Gomes
# Copyright   : Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
# Description : GNU Makefile to build threadpool
#=======================================================================
.PHONY: default dir all depend clean clobber 

.SUFFIXES:
.SUFFIXES: .cpp .o

.DEFAULT_GOAL = default

CXX = g++
RM = rm 
SHELL = /bin/sh

CXXFLAGS = -static -std=c++11 -g -Wall -Wextra  -pedantic \
  $(INCLUDES) $(LDIR)

# boost must be installed in following path
BOOSTDIR = /usr/local/boost_1_60_0
BUILDDIR = build
LDIR = \
  -L/usr/local/boost_1_60_0/stage/lib
SRCDIR = src
TESTDIR = test

INCLUDES = \
  -I. \
  -I$(SRCDIR) \
  -I$(BOOSTDIR)

LIBS = \
  -lboost_thread \
  -lboost_system 

MYSRCS = $(wildcard $(SRCDIR)/*.cpp) 
TESTSRCS = $(wildcard $(TESTDIR)/*.cpp) 

SRCS = $(MYSRCS) $(TESTSRCS)

OBJS = \
  $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS)) \
  $(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TESTSRCS))

TARGET = $(BUILDDIR)/test

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS) 

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all: dir $(TARGET)

default: dir $(TARGET) 

dir: $(BUILDDIR)/

$(BUILDDIR)/: 
	mkdir -p $@

clean:
	$(RM) -f $(OBJS) $(TARGET)

clobber: clean
	$(RM) -f *~ ./.depend
	$(RM) -fr $(BUILDDIR)

depend: .depend

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ >>./.depend;

include ./.depend
