#=======================================================================
# Copyright   : Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
# Name        : Makefile
# Author      : Rubens Gomes
# Description : C++ GNU Makefile to build reactor
#=======================================================================
.PHONY: all clean default

.SUFFIXES:
.SUFFIXES: .cpp .o

CXX = g++
MDIR = mkdir
MV = mv
RM = rm 
SHELL = /bin/sh

# unames to identify OS
uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')
uname_M := $(shell sh -c 'uname -m 2>/dev/null || echo not')
uname_O := $(shell sh -c 'uname -o 2>/dev/null || echo not')
uname_R := $(shell sh -c 'uname -r 2>/dev/null || echo not')
uname_P := $(shell sh -c 'uname -p 2>/dev/null || echo not')
uname_V := $(shell sh -c 'uname -v 2>/dev/null || echo not')

# boost must be installed in following path
BOOST_DIR = /usr/local/boost_1_60_0

# dependency settings
DEP_DIR = .depend
$(shell $(MDIR) -p $(DEP_DIR))
$(shell $(MDIR) -p $(DEP_DIR)/src)
$(shell $(MDIR) -p $(DEP_DIR)/test)
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
POSTCOMPILE = $(MV) -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d

# preprocessor macro definitions
# BOOST_ALL_DYN_LINK to dynamic link to the Boost libraries
DEFS = \
  -DBOOST_ALL_DYN_LINK 

ifeq ($(uname_O),Cygwin)
# cancel definitioin of following names to fix
# compiling issue in cygwin
  UNDEF_NAMES = \
    -U__STRICT_ANSI__
else
  UNDEF_NAMES = 
endif

UNDEFS = \
  $(UNDEF_NAMES)

# preprocessor header files search paths
INCLUDES = \
  -I$(CURDIR)/src \
  -I$(CURDIR)/test \
  -I$(BOOST_DIR)

# compiling flags
# -Wextra -pedantic 
CXX_FLAGS = \
  -c -g -Wall -std=c++11 \
  $(DEFS) $(UNDEFS) $(INCLUDES) 

# linking flags
LD_FLAGS = \

# linking libs search paths
LIB_DIRS = \
  -L$(BOOST_DIR)/stage/lib

# linking libs to search
LIBS = \
  -lboost_system \
  -lboost_thread \
  -lboost_log 

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
TARGET = reactortest

# linking pattern rule to create target
$(TARGET): $(OBJS)
	$(CXX) $(LD_FLAGS) $(LIB_DIRS) -o $(TARGET) $(OBJS) $(LIBS)

# compiling rule
%.o: %.cpp
	$(CXX) $(DEP_FLAGS) $(CXX_FLAGS) -o $@ $<  
	$(POSTCOMPILE)

# cleans build
clean:
	$(RM) -f $(OBJS) $(TARGET) $(TARGET).stackdump\
                 $(TARGET).exe.stackdump $(TARGET).core
	$(RM) -fr $(DEP_DIR)

$(DEP_DIR)/%.d: ;
.PRECIOUS: $(DEP_DIR)/%.d

-include $(patsubst %,$(DEP_DIR)/%.d,$(basename $(SRCS)))
