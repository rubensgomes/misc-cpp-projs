#=======================================================================
# Copyright   : Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
# Name        : Makefile
# Author      : Rubens Gomes
# Description : GNU Makefile to build threadpool
#=======================================================================
.PHONY: all clean default depend 

.SUFFIXES:
.SUFFIXES: .cpp .o

.DEFAULT_GOAL = default

CXX = g++
RM = rm 
SHELL = /bin/sh

# boost must be installed in following path
BOOST_DIR = /usr/local/boost_1_60_0

# file to place all the makedepend depencies
MAKEDEP_FILE = Make.dep

# preprocessor macro definitions
DEFS = \
  -DBOOST_THREAD_POSIX \
  -DBOOST_THREAD_USE_LIB

# cygwin flags to fix compiling issues
CYGWIN_FLAGS = -U__STRICT_ANSI__

# C header files search path
C_INCLUDES = \
  -I/usr/lib/gcc/i686-pc-cygwin/4.9.3/include

# C++ header files search path
CXX_INCLUDES = \
  -I/usr/lib/gcc/i686-pc-cygwin/4.9.3/include/c++ \
  -I/lib/gcc/i686-pc-cygwin/4.9.3/include/c++/i686-pc-cygwin

# preprocessor header files search paths
INCLUDES = \
  -I. \
  -I$(CXX_SRCDIR) \
  -I$(BOOST_DIR) \
  $(C_INCLUDES) \
  $(CXX_INCLUDES)

# compiling flags
CXX_FLAGS = -g -c -Wall -Wextra -pedantic -std=c++11  \
  $(DEFS) $(INCLUDES) $(CYGWIN_FLAGS)

# linking flags
LD_FLAGS = -static

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
CXX_SRCDIR = src
CXX_SRCS = $(wildcard $(CXX_SRCDIR)/*.cpp) 

# project test source code folder
TEST_DIR = test
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp) 

# all the sources
SRCS = $(CXX_SRCS) $(TEST_SRCS)

# all the .o object files
OBJS = $(SRCS:.cpp=.o)

# the target main application
TARGET = pooltest

# compiling pattern rule
%.o : %.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@ 

# linking to create target
$(TARGET): $(OBJS)
	$(CXX) $(LD_FLAGS) $(LIB_DIRS) -o $(TARGET) $(OBJS) $(LIBS)

# makes minimum necessary
default: $(TARGET) 

# cleans build
clean:
	$(RM) -f $(OBJS) $(TARGET)

# the makedepend target
depend: 
	makedepend -f$(MAKEDEP_FILE) -- $(CXX_FLAGS) -- $(SRCS)

# makes everything
#all: clean depend default
# for simplicity make default for now.
all: default

include ./$(MAKEDEP_FILE)
# DO NOT DELETE
