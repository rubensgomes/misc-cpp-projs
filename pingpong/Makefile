#=======================================================================
# Name        : Makefile
# Author      : Rubens Gomes
# Copyright   : Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
# Description : GNU Makefile to build the application
#=======================================================================
.PHONY: default all depend clean clobber install

.SUFFIXES:
.SUFFIXES: .cpp .o

CXX = g++
RM = rm -f
SHELL = /bin/sh

CXXFLAGS = -std=c++11 -g -Wall -Wextra  -pedantic $(INCLUDES)

# ensure following paths are found in the environment
INCLUDES = \
  -I. \
  -I/usr/local/boost_1_60_0
LIBS =
SRCDIR = src

SRCS = \
  $(SRCDIR)/match.cpp \
  $(SRCDIR)/game.cpp \
  $(SRCDIR)/pingpong.cpp \
  $(SRCDIR)/player.cpp

OBJS = $(subst .cpp,.o,$(SRCS))

TARGET = pingpong

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

all: $(TARGET)

clean:
	$(RM) $(OBJS) $(TARGET)

distclean: clean
	$(RM) *~ ./.depend

depend: .depend

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ >>./.depend;

include ./.depend
