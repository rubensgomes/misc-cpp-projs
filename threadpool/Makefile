#=======================================================================
# Copyright   : Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
# Name        : Makefile
# Author      : Rubens Gomes
# Description : C++ GNU Makefile to build threadpool
#=======================================================================
.PHONY: all clean default

.SUFFIXES:
.SUFFIXES: .cpp .o

CXX = g++
MDIR = mkdir
MV = mv
RM = rm 
SHELL = /bin/sh

# boost must be installed in following path
BOOST_DIR = /usr/local/boost_1_60_0

# dependency settings
DEP_DIR = .depend
$(shell $(MDIR) -p $(DEP_DIR) >/dev/null)
$(shell $(MDIR) -p $(DEP_DIR)/src >/dev/null)
$(shell $(MDIR) -p $(DEP_DIR)/test >/dev/null)
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
POSTCOMPILE = $(MV) -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d

# preprocessor macro definitions
DEFS = \
  -DBOOST_THREAD_POSIX \
  -DBOOST_THREAD_USE_LIB

# cygwin flags to fix compiling issues
CYGWIN_FLAGS = -U__STRICT_ANSI__

# preprocessor header files search paths
INCLUDES = \
  -I$(CURDIR)/src \
  -I$(BOOST_DIR)

# compiling flags
CXX_FLAGS = -c -g -Wall -Wextra -pedantic -std=c++11  \
  $(DEFS) $(INCLUDES) $(CYGWIN_FLAGS)

# linking flags
LD_FLAGS = -static

# linking libs search paths
LIB_DIRS = \
  -L$(BOOST_DIR)/stage/lib

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

# linking pattern rule to create target
$(TARGET): $(OBJS)
	$(CXX) $(LD_FLAGS) $(LIB_DIRS) -o $(TARGET) $(OBJS) $(LIBS)

# delete this rule, and use the following instead
%.o: %.cpp
	$(CXX) $(DEP_FLAGS) $(CXX_FLAGS) -o $@ $<  
	$(POSTCOMPILE)

# cleans build
clean:
	$(RM) -f $(OBJS) $(TARGET)
	$(RM) -fr $(DEP_DIR)

$(DEP_DIR)/%.d: ;
.PRECIOUS: $(DEP_DIR)/%.d

-include $(patsubst %,$(DEP_DIR)/%.d,$(basename $(SRCS)))
